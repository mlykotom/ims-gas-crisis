#include "cpu.h"

using namespace std;

vector<CpuProcess*> Cpu::process_table;

Cpu::Cpu(int cores, double cpu_freq, double ram_size, double ram_access_time, double hd_size, double hd_access_time, double r_speed, double w_speed) {
    cores_cnt_ = cores;
    clock_rate = cpu_freq;
    for (int i = 0; i < cores_cnt_; i++) {
        core_names_.push_back(string("core " + IntToStr(i)));
        fac_cores.push_back(new Facility(core_names_[i].c_str()));
        process_per_core_cnt_.push_back(0);
        noi_per_core_cnt_.push_back(0.0);
    }
    p_ram = new Ram(ram_size, ram_access_time, glob_sim_args->ram->data_rate);
    p_hd = new HardDisk(p_ram, hd_size, hd_access_time, r_speed, w_speed);
    db_server = new DbServer(p_ram, p_hd, 0.0, 1);
    web_server = NULL;
    process_in_system_cnt_ = 0;
    process_in_system_max_ = 0;
    process_waiting_cnt_ = 0;
}

Cpu::~Cpu() {
    for (int i = 0; i < cores_cnt_; i++) {
        delete fac_cores[i];
    }
    delete p_ram;
    delete p_hd;
    delete db_server;

    //  unsigned size = process_table.size();
    //  for(unsigned i=0; i < size; i++) {  
    //    cout << process_table[i]->pid << endl;
    //  }
}

void Cpu::Log() {
    for (int i = 0; i < cores_cnt_; i++) {
        fac_cores[i]->Output();
    }
    p_ram->Log();
    p_hd->Log();
    db_server->Log();
    if (web_server != NULL) {
        web_server->Log();
    }
}

/*
 * Zahaji zpracovani procesu na CPU
 * Zatim nepreemtivni
 */
int Cpu::Start(CpuProcess *proc) {
    do {
        // vyhleda jadro na kterem bude proces bezet
        SelectCore(proc);
        cout.width(10);
        cout << Time;
        cout.width(8);
        cout << " PID: ";
        cout.width(3);
        cout << proc->pid;
        cout.width(8);
        cout << proc->name << " = READY" << endl;
        process_in_system_cnt_++;
        if (process_in_system_max_ < process_in_system_cnt_) {
            process_in_system_max_ = process_in_system_cnt_;
        }
        process_per_core_cnt_[proc->core_no] += 1;
        // proces se spusti a nebo se zaradi do fronty pripravenych procesu
        fac_cores[proc->core_no]->Seize(proc);
        cout.width(10);
        cout << Time;
        cout.width(8);
        cout << " PID: ";
        cout.width(3);
        cout << proc->pid << " = RUNNING" << endl;
        // simulace behu procesu
        proc->status = RUNNING;

        double tmp_data = 0.0;
        int actual_op = -1;
        // smycka vykonavani operaci procesu
        while (proc->vec_op->size() > 0) {
            // zjisteni operace
            actual_op = proc->vec_op->front().op_code;

            if (proc->unfinish_op_flag == false) { // DEBUG vypisuj pouze na zacatku kazde operace, mimo jeji preruseni
                proc->Debug(); // DEBUG
            }

            tmp_data = proc->vec_op->front().data;
            switch (actual_op) {
                case RAM:
                case CACHE:
                    // pristup do RAM ci CACHE

                    p_ram->MemoryAccess(proc, proc->vec_op->front().data);
                    CheckForWebServerProcess(proc, actual_op, tmp_data);
                    break;
                case READ:
                case WRITE:
                    // pristup na HD
                    p_hd->DiskAccess(proc, proc->vec_op->front().data, actual_op);
                    CheckForWebServerProcess(proc, actual_op, tmp_data);
                    break;
                case CPU:
                    // simulace vypoctu na CPU
                    CpuOperate(proc, proc->vec_op->front().data);
                    CheckForWebServerProcess(proc, actual_op, tmp_data);
                    break;
                case DB_INIT:
                    db_server->Init(proc, proc->vec_op->front().data);
                    CheckForWebServerProcess(proc, actual_op, tmp_data);
                    break;
                case DB_QUERY:
                    db_server->Query(proc, proc->vec_op->front().locality, proc->vec_op->front().data);
                    CheckForWebServerProcess(proc, actual_op, tmp_data);
                    break;
                case DB_QUERY_DONE:
                    proc->db_request_delay = Time - proc->db_request_delay; // vypocti delku obsluhy db pozadavku            
                    if (glob_logger->max_db_request_delay < proc->db_request_delay) {
                      glob_logger->max_db_request_delay = proc->db_request_delay;
                    }
                    glob_logger->WriteDbRequest(proc->db_request_delay); // vypis do datoveho souboru delku obsluhy db pozadavku
                    cout << "===== db_request_delay:" << proc->db_request_delay << endl;  
                    // smazani operace
                    proc->vec_op->erase(proc->vec_op->begin());
                    CheckForWebServerProcess(proc, actual_op, tmp_data);
                    break;
                case ALLOC:
                    // (pri)alokace pameti
                    p_ram->RamAlloc(proc->vec_op->front().data, proc);
                    CheckForWebServerProcess(proc, actual_op, tmp_data);
                    break;
                case FREE:
                    // uvolneni pameti
                    p_ram->RamFree(proc->vec_op->front().data, proc);
                    CheckForWebServerProcess(proc, actual_op, tmp_data);
                    break;
                case READ_FROM_DB:
                    cout << "READ_FROM_DB" << endl;
                    CheckForWebServerProcess(proc, actual_op, tmp_data);
                    break;
                default:
                    cerr << "ERROR: Cpu::Start(), switch => default" << endl;
                    exit(-1);
            }
            //obasluha podle toho, o jaky typ procesu se jedna
        }


        // ukonceni procesu
        fac_cores[proc->core_no]->Release(proc);
        process_per_core_cnt_[proc->core_no] -= 1;
        if (proc->processType == WEBSERVER_MASTER) {
            web_server->activate_master_process = true;
            proc->Passivate();
            //return 0;
        }
    }    while (proc->processType == WEBSERVER_MASTER);
    cout.width(10);
    cout << Time;
    cout.width(8);
    cout << " PID: ";
    cout.width(3);
    cout << proc->pid << " = TERMINATED" << endl;
    proc->status = TERMINATED;
    process_in_system_cnt_--;

    return 0;
}

void Cpu::CpuOperate(CpuProcess *proc, double noi) {
    if (proc->unfinish_op_flag == false) { // pokud je operace nerozpracovana, nastav cas jeji obsluhy
        // vzorec vypoctu obsluhy CPU
        proc->working_time = noi / clock_rate;
        cout.width(10);
        cout << Time;
        cout.width(8);
        cout << " PID: ";
        cout.width(3);
        cout << proc->pid << " $ CPU: \t" << proc->working_time << endl;
    }

    // cas kroku operace
    double wait_step = PreemptivStep(proc);
    // pocitadlo provedenych instrukci
    noi_per_core_cnt_[proc->core_no] += clock_rate * wait_step;
    // simulace vypoctu instrukci
    proc->Wait(wait_step);
    noi_per_core_cnt_[proc->core_no] -= clock_rate * wait_step;

    if (proc->unfinish_op_flag == false) { // pokud je operace nerozpracovana => tedy uz dokoncena
        // smazani prave dokoncene operace
        proc->vec_op->erase(proc->vec_op->begin());
    }
}

int Cpu::GetCoreCount() {
    return cores_cnt_;
}

int Cpu::GetProcessCount() {
    return process_in_system_cnt_;
}

void Cpu::SetWaitingProcessCount(int value) {
    process_waiting_cnt_ += value;
}

int Cpu::GetWaitingProcessCount() {
    return process_waiting_cnt_;
}

int Cpu::GetProcessMaxCount() {
    return process_in_system_max_;
}

void Cpu::SetProcessPerCoreCount(int core, int value) {
    process_per_core_cnt_[core] += value;
}

int Cpu::GetProcessPerCoreCount(int core) {
    return process_per_core_cnt_[core];
}

int Cpu::GetRunnablePerCoreCount(int core) {
    return fac_cores[core]->QueueLen();
}

double Cpu::GetNoiPerCore(int core) {
    return noi_per_core_cnt_[core];
}

void Cpu::SelectCore(CpuProcess *proc) {
    proc->core_no = 0;
    if (cores_cnt_ > 1) { // vice jadrovy procesor
        // najdi nejmene vytizene jadro
        unsigned min = fac_cores[0]->QueueLen();
        if (fac_cores[0]->Busy()) {
            min++;
        }
        for (int i = 1; i < cores_cnt_; i++) {
            unsigned next_core = fac_cores[i]->QueueLen();
            if (fac_cores[i]->Busy()) {
                next_core++;
            }
            if (next_core < min) {
                min = next_core;
                //        proc->core_no = i;
            }
        }
        // zapamatuj si vsechna minima
        vector<int> min_set;
        for (int i = 0; i < cores_cnt_; i++) {
            unsigned current_min = fac_cores[i]->QueueLen();
            if (fac_cores[i]->Busy()) {
                current_min++;
            }
            if (min == current_min) {
                min_set.push_back(i);
            }
        }
        // nahodny vyber z jader s nejmensi frontou
        random_shuffle(min_set.begin(), min_set.end());
        // prirad jadro k procesu
        proc->core_no = min_set.front();

    } else if (cores_cnt_ <= 0) { // chyba
        cerr << "CHYBA: Cpu::SelectCore() pocet jader musi byt aspon 1" << endl;
        exit(-1);
    }
}

/**
 * Pokud je proces svazany s WebServerem, tak jsem pro nej pridal popis chovani.
 * Staci procesu jenom rict, ze jsi neco provedl na CPU a on ti rekne, co mas dale udelat. O nic vice se starat nemusis.
 * @param process
 * @param operation
 */
void Cpu::CheckForWebServerProcess(CpuProcess* process, int operation, double info) {
    if ((process->processType == WEBSERVER || process->processType == WEBSERVER_MASTER) == false) { // pokud se nejedna o process z WebServeru
        return; // tak se tim nema smysl zabivat
    }
    if (process->unfinish_op_flag == true) {
        return;
    }
    int perform = process->webServerProcessBehavior->operationPerformed(operation); // ziskame operaci, kterou mame provest
    cout << "CPU > switch > " << process->name << " perform> " << perform << " size> " << process->webServerProcessBehavior->operations->size() << "\n";

    switch (perform) {
        case INIT_SERVER:
            web_server->webServerIsInitialized();
            break;
        case CREATE_IDLE_SERVER:
            web_server->idleServerCreated();
            break;
        case RETURN_IDLE_SERVER:
            process->web_request_delay = Time - process->web_request_delay; // vypocti delku obsluhy weboveho pozadavku            
            if (glob_logger->max_web_request_delay < process->web_request_delay) {
              glob_logger->max_web_request_delay = process->web_request_delay;
            }
            glob_logger->WriteWebRequest(process->web_request_delay); // vypis do datoveho souboru delku obsluhy weboveho pozadavku            
            web_server->returnServerFromCPU();
            break;
        case SERVER_IS_RUNNING:
            process->web_request_delay = Time;    // uloz cas startu procesu
            web_server->anotherServerIsRunning();
            break;
        case ALLOC_RAM_PERMANENTLY:
            process->p_cpu->p_ram->RamAlloc(process->processSizeInRam, NULL);
            break;
        case ALLOC_RAM_TEMP:
            //process->p_cpu->p_ram->RamAlloc(glob_sim_args->web_server->process_size, process);
            break;
        case FREE_RAM_TEMP:
            //process->p_cpu->p_ram->RamFree(glob_sim_args->web_server->process_size, process);
            break;
        case CALL_DB:
            process->p_cpu->db_server->Query(process, info, info);
            // TADY SI ZAVOLAS DATABAZI
            break;
        case NONE:
            return;
        case KILL_PROCESS: // tady muze napriklad pridat nejakou rezii pro CPU, kdyz se killuje process
            //process->p_cpu->p_ram->RamFree(glob_sim_args->web_server->process_size, process);
            return;
    }
}
