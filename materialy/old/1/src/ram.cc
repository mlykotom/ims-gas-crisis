#include "ram.h"

/*
 * size => velikost v KB
 * access_time => cas v ns (radove v desitkach ns) 
 */
Ram::Ram(double size, double acc_time, double d_rate) {
//  ram_name_ = string("RAM");
//  store_ram = new Store(ram_name_.c_str(), size);
  ram_access_name_ = string("RAM access");
  fac_ram_access = new Facility(ram_access_name_.c_str());
  access_time = acc_time;
  busy_ram_ = 0.0;
  max_busy_ram_ = 0.0;
  ram_capacity_ = size;
  data_rate = d_rate;
}

Ram::~Ram() {
//  delete store_ram;
  delete fac_ram_access;
}

void Ram::Log() {
//  store_ram->Output();
  fac_ram_access->Output();
}

void Ram::MemoryAccess(CpuProcess *proc, double size) {
  /**
   * http://cs.wikipedia.org/wiki/%C4%8Casov%C3%A1n%C3%AD_RAM
   * http://en.wikipedia.org/wiki/SDRAM_latency
   * http://en.wikipedia.org/wiki/DDR3_SDRAM
   */
  if (proc->unfinish_op_flag == false) { // pokud je operace nerozpracovana, nastav cas jeji obsluhy
/*    if (size > GetBusyRam()) {
      cerr << "CHYBA: Ram::MemoryAccess, process PID: " << proc->pid << " chce cist vice pameti nez je alokovano v RAM !!!" << endl;
      cerr << "Busy RAM: " << GetBusyRam() << endl;
      cerr << "pozadovano: " << size << endl;
      exit(-1);
    }*/
    // vzorec vypoctu doby obsluhy RAM
    proc->working_time = (size / ((data_rate * 8.0) * 2.0));

    // velmi pravdepodobny pristup pres cache procesoru
    double cache_hit = Uniform(0.0, 1.0);
    if (cache_hit < glob_sim_args->cpu->cache_hit) {
      proc->working_time *= glob_sim_args->cpu->cache_factor;
    }

    cout.width(10); cout << Time; cout.width(8); cout << " PID: "; cout.width(3); cout << proc->pid << " $ RAM_ACC: \t" << size << endl;
  }

  // cas kroku operace
  double wait_step = PreemptivStep(proc);
  // simulace pristupu/prace s RAM
  proc->Wait(wait_step);

  if (proc->unfinish_op_flag == false) { // pokud je operace nerozpracovana => tedy uz dokoncena
    // smazani prave dokoncene operace
    proc->vec_op->erase(proc->vec_op->begin());
  }
}

void Ram::RamAlloc(double size, CpuProcess *proc) {
  busy_ram_ += size;
  if (busy_ram_ > max_busy_ram_) {
    max_busy_ram_ = busy_ram_;
  }
  if (busy_ram_ > ram_capacity_) {
    cerr << "CHYBA: Ram::RamAlloc, malo pameti RAM." << endl;
    exit(-1);
  }
  if (proc != NULL) {
    proc->busy_memory += size;
    proc->vec_op->erase(proc->vec_op->begin());
  }
}

void Ram::RamFree(double size, CpuProcess *proc) {
  busy_ram_ -= size;
  if (busy_ram_ < 0.0) {
    cerr << "CHYBA: Ram::RamFree, zaporny stav pameti RAM !!!" << endl;
//    exit(-1);
    busy_ram_ = 0.0;
  }
  if (proc != NULL) {
    proc->busy_memory -= size;
    if (proc->busy_memory < 0.0) {
      cerr << "CHYBA: Ram::RamFree, zaporny stav pameti PROCESU !!!" << endl;
    //  exit(-1);
      proc->busy_memory = 0.0;
    }
    proc->vec_op->erase(proc->vec_op->begin());
  }
}

double Ram::GetBusyRam() {
  return busy_ram_;
}

double Ram::GetMaxBusyRam() {
  return max_busy_ram_;
}
