#include "global.h"

string IntToStr(int integer) {
  stringstream s;
  s << integer;
  return s.str();
}

// preemptivni planovani
double PreemptivStep(CpuProcess *proc) {
  double wait_step;
//  bool ram_preemp = proc->p_cpu->p_ram->fac_ram_access->Busy();

  if (proc->working_time > proc->quantum) { // obsluha je delsi nez kvantum, bude se prepinat kontext
    proc->unfinish_op_flag = true;
    proc->working_time -= proc->quantum;
    wait_step = proc->quantum;
    // pokud je fronta procesu pripravenych bezet neprazdna
    if (proc->p_cpu->fac_cores[proc->core_no]->QueueLen() != 0) {

/*      if (ram_preemp) {
        // uvolneni vylucny pristup do RAM
        proc->p_cpu->p_ram->fac_ram_access->Release(proc);
      }*/

      proc->p_cpu->fac_cores[proc->core_no]->Release(proc); // prepnuti kontextu, proces se vzda jadra a hned se zaradi do fronty cekajicich procesu
//      cout.width(10); cout << Time; cout.width(8); cout << " PID: "; cout.width(3); cout << proc->pid << " # PREEMPT" << endl;
      proc->status = READY;
      proc->p_cpu->fac_cores[proc->core_no]->Seize(proc);
      proc->status = RUNNING;

/*      if (ram_preemp) {
        // uvolneni vylucny pristup do RAM
        proc->p_cpu->p_ram->fac_ram_access->Seize(proc);
      }*/

    }
  } else { // obsluha operace se stihne dokoncit v nasledujicim kvantu
    proc->unfinish_op_flag = false;
    wait_step = proc->working_time;
  }

  return wait_step;
}

// globalni ukazatel na parsovane parametry
ArgsParser *glob_sim_args = NULL;

// globalni ukazatel na logovaci tridu
Logger *glob_logger = NULL;

double NormalDist(double input) {
  double data = Normal(0, input);
  if(data < 0.0){
      data = data*(-1);
  }
  if(data < (input/10.0)){
      data = input/10.0;
  }
  else if(data > (input*10.0)){
      data = input*10.0;
  }
  return data;
}
