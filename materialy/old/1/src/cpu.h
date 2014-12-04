#ifndef CPU_H_
#define CPU_H_

#include <simlib.h>
#include <vector>
#include <string>
#include <iostream>
#include "global.h"
//#include "web_server.h"
//#include "cpu_process.h"
//#include "ram.h"
//#include "hard_disk.h"

using namespace std;

class CpuProcess;
class Ram;
class HardDisk;
class WebServer;
class WebServerProcessBehavior;
class DbServer;

class Cpu {
 public:
  
  Cpu(int cores, double cpu_freq, double ram_size, double ram_access_time, double hd_size, double hd_access_time, double r_speed, double w_speed);
  ~Cpu();
  void Log();
  int Start(CpuProcess *p);
  void CpuOperate(CpuProcess *proc, double noi);
  /*
   * Hleda jadro s nejkratsi frontou pripravenych procesu a k tomu priradi proces
   */
  void SelectCore(CpuProcess *proc);
  int GetCoreCount();
  int GetProcessCount();
  int GetWaitingProcessCount();
  void SetWaitingProcessCount(int value);
  int GetProcessMaxCount();
  void SetProcessPerCoreCount(int core, int value);
  int GetProcessPerCoreCount(int core);
  int GetRunnablePerCoreCount(int core);
  double GetNoiPerCore(int core);
  // tabulka vsech procesu
  static vector<CpuProcess*> process_table;
  Ram *p_ram;
  HardDisk *p_hd;
  // fronta Q1 u kazdeho jadra predstavuje frontu pripravenych (READY) procesu
  vector<Facility*> fac_cores;
  // clock_rate == cpu_freq, jednotka Mhz
  double clock_rate;
  WebServer * web_server;
  DbServer * db_server;
    
 private:
  int cores_cnt_;
  vector<string> core_names_;
  int process_in_system_cnt_;
  int process_in_system_max_;
  vector<int> process_per_core_cnt_;
  int process_waiting_cnt_;
  vector<double> noi_per_core_cnt_;

  void CheckForWebServerProcess(CpuProcess * process, int operation, double info);

};

#endif // CPU_H_
