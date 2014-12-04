#include "cpu_process.h"

int CpuProcess::pid_counter = 1;

CpuProcess::CpuProcess(Cpu *cpu, vector<TOperation> *op_description, int _processType) {
  pid = pid_counter++;
  status = READY;
  busy_memory = 0.0;
  core_no = -1;
  isWebServerProcess = false; // defaultne je false. Musi se nastavit rucne
  webServerProcessBehavior = NULL;
//  required_memory = memory;
//  required_disk = disk;
//  noi = number_of_instructions;
  p_cpu = cpu;
  SetRequiredCpuTime_();
  p_cpu->process_table.push_back(this);
  cache_access_to_disk = false;
  quantum = glob_sim_args->process->quantum; // defaultne 10 ns
  usage_cnt = 0.0;
  processSizeInRam = 0.0;
  unfinish_op_flag = false;
  vec_op = op_description;
  name = string("");
  processType = BASIC_TYPE;
  web_request_delay = 0.0;
  db_request_delay = 0.0;
  Activate();
}

CpuProcess::CpuProcess(Cpu *cpu, vector<TOperation> *op_description, bool startImmiadiate, int _processType, double _processSizeInRam) {
  pid = pid_counter++;
  status = READY;
  busy_memory = 0.0;
  core_no = -1;
  isWebServerProcess = false;  // defaultne je false. Musi se nastavit rucne
  webServerProcessBehavior = NULL;
//  required_memory = memory;
//  required_disk = disk;
//  noi = number_of_instructions;
  p_cpu = cpu;
  SetRequiredCpuTime_();
  p_cpu->process_table.push_back(this);
  cache_access_to_disk = false;
  quantum = glob_sim_args->process->ram; // defaultne 10 ns
  usage_cnt = 0.0;
  unfinish_op_flag = false;
  vec_op = op_description;
  processSizeInRam = _processSizeInRam;
  name = string("");
  processType = _processType;
  web_request_delay = 0.0;
  if(startImmiadiate == true){
    Activate();
  }
}

CpuProcess::~CpuProcess() {
  delete vec_op;
}

void CpuProcess::DebugPrintWecOp(unsigned int i) {
  if (webServerProcessBehavior != NULL) {
//    if (i < webServerProcessBehavior->operations->size()) {
    int web_op = -1;

    list<int>::iterator it;
    unsigned int j = 0;
    for (it=webServerProcessBehavior->operations->begin(), j=0;
         it != webServerProcessBehavior->operations->end(); it++, j++) {
      if (i == j) {
        web_op = *it;
        switch(web_op) {
          case NONE:
            cout << "web " << " NONE" << endl;
            break;
          case INIT_SERVER:
            cout << "web " << " INIT_SERVER" << endl;
            break;
          case CREATE_IDLE_SERVER:
            cout << "web " << " CREATE_IDLE_SERVER" << endl;
            break;
          case RETURN_IDLE_SERVER:
            cout << "web " << " RETURN_IDLE_SERVER" << endl;
            break;
          case CALL_DB:
            cout << "web " << " CALL_DB" << endl;
            break;
          case KILL_PROCESS:
            cout << "web " << " KILL_PROCESS" << endl;
            break;
          case SERVER_IS_RUNNING:
            cout << "web " << " SERVER_IS_RUNNING" << endl;
            break;
          case ALLOC_RAM_PERMANENTLY:
            cout << "web " << " ALLOC_RAM_PERMANENTLY" << endl;
            break;
          case FREE_RAM_TEMP:
            cout << "web " << " FREE_RAM_TEMP" << endl;
            break;
          case ALLOC_RAM_TEMP:
            cout << "web " << " ALLOC_RAM_TEMP" << endl;
            break;
          default:
            cout << "web " << " enum: " << web_op << endl;
            break;
        }
      }
    }
  }
//  }
}

void CpuProcess::Debug() {
  cout << ":::>>> PID " << pid << " <<<:::" << endl;
  cout << "    name: " << name << endl;
  cout << "    status: " << status << endl;
  cout << "    working_t: " << working_time << endl;
  cout << "    Process Operation: " << endl;
  cout << "    Webserver Operation: " << endl;
  unsigned int vec_op_size = vec_op->size();
  unsigned int web_op_size = 0;
  if (processType == WEBSERVER || processType == WEBSERVER_MASTER) {
    web_op_size = webServerProcessBehavior->operations->size();
  }
  for (unsigned int i = 0; i < vec_op_size; i++) {
    switch((*vec_op)[i].op_code) {
      case RAM:
        cout << "vec " << i << " RAM" << endl;
        break;
      case READ:
        cout << "vec " << i << " READ" << endl;
        break;
      case CACHE:
        cout << "vec " << i << " CACHE" << endl;
        break;
      case WRITE:
        cout << "vec " << i << " WRITE" << endl;
        break;
      case CPU:
        cout << "vec " << i << " CPU" << endl;
        break;
      case DB_INIT:
        cout << "vec " << i << " DB_INIT" << endl;
        break;
      case DB_QUERY:
        cout << "vec " << i << " DB_QUERY" << endl;
        break;
      case ALLOC:
        cout << "vec " << i << " ALLOC" << endl;
        break;
      case FREE:
        cout << "vec " << i << " FREE" << endl;
        break;
      case READ_FROM_DB:
        cout << "vec " << i << " READ_FROM_DB" << endl;
        break;
      default:
        cout << "vec " << i << " enum: " << (*vec_op)[i].op_code << endl;
        break;
    }
    DebugPrintWecOp(i);
  }
  if (processType == WEBSERVER || processType == WEBSERVER_MASTER) {
    if (vec_op_size != web_op_size) { // tisk prebytecnych polozek webovych operaci
      cout << "POZOR: CpuProcess::Debug()   vec_op_size != web_op_size (" << vec_op_size << " != " << web_op_size << ") rozdilne velikosti seznamu operaci " << endl;
      for (unsigned int i = vec_op_size; i < web_op_size; i++) {
        DebugPrintWecOp(i);
      }
      exit(-1);
    }
  }
  cout << ":::::::::::::::::" << endl;
}

void CpuProcess::SetName(string *n) {
  name = *n;
}

void CpuProcess::SetRequiredCpuTime_() {
  // Execution time (T) = CPI*Instruction count*clock time = CPI*Instruction count/frequency = 1.55*100000/40000000 = 1.55/400 = 3.87 ms.
  // pro jednoduchost predpokladam CPI(Cycles per instruction) = 1 
  required_cpu_time = noi / p_cpu->clock_rate;
}

void CpuProcess::Behavior() {
  input_time = Time;
  p_cpu->Start(this);
}

//// ProcessGenerator

ProcessGenerator::ProcessGenerator(Cpu *cpu) {
  p_cpu_ = cpu;
  Activate();
}

ProcessGenerator::~ProcessGenerator() {

}

void ProcessGenerator::Behavior() {
  double ram_size = NormalDist(glob_sim_args->process->ram);
  double read_size = NormalDist(glob_sim_args->process->read);
  double cpu_size = NormalDist(glob_sim_args->process->cpu);

  // vytvoreni popisu operaci procesu:
  vector<Operation> *my_process_description = new vector<Operation>;
  TOperation aa = {ALLOC, ram_size}; // default 1000 Kilo Bajtu
  TOperation a = {RAM, ram_size}; // 1000 Kilo Bajtu
  TOperation b = {READ, read_size}; // 1 Mega Bajtu
  TOperation c = {CPU, cpu_size}; // 1000 instrukci
  TOperation d = {FREE, ram_size}; // 1000 Kilo Bajtu
  my_process_description->push_back(aa);
  my_process_description->push_back(a);
  my_process_description->push_back(b);
  my_process_description->push_back(c);
  my_process_description->push_back(d);
  // vytvor proces na cpu
  new CpuProcess(p_cpu_, my_process_description, BASIC_TYPE);

  if (glob_sim_args->process->event_start < Time && Time < glob_sim_args->process->event_stop) {
    // naplanuj vytvoreni dalsiho procesu s faktorem zpomaleni (zrychleni)
    Activate(Time + Exponential(glob_sim_args->process->exp) * glob_sim_args->process->slow_factor);
  } else {
    Activate(Time + Exponential(glob_sim_args->process->exp));
  }
}
