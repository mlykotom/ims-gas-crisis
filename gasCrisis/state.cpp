//----------------------------------------------------------------------------------------
#include "state.h"
//----------------------------------------------------------------------------------------
// class cState
//----------------------------------------------------------------------------------------
cState::cState(const std::string name, cLogger &logger, double consumSummer, double consumWinter, double storageCapacity, double maxStorWith, double maxStorStore, double production) :
mName(name),
mLogger(logger),
mConsumSummer(consumSummer),
mConsumWinter(consumWinter),
mStorageCapacity(storageCapacity),
mStorageMaxWithdraw(maxStorWith),
mStorageMaxStore(maxStorStore),
mProduction(production)
{
	std::poisson_distribution<int> tmpPro(mProduction);
	mDistributionProduction = tmpPro;
}
//----------------------------------------------------------------------------------------
cState::~cState(void)
{
	// EMPTY
}
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
void cState::printInfo()
{
	std::cout << this->getName() << std::endl;
	std::cout << this->getConsumSummer() << "|" << this->getConsumWinter() << std::endl;
	std::cout << this->getStorageCapacity() << "|" << this->getStorageMaxWithdraw() << "|" << this->getStorageMaxStore() << std::endl;
	std::cout << this->getProduction() << std::endl;
	std::cout << "--- IN ---" << std::endl;
	for (cPipe *pipe : this->getAllPipesIn()){
		std::cout << pipe->getLength() << "|" << pipe->getFlowSummer() << '|' << pipe->getFlowWinter() << std::endl;
	}
	std::cout << "--- OUT ---" << std::endl;
	for (cPipe *pipe : this->getAllPipesOut()){
		std::cout << pipe->getLength() << "|" << pipe->getFlowSummer() << '|' << pipe->getFlowWinter() << std::endl;
	}

	std::cout << "------------------------------" << std::endl;
	std::cout << "------------------------------" << std::endl;
}
//----------------------------------------------------------------------------------------
void cState::addPipelineIn(cPipe* pipe)
{
	this->mPipesIn.push_back(pipe);
}
//----------------------------------------------------------------------------------------
void cState::addPipelineOut(cPipe* pipe)
{
	this->mPipesOut.push_back(pipe);
}
//----------------------------------------------------------------------------------------
void cState::behaviour(void)
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

	std::cout << mName << " income: " << income << " outcome: " << outcome << " product: " << production << " consum: " << consumption << std::endl;

	// ziskanie dlhu / prebitku
	amount = (income + production) - (outcome + consumption);

	std::cout << mName << " amount: " << amount;

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

		std::cout << " overflow: " << overflow << std::endl;
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

		std::cout << " deficit: " << deficit << std::endl;
	}

}
//----------------------------------------------------------------------------------------
double cState::getGasFromPipes(void)
{
	double amount = 0;

	for (unsigned i = 0; i < mPipesIn.size(); i++)
	{
		amount += mPipesIn[i]->getGas();
	}

	return amount;
}
//----------------------------------------------------------------------------------------
double cState::pushGasIntoPipes(void)
{
	double amount = 0;
	
	for (unsigned i = 0; i < mPipesOut.size(); i++)
	{
		amount += mPipesOut[i]->putGas();
	}

	return amount;
}
//----------------------------------------------------------------------------------------
double cState::product(void)
{
	return mDistributionProduction(mGenerator);
}
//----------------------------------------------------------------------------------------
double cState::consum(void)
{
	return mDistributionConsumption(mGenerator);
}
//----------------------------------------------------------------------------------------
void cState::setSummer(void)
{
	std::poisson_distribution<int> tmpCons(mConsumSummer);
	mDistributionProduction = tmpCons;
}
//----------------------------------------------------------------------------------------
void cState::setWinter(void)
{
	std::poisson_distribution<int> tmpCons(mConsumWinter);
	mDistributionProduction = tmpCons;
}
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
// class cFakeState
//----------------------------------------------------------------------------------------
cFakeState::cFakeState(const std::string name, cLogger &logger, double cSumm, double cWint, double storCap, double maxStorWith, double maxStorStore, double production) :
cState(name, logger, cSumm, cWint, storCap, maxStorWith, maxStorStore, production)
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
void cFakeState::behaviour(void)
{
	getGasFromPipes();
	pushGasIntoPipes();
}
//----------------------------------------------------------------------------------------