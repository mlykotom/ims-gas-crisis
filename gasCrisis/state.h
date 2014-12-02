/*
**	ISA - Síťové aplikace a správa sítí
**	Projekt: XMPP/Jabber klient
**	Autor: Jakub Tutko, xtutko00@stud.fit.vutbr.cz
**	Rok: 2014/2015
**/

#pragma once

#include <string>
#include <vector>

#include "pipe.h"
#include "logger.h"

class cFakeState;

/* trieda spracuvava argumenty programu */
class cState
{
public:
	cState(const std::string name, cLogger &logger, double consumSummer, double consumWinter, double storageCapacity, double maxStorWith, double maxStorStore, double production):
		mName(name), 
		mLogger(logger),
		mConsumSummer(consumSummer), 
		mConsumWinter(consumWinter), 
		mStorageCapacity(storageCapacity), 
		mStorageMaxWithdraw(maxStorWith), 
		mStorageMaxStore(maxStorStore),
		mProduction(production)
	{}

	virtual ~cState(void){}

private:
	std::string mName;

	std::vector<cPipe *> mPipesIn;
	std::vector<cPipe *> mPipesOut;

	cLogger mLogger;

	double mConsumSummer;
	double mConsumWinter;

	double mStorageCapacity;
	double mStorageMaxWithdraw;
	double mStorageMaxStore;

	double mProduction;

	bool mSummer;

public:
	void addPipelineIn(const cPipe& pipe);
	void addPipelineOut(const cPipe& pipe);

	void behaviour(void);

	std::string getName(void){ return mName; }
	double getConsumSummer(void) { return mConsumSummer; }
	double getConsumWinter(void) { return mConsumWinter; }
	
	double getStorageCapacity(void) { return mStorageCapacity; }
	double getStorageMaxWithdraw(void) { return mStorageMaxWithdraw; }
	double getStorageMaxStore(void) { return mStorageMaxStore; }
	double getProduction(void) { return mProduction; }

	void setLogger(const cLogger logger);

	virtual bool isFake(void){ return false; }

	void printInfo(){
		std::cout << this->getName() << std::endl;
		std::cout << this->getConsumSummer() << "|" << this->getConsumWinter() << std::endl;
		std::cout << this->getStorageCapacity() << "|" << this->getStorageMaxWithdraw() << "|" << this->getStorageMaxStore() << std::endl;
		std::cout << this->getProduction() << std::endl;
		std::cout << "----------" << std::endl;
	}

private:
	double getGasFromPipes(void);
	double pushGasIntoPipes(void);
};


class cFakeState : public cState{
public:
	cFakeState(const std::string name, cLogger &logger, double cSumm, double cWint, double storCap, double maxStorWith, double maxStorStore, double production) : cState(name, logger, cSumm, cWint, storCap, maxStorWith, maxStorStore, production){}

	~cFakeState(){}

	bool isFake(void){ return true; }
};
