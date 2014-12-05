/**
** IMS - Modelovani a simulace
**
** projekt: Plynova krize v Evrope
** autori:	Jakub Tutko, xtutko00@stud.fit.vutbr.cz
**			Tomas Mlynaric, xmlyna06@stud.fit.vutbr.cz
** rok:		2014/2015
**/

#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <chrono>
#include <memory>

#include "inout.h"
#include "consts.h"
#include "date_time.h"
#include "pipe.h"
#include "logger.h"
#include "stateStats.h"

class cFakeState;

/* trieda spracuvava argumenty programu */
class cState
{
public:
	cState(const std::string name, cLogger &logger, double consumSummer, double consumWinter, double storageDefaultValue, double storageCapacity, double maxStorWith, double maxStorStore, double production);
	virtual ~cState(void);

private:
	std::string mName;

	std::vector<cPipe *> mPipesIn;
	std::vector<cPipe *> mPipesOut;

	cLogger mLogger;

	cStateStats* mStats;

	double mAvgSummerIncome;
	double mAvgWinterIncome;

	bool mSummer;

	cDateTime mLastKnownTime;
	consts::sDayStat mDayStat;

	std::map<std::string, consts::sDayStat> dayConstumptStats;

	std::default_random_engine mGenerator;
	std::poisson_distribution<int> mDistributionProduction;
	std::poisson_distribution<int> mDistributionConsumption;

	double mConsumSummer;
	double mConsumWinter;

	double mStorageCapacity;
	double mStorageMaxWithdraw;
	double mStorageMaxStore;
	double mStorageStat;

	double mProduction;

public:
	void addPipelineIn(cPipe* pipe);
	void addPipelineOut(cPipe* pipe);

	virtual void behaviour(cDateTime *);

	std::string getName(void)			{ return mName; }
	double getConsumSummer(void)		{ return mConsumSummer; }
	double getConsumWinter(void)		{ return mConsumWinter; }
	double getStorageCapacity(void)		{ return mStorageCapacity; }
	double getStorageMaxWithdraw(void)	{ return mStorageMaxWithdraw; }
	double getStorageMaxStore(void)		{ return mStorageMaxStore; }
	double getStorageStat(void)			{ return mStorageStat; }
	double getProduction(void)			{ return mProduction; }

	void setLogger(const cLogger logger);
	void setSummer(void);
	void setWinter(void);
	void changeCoeficient(double value);

	std::vector<cPipe *> getAllPipesIn()	{ return this->mPipesIn; }
	std::vector<cPipe *> getAllPipesOut()	{ return this->mPipesOut; }

	virtual std::string getStats(bool total, bool summer, bool winter, bool consumption, bool production, bool storage, bool overflow, bool deficit, bool incomeFlows, bool outcomeFlows);

protected:
	double getGasFromPipes(void);
	double pushGasIntoPipes(double coeficient, bool fake);
	double product(void);
	double consum(void);
};


class cFakeState : public cState{
public:
	cFakeState(const std::string name, cLogger &logger, double cSumm, double cWint, double storDefVal, double storCap, double maxStorWith, double maxStorStore, double production);
	~cFakeState();

	void behaviour(cDateTime *);

	std::string getStats(bool total, bool summer, bool winter, bool consumption, bool production, bool storage, bool overflow, bool deficit, bool incomeFlows, bool outcomeFlows);
};
