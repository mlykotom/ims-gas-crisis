/**
** IMS projekt
*/

#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

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
		std::ifstream file("./config/" + fileName);

		if (!file.is_open()) throw PrgException(consts::E_CFG_FILE_OPEN);

		std::string fileStr;

		file.seekg(0, std::ios::end);
		fileStr.reserve(file.tellg());
		file.seekg(0, std::ios::beg);

		fileStr.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

		return fileStr;
	}

}


class cLogger
{
public:
	cLogger(void);
	~cLogger(void);

private:
	std::string mFile;

	std::vector<std::string> mStateNames;

	bool mFlowLogs;
	bool mStatLogs;

public:
	void createFlowLog(const std::string& type, const std::string& source, const std::string& destination, double amount);
	void createStatLog(const std::string& type, const std::string& source, const std::string& message);

	void addStateName(const std::string& stateName);

	void setLogFile(const std::string& file);
	void showFlowLogs(bool show);
	void showStatLogs(bool show);
};