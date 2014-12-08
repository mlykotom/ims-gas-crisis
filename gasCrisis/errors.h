/**
** IMS - Modelovani a simulace
**
** projekt: Plynova krize v Evrope
** autori:	Jakub Tutko, xtutko00@stud.fit.vutbr.cz
**			Tomas Mlynaric, xmlyna06@stud.fit.vutbr.cz
** rok:		2014/2015
**/


#ifndef _ERRORS_H_
#define _ERRORS_H_

#include <exception>
#include <stdexcept>
#include "consts.h"

// hlavni trida osetrenych vyjimek pro tento program
class PrgException : public std::exception{
protected:
	// chybovy kod z enumu kodu
	consts::error_code codeType;
public:
	
	virtual consts::error_code getCode() { return codeType; }
	PrgException(consts::error_code exc) : codeType(exc){}

	virtual const char* what() const NOTHROW{ return "Obecna chyba programu"; }

	virtual std::string showError() try{ 
		return consts::exceptionCodes.at(codeType); 
	} catch(std::out_of_range oExc){
		return "Neexistujici chybova hlaska (" + std::to_string(codeType) + ")";
	}
};

#endif