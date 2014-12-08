/**
** IMS - Modelovani a simulace
**
** projekt: Plynova krize v Evrope
** autori:	Jakub Tutko, xtutko00@stud.fit.vutbr.cz
**			Tomas Mlynaric, xmlyna06@stud.fit.vutbr.cz
** rok:		2014/2015
**/

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
	std::string ShowError(std::string errorMsg, std::string caption = "");

	/**
	* Cte soubor ze slozky ./config/ a vrati jako string
	* @param std::string fileName
	* @return std::string
	*/
	std::string ReadWholeFile(std::string fileName, std::string fileExtension = "");
}