#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "errors.h"
#include "consts.h"

namespace inout{
	/**
	* Vypise chybu dle formatu
	* @param string errorMsg - hlaska k vypsani
	* @param string caption  - zahlavi chyby
	* @return string cela hlaska
	**/
	std::string ShowError(std::string errorMsg, std::string caption = ""){
		std::ostringstream errOut;

		if (!caption.empty()){
			errOut << std::string(consts::defaultSizeOfPrint, '-') << std::endl;
			errOut << caption << std::endl;
		}

		errOut << std::string(consts::defaultSizeOfPrint, '-') << std::endl;
		errOut << errorMsg << std::endl;
		errOut << std::string(consts::defaultSizeOfPrint, '-') << std::endl;

		std::cerr << errOut.str();

		return errOut.str();
	}

	/**
	* Cte soubor ze slozky ./config/ a vrati jako string
	* @param std::string fileName
	* @return std::string
	*/
	std::string ReadWholeFile(std::string fileName){
		std::ifstream file(consts::configFolder + fileName);

		if (!file.is_open()) throw PrgException(consts::E_CFG_FILE_OPEN);

		std::string fileStr;

		file.seekg(0, std::ios::end);
		fileStr.reserve((unsigned)file.tellg());
		file.seekg(0, std::ios::beg);

		fileStr.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

		return fileStr;
	}

}