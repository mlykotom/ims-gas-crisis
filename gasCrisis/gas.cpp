#include <stdexcept>
#include <string>
#include <iostream>
#include <fstream>
#include <streambuf>

#include "json.h"
#include "consts.h"
#include "errors.h"
#include "inout.h"

#include "date_time.h"
#include "pipe.h"
#include "state.h"
#include "timer.h"

cTimer * ParseConfig(std::string fileName, cLogger &logger){
	// --------------------------- deserializace konfigurace
	json::Value cfg_data = json::Deserialize(inout::ReadWholeFile(fileName));

	// --------------------------- overeni zda je prvni objekt 
	if (cfg_data.GetType() != json::ObjectVal) throw PrgException(consts::E_CFG_FILE_FORMAT);

	// --------------------------- hlavni objekt configu
	json::Object objMain = cfg_data.ToObject();

	// --------------------------- pokud nejsou potrebne sekce - error
	if (objMain.HasKeys(consts::cfgReqParams) != -1) throw PrgException(consts::E_CFG_SECTION);

	// --------------------------- objekt casu z configu
	json::Value valTimer = objMain["Timer"];
	if (valTimer.GetType() != json::ObjectVal) throw PrgException(consts::E_CFG_SECTION);

	// ziskani objektu start a end casu
	json::Value dateStart = valTimer["dateStart"], dateEnd = valTimer["dateEnd"];

	// overeni zda dateStart + dateEnd ma potrebne parametry
	if (dateStart.HasKeys(consts::cfgDateParams) != -1 || dateStart.HasKeys(consts::cfgDateParams) != -1) throw PrgException(consts::E_CFG_TIMER_MISSING_PARAM);

	// vytvoreni + alokovani timeru
	cTimer *timer = new cTimer(dateStart["year"].ToInt(), dateStart["month"].ToInt(), dateStart["day"].ToInt(), dateEnd["year"].ToInt(), dateEnd["month"].ToInt(), dateEnd["day"].ToInt());

	// -------------------------------------------------------
	// --------------------------- nacteni statu
	// -------------------------------------------------------
	json::Array states = objMain["Countries"].ToArray(); // TODO nejake osetreni pole?
	// TODO - nemely by v configu byt alespon nejake staty?
	for (auto st : states){
		if (st.HasKeys(consts::cfgStateParams) != -1) throw PrgException(consts::E_CFG_STATE_MISSING_PARAM);
		cState *country;

		if (st["storageDefaultValue"].ToDouble() > st["storageCapacity"].ToDouble()) throw PrgException(consts::E_CFG_STORAGE_MISMATCH);

		// vytvoreni fake statu pokud je nastaven parametr
		if (st["fake"].GetType() == json::BoolVal && st["fake"].ToBool() == true){
			country = new cFakeState(st["name"].ToString(), logger, st["consumptSumm"].ToDouble(), st["consumptWint"].ToDouble(), st["storageDefaultValue"].ToDouble(), st["storageCapacity"].ToDouble(), st["storageMaxWithdraw"].ToDouble(), st["storageMaxStore"].ToDouble(), st["production"].ToDouble());
		}
		// jinak vytvori normalni stat
		else{
			country = new cState(st["name"].ToString(), logger, st["consumptSumm"].ToDouble(), st["consumptWint"].ToDouble(), st["storageDefaultValue"].ToDouble(), st["storageCapacity"].ToDouble(), st["storageMaxWithdraw"].ToDouble(), st["storageMaxStore"].ToDouble(), st["production"].ToDouble());
		}
		
		// prida stat do timeru
		timer->addState(country);
	}

	// -------------------------------------------------------
	// --------------------------- nacteni potrubi
	// -------------------------------------------------------
	json::Array pipes = objMain["Pipes"].ToArray(); // TODO nejake osetreni pole?
	for (auto p : pipes){
		if (p.HasKeys(consts::cfgPipeParams) != -1) throw PrgException(consts::E_CFG_PIPE_MISSING_PARAM);

		cState *stateFrom = timer->getState(p["from"].ToString());
		cState *stateTo = timer->getState(p["to"].ToString());
		
		// kontrola zda oba staty existuji
		if (stateFrom == nullptr || stateTo == nullptr) throw PrgException(consts::E_CFG_PIPE_MISSING_STATE);

		cPipe *pipe = new cPipe(5, stateFrom->getName(), stateTo->getName(), (unsigned)p["length"].ToInt(), p["flowSummer"].ToDouble(), p["flowWinter"].ToDouble());
		stateFrom->addPipelineOut(pipe);
		stateTo->addPipelineIn(pipe);
	}

	return timer;
}


int main(int argc, char * argv[]) {
	try{
		std::string fileName("cfg.json");
		// ------------ osetreni parametru
		switch (argc){
			case 2:
				fileName = std::string(argv[1]);
			case 1:
				break;

			default:
				throw PrgException(consts::E_PRG_PARAMS);
		}
		
		cLogger logger;

		// ------------ overeni + parsovani configu
		cTimer *timer = ParseConfig(fileName, logger);

		for (auto par : timer->getAllStates()){
			par.second->printInfo();
		}

		timer->start();

	}
	catch (std::runtime_error &rExc){
		// todo nejak lepe osefovat hlasky z json parseru?
		inout::ShowError(rExc.what(), "Chyba za behu programu");
	}
	catch (PrgException &pExc){
		inout::ShowError(pExc.showError(), pExc.what());
	}
	catch (std::exception &exc){
		std::cerr << exc.what() << std::endl;
	}
	
	return 0;
}