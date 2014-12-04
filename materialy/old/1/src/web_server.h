#ifndef WEB_SERVER_H_
#define WEB_SERVER_H_

#include <simlib.h>
#include <vector>
#include <string>
#include <iostream>
#include "global.h"
//#include "web_server.h"
//#include "cpu.h"
//#include "cpu_process.h"

class Cpu;
class CpuProcess;

using namespace std;

class WebServerRequest {
public:
    WebServerRequest(double _cycles_to_perform, double _database_requests, double page_size);
    ~WebServerRequest();
    double cycles_to_perform;
    double database_requests;
    double page_size;
private:
};



class WebServer {
 public:  
    WebServer(Cpu * cpu, int maxServers, int maxFreeServers, int minFreeServers);
    ~WebServer();
    void acceptNewRequest(WebServerRequest * _webRequest);
    void webServerIsInitialized(); // zavola se z CPU pokud prvotni process inicializoval server
    void returnServerFromCPU(); // pokud se ma vratit nejaky server. A je jedno jestli z obsluhy webRequestu nebo pri vytvareni nebo 
    void idleServerCreated();  
    void anotherServerIsRunning();  
    int getIdleServersCnt();
    int getRunningServersCnt();
    int getIncomingBufferSize();
    void Log();
//    WebRequestsGenerator * getWebRequestsGenerator();
    int incomingWebRequests;
    int servedWebRequests;
    Histogram *hisWebRequestSize;
    CpuProcess * consoliding_process;
    bool activate_master_process;
    
 private:
     void consilideIdleServers();
     int maxServers;
     int maxFreeServers;
     int minFreeServers;
     int idleServers;
     int runningServers;
     int serversToBeCreated;
     void preforkNewServer();
     void killIdleServer();
     //CpuProcess * masterProcess;
     Cpu * cpu_pointer;
     list<WebServerRequest*> * incomingRequests;
//     WebRequestsGenerator * servers_requests_generator;
     

};

class WebRequestsGenerator : public Event {
 public:
  WebRequestsGenerator(WebServer *web_server);
  ~WebRequestsGenerator();
 private:
  WebServer * web_server_pointer;
  void Behavior();
};

class WebServerProcessBehavior {
public:
    WebServerProcessBehavior();
    WebServerProcessBehavior(list<int> * listOfOperations);
    ~WebServerProcessBehavior();
    int operationPerformed(int operation);
    
    void addOperation(int operation);
    void addToFrontOperation(int operation);
    list<int> * operations;
    
private:
    
};

#endif // WEB_SERVER_H_
