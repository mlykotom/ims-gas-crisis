//----------------------------------------------------------------------------------------
#include "state.h"
// jelikoz na windows nefunguje default_random_engine, tak je pouzit time(NULL) << definice v consts.h 
#if TIME_RANDOM_GENERATOR
	#define RANDOM_GENERATOR  std::default_random_engine tmpGen(time(NULL));
#else
	#define RANDOM_GENERATOR 	std::random_device rd; std::default_random_engine tmpGen(rd());
#endif
//----------------------------------------------------------------------------------------
// class cState
//----------------------------------------------------------------------------------------
cState::cState(const std::string name, cLogger &logger, double consumSummer, double consumWinter, double storageDefaultValue, double storageCapacity, double maxStorWith, double maxStorStore, double production):
mName(name),
mLogger(logger),
mLastKnownTime(),
mDayStat(),
mConsumSummer(consumSummer),
mConsumWinter(consumWinter),
mStorageCapacity(storageCapacity),
mStorageMaxWithdraw(maxStorWith),
mStorageMaxStore(maxStorStore),
mStorageStat(storageDefaultValue),
mProduction(production)
{	
	// vygenerovanie noveho distributoru pre produkciu
	if (mProduction > 0)
	{
		std::poisson_distribution<int> tmpPro(mProduction);
		mDistributionProduction = tmpPro;
	}

	// vygenerovanie noveho seedu pre generator
	RANDOM_GENERATOR
	mGenerator = tmpGen;

	// trieda pre zachytavanie statistik
	mStats = new cStateStats(mName);
}
//----------------------------------------------------------------------------------------
cState::~cState(void)
{
	// zrusenie potrubi
	for (unsigned i = 0; i < mPipesIn.size(); i++)
	{
		delete mPipesIn[i];
	}

	// zrusenie potrubi
	for (unsigned i = 0; i < mPipesOut.size(); i++)
	{
		delete mPipesOut[i];
	}

	// zrusenie statistik
	delete mStats;
}
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
// metoda prida ku statu potrubie ktore do neho smeruje
// @pipe dane potrubie
void cState::addPipelineIn(cPipe* pipe)
{
	this->mPipesIn.push_back(pipe);
}
//----------------------------------------------------------------------------------------
// metoda prida do statu potrubie ktore z neho smeruje
// @pipe dane potrubie
void cState::addPipelineOut(cPipe* pipe)
{
	this->mPipesOut.push_back(pipe);
}
//----------------------------------------------------------------------------------------
void cState::behaviour(cDateTime * actDateTime)
{
	// pomocne premenne
	double production = 0;
	double consumption = 0;
	double outcome = 0;
	double income = 0;
	double amount = 0;


	// ziskanie vsetkych vstupov / vystupov
	income = getGasFromPipes();
	outcome = pushGasIntoPipes();
	production = product();
	consumption = consum();

	// ulozenie statistik
	mStats->addConsumption(consumption, mSummer);
	mStats->addProduction(production, mSummer);

	// ziskanie dlhu / prebitku
	amount = (income + production) - (outcome + consumption);

	if (amount > 0)
	{
		double overflow = 0;

		// orezanie kolko sa maximalne da vlozit za hodinu do zasobniku
		if (amount > mStorageMaxStore)
		{
			overflow = amount - mStorageMaxStore;
			amount = mStorageMaxStore;
		}

		// ak je dostatok miesta na zasobniku
		if ((mStorageStat + amount) <= mStorageCapacity)
		{
			mStorageStat += amount;
			amount = 0;
		}
		// ak je nedostatok miesta na zasobniku
		else
		{
			amount = (mStorageStat + amount) - mStorageCapacity;
			mStorageStat = mStorageCapacity;
		}

		// celkovy zisk statu
		overflow += amount;

		// ulozenie statistik
		mDayStat.overflow += overflow;
		mStats->addOverflow(overflow, mSummer);
	}
	else if (amount < 0)
	{
		double deficit = 0;

		// orezanie kolko sa maximalne da ziskat za hodinu zo zasobniku
		if (amount > mStorageMaxWithdraw)
		{
			deficit = amount - mStorageMaxWithdraw;
			amount = mStorageMaxWithdraw;
		}

		// ak je dostatok plynu na zasobniku
		if ((mStorageStat - amount) >= 0)
		{
			mStorageStat -= amount;
			amount = 0;
		}
		// ak je nedostatok plynu na zasobniku
		else
		{
			amount = amount - mStorageStat;
			mStorageStat = 0;
		}

		// celkovy deficit zo dna
		deficit += amount;

		// ulozenie statistik
		mDayStat.deficit += deficit;
		mStats->addDeficit(deficit, mSummer);
	}

	// pripocteni denni statistiky
	mDayStat.consumption += consumption;
	mDayStat.production += production;
	mDayStat.storageStat += mStorageStat;

	if (actDateTime->getDay() != mLastKnownTime.getDay()){
		mLastKnownTime = *actDateTime;
		dayConstumptStats[mLastKnownTime.render()] = mDayStat;
		// resetovani pro dalsi den
		mDayStat.reset();
	}

	// ulozenie statistik
	mStats->addStorage(mStorageStat, mSummer);
	mStats->incEntrie(mSummer);
}
//----------------------------------------------------------------------------------------
double cState::getGasFromPipes(void)
{
	double amount = 0;
	double actualAmount;

	for (unsigned i = 0; i < mPipesIn.size(); i++)
	{
		actualAmount = mPipesIn[i]->getGas();
		amount += actualAmount;

		mStats->addIncomeFlow(mPipesIn[i]->getSource(), actualAmount, mSummer);
	}

	return amount;
}
//----------------------------------------------------------------------------------------
double cState::pushGasIntoPipes(void)
{
	double amount = 0;
	double actualAmount;
	
	for (unsigned i = 0; i < mPipesOut.size(); i++)
	{
		actualAmount = mPipesOut[i]->putGas();
		amount += actualAmount;

		mStats->addOutcomeFlow(mPipesOut[i]->getDestination(), actualAmount, mSummer);
	}

	return amount;
}
//----------------------------------------------------------------------------------------
double cState::product(void)
{
	if (mProduction > 0)
	{
		return mDistributionProduction(mGenerator);
	}
	else
	{
		return 0;
	}
}
//----------------------------------------------------------------------------------------
double cState::consum(void)
{
	if ((mSummer && (mConsumSummer > 0)) || (!mSummer && (mConsumWinter > 0)))
	{
		return mDistributionConsumption(mGenerator);
	}
	else
	{
		return 0;
	}
}
//----------------------------------------------------------------------------------------
void cState::setSummer(void)
{
	mSummer = true;

	if (mConsumSummer > 0)
	{
		std::poisson_distribution<int> tmpCons(mConsumSummer);
		mDistributionConsumption = tmpCons;
	}

	for (unsigned i = 0; i < mPipesIn.size(); i++)
	{
		mPipesIn[i]->setSummer();
	}

	for (unsigned i = 0; i < mPipesOut.size(); i++)
	{
		mPipesOut[i]->setSummer();
	}
}
//----------------------------------------------------------------------------------------
void cState::setWinter(void)
{
	mSummer = false;
	
	if (mConsumWinter > 0)
	{
		std::poisson_distribution<int> tmpCons(mConsumWinter);
		mDistributionConsumption = tmpCons;
	}

	for (unsigned i = 0; i < mPipesIn.size(); i++)
	{
		mPipesIn[i]->setWinter();
	}

	for (unsigned i = 0; i < mPipesOut.size(); i++)
	{
		mPipesOut[i]->setWinter();
	}
}
//----------------------------------------------------------------------------------------
void cState::changeCoeficient(double value)
{
	if (mConsumWinter > 0)
	{
		if (mSummer == true)
		{
			std::poisson_distribution<int> tmpCons(mConsumSummer * value);
			mDistributionConsumption = tmpCons;
		}
		else
		{
			std::poisson_distribution<int> tmpCons(mConsumWinter * value);
			mDistributionConsumption = tmpCons;
		}
	}
}
//----------------------------------------------------------------------------------------
std::string cState::getStats(bool total, bool summer, bool winter, bool consumption, bool production, bool storage, bool overflow, bool deficit, bool incomeFlows, bool outcomeFlows)
{
	std::cout << mStats->getStats(total, summer, winter, consumption, production, storage, overflow, deficit, incomeFlows, outcomeFlows);

	std::ofstream out(consts::outputFolder + this->getName() + ".csv");
	// TODO osetrit jestli je otevreny soubor

	std::vector<std::string> header = { "Day", "Production", "Consumption", "Overflow", "Deficit", "StorageStat" };

	for (auto h : header) out << h << consts::csvDelimiter;
	out << std::endl;

	for (auto st : dayConstumptStats){
		out << st.first << consts::csvDelimiter;
		out << st.second.production << consts::csvDelimiter;
		out << st.second.consumption << consts::csvDelimiter;
		out << st.second.overflow << consts::csvDelimiter;
		out << st.second.deficit << consts::csvDelimiter;
		out << st.second.storageStat << consts::csvDelimiter;
		out << std::endl;
	}

	return "";
}
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
// class cFakeState
//----------------------------------------------------------------------------------------
cFakeState::cFakeState(const std::string name, cLogger &logger, double cSumm, double cWint, double storDefVal, double storCap, double maxStorWith, double maxStorStore, double production):
cState(name, logger, cSumm, cWint, storDefVal, storCap, maxStorWith, maxStorStore, production)
{
	// EMPTY
}
//----------------------------------------------------------------------------------------
cFakeState::~cFakeState()
{
	// EMPTY
}
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
void cFakeState::behaviour(cDateTime * actDateTime)
{
	getGasFromPipes();
	pushGasIntoPipes();
}
//----------------------------------------------------------------------------------------
std::string cFakeState::getStats(bool total, bool summer, bool winter, bool consumption, bool production, bool storage, bool overflow, bool deficit, bool incomeFlows, bool outcomeFlows)
{
	return "";
}
//----------------------------------------------------------------------------------------