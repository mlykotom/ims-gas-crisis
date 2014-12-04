#ifndef RAM_H_
#define RAM_H_

#include <simlib.h>
#include <vector>
#include <string>
#include <iostream>
#include "global.h"

using namespace std;

class Ram {
 public:
  
  Ram(double size, double acc_time, double d_rate);
  ~Ram();
  void Log();
  void MemoryAccess(CpuProcess *proc, double size);
  /*
   * RamAlloc - Obsazeni RAM
   *   size - velikost alokovane pameti
   *   proc - proces u ktereho se aktualizuje pocitadlo vyuzite pameti
   */
  void RamAlloc(double size, CpuProcess *proc);
  void RamFree(double size, CpuProcess *proc);
  double GetBusyRam();
  double GetMaxBusyRam();

//  Store *store_ram;
  Facility *fac_ram_access;
  double access_time;
  double data_rate;
    
 private:
  double busy_ram_;
  double max_busy_ram_;
  double ram_capacity_;
  string ram_name_;
  string ram_access_name_;

};

#endif // RAM_H_
