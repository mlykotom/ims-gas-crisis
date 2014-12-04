#ifndef DISK_H_
#define DISK_H_

#include <simlib.h>
#include <vector>
#include <string>
#include <iostream>
#include "global.h"

using namespace std;

class Ram;

class HardDisk {
 public:
  
  HardDisk(Ram *cache, double size, double acc_time, double r_speed, double w_speed);
  ~HardDisk();
  void Log();
  /*
   * Pristup na disk, obecne pro cteni nebo zapis
   * proc => ukazatel na proces vykonavajici operaci
   * size => mnozstvi dat
   *
   * Vytvori I/O pozadavek, uspi proces, vykona I/O, probudi proces a zaradi do fronty pripravenych procesu
   */
  void DiskAccess(CpuProcess *proc, double size, int mode);
  double GetReadedCnt();
  double GetWritedCnt();
//  void BufferedDiskAccess(CpuProcess *proc, double size);

//  Histogram *his_hd;
  Store *store_hd;
  // Fronta Q1 u zarizeni hd_controller predstavuje frontu cekajicich procesu na I/O operaci.
  Facility *fac_hd_controller;
  double access_time;
  double read_speed;
  double write_speed;
  Ram *p_page_cache;
    
 private:
  string hard_disk_name_;
  string hd_controller_name_;
  double readed_cnt_;
  double writed_cnt_;
};

#endif // DISK_H_
