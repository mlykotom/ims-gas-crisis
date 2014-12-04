/* 
 * File:   ArgsParser.h
 * Author: root
 *
 * Created on December 5, 2012, 6:44 PM
 */

#ifndef ARGSPARSER_H
#define	ARGSPARSER_H
#include "global.h"


class ArgsCPU{
public:
    int cores;
    double frequency;
    double cache_hit;
    double cache_factor; // cislo mensi jak 0 => urychluje
};

class ArgsRAM{
public:
    double size;
    double access_time;
    double data_rate;
};

class ArgsHD{
public:
    double size;
    double access_time;
    double r_speed;
    double w_speed;
};

class ArgsSIM{
public:
    double start;
    double stop;
    double plot_step;
};

class ArgsWebServerQuery{
public:
    double cycles;
    double page_size;
    double locality; // nakonec nepouzito, jako lokalita je pouzita page_size
    int slow_factor;
    int event_start;
    int event_stop;
    int fixed_page_size;
};

class ArgsWebServer{
public:
    double exp;
    int max_servers;
    int max_free_servers;
    int min_free_servers;
    int buffer_size;
    int enable;
    double init_size;
    double process_size;
    ArgsWebServerQuery *query;
};

class ArgsDatabaseQuery{
public:
    int size;
    int locality;
    double cycles;
    int slow_factor;
    int event_start;
    int event_stop;
};

class ArgsDatabase{
public:
    double exp;
    double buffer;
    int enable;
    ArgsDatabaseQuery *query;
};

class ArgsProcess{
public:
    double ram;
    double read;
    double cpu;
    double quantum;
    double exp;
    int enable;
    int slow_factor;
    int event_start;
    int event_stop;
};


class ArgsParser {
public:
    ArgsParser(char * _config_file_path, bool print_config);
    ArgsParser(const ArgsParser& orig);
    virtual ~ArgsParser();
    
    ArgsCPU *cpu;
    ArgsRAM *ram;
    ArgsHD *hd;
    ArgsSIM *sim;
    ArgsWebServer *web_server;
    ArgsDatabase *database;
    ArgsProcess *process;
    
private:
    void initDataObjects();
    bool parseLine(string line_to_parse);
    bool parseCPU(string line_to_parse);
    bool parseRAM(string line_to_parse);
    bool parseHD(string line_to_parse);
    bool parseSIM(string line_to_parse);
    bool parseWebServer(string line_to_parse);
    bool parseWebServerQuery(string line_to_parse);
    bool parseDatabase(string line_to_parse);
    bool parseDatabaseQuery(string line_to_parse);
    bool parseProcess(string line_to_parse);
};

#endif	/* ARGSPARSER_H */
