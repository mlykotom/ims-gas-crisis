#include "web_server.h"
//#include "cpu_process.h"
//#include "global.h"

/**
 * REALNE DATA PRO APACHE2 - classic preforked version
 * 
 * sudo /etc/init.d/apache2 restart
 * Velikost binarky na disku:   1.8 MB HDD/SSD
 * Velikost hlavniho procesu:   2.8 MiB RAM
 * Velikost child procesu:      2.8 MiB RAM
 * Velikost child procesu:      1.1 MiB RAM
 */

using namespace std;

WebServer::WebServer(Cpu * cpu, int _maxServers, int _maxFreeServers, int _minFreeServers) {
    cpu_pointer = cpu;
    incomingRequests = new list<WebServerRequest*>();
    maxServers = _maxServers;
    maxFreeServers = _maxFreeServers;
    minFreeServers = _minFreeServers;
    idleServers = 0;
    runningServers = 0;
    serversToBeCreated = 0;
    incomingWebRequests = 0;
    servedWebRequests = 0;
    hisWebRequestSize = new Histogram("web request size (KB)", 0.0, 100.0, 20.0);
//  his_hd = new Histogram("his_hd", 0.0, 1e6, 30e6);
    
    cpu->p_ram->RamAlloc(glob_sim_args->web_server->init_size, NULL);
//    cpu->p_ram->RamAlloc(2800000, NULL);
    
//    WebServerProcessBehavior * master_behavior = new WebServerProcessBehavior();
//    vector<Operation> *master_op = new vector<Operation>;
//    consoliding_process = new CpuProcess(cpu_pointer, master_op, false, WEBSERVER_MASTER, 2000000);
//    consoliding_process->webServerProcessBehavior = master_behavior;
//    consoliding_process->name = "WS consolidation";
//    consoliding_process->processType = WEBSERVER_MASTER;
    activate_master_process = true;

    // pri startu pocitace se musi Web Server prvni spustit
    WebServerProcessBehavior * behavior = new WebServerProcessBehavior();
    vector<Operation> *prefork_server_process = new vector<Operation>;
    consoliding_process = NULL;
    
    
    
    TOperation tmp_ram = {RAM, 2800000.0}; // 2.8MB
    TOperation tmp_disk = {READ, 1800000.0}; // 1.8MB
    TOperation tmp_cpu = {CPU, 500000}; // 0.5M cyklu
    prefork_server_process->push_back(tmp_ram);
    behavior->addOperation(ALLOC_RAM_PERMANENTLY);
    prefork_server_process->push_back(tmp_disk);
    behavior->addOperation(NONE);
    prefork_server_process->push_back(tmp_cpu);
    behavior->addOperation(INIT_SERVER);
    CpuProcess * tmp_cpu_process = new CpuProcess(cpu_pointer, prefork_server_process, false, WEBSERVER, 5000000);
    tmp_cpu_process->processType = WEBSERVER;
    tmp_cpu_process->webServerProcessBehavior = behavior;
    tmp_cpu_process->name = "WS init";
    
    
    tmp_cpu_process->Activate();
    
    
}

WebServer::~WebServer() {
  delete hisWebRequestSize;
}

void WebServer::webServerIsInitialized() {
    // nyni doslo k inicializaci serveru
    consilideIdleServers(); // predforkuji si nejake thready
    new WebRequestsGenerator(this);
}

void WebServer::consilideIdleServers() {
//    vector<Operation> * prefork_server_process = NULL;
//    WebServerProcessBehavior * behavior = NULL;
//    bool new_created = false;
    if(consoliding_process == NULL){
        WebServerProcessBehavior * master_behavior = new WebServerProcessBehavior();
        vector<Operation> *master_op = new vector<Operation>;
        consoliding_process = new CpuProcess(cpu_pointer, master_op, false, WEBSERVER_MASTER, 2000000);
        consoliding_process->webServerProcessBehavior = master_behavior;
        consoliding_process->name = "WS consolidation";
        consoliding_process->processType = WEBSERVER_MASTER;
        activate_master_process = true;
    }
    while ((((serversToBeCreated + idleServers) < minFreeServers)) && ((serversToBeCreated + idleServers + runningServers) < maxServers)) { //pokud je nedostatek predforkovanych serveru a neprekrocim celkovy limit

        
        TOperation aloc = {ALLOC, glob_sim_args->web_server->process_size}; // 2.8MB
        TOperation ram = {RAM, 500000.0}; // 2.8MB
        TOperation disk = {READ, 0.0}; // 3MB
        TOperation cpu = {CPU, 500000}; // 0.5M cyklu
        
        
        consoliding_process->vec_op->push_back(aloc);
        consoliding_process->webServerProcessBehavior->addOperation(ALLOC_RAM_TEMP);
        
        consoliding_process->vec_op->push_back(ram);
        consoliding_process->webServerProcessBehavior->addOperation(NONE);
        
        consoliding_process->vec_op->push_back(disk);
        consoliding_process->webServerProcessBehavior->addOperation(NONE);
        
        consoliding_process->vec_op->push_back(cpu);
        consoliding_process->webServerProcessBehavior->addOperation(CREATE_IDLE_SERVER);
        
//        prefork_server_process->push_back(aloc);
//        behavior->addOperation(ALLOC_RAM_TEMP);
//        prefork_server_process->push_back(ram);
//        behavior->addOperation(NONE);
//        prefork_server_process->push_back(disk);
//        behavior->addOperation(NONE);
//        prefork_server_process->push_back(cpu);
//        behavior->addOperation(CREATE_IDLE_SERVER); // rekne se web serveru, ze si ma inkrementovat pocet idle procesu
        serversToBeCreated++;
        //incomingWebRequests--;
    }
    while ((idleServers) > maxFreeServers) { // pokud potrebuji ubrat par serveru
        TOperation ram = {RAM, 2000.0}; // 0.002MB
        TOperation disk = {READ, 0.0}; // 3MB
        TOperation cpu = {CPU, 50000}; // 0.05M cyklu
        TOperation dealoc = {FREE, glob_sim_args->web_server->process_size}; // 0.05M cyklu
        
        consoliding_process->vec_op->push_back(ram);
        consoliding_process->webServerProcessBehavior->addOperation(NONE);
        
        consoliding_process->vec_op->push_back(disk);
        consoliding_process->webServerProcessBehavior->addOperation(NONE);
        
        consoliding_process->vec_op->push_back(cpu);
        consoliding_process->webServerProcessBehavior->addOperation(NONE);
        
        consoliding_process->vec_op->push_back(dealoc);
        consoliding_process->webServerProcessBehavior->addOperation(KILL_PROCESS);
        
//        prefork_server_process->push_back(ram);
//        behavior->addOperation(NONE);
//        prefork_server_process->push_back(disk);
//        behavior->addOperation(NONE);
//        prefork_server_process->push_back(cpu);
//        behavior->addOperation(NONE);
//        prefork_server_process->push_back(dealoc);
//        behavior->addOperation(KILL_PROCESS); // nic nebudeme delat, process bude killnut
        idleServers--;
    }

    
    if (activate_master_process == true) { 
        activate_master_process = false;
        consoliding_process->Activate();
    }
}

void WebServer::acceptNewRequest(WebServerRequest * _webRequest) {
    incomingWebRequests++;
    if(incomingRequests->size() > static_cast<unsigned int>(glob_sim_args->web_server->buffer_size)){
        return;
    }
    (*hisWebRequestSize)(_webRequest->page_size/1e3);
    if (idleServers > 0) { // pokud mam jeste nejake volne servery
        idleServers--;
        runningServers++;

        WebServerProcessBehavior * behavior = new WebServerProcessBehavior();
        vector<Operation> *my_process_description = new vector<Operation>;
        TOperation a = {RAM, _webRequest->page_size}; // 2.8MB
        TOperation b = {READ_FROM_DB, _webRequest->page_size}; // tato operace predava velikost stranky do DB_QUERY
        TOperation c = {CPU, _webRequest->cycles_to_perform};
        my_process_description->push_back(a);
        behavior->addOperation(SERVER_IS_RUNNING); // rekne se Web Serveru, ze jeden process presel z IDLE stavu do stavu RUNNING
        my_process_description->push_back(b);
        behavior->addOperation(CALL_DB); //misto cteni disku si zavolam databazi
        my_process_description->push_back(c);
        behavior->addOperation(RETURN_IDLE_SERVER); // po provedeni vseho mozneho vratime process k recyklaci

        CpuProcess * tmp_cpu_process = new CpuProcess(cpu_pointer, my_process_description, false, WEBSERVER, 2000000);
//        tmp_cpu_process->processType = WEBSERVER;
        tmp_cpu_process->webServerProcessBehavior = behavior;
        tmp_cpu_process->name = "WS accrept request";
        if(incomingRequests == 0){
            cout << "Incoming request < 0\n";
        }
//        incomingWebRequests--;
        tmp_cpu_process->Activate(); // zarad do CPU
    } else { // pokud nejsou servery volne, tak zapocni konsolidaci
        incomingRequests->push_back(_webRequest);
        //delete _webRequest;
        consilideIdleServers();
    }
}

void WebServer::returnServerFromCPU() {
    //if ((idleServers + serversToBeCreated + runningServers) < maxServers) { // pokud to je vubec mozne, tak pridej server jako IDLE
        idleServers++;
    //}
    servedWebRequests++;
    if(runningServers == 0){
        cout << "Runing servers < 0\n";
      //  exit(1);
    }
    runningServers--;
    if (incomingRequests->size() > 0) { // pokud jsou ve fronte pozadavky ktere jeste nemohly byt obslouzeny, tak z tama jeden odeberu
            WebServerRequest *_webRequest = incomingRequests->front();
            incomingRequests->pop_front();

            WebServerProcessBehavior * behavior = new WebServerProcessBehavior();
            vector<Operation> *my_process_description = new vector<Operation>;
            TOperation a = {RAM, _webRequest->page_size}; // 2.8MB
            TOperation b = {READ_FROM_DB, _webRequest->page_size}; // tato operace predava velikost stranky do DB_QUERY
            TOperation c = {CPU, _webRequest->cycles_to_perform};
            my_process_description->push_back(a);
            behavior->addOperation(SERVER_IS_RUNNING); // rekne se Web Serveru, ze jeden process presel z IDLE stavu do stavu RUNNING
            my_process_description->push_back(b);
            behavior->addOperation(CALL_DB); //misto cteni disku si zavolam databazi
            my_process_description->push_back(c);
            behavior->addOperation(RETURN_IDLE_SERVER); // po provedeni vseho mozneho vratime process k recyklaci

            CpuProcess * tmp_cpu_process = new CpuProcess(cpu_pointer, my_process_description, false, WEBSERVER, 2000000);
//            tmp_cpu_process->processType = WEBSERVER;
            tmp_cpu_process->webServerProcessBehavior = behavior;
            tmp_cpu_process->name = "WS served request";
            if(idleServers == 0){
                cout << "idle servers < 0\n";
            }
/*            if(incomingWebRequests == 0){
                cout << "incoming Web Requests < 0\n";
            }*/
            idleServers--;
            runningServers++;
            tmp_cpu_process->Activate(); // zarad do CPU
        }
    consilideIdleServers();
}

void WebServer::anotherServerIsRunning(){
//    idleServers--;
//    runningServers++;
}

int WebServer::getIdleServersCnt() {
  return idleServers;
}

int WebServer::getRunningServersCnt() {
  return runningServers;
}

int WebServer::getIncomingBufferSize() {
  return static_cast<int>(incomingRequests->size());
}

void WebServer::Log() {
  cout << "Celkem obslouzenych webovych pozadavku: " << servedWebRequests << endl;
  cout << "Pocet prichozich webovych pozadavku: " << incomingWebRequests << endl;
  hisWebRequestSize->Output();
}

void WebServer::idleServerCreated() {
   // if ((idleServers + runningServers + serversToBeCreated) < maxServers) { // pokud to je vubec mozne, tak pridej server jako IDLE
        idleServers++;
        if(serversToBeCreated == 0){
            cout << "Servers to be created < 0\n";
        }
        serversToBeCreated--;
        if (incomingRequests->size() > 0) { // pokud jsou ve fronte pozadavky ktere jeste nemohly byt obslouzeny, tak z tama jeden odeberu
            WebServerRequest *_webRequest = incomingRequests->front();
            incomingRequests->pop_front();

            WebServerProcessBehavior * behavior = new WebServerProcessBehavior();
            vector<Operation> *my_process_description = new vector<Operation>;
            TOperation a = {RAM, _webRequest->page_size}; // 2.8MB
            TOperation b = {READ_FROM_DB, _webRequest->page_size}; // tato operace predava velikost stranky do DB_QUERY
            TOperation c = {CPU, _webRequest->cycles_to_perform};
            my_process_description->push_back(a);
            behavior->addOperation(SERVER_IS_RUNNING); // rekne se Web Serveru, ze jeden process presel z IDLE stavu do stavu RUNNING
            my_process_description->push_back(b);
            behavior->addOperation(CALL_DB); //misto cteni disku si zavolam databazi
            my_process_description->push_back(c);
            behavior->addOperation(RETURN_IDLE_SERVER); // po provedeni vseho mozneho vratime process k recyklaci

            CpuProcess * tmp_cpu_process = new CpuProcess(cpu_pointer, my_process_description, false, WEBSERVER, 2000000);
//            tmp_cpu_process->processType = WEBSERVER;
            tmp_cpu_process->webServerProcessBehavior = behavior;
            tmp_cpu_process->name = "WS served request";
            if(idleServers == 0){
                cout << "idle servers < 0\n";
            }
/*            if(incomingWebRequests == 0){
                cout << "incoming Web Requests < 0\n";
            }*/
            idleServers--;
            runningServers++;
            tmp_cpu_process->Activate(); // zarad do CPU
        }
    //}
    consilideIdleServers();
}

/**
 * Generator prichodu pozadavku na webovy server.
 * @param web_server
 */

WebRequestsGenerator::WebRequestsGenerator(WebServer *web_server) {
    web_server_pointer = web_server;
    Activate();
}

WebRequestsGenerator::~WebRequestsGenerator() {

}

void WebRequestsGenerator::Behavior() {
    double page = Normal(0, glob_sim_args->web_server->query->page_size);
    if(page < 0.0){
        page = page*(-1);
    }
    if(page < (glob_sim_args->web_server->query->page_size/10.0)){
        page = glob_sim_args->web_server->query->page_size/10.0;
    }
    else if(page > (glob_sim_args->web_server->query->page_size*10.0)){
        page = glob_sim_args->web_server->query->page_size*10.0;
    }
//    cout << "DEBUG::WebRequestGenerator::Behavior" << endl;    
//    cout << "page: " << page << endl;
//    cout << "cycles: " << glob_sim_args->web_server->query->cycles << endl;
//    cout << "page_size: " << page * glob_sim_args->web_server->query->cycles << endl;
    if (glob_sim_args->web_server->query->fixed_page_size == 1) {
      web_server_pointer->acceptNewRequest(new WebServerRequest(glob_sim_args->web_server->query->page_size * glob_sim_args->web_server->query->cycles, 1, glob_sim_args->web_server->query->page_size));
    } else {
      web_server_pointer->acceptNewRequest(new WebServerRequest(page*glob_sim_args->web_server->query->cycles, 1, page));
    }

    if (glob_sim_args->web_server->query->event_start < Time && Time < glob_sim_args->web_server->query->event_stop) {
      // naplanuj vytvoreni dalsiho procesu s faktorem zpomaleni (zrychleni)
      Activate(Time + Exponential(glob_sim_args->web_server->exp * glob_sim_args->web_server->query->slow_factor));
    } else {
      Activate(Time + Exponential(glob_sim_args->web_server->exp));
    }
}

WebServerRequest::WebServerRequest(double _cycles_to_perform, double _database_requests, double _page_size) {
    cycles_to_perform = _cycles_to_perform;
    database_requests = _database_requests;
    page_size = _page_size;
}

WebServerRequest::~WebServerRequest() {
}

WebServerProcessBehavior::WebServerProcessBehavior() {
    operations = new list<int>();
}

WebServerProcessBehavior::WebServerProcessBehavior(list<int>* listOfOperations) {
    operations = listOfOperations;
}

WebServerProcessBehavior::~WebServerProcessBehavior() {
    delete operations;
}

int WebServerProcessBehavior::operationPerformed(int operation) {
    int toReturn = operations->front();
    if(operations->size() > 0){
//        cout << "OP size >> " << operations->size() <<"\n";
        operations->pop_front();
    }
    else{
//        cout << "Operation list empty\n";
    }
    return toReturn;
}

void WebServerProcessBehavior::addOperation(int operation) {
    operations->push_back(operation); // prida dalsi operaci v poradi
}
void WebServerProcessBehavior::addToFrontOperation(int operation) {
    operations->push_front(operation); // prida dalsi operaci v poradi            
}
