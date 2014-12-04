#include "logger.h"
//GetRunnablePerCoreCount(int core)
Logger::Logger(Cpu *cpu, double step) {
  p_cpu = cpu;
  step_ = step;
  max_web_request_delay = 0.0;
  max_db_request_delay = 0.0;

  file_name_ = "out/output.dat";
  file_.open(file_name_.c_str());
  if (file_.is_open()) {
    file_ << "# 1(cas) 2(aktualni pocet cekajicich procesu) ";
    for (int i = 0; i < p_cpu->GetCoreCount(); i++) {
      file_ << i + 3 << "(aktualni pocet instrukci zpracovavanych na jadre " << i << ") ";
//      file_ << i + 5 << "(aktualni pocet pripravenych procesu bezet na jadru " << i << ") ";
    }
    file_ << endl;
  } else {
    cerr << "CHYBA: nelze otevrit " << file_name_ << endl;
    exit(-1);
  }
  // ram
  ram_file_name_ = "out/ram.dat";
  ram_file_.open(ram_file_name_.c_str());
  if (ram_file_.is_open()) {
    ram_file_ << "# 1(cas) 2(aktualni hodnota obsazene RAM) " << endl;
  } else {
    cerr << "CHYBA: nelze otevrit " << ram_file_name_ << endl;
    exit(-1);
  }
  // hd
  hd_file_name_ = "out/hd.dat";
  hd_file_.open(hd_file_name_.c_str());
  if (hd_file_.is_open()) {
    hd_file_ << "# 1(cas) 2(prectena data) 3(zapsana data) " << endl;
  } else {
    cerr << "CHYBA: nelze otevrit " << hd_file_name_ << endl;
    exit(-1);
  }
  // web
  web_file_name_ = "out/web.dat";
  web_file_.open(web_file_name_.c_str());
  if (web_file_.is_open()) {
    web_file_ << "# 1(cas) 2(idle) 3(running) 4(waiting request in buffer)" << endl;
  } else {
    cerr << "CHYBA: nelze otevrit " << web_file_name_ << endl;
    exit(-1);
  }
  // web request delay
  web_request_file_name_ = "out/web_request.dat";
  web_request_file_.open(web_request_file_name_.c_str());
  if (web_request_file_.is_open()) {
    web_request_file_ << "# 1(cas) 2(doba zpozdeni) " << endl;
  } else {
    cerr << "CHYBA: nelze otevrit " << web_request_file_name_ << endl;
    exit(-1);
  }
  // database
  db_file_name_ = "out/db.dat";
  db_file_.open(db_file_name_.c_str());
  if (db_file_.is_open()) {
    db_file_ << "# 1(cas) 2(actual_buffer_size) " << endl;
  } else {
    cerr << "CHYBA: nelze otevrit " << db_file_name_ << endl;
    exit(-1);
  }
  // database request delay
  db_request_file_name_ = "out/db_request.dat";
  db_request_file_.open(db_request_file_name_.c_str());
  if (db_request_file_.is_open()) {
    db_request_file_ << "# 1(cas) 2(doba zpozdeni) " << endl;
  } else {
    cerr << "CHYBA: nelze otevrit " << db_request_file_name_ << endl;
    exit(-1);
  }
  Activate();
}

Logger::~Logger() {
  file_.close();
  gnuplot_file_.close();
  ram_file_.close();
  hd_file_.close();
  web_file_.close();
  web_request_file_.close();
  db_file_.close();
  db_request_file_.close();
}

void Logger::PlotFile() {
  // gnuplot (out/plot.plt)
  gnuplot_file_name_ = "out/plot.plt";
  gnuplot_file_.open(gnuplot_file_name_.c_str());
  if (gnuplot_file_.is_open()) {
    gnuplot_file_ << "set terminal png size 1000,600" << endl;
    gnuplot_file_ << "set autoscale y" << endl;
    gnuplot_file_ << "unset autoscale x" << endl;
    gnuplot_file_ << "set key below" << endl;
    gnuplot_file_ << "set xrange [\"" << glob_sim_args->sim->start << "\":\"" << glob_sim_args->sim->stop << "\"]" << endl;
    gnuplot_file_ << "set xlabel \"Cas (s)\"" << endl;
    gnuplot_file_ << "set ylabel \"Pocet procesu\"" << endl;
    gnuplot_file_ << "set title \"Pocet cekajicich procesu na I/O\"" << endl;
    gnuplot_file_ << "set output 'waiting_process_count.png'" << endl;
    gnuplot_file_ << "plot \"output.dat\" using 1:2 title \"Celkem cekajicich na I/O\" with steps linewidth 3" << endl;
    gnuplot_file_ << "set output 'waiting_process_count_sampled.png'" << endl;
    gnuplot_file_ << "plot \"output2.dat\" using 1:2 title \"Celkem cekajicich na I/O\" with steps linewidth 3" << endl;
//    gnuplot_file_ << "set key right top" << endl;
    gnuplot_file_ << "set ylabel \"Pocet instrukci za casove kvantum (" << glob_sim_args->process->quantum << ") s\"" << endl;
    gnuplot_file_ << "set title \"Soucet vyuziti CPU vsemi jadry\"" << endl;
    gnuplot_file_ << "set output 'cpu_usage.png'" << endl;
//    plot "bench.dat" using 1:($2+$3+$4+$5+$6)/5 with boxes title "Prumerny vykon"
    gnuplot_file_ << "plot \"output2.dat\" using 1:(";
    for (int i = 0; i < p_cpu->GetCoreCount(); i++) {
      gnuplot_file_ << "$" << 3 + i;
      if (i+1 < p_cpu->GetCoreCount()) {
        gnuplot_file_ << "+";
      }
    }  
    gnuplot_file_ << ")/" << p_cpu->GetCoreCount() << " title \"Celkove vytizeni\" with steps linewidth 3" << endl;
    // jednotliva jadra
    for (int i = 0; i < p_cpu->GetCoreCount(); i++) {
      gnuplot_file_ << "set title \"Vyuziti jadra "<< i << "\"" << endl;
      gnuplot_file_ << "set output 'cpu_core" << i << ".png'" << endl;
      gnuplot_file_ << "plot \"output2.dat\" using 1:" << 3 + i << " title \"Jadro " << i << "\" with steps linewidth 3" << endl;
    }

/*      gnuplot_file_ << "\"output.dat\" using 1:" << 5 + i << " title \"Pripravene bezet na jadru " << i << "\" with steps";
      if (i+1 != p_cpu->GetCoreCount()) {
        gnuplot_file_ << ", \\";
      }
      gnuplot_file_ << endl;*/

//    gnuplot_file_ << "set key left top" << endl;
    // ram
    gnuplot_file_ << "set ylabel \"Obsazena RAM (B)\"" << endl;
    gnuplot_file_ << "set title \"Vyuziti pameti RAM\"" << endl;
    gnuplot_file_ << "set yrange [0:" << p_cpu->p_ram->GetMaxBusyRam() << "]" << endl;
    gnuplot_file_ << "set output 'ram_usage.png'" << endl;
    gnuplot_file_ << "plot \"ram.dat\" using 1:2 title \"Obsazana RAM (B)\" with steps linewidth 3" << endl;
    // hd
    gnuplot_file_ << "set ylabel \"Data (B)\"" << endl;
    gnuplot_file_ << "set title \"Prectena data z disku\"" << endl;
    gnuplot_file_ << "set yrange [0:]" << endl;
    gnuplot_file_ << "set autoscale y" << endl;
    gnuplot_file_ << "set output 'hd_read_write.png'" << endl;
    gnuplot_file_ << "plot \"hd.dat\" using 1:2 title \"Prectena data (B)\" with steps linewidth 3 linetype 1" << endl;
//    gnuplot_file_ << "\"hd.dat\" using 1:3 title \"Zapsana data (B)\" with steps linewidth 2 linetype 3" << endl;
    // web
    if (p_cpu->web_server != NULL) {
      gnuplot_file_ << "set ylabel \"Pocet\"" << endl;
      gnuplot_file_ << "set title \"Pocty cekajicich a bezicich procesu web serveru - samplovano\"" << endl;
      gnuplot_file_ << "set yrange [0:]" << endl;
      // web obsluzne procesy - samplovane
      gnuplot_file_ << "set output 'web_idle_running_sampled.png'" << endl;
      gnuplot_file_ << "plot \"web2.dat\" using 1:2 title \"cekajici\" with steps linewidth 3 linetype 1, \\" << endl;
      gnuplot_file_ << "\"web2.dat\" using 1:3 title \"Bezici\" with steps linewidth 3 linetype 3" << endl;
      // web obsluzne procesy prvnich 5 sekund
      gnuplot_file_ << "set xrange [0:5]" << endl;
      gnuplot_file_ << "set title \"Pocty cekajicich a bezicich procesu web serveru - prvnich 5 sekund\"" << endl;
      gnuplot_file_ << "set output 'web_idle_running_start.png'" << endl;
      gnuplot_file_ << "plot \"web.dat\" using 1:2 title \"cekajici\" with steps linewidth 3 linetype 1, \\" << endl;
      gnuplot_file_ << "\"web.dat\" using 1:3 title \"Bezici\" with steps linewidth 3 linetype 3" << endl;
      gnuplot_file_ << "set xrange [\"" << glob_sim_args->sim->start << "\":\"" << glob_sim_args->sim->stop << "\"]" << endl;
      // web obsluzne procesy - cista data
      gnuplot_file_ << "set title \"Pocty cekajicich a bezicich procesu web serveru - cista data\"" << endl;
      gnuplot_file_ << "set output 'web_idle_running.png'" << endl;
      gnuplot_file_ << "plot \"web.dat\" using 1:2 title \"cekajici\" with steps linewidth 3 linetype 1, \\" << endl;
      gnuplot_file_ << "\"web.dat\" using 1:3 title \"Bezici\" with steps linewidth 3 linetype 3" << endl;
      // web request histogram
      gnuplot_file_ << "set ylabel \"Pocet pozadavku\"" << endl;
      gnuplot_file_ << "set title \"Histogram zpozdeni webovych pozadavku\"" << endl;
      gnuplot_file_ << "set output 'web_request_histogram.png'" << endl;
      gnuplot_file_ << "set xlabel \"Doba obsluhy (s)\"" << endl;
      gnuplot_file_ << "set xrange [0:" << max_web_request_delay << "]" << endl;
      gnuplot_file_ << "bin(x,size) = floor(1.0*x/size)*size" << endl;
      gnuplot_file_ << "plot \"web_request.dat\" using (bin($2," << max_web_request_delay/10.0 << ")):(2) smooth frequency with boxes linewidth 3 title \"Pozadavky\"" << endl;
      gnuplot_file_ << "set xrange [\"" << glob_sim_args->sim->start << "\":\"" << glob_sim_args->sim->stop << "\"]" << endl;
      gnuplot_file_ << "set xlabel \"cas (s)\"" << endl;
      // web request - cista data
      gnuplot_file_ << "set ylabel \"Doba obsluhy (s)\"" << endl;
      gnuplot_file_ << "set title \"Prehled zpozdeni webovych pozadavku\"" << endl;
      gnuplot_file_ << "set yrange [0:]" << endl;
      gnuplot_file_ << "set output 'web_request.png'" << endl;
      gnuplot_file_ << "plot \"web_request.dat\" using 1:2 title \"Pozadavky\" with points linetype 3" << endl;
      // web request buffer
      gnuplot_file_ << "set ylabel \"Pocet pozadavku\"" << endl;
      gnuplot_file_ << "set title \"Zaplneni bufferu webovych pozadavku\"" << endl;
      gnuplot_file_ << "set yrange [0:]" << endl;
      gnuplot_file_ << "set output 'web_request_buffer.png'" << endl;
      gnuplot_file_ << "plot \"web.dat\" using 1:4 title \"Pocet pozadavku v bufferu\" with steps linetype 3" << endl;
    }
    if (glob_sim_args->database->enable == 1) {
      // database
      gnuplot_file_ << "set ylabel \"Data (B)\"" << endl;
      gnuplot_file_ << "set title \"Vytizeni databazoveho serveru\"" << endl;
      gnuplot_file_ << "set yrange [0:]" << endl;
      gnuplot_file_ << "set autoscale y" << endl;
      gnuplot_file_ << "set output 'database_usage.png'" << endl;
      gnuplot_file_ << "plot \"db.dat\" using 1:2 title \"Aktualni velikost vyrovnavaci pameti (B)\" with steps linewidth 3 linetype 1" << endl;
      // database request histogram
      gnuplot_file_ << "set ylabel \"Pocet pozadavku\"" << endl;
      gnuplot_file_ << "set title \"Histogram zpozdeni databazovych pozadavku\"" << endl;
      gnuplot_file_ << "set output 'db_request_histogram.png'" << endl;
      gnuplot_file_ << "set xlabel \"Doba obsluhy (s)\"" << endl;
      gnuplot_file_ << "set xrange [0:" << max_db_request_delay << "]" << endl;
      gnuplot_file_ << "bin(x,size) = floor(1.0*x/size)*size" << endl;
      gnuplot_file_ << "plot \"db_request.dat\" using (bin($2," << max_db_request_delay/10.0 << ")):(2) smooth frequency with boxes linewidth 3 title \"Pozadavky\"" << endl;
      gnuplot_file_ << "set xrange [\"" << glob_sim_args->sim->start << "\":\"" << glob_sim_args->sim->stop << "\"]" << endl;
      gnuplot_file_ << "set xlabel \"cas (s)\"" << endl;
    }
  } else {
    cerr << "CHYBA: nelze otevrit " << gnuplot_file_name_ << endl;
    exit(-1);
  }
}

string Logger::TimeForGraph(double time) {
  return "";
}

void Logger::WriteWebRequest(double t) {
  if (p_cpu->web_server != NULL) {
    web_request_file_ << Time << "\t";
    web_request_file_ << t << "\t";
    web_request_file_ << endl;
  }
}

void Logger::WriteDbRequest(double t) {
  db_request_file_ << Time << "\t";
  db_request_file_ << t << "\t";
  db_request_file_ << endl;
}

void Logger::Behavior() {
  file_ << Time << "\t";
//  file_ << p_cpu->GetProcessCount() << "\t";
  file_ << p_cpu->GetWaitingProcessCount() << "\t";
  for (int i = 0; i < p_cpu->GetCoreCount(); i++) {
    file_ << p_cpu->GetNoiPerCore(i) << "\t";
//    file_ << p_cpu->GetRunnablePerCoreCount(i) << "\t";
  }
  file_ << endl;
  // ram
  ram_file_ << Time << "\t";
  ram_file_ << p_cpu->p_ram->GetBusyRam() << "\t";
  ram_file_ << endl;
  // hd
  hd_file_ << Time << "\t";
  hd_file_ << p_cpu->p_hd->GetReadedCnt() << "\t";
  hd_file_ << p_cpu->p_hd->GetWritedCnt() << "\t";
  hd_file_ << endl;
  // web
  if (p_cpu->web_server != NULL) {
    web_file_ << Time << "\t";
    web_file_ << p_cpu->web_server->getIdleServersCnt() << "\t";
    web_file_ << p_cpu->web_server->getRunningServersCnt() << "\t";
    web_file_ << p_cpu->web_server->getIncomingBufferSize() << "\t";
    web_file_ << endl;
  }
  // db
  db_file_ << Time << "\t";
  db_file_ << p_cpu->db_server->actual_buffer_size << "\t";
  db_file_ << endl;

  Activate(Time + step_);
}


