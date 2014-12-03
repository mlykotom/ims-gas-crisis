#ifndef _CONSTS_H_
#define _CONSTS_H_

#include <string>
#include <map>
#include <vector>

#define NOTHROW throw()

#define DEBUG false

// zmena na casovy  generator misto std::random_device
#define TIME_RANDOM_GENERATOR false

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
		E_CFG_TIMER_MISMATCH,
		E_CFG_PARAM_LOW,
		E_CFG_STATE_SECTION_PARAM,
		E_CFG_STATE_NONE,
		E_CFG_TIMER_MISSING_PARAM,
		E_CFG_STATE_MISSING_PARAM,
		E_CFG_STORAGE_MISMATCH,

		E_CFG_DUPLICATE_STATES,
		E_CFG_PIPE_SECTION_PARAM,
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
		{ E_CFG_FILE_OPEN, 				"[CONFIG] Nelze otevrit soubor" },
		{ E_CFG_FILE_FORMAT, 			"[CONFIG] spatny format JSON" },
		{ E_CFG_SECTION, 					"[CONFIG] Chybi pozadovana sekce" },
		{ E_CFG_STATE_SECTION_PARAM,	"[CONFIG][COUNTRIES] Hodnota musi byt pole" },
		{ E_CFG_PIPE_SECTION_PARAM,	"[CONFIG][PIPES] Hodnota musi byt pole" },


		{ E_CFG_PARAM_LOW,				"[CONFIG] Hodnota parametru musi byt >= 0" },

		{ E_CFG_TIMER_MISSING_PARAM,	"[CONFIG][TIMER] Chybejici parametr" },
		{ E_CFG_TIMER_MISMATCH,			"[CONFIG][TIMER] Datum konce musi byt pozdeji nez startu" },
		{ E_CFG_STATE_MISSING_PARAM, "[CONFIG][COUNTRY] Chybejici parametr" },

		{ E_CFG_STATE_NONE,				"[CONFIG][COUNTRIES] Neni definovan zadny stat" },
		{ E_CFG_DUPLICATE_STATES,		"[CONFIG][COUNTRIES] Vice statu se stejnym nazvem" },

		{ E_CFG_STORAGE_MISMATCH,		"[CONFIG][COUNTRY] Mensi kapacita skladu nez hodnota" },

		{ E_CFG_PIPE_MISSING_PARAM,	"[CONFIG][PIPES] Chybejici parametr" },
		{ E_CFG_PIPE_MISSING_STATE,	"[CONFIG][PIPES] Chybi stat, pro ktery je vytvoreno" },
		
	};
}

#endif