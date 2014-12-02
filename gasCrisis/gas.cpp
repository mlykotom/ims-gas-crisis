#include <stdexcept>
#include <string>
#include <iostream>
#include <fstream>
#include <streambuf>

#include "json.h"
#include "consts.h"
#include "errors.h"
#include "logger.h"
#include "timer.h"


int main(int argc, char * argv[]) {
	try{
		std::string fileName("cfg.json");
		// osetreni parametru
		switch (argc){
			case 2:
				fileName = std::string(argv[1]);
			case 1:
				break;

			default:
				throw PrgException(consts::E_PRG_PARAMS);
		}
		
		// deserializace konfigurace
		json::Value cfg_data = json::Deserialize(inout::ReadWholeFile(fileName));

		// overeni zda je prvni objekt 
		if (cfg_data.GetType() != json::ObjectVal) throw PrgException(consts::E_CFG_FILE_FORMAT);

		// hlavni objekt configu
		json::Object objMain = cfg_data.ToObject();
		// objekt casu z configu
		json::Value valTimer = objMain["Timer"];
		if (valTimer.GetType() != json::ObjectVal) throw PrgException(consts::E_CFG_SECTION);

		if (valTimer["dateTimeStart"].GetType() == json::NULLVal || valTimer["dateTimeEnd"].GetType() == json::NULLVal) throw PrgException(consts::E_CFG_MISSING_PARAM);

		// inicializace timeru
		cTimer timer((unsigned) valTimer["dateTimeStart"].ToInt(), (unsigned) valTimer["dateTimeEnd"].ToInt());

		
		json::Array staty = objMain["Countries"].ToArray();

		for (auto par : staty){
			std::cout << par["name"].ToString() << std::endl;
		}


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