#ifndef DB_SERVER_H_
#define DB_SERVER_H_

#include <simlib.h>
#include <vector>
#include <string>
#include <iostream>
#include "global.h"

using namespace std;

class Ram;
class HardDisk;

class DbServer {
 public:
  
  DbServer(Ram *ram, HardDisk *hd, double buf_size, int max_connect);
  ~DbServer();
  void Log();
  // alokace RAM podle max_buffer_size, zustava alokovana DB serverem i kdyz ji aktivne nevyuzije
  void Init(CpuProcess *proc, double max_buffer);
  /*
   * Dotaz na DB, bude volan samostatnymy procesy i Web serverem
   * proc => ukazatel na proces vykonavajici operaci
   * size => mnozstvi dat
   * locality => cislo slouzici pro identifikaci dotazu na shodna data
   *
   */
  void Query(CpuProcess *proc, int locality, double size);

  // Fronta Q1 u zarizeni fac_db predstavuje frontu cekajicich dotazu (pozadavku) na DB.
  Facility *fac_db;
  double max_buffer_size;
  double actual_buffer_size;
  int max_connections;
  Ram *p_ram;
  HardDisk *p_hd;
    
 private:
  string database_name_;
  vector<struct DbBuffer> buffer_;

  bool TryBuffer_(int locality);
  bool CompactBuffer_(double needed_space);
  void WriteToBuffer_(int locality, double data_size);
};

class InitDbProcessGenerator : public Event {
 public:
  InitDbProcessGenerator(Cpu *cpu, double max_buffer_size);
  ~InitDbProcessGenerator();
  double max_buffer;
 private:
  Cpu *p_cpu_;
  void Behavior();
};

class DbServerRequestGenerator : public Event {
 public:
  DbServerRequestGenerator(Cpu *cpu);
  ~DbServerRequestGenerator();
 private:
  Cpu *p_cpu_;
  void Behavior();
};

#endif // DISK_H_
