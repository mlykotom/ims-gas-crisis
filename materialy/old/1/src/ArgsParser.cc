/* 
 * File:   ArgsParser.cpp
 * Author: root
 * 
 * Created on December 5, 2012, 6:44 PM
 */

#include "ArgsParser.h"


ArgsParser::ArgsParser(char * _config_file_path, bool print_config) {
    string line;
    ifstream config_file (_config_file_path);
    initDataObjects();
    if (config_file.is_open())
    {
      while ( config_file.good() )
      {
        getline (config_file,line);
        if(print_config == true){
            cout << line << endl;
        }
        
        if(line != "" && parseLine(line) == false){
            cout << "error while parsing line >" << line << endl;
        }
      }
      config_file.close();
    }

    else cout << "Unable to open configuration file. :-("; 
}

ArgsParser::ArgsParser(const ArgsParser& orig) {
}

ArgsParser::~ArgsParser() {
    delete cpu;
    delete ram;
    delete hd;
    delete sim;
}

bool ArgsParser::parseLine(string line_to_parse){
    if(line_to_parse.substr(0, 4) == "cpu."){
        return parseCPU(line_to_parse.substr(4, line_to_parse.length()));
    }
    else if(line_to_parse.substr(0, 4) == "ram."){
        return parseRAM(line_to_parse.substr(4, line_to_parse.length()));
    }
    else if(line_to_parse.substr(0, 3) == "hd."){
        return parseHD(line_to_parse.substr(3, line_to_parse.length()));
    }
    else if(line_to_parse.substr(0, 4) == "sim."){
        return parseSIM(line_to_parse.substr(4, line_to_parse.length()));
    }
    else if(line_to_parse.substr(0, 11) == "web_server."){
        return parseWebServer(line_to_parse.substr(11, line_to_parse.length()));
    }
    else if(line_to_parse.substr(0, 9) == "database."){
        return parseDatabase(line_to_parse.substr(9, line_to_parse.length()));
    }
    else if(line_to_parse.substr(0, 8) == "process."){
        return parseProcess(line_to_parse.substr(8, line_to_parse.length()));
    }
    return false;
}

bool ArgsParser::parseCPU(string line_to_parse){
    if(line_to_parse.substr(0, 10) == "frequency="){
        cpu->frequency = atof(line_to_parse.substr(10, line_to_parse.length()).c_str());
    }
    else if(line_to_parse.substr(0, 6) == "cores="){
        cpu->cores = atoi(line_to_parse.substr(6, line_to_parse.length()).c_str());
    }
    else if(line_to_parse.substr(0, 10) == "cache_hit="){
        cpu->cache_hit = atof(line_to_parse.substr(10, line_to_parse.length()).c_str());
    }
    else if(line_to_parse.substr(0, 13) == "cache_factor="){
        cpu->cache_factor = atof(line_to_parse.substr(13, line_to_parse.length()).c_str());
    }
    
    return true;
}

bool ArgsParser::parseRAM(string line_to_parse){
    if(line_to_parse.substr(0, 5) == "size="){
        ram->size = atof(line_to_parse.substr(5, line_to_parse.length()).c_str());
    }
    else if(line_to_parse.substr(0, 12) == "access_time="){
        ram->access_time = atof(line_to_parse.substr(12, line_to_parse.length()).c_str());
    }
    else if(line_to_parse.substr(0, 10) == "data_rate="){
        ram->data_rate = atof(line_to_parse.substr(10, line_to_parse.length()).c_str());
    }
    
    return true;
}

bool ArgsParser::parseHD(string line_to_parse){
    if(line_to_parse.substr(0, 5) == "size="){
        hd->size = atof(line_to_parse.substr(5, line_to_parse.length()).c_str());
    }
    else if(line_to_parse.substr(0, 12) == "access_time="){
        hd->access_time = atof(line_to_parse.substr(12, line_to_parse.length()).c_str());
    }
    else if(line_to_parse.substr(0, 8) == "r_speed="){
        hd->r_speed = atof(line_to_parse.substr(8, line_to_parse.length()).c_str());
    }
    else if(line_to_parse.substr(0, 8) == "w_speed="){
        hd->w_speed = atof(line_to_parse.substr(8, line_to_parse.length()).c_str());
    }
    
    return true;
}

bool ArgsParser::parseSIM(string line_to_parse){
    if(line_to_parse.substr(0, 6) == "start="){
        sim->start = atof(line_to_parse.substr(6, line_to_parse.length()).c_str());
    }
    else if(line_to_parse.substr(0, 5) == "stop="){
        sim->stop = atof(line_to_parse.substr(5, line_to_parse.length()).c_str());
    }
    else if(line_to_parse.substr(0, 10) == "plot_step="){
        sim->plot_step = atof(line_to_parse.substr(10, line_to_parse.length()).c_str());
    }
    
    return true;
}

bool ArgsParser::parseWebServer(string line_to_parse){
    if(line_to_parse.substr(0, 12) == "max_servers="){
        web_server->max_servers = atoi(line_to_parse.substr(12, line_to_parse.length()).c_str());
    }
    else if(line_to_parse.substr(0, 17) == "max_free_servers="){
        web_server->max_free_servers = atoi(line_to_parse.substr(17, line_to_parse.length()).c_str());
    }
    else if(line_to_parse.substr(0, 17) == "min_free_servers="){
        web_server->min_free_servers = atoi(line_to_parse.substr(17, line_to_parse.length()).c_str());
    }
    else if(line_to_parse.substr(0, 4) == "exp="){
        web_server->exp = atof(line_to_parse.substr(4, line_to_parse.length()).c_str());
    }
    else if(line_to_parse.substr(0, 10) == "init_size="){
        web_server->init_size = atof(line_to_parse.substr(10, line_to_parse.length()).c_str());
    }
    else if(line_to_parse.substr(0, 13) == "process_size="){
        web_server->process_size = atof(line_to_parse.substr(13, line_to_parse.length()).c_str());
    }
    else if(line_to_parse.substr(0, 12) == "buffer_size="){
        web_server->buffer_size = atoi(line_to_parse.substr(12, line_to_parse.length()).c_str());
    }
    else if(line_to_parse.substr(0, 7) == "enable="){
        web_server->enable = atoi(line_to_parse.substr(7, line_to_parse.length()).c_str());
    }
    else if(line_to_parse.substr(0, 6) == "query."){
        parseWebServerQuery(line_to_parse.substr(6, line_to_parse.length()).c_str());
    }
    
    return true;
}
bool ArgsParser::parseWebServerQuery(string line_to_parse){
    if(line_to_parse.substr(0, 7) == "cycles="){
        web_server->query->cycles = atof(line_to_parse.substr(7, line_to_parse.length()).c_str());
    }
    else if(line_to_parse.substr(0, 10) == "page_size="){
        web_server->query->page_size = atof(line_to_parse.substr(10, line_to_parse.length()).c_str());
    }
    else if(line_to_parse.substr(0, 9) == "locality="){
        web_server->query->locality = atof(line_to_parse.substr(9, line_to_parse.length()).c_str());
    }
    else if(line_to_parse.substr(0, 12) == "slow_factor="){
        web_server->query->slow_factor = atoi(line_to_parse.substr(12, line_to_parse.length()).c_str());
    }
    else if(line_to_parse.substr(0, 12) == "event_start="){
        web_server->query->event_start = atoi(line_to_parse.substr(12, line_to_parse.length()).c_str());
    }
    else if(line_to_parse.substr(0, 11) == "event_stop="){
        web_server->query->event_stop = atoi(line_to_parse.substr(11, line_to_parse.length()).c_str());
    }
    else if(line_to_parse.substr(0, 16) == "fixed_page_size="){
        web_server->query->fixed_page_size = atoi(line_to_parse.substr(16, line_to_parse.length()).c_str());
    }
    
    return true;
}

bool ArgsParser::parseDatabase(string line_to_parse){
    if(line_to_parse.substr(0, 4) == "exp="){
        database->exp = atof(line_to_parse.substr(4, line_to_parse.length()).c_str());
    }
    else if(line_to_parse.substr(0, 7) == "buffer="){
        database->buffer = atof(line_to_parse.substr(7, line_to_parse.length()).c_str());
    }
    else if(line_to_parse.substr(0, 7) == "enable="){
        database->enable = atoi(line_to_parse.substr(7, line_to_parse.length()).c_str());
    }
    else if(line_to_parse.substr(0, 6) == "query."){
        parseDatabaseQuery(line_to_parse.substr(6, line_to_parse.length()).c_str());
    }
    
    return true;
}
bool ArgsParser::parseDatabaseQuery(string line_to_parse){
    if(line_to_parse.substr(0, 5) == "size="){
        database->query->size = atoi(line_to_parse.substr(5, line_to_parse.length()).c_str());
    }
    else if(line_to_parse.substr(0, 9) == "locality="){
        database->query->locality = atoi(line_to_parse.substr(9, line_to_parse.length()).c_str());
    }
    else if(line_to_parse.substr(0, 7) == "cycles="){
        database->query->cycles = atof(line_to_parse.substr(7, line_to_parse.length()).c_str());
    }
    else if(line_to_parse.substr(0, 12) == "slow_factor="){
        database->query->slow_factor = atoi(line_to_parse.substr(12, line_to_parse.length()).c_str());
    }
    else if(line_to_parse.substr(0, 12) == "event_start="){
        database->query->event_start = atoi(line_to_parse.substr(12, line_to_parse.length()).c_str());
    }
    else if(line_to_parse.substr(0, 11) == "event_stop="){
        database->query->event_stop = atoi(line_to_parse.substr(11, line_to_parse.length()).c_str());
    }
    
    return true;
}

bool ArgsParser::parseProcess(string line_to_parse){
    if(line_to_parse.substr(0, 4) == "ram="){
        process->ram = atof(line_to_parse.substr(4, line_to_parse.length()).c_str());
    }
    else if(line_to_parse.substr(0, 4) == "cpu="){
        process->cpu = atof(line_to_parse.substr(4, line_to_parse.length()).c_str());
    }
    else if(line_to_parse.substr(0, 8) == "quantum="){
        process->quantum = atof(line_to_parse.substr(8, line_to_parse.length()).c_str());
    }
    else if(line_to_parse.substr(0, 5) == "read="){
        process->read = atof(line_to_parse.substr(5, line_to_parse.length()).c_str());
    }
    else if(line_to_parse.substr(0, 7) == "enable="){
        process->enable = atoi(line_to_parse.substr(7, line_to_parse.length()).c_str());
    }
    else if(line_to_parse.substr(0, 4) == "exp="){
        process->exp = atof(line_to_parse.substr(4, line_to_parse.length()).c_str());
    }
    else if(line_to_parse.substr(0, 12) == "slow_factor="){
        process->slow_factor = atoi(line_to_parse.substr(12, line_to_parse.length()).c_str());
    }
    else if(line_to_parse.substr(0, 12) == "event_start="){
        process->event_start = atoi(line_to_parse.substr(12, line_to_parse.length()).c_str());
    }
    else if(line_to_parse.substr(0, 11) == "event_stop="){
        process->event_stop = atoi(line_to_parse.substr(11, line_to_parse.length()).c_str());
    }
    
    return true;
}



void ArgsParser::initDataObjects(){
    cpu = new ArgsCPU();
    ram = new ArgsRAM();
    hd = new ArgsHD();
    sim = new ArgsSIM();
    web_server = new ArgsWebServer();
    web_server->query = new ArgsWebServerQuery();
    database = new ArgsDatabase();
    database->query = new ArgsDatabaseQuery();
    process = new ArgsProcess();    
}
