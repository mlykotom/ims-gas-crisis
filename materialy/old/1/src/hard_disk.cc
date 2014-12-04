#include "hard_disk.h"

/*
 * size => velikost v B
 * access_time => cas v s (radove v desitkach ms) 
 */
HardDisk::HardDisk(Ram *cache, double size, double acc_time, double r_speed, double w_speed) {
  p_page_cache = cache;
  hard_disk_name_ = string("HARD DISK");
  hd_controller_name_ = string("HD controller");
  store_hd = new Store(hard_disk_name_.c_str(), size);
  fac_hd_controller = new Facility(hd_controller_name_.c_str());
  access_time = acc_time;
  read_speed = r_speed;
  write_speed = w_speed;
  readed_cnt_ = 0.0;
  writed_cnt_ = 0.0;
//  his_hd = new Histogram("his_hd", 0.0, 1e6, 30e6);
}

HardDisk::~HardDisk() {
  delete store_hd;
  delete fac_hd_controller;
//  delete his_hd;
}

void HardDisk::Log() {
  store_hd->Output();
  fac_hd_controller->Output();
//  his_hd->Output();
}

void HardDisk::DiskAccess(CpuProcess *proc, double size, int mode) {
  // prechod do fronty cekajicich procesu
  (proc->p_cpu->fac_cores[proc->core_no])->Release(proc);
  // snizeni pocitadla running/runnable
//  proc->process_per_core_cnt_[proc->core_no] -= 1;
  proc->p_cpu->SetProcessPerCoreCount(proc->core_no, -1);
  proc->p_cpu->SetWaitingProcessCount(+1);
  cout.width(10); cout << Time; cout.width(8); cout << " PID: "; cout.width(3); cout << proc->pid << " = WAITING" << endl;
  proc->status = WAITING;
  fac_hd_controller->Seize(proc);
//  (*his_hd)(size);

  // cteni/zapis z disku
  switch (mode) {
    case READ:
      cout.width(10); cout << Time; cout.width(8); cout << " PID: "; cout.width(3); cout << proc->pid << " $ HD R: \t" << size / read_speed + access_time << endl;
      proc->Wait(size / read_speed + access_time);
      readed_cnt_ += size;
      break;
    case WRITE:
      cout.width(10); cout << Time; cout.width(8); cout << " PID: "; cout.width(3); cout << proc->pid << " $ HD W: \t" << size / write_speed + access_time << endl;
      proc->Wait(size / write_speed + access_time);
      writed_cnt_ += size;
      break;
    default:
      cerr << "ERROR: HardDisk::DiskAccess(), switch => default" << endl;
      exit(-1);
      break;
  }

  // prechod do fronty procesu pripravenych bezet
  fac_hd_controller->Release(proc);
  // vyber volnejsiho procesoru
  proc->p_cpu->SelectCore(proc);
  cout.width(10); cout << Time; cout.width(8); cout << " PID: "; cout.width(3); cout << proc->pid << " = READY" << endl;
  proc->status = READY;
  // navyseni pocitadla running/runnable
//  proc->process_per_core_cnt_[proc->core_no] += 1;
  proc->p_cpu->SetProcessPerCoreCount(proc->core_no, +1);
  proc->p_cpu->SetWaitingProcessCount(-1);
  proc->Priority = 1; // zvednuti priority procesu, aby se proces ktery dokoncil I/O operaci zaradil dopredu ve fronte.
  proc->p_cpu->fac_cores[proc->core_no]->Seize(proc); 
  proc->Priority = 0; // vychozi priorita procesu
  // smazani prave dokoncene operace
  proc->vec_op->erase(proc->vec_op->begin());
}

double HardDisk::GetReadedCnt() {
  return readed_cnt_;
}

double HardDisk::GetWritedCnt() {
  return writed_cnt_;
}

