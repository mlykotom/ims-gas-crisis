#ifndef _CONSTS_H_
#define _CONSTS_H_

#include <string>
#include <map>

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
		E_CFG_MISSING_PARAM,
	};

	// chybove hlasky programu
	const std::map<error_code, std::string> exceptionCodes = {
		{ ALL_OK, "" },
		{ E_UNKNOWN_EXCEPTION, 			"Vyskytl se neznamy problem" },

		{ E_PRG_PARAMS, 					"Program prijima max 1 parametr" },
		{ E_CFG_FILE_OPEN, 				"Nelze otevrit konfiguracni soubor" },
		{ E_CFG_FILE_FORMAT, 			"Konfiguracni soubor je ve spatnem JSON formatu" },
		{ E_CFG_SECTION, 					"Chybejici pozadovana sekce konfiguracniho souboru" },
		{ E_CFG_MISSING_PARAM,			"Chybejici parametr v dane sekci" },
	};
}

#endif