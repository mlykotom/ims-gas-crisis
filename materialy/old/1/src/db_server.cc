#include "db_server.h"

DbServer::DbServer(Ram *ram, HardDisk *hd, double buf_size, int max_connect) {
  p_ram = ram;
  p_hd = hd;
  database_name_ = string("DATABASE");
  fac_db = new Facility(database_name_.c_str());
  max_buffer_size = buf_size;
  actual_buffer_size = 0.0;
  max_connections = max_connect;
}

DbServer::~DbServer() {
  delete fac_db;
}

void DbServer::Log() {
  fac_db->Output();
}

void DbServer::Init(CpuProcess *proc, double max_buffer) {
  // smazani operace
  proc->vec_op->erase(proc->vec_op->begin());

  max_buffer_size = max_buffer;
//  TOperation op = {RAM, max_buffer_size};
//  proc->vec_op->push_back(op);

  // inicializacni alokace pameti databaze, neni svazana s zadnym procesem
  proc->p_cpu->p_ram->RamAlloc(max_buffer_size, NULL);

  cout.width(10); cout << Time; cout.width(8); cout << " PID: "; cout.width(3); cout << proc->pid << " $ DB INIT: \t" << max_buffer_size << endl;
}

void DbServer::Query(CpuProcess *proc, int locality, double size) {
  if (proc->vec_op->size() == 0) {
    cout << "CHYBA: DbServer::Query    proc->vec_op->size() == 0   nelze odmazat operaci" << endl;
    proc->Debug();
//    exit(-1);
  }
  // smazani operace
  proc->vec_op->erase(proc->vec_op->begin());

  fac_db->Seize(proc);
  proc->db_request_delay = Time;    // uloz cas startu procesu

  vector<struct Operation>::iterator it;

  TOperation op_ram = {RAM, size};
  TOperation op_hd = {READ, size};
  TOperation op_cpu = {CPU, glob_sim_args->database->query->cycles};
  TOperation op_db_done = {DB_QUERY_DONE, 0.0};
  
  // nactou se data z bufferu?
  if (TryBuffer_(locality)) { // ano, ram access
    cout.width(10); cout << Time; cout.width(8); cout << " PID: "; cout.width(3); cout << proc->pid << " $ DB BUFF: \t" << size << endl;
    it = proc->vec_op->begin();
    proc->vec_op->insert(it, op_db_done);
    if (proc->processType == WEBSERVER) {
      proc->webServerProcessBehavior->addToFrontOperation(NONE);
    }
    it = proc->vec_op->begin();
    proc->vec_op->insert(it, op_cpu);
    if (proc->processType == WEBSERVER) {
      proc->webServerProcessBehavior->addToFrontOperation(NONE);
    }
    it = proc->vec_op->begin();
    proc->vec_op->insert(it, op_ram);
    if (proc->processType == WEBSERVER) {
      proc->webServerProcessBehavior->addToFrontOperation(NONE);
    }
  } else { // ne, cteni z disku, uvolneni tolik nejstarsich dat v bufferu, aby se tam vesla nova data
    cout.width(10); cout << Time; cout.width(8); cout << " PID: "; cout.width(3); cout << proc->pid << " $ DB DISK: \t" << size << endl;
    WriteToBuffer_(locality, size);
    it = proc->vec_op->begin();
    proc->vec_op->insert(it, op_db_done);
    if (proc->processType == WEBSERVER) {
      proc->webServerProcessBehavior->addToFrontOperation(NONE);
    }
    it = proc->vec_op->begin();
    proc->vec_op->insert(it, op_cpu);
    if (proc->processType == WEBSERVER) {
      proc->webServerProcessBehavior->addToFrontOperation(NONE);
    }
    it = proc->vec_op->begin();
    proc->vec_op->insert(it, op_hd);
    if (proc->processType == WEBSERVER) {
      proc->webServerProcessBehavior->addToFrontOperation(NONE);
    }
    it = proc->vec_op->begin();
    proc->vec_op->insert(it, op_ram);
    if (proc->processType == WEBSERVER) {
      proc->webServerProcessBehavior->addToFrontOperation(NONE);
    }
  }

  fac_db->Release(proc);
}

bool DbServer::TryBuffer_(int locality) {
  unsigned size = buffer_.size();
  for (unsigned i = 0; i < size; i++) {
    if (buffer_[i].locality == locality) {
      // data nalezena, posunem obcerstvime zivotnost pozadovanych dat, dame je na konec vectoru
      buffer_.push_back(buffer_[i]);
      buffer_.erase(buffer_.begin() + i);
      return true;
    }
  }
  return false;
}

bool DbServer::CompactBuffer_(double needed_space) {
  if (needed_space > max_buffer_size) { // pokud jsou data vetsi nez je kapacita bufferu, tak nic neuvolnuj
    return false;
  }
  while (max_buffer_size - actual_buffer_size < needed_space) { // uvolnuj ze zacatku (nejstarsi) data, dokud nebude uvolneno dost misto pro nove data
    actual_buffer_size -= buffer_.front().data_size;
    buffer_.erase(buffer_.begin());
  }
  return true;
}

void DbServer::WriteToBuffer_(int locality, double data_size) {
  if (CompactBuffer_(data_size)) { // buffer vyprazdnil stare data a je pripraven pro zapis novych
    actual_buffer_size += data_size;
    TDbBuffer new_item = {locality, data_size};
    buffer_.push_back(new_item);
  }
}

//// InitDbProcessGenerator

InitDbProcessGenerator::InitDbProcessGenerator(Cpu *cpu, double max_buffer_size) {
  p_cpu_ = cpu;
  max_buffer = max_buffer_size;
  Activate();
}

InitDbProcessGenerator::~InitDbProcessGenerator() {

}

void InitDbProcessGenerator::Behavior() {
  vector<Operation> *my_process_description = new vector<Operation>;
  TOperation init_op = {DB_INIT, max_buffer}; // Vychozi velikost max_buffer_size byva 128 MB
  my_process_description->push_back(init_op);
  CpuProcess *p = new CpuProcess(p_cpu_, my_process_description, DB_INIT);
  p->processType = DB_INIT;
  string n = string("INIT_DB");
  p->SetName(&n);
}

//// DbServerRequestGenerator

DbServerRequestGenerator::DbServerRequestGenerator(Cpu *cpu) {
  p_cpu_ = cpu;
  Activate();
}

DbServerRequestGenerator::~DbServerRequestGenerator() {

}

void DbServerRequestGenerator::Behavior() {
  vector<Operation> *my_process_description = new vector<Operation>;
  int locality = static_cast<int>(Normal(100.0, glob_sim_args->database->query->locality));
  TOperation db_request = {DB_QUERY, glob_sim_args->database->query->size, locality}; // default 5 KB dat
  my_process_description->push_back(db_request);
  // vytvor proces na cpu
  CpuProcess *p = new CpuProcess(p_cpu_, my_process_description, DB_QUERY);
  p->processType = DB_QUERY;

  if (glob_sim_args->database->query->event_start < Time && Time < glob_sim_args->database->query->event_stop) {
    // naplanuj vytvoreni dalsiho procesu s faktorem zpomaleni (zrychleni)
    Activate(Time + Exponential(glob_sim_args->database->exp) * glob_sim_args->database->query->slow_factor);
  } else {
    Activate(Time + Exponential(glob_sim_args->database->exp));
  }
}


