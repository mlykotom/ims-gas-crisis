#ifndef _CONSTS_H_
#define _CONSTS_H_

#include <string>
#include <map>
#include <vector>

#define NOTHROW throw()

#define DEBUG false

namespace consts{
	// vychozi delka ------- ve vypisech
	const unsigned int defaultSizeOfPrint = 50;

	// chybove kody
	enum error_code{
		ALL_OK = 0,
		E_UNKNOWN_EXCEPTION,

		E_PRG_PARAMS,
		E_CFG_FILE_OPEN,
		E_CFG_FILE_FORMAT,
		E_CFG_SECTION,

		E_CFG_TIMER_MISSING_PARAM,
		E_CFG_STATE_MISSING_PARAM,
		E_CFG_STORAGE_MISMATCH,

		E_CFG_DUPLICATE_STATES,
		E_CFG_PIPE_MISSING_PARAM,
		E_CFG_PIPE_MISSING_STATE,
	};

	// povinne parametry configu
	const std::vector<std::string> cfgReqParams = { "Timer", "Countries", "Pipes" };
	// povinne parametry v timeru (dateStart / dateEnd)
	const std::vector<std::string> cfgDateParams = { "year", "month", "day" };
	// povinne parametry statu
	const std::vector<std::string> cfgStateParams = { "name", "production", "consumptSumm", "consumptWint", "storageDefaultValue", "storageCapacity", "storageMaxWithdraw", "storageMaxStore" };
	// povinne parametry potrubi
	const std::vector<std::string> cfgPipeParams = { "from", "to", "length", "flowSummer", "flowWinter" };

	// chybove hlasky programu
	const std::map<error_code, std::string> exceptionCodes = {
		{ ALL_OK, "" },
		{ E_UNKNOWN_EXCEPTION, 			"Vyskytl se neznamy problem" },

		{ E_PRG_PARAMS, 					"Program prijima max 1 parametr" },
		{ E_CFG_FILE_OPEN, 				"Nelze otevrit CONFIG" },
		{ E_CFG_FILE_FORMAT, 			"CONFIG je ve spatnem JSON formatu" },
		{ E_CFG_SECTION, 					"Chybi pozadovana sekce CONFIGU" },

		{ E_CFG_TIMER_MISSING_PARAM,	"Chybejici parametr v sekci Timer" },
		{ E_CFG_STATE_MISSING_PARAM,	"Chybejici parametr v sekci daneho statu" },

		{ E_CFG_DUPLICATE_STATES,		"V CONFIGU je vice statu se stejnym nazvem" },

		{ E_CFG_STORAGE_MISMATCH,		"V CONFIGU je u statu mensi kapacita skladu nez vychozi hodnota" },

		{ E_CFG_PIPE_MISSING_PARAM,	"Chybejici parametr u potrubi" },
		{ E_CFG_PIPE_MISSING_STATE,	"Chybi stat, pro ktery je vytvoreno potrubi" },
		
	};
}

#endif