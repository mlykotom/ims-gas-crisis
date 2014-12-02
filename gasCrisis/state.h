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

/* trieda spracuvava argumenty programu */
class cState
{
public:
	cState(void);
	cState(const std::string name, double consumSummer, double consumWinter, double storageCapacity, double maxStorageWithdraw, double maxStorageInject, double production);
	~cState(void);

private:
	std::string mName;

	std::vector<cPipe *> mPipesIn;
	std::vector<cPipe *> mPipesOut;

	cLogger mLogger;

	double mConsumSummer;
	double mConsumWinter;

	double mStorageCapacity;
	double mMaxStorageWithdraw;
	double mMaxStorageInject;

	double mProduction;

	bool mSummer;

public:
	void addPipelineIn(const cPipe& pipe);
	void addPipelineOut(const cPipe& pipe);

	void behaviour(void);

	std::string getName(void);

	void setLogger(const cLogger logger);
	void setName(const std::string& Name);
	void setConsumSummer(double consumption);
	void setConsumWinter(double consumption);
	void setStorageCapacity(double capacity);
	void setMaxStorageWithDraw(double withdraw);
	void setMaxStorageInject(double inject);
	void setProduction(double production);
	void setSummer(void);
	void setWinter(void);

private:
	double getGasFromPipes(void);
	double pushGasIntoPipes(void);
};
