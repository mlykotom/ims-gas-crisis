#ifndef LOGGER_H_
#define LOGGER_H_

#include "global.h"

using namespace std;

class Logger : public Event {
 public:
  Logger(Cpu *cpu, double step);
  ~Logger();
  void PlotFile();
  string TimeForGraph(double time);
  void WriteWebRequest(double t);
  void WriteDbRequest(double t);
  double max_web_request_delay;
  double max_db_request_delay;
  
 private:
  void Behavior();
  string file_name_;
  string gnuplot_file_name_;
  string ram_file_name_;
  string hd_file_name_;
  string web_file_name_;
  string web_request_file_name_;
  string db_file_name_;
  string db_request_file_name_;
  Cpu *p_cpu;
  double step_;
  ofstream file_;
  ofstream gnuplot_file_;
  ofstream ram_file_;
  ofstream hd_file_;
  ofstream web_file_;
  ofstream web_request_file_;
  ofstream db_file_;
  ofstream db_request_file_;
};


#endif // LOGGER_H_

