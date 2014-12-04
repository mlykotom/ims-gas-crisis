#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <simlib.h>
#include "global.h"

using namespace std;

int main(int argc, char* argv[]) {
  ArgsParser simArgs = ArgsParser(argv[1], true);
  glob_sim_args = &simArgs;

  // inicializace doby simulace, jednotka simulace predstavuje 1 s
  Init(glob_sim_args->sim->start, glob_sim_args->sim->stop);

  // inicializace procesoru, napr. (dvou jadro, 1826 Mhz CPU, 256 MB RAM, 10 ns pristupova doba do RAM, 1 GB HD, 5 ms pristupova doba disku, 30 MB/s rychlost cteni disku, 25 MB/s rychlost zapisu na disk)
  Cpu cpu(glob_sim_args->cpu->cores, 
          glob_sim_args->cpu->frequency, 
          glob_sim_args->ram->size, 
          glob_sim_args->ram->access_time, 
          glob_sim_args->hd->size,
          glob_sim_args->hd->access_time,
          glob_sim_args->hd->r_speed,
          glob_sim_args->hd->w_speed);
  if (glob_sim_args->web_server->enable == 1) {
    cpu.web_server = new WebServer(&cpu, glob_sim_args->web_server->max_servers, 
                                         glob_sim_args->web_server->max_free_servers, 
                                         glob_sim_args->web_server->min_free_servers);
  }

  // inicializace a generator databazovych dotazu
  if (glob_sim_args->database->enable == 1) {
    new InitDbProcessGenerator(&cpu, glob_sim_args->database->buffer); // Vychozi velikost databazoveho bufferu byva 128 MB
    new DbServerRequestGenerator(&cpu);
  }
  // generator procesu
  if (glob_sim_args->process->enable == 1) {
    new ProcessGenerator(&cpu);
  }

  Logger *logger = new Logger(&cpu, glob_sim_args->sim->plot_step);
  glob_logger = logger;
  Run();
  // vypis statistik
  logger->PlotFile();
  cpu.Log();
  SIMLIB_statistics.Output();
  

  return 0;
}
