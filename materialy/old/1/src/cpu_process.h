#ifndef PROCESS_H_
#define PROCESS_H_

#include <iostream>
#include <vector>
#include <simlib.h>
#include "global.h"

using namespace std;

class Cpu;
class WebServerProcessBehavior;

class CpuProcess : public Process {
 public:
  /*
   * Konstruktor procesu
   * cpu => svaze process s procesorem (Simulace bude vzdy obsahovat jeden procesor, ktery muze mit vice jader)
   * number_of_instructions => pocet instrukci pro vykonani procesu
   * memory => velikost spotrebovane pameti (Bajty)
   * disk => velikost spotrebovaneho mista na disku (Bajty)
   *
   * Proces ma vychozi stav READY. Proces je zarazen do tabulky vsech procesu v simulaci 'CpuProcess::process_table'
   */
  CpuProcess(Cpu *cpu, vector<struct Operation> *op_description, int processType);
  CpuProcess(Cpu *cpu, vector<struct Operation> *op_description, bool startImmiadiate, int processType, double _processSizeInRam);
  ~CpuProcess();

  // pocitadlo pid pro tvorbu novych objektu
  static int pid_counter;
  // stav procesu
  int status;
  // mnozstvi zabrane RAM procesem
  double busy_memory;
  // pocet instrukci na proces (number of instructions)
  double noi;
  // pozadovany cas CPU (v sekundach)
  double required_cpu_time;
  // pozadovane mnozstvi dat z disku
  double required_disk;
  // cachovany pristup na disk
  bool cache_access_to_disk;
  // ukazatel na objekt Cpu
  Cpu *p_cpu;
  // cislo obsazeneho jadra
  int core_no;
  // id procesu
  int pid;
  // nazev procesu
  string name;
  // casove kvantum po kterem bude proces prerusen a zarazen zpet do fronty cekajicich procesu
  double quantum;
  // cas pro vykonani jedne operace
  double working_time;
  // priznak rozpracovane operace
  bool unfinish_op_flag;
  // cekaci doba pri praci s RAM
  double timer_ram;
  // cekaci doba pri cteni z disku
  double timer_disk_read;
  // cekaci doba pri zapisu na disk
  double timer_disk_write;
  // cekaci doba pri praci s vyrovnaci cache disku
  double timer_cache;
  // celkova doba zivotu procesu
  double timer_all;
  // simulacni cas ve kterem byl proces vytvoren
  double input_time;
  // aktualni spotreba casu na CPU pri behu (RUNNING)
  double running_cnt;
  // aktualni spotreba casu ve fronte pripravenych procesu (READY)
  double ready_cnt;
  // aktualni spotreba casu ve fronte cekajicich (WAITING) na I/O ci RAM
  double waiting_cnt;
  // aktualni spotreba celkova
  double usage_cnt;
  // web server request delay
  double web_request_delay;
  // web server request delay
  double db_request_delay;
  // seznam operaci procesu, podle ktereho se vykonava jeho simulace. napr <RAM 15000; READ 3000000; WRITE 1000000; CPU 1000>
  vector<struct Operation> *vec_op;
  int processType;
  double processSizeInRam;
  void DebugPrintWecOp(unsigned int i);
  void Debug();
  void SetName(string *n);
  bool isWebServerProcess;
  WebServerProcessBehavior * webServerProcessBehavior; // je tam popsane chovani procesu
  
 private:

  // vypocte spotrebu casu procesoru, dle parametru Cpu a poctu instrukci procesu
  void SetRequiredCpuTime_();
  
  void Behavior();
};

class ProcessGenerator : public Event {
 public:
  ProcessGenerator(Cpu *cpu);
  ~ProcessGenerator();
 private:
  Cpu *p_cpu_;
  void Behavior();
};

#endif // PROCESS_H_
