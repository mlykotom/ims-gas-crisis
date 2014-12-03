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

/**
 * Nacteni souboru ze slozky ./config/
 * @param std::string fileName 
 * @param cLogger &logger
 * @return cTimer *
 */
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

	// overeni datum_start < datum_end
	if ((dateStart["year"].ToInt() + dateStart["month"].ToInt() + dateStart["day"].ToInt()) > (dateEnd["year"].ToInt() + dateEnd["month"].ToInt() + dateEnd["day"].ToInt())) throw PrgException(consts::E_CFG_TIMER_MISMATCH);

	// vytvoreni + alokovani timeru
	cTimer *timer = new cTimer(dateStart["year"].ToInt(), dateStart["month"].ToInt(), dateStart["day"].ToInt(), dateEnd["year"].ToInt(), dateEnd["month"].ToInt(), dateEnd["day"].ToInt());

	// -------------------------------------------------------
	// --------------------------- nacteni statu
	// -------------------------------------------------------
	if (objMain["Countries"].GetType() != json::ArrayVal) throw PrgException(consts::E_CFG_STATE_SECTION_PARAM);
	json::Array states = objMain["Countries"].ToArray();
	unsigned stateCount = 0;
	for (auto st : states){
		// jestli jsou vsechny povinne parametry
		if (st.HasKeys(consts::cfgStateParams) != -1) throw PrgException(consts::E_CFG_STATE_MISSING_PARAM);
		
		// overeni, aby vsechny hodnoty byly >= 0
		for (auto constPar : consts::cfgStateParams){
			if (constPar == "name") continue;
			// kazdy parametr statu musi byt >= 0
			if (st[constPar].ToDouble() < 0.0) throw PrgException(consts::E_CFG_PARAM_LOW);
		}

		// overeni, aby vychozi hodnota nebyla vetsi nez max kapacita zasobniku
		if (st["storageDefaultValue"].ToDouble() > st["storageCapacity"].ToDouble()) throw PrgException(consts::E_CFG_TIMER_MISMATCH);

		// overeni, ze ukladani / tezeni je mensi nez kapacita
		if (st["storageMaxWithdraw"].ToDouble() > st["storageCapacity"].ToDouble() || st["storageMaxStore"].ToDouble() > st["storageCapacity"].ToDouble()) throw PrgException(consts::E_CFG_STORAGE_MISMATCH);

		cState *country;
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
		stateCount++;
	}

	// overeni poctu statu
	if (stateCount == 0) throw PrgException(consts::E_CFG_STATE_NONE);

	// -------------------------------------------------------
	// --------------------------- nacteni potrubi
	// -------------------------------------------------------
	if (objMain["Pipes"].GetType() != json::ArrayVal) throw PrgException(consts::E_CFG_PIPE_SECTION_PARAM);
	json::Array pipes = objMain["Pipes"].ToArray(); // TODO nejake osetreni pole?
	for (auto p : pipes){
		if (p.HasKeys(consts::cfgPipeParams) != -1) throw PrgException(consts::E_CFG_PIPE_MISSING_PARAM);

		// parametry musi byt >= 0
		if (p["length"].ToInt() < 0 || p["flowSummer"].ToDouble() < 0 || p["flowWinter"].ToDouble() < 0) throw PrgException(consts::E_CFG_PARAM_LOW);

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

		// zacatek simulace
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
	
	// TODO delete timer

	return 0;
}