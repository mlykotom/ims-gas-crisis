#ifndef GLOBAL_H_
#define GLOBAL_H_

#include <cstdlib>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <algorithm>
#include "cpu.h"
#include "cpu_process.h"
#include "hard_disk.h"
#include "ram.h"
#include "web_server.h"
#include "db_server.h"
#include "logger.h"
#include "ArgsParser.h"
using namespace std;

class Cpu;
class CpuProcess;
class Ram;
class HardDisk;
class ArgsParser;
class Logger;

enum CpuProcessStatuses {
  READY = 0,
  RUNNING = 1,
  WAITING = 2,
  TERMINATED = 3,
  SUSPENDED = 4
};

enum Operations {
  RAM = 4,
  READ = 5,
  CACHE = 6,
  WRITE = 7,
  CPU = 8,
  ALLOC = 9,
  FREE = 10,
  READ_FROM_DB = 11
};

enum WebServerProcessBehaviorEnum {
  NONE = 0,
  INIT_SERVER = 1,
  CREATE_IDLE_SERVER = 2,
  RETURN_IDLE_SERVER = 3,
  CALL_DB = 4,
  KILL_PROCESS = 13,
  SERVER_IS_RUNNING = 15,
  ALLOC_RAM_PERMANENTLY = 16,
  FREE_RAM_TEMP = 17,
  ALLOC_RAM_TEMP = 18
};

enum ProcessType {
    WEBSERVER = 20,
    WEBSERVER_INITIALIZE = 21, // pokud se server teprve spousti. Po dokonceni tohoto procesu se zavola metoda void WebServer::webServerIsInitialized()
    WEBSERVER_CONSOLIDE = 22, // pokud MASTER process upravuje pocet vlaken
    WEBSERVER_REQUEST_HANDLE = 23, // pokud se jedna o proces vyrizujici pozadavek klienta
    WEBSERVER_MASTER = 24,
    DB_INIT = 30,         // po startu systemu alokuje pamet DB bufferu
    DB_QUERY = 31,         // DB dotaz
    DB_QUERY_DONE = 32,         // DB dotaz dokoncen
    BASIC_TYPE = 40       // zakladni typ procesu
};

typedef struct Operation {
  int op_code; // viz enum Operations
  double data;
  int locality;
} TOperation;

typedef struct DbBuffer {
  int locality; // identifikator shodnosti dat
  double data_size;  // mnozstvi dat
} TDbBuffer;

string IntToStr(int integer);

// preemptivni planovani
double PreemptivStep(CpuProcess *proc);

// globalni ukazatel na parsovane parametry
extern ArgsParser *glob_sim_args;

// globalni ukazatel na logovaci tridu
extern Logger *glob_logger;

double NormalDist(double input);

#endif // GLOBAL_H_
