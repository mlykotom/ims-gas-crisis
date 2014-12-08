/**
** IMS - Modelovani a simulace
**
** projekt: Plynova krize v Evrope
** autori:	Jakub Tutko, xtutko00@stud.fit.vutbr.cz
**			Tomas Mlynaric, xmlyna06@stud.fit.vutbr.cz
** rok:		2014/2015
**/

//----------------------------------------------------------------------------------------
#include "state.h"
//----------------------------------------------------------------------------------------
// jelikoz na windows nefunguje default_random_engine, tak je pouzit time(NULL) << definice v consts.h 
#if TIME_RANDOM_GENERATOR
	#define RANDOM_GENERATOR  std::default_random_engine tmpGen((unsigned)time(NULL));
#else
	#define RANDOM_GENERATOR 	std::random_device rd; std::default_random_engine tmpGen(rd());
#endif
//----------------------------------------------------------------------------------------
// class cState
//----------------------------------------------------------------------------------------
// konstruktor triedy cState s naplnenim potrebnym parametrov statu
cState::cState(const std::string name, cLogger &logger, double consumSummer, double consumWinter, double storageDefaultValue, double storageCapacity, double maxStorWith, double maxStorStore, double production):
mName(name),
mLogger(logger),
mAvgSummerIncome(0),
mAvgWinterIncome(0),
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
// dekonstruktor
cState::~cState(void)
{	
	// zrusi se jenom vstupni potrubi, protoze objekty jsou sdilene mezi staty 
	// nemuze byt stat, ktery by mel pouze vystupni potrubi
	for(auto pipe: mPipesIn){
		delete pipe;
	}

	this->mPipesIn.clear();
	this->mPipesOut.clear();

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

	mAvgSummerIncome += pipe->getExpectedFlowSummer();
	mAvgWinterIncome += pipe->getExpectedFlowWinter();
}
//----------------------------------------------------------------------------------------
// metoda prida do statu potrubie ktore z neho smeruje
// @pipe dane potrubie
void cState::addPipelineOut(cPipe* pipe)
{
	this->mPipesOut.push_back(pipe);
}
//----------------------------------------------------------------------------------------
// metoda simuluje spravanie sa statu za jednu hodinu
// @actDateTime aktualny cas simulacie
void cState::behaviour(cDateTime * actDateTime)
{
	// pomocne premenne
	double production = 0;
	double consumption = 0;
	double outcome = 0;
	double income = 0;
	double amount = 0;

	// ziskanie vsetkych hodnot ohladom plynu v danej hodine
	income = getGasFromPipes();
	production = product();
	consumption = consum();

	// na potrubia sa posle percentualny podiel prijatych hodnot
	if (mSummer == true)
		outcome = pushGasIntoPipes(income / mAvgSummerIncome, false);
	else
		outcome = pushGasIntoPipes(income / mAvgWinterIncome, false);

	// ulozenie statistik
	mStats->addConsumption(consumption, mSummer);
	mStats->addProduction(production, mSummer);

	// ziskanie dlhu / prebitku
	amount = (income + production) - (outcome + consumption);

	// ak je stat v pluse pokusi sa prebytok vlozit do zasob
	if (amount > 0)
	{
		// prebytok ktory sa nepodarilo vlozit do zasobnikov
		double overflow = 0;

		// orezanie kolko sa maximalne da vlozit za hodinu do zasobniku
		if (amount > mStorageMaxStore)
		{
			// prebytku sa ulozia
			overflow = amount - mStorageMaxStore;
			amount = mStorageMaxStore;
		}

		// ak je dostatok miesta na zasobniku
		if ((mStorageStat + amount) <= mStorageCapacity)
		{
			// prebytok sa vlozi do zasobniku
			mStorageStat += amount;
			amount = 0;
		}
		// ak je nedostatok miesta na zasobniku
		else
		{
			// zasobnik sa naplni do plna
			amount = (mStorageStat + amount) - mStorageCapacity;
			mStorageStat = mStorageCapacity;
		}

		// celkovy prebytok statu
		overflow += amount;

		// ulozenie statistik
		mDayStat.overflow += overflow;
		mStats->addOverflow(overflow, mSummer);
	}
	// ak je stat v danej hodine v deficite
	else if (amount < 0)
	{
		// deficit daneho statu za hodinu
		double deficit = 0;

		// z nedostatkom dalej pracujeme ako s kladnym cislom
		amount *= -1;

		// orezanie kolko sa maximalne da ziskat za hodinu zo zasobniku
		if (amount > mStorageMaxWithdraw)
		{
			// zbytky sa automaticky zarataju do deficitu
			deficit = amount - mStorageMaxWithdraw;
			amount = mStorageMaxWithdraw;
		}

		// ak je dostatok plynu na zasobniku
		if ((mStorageStat - amount) >= 0)
		{
			// deficit sa odrata zo zasobniku
			mStorageStat -= amount;
			amount = 0;
		}
		// ak je nedostatok plynu na zasobniku
		else
		{
			// vyberie sa zo zasobniku vsetko co nanom ostalo
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
	mDayStat.income += income;
	mDayStat.outcome += outcome;
	mDayStat.consumption += consumption;
	mDayStat.production += production;	
	// ulozi statistiku pouze pokud je novy den
	if (actDateTime->getDay() != mLastKnownTime.getDay()){
		mLastKnownTime = *actDateTime;
		// na konci dne kvuli propoctum
		mDayStat.storageStat = mStorageStat;
		// ulozit celou strukturu pro dany den
		dayConstumptStats[mLastKnownTime.render()] = mDayStat;
		// resetovani pro dalsi den
		mDayStat.reset();
	}

	// ulozenie statistik
	mStats->addStorage(mStorageStat, mSummer);
	mStats->incEntrie(mSummer);
}
//----------------------------------------------------------------------------------------
// metoda ziska prytoky plynu do statu zo vsetkych potrubi
// @return celkovy pritok do statu
double cState::getGasFromPipes(void)
{
	double amount = 0;
	double actualAmount;

	// prechadzanie vsetkych potruby ktore vedu do statu
	for (unsigned i = 0; i < mPipesIn.size(); i++)
	{
		// ziskanie aktualnej hodnoty a pripocitanie do celkovej hodnoty
		actualAmount = mPipesIn[i]->getGas();
		amount += actualAmount;

		// ulozenie statistiky
		mStats->addIncomeFlow(mPipesIn[i]->getSource(), actualAmount, mSummer);
	}

	// vrati sa celkovy pritok plynu do statu
	return amount;
}
//----------------------------------------------------------------------------------------
// metoda naplni vsetky potrubia ktore vedu zo statu, potrubie si hodnoty generuje samo
// @return celkove mnozstvo odoslaneho plynu
double cState::pushGasIntoPipes(double coeficient, bool fake)
{
	double amount = 0;
	double actualAmount;
	
	// prechadznaie vsetkyck potruby ktore vedu zo statu
	for (unsigned i = 0; i < mPipesOut.size(); i++)
	{
		// ziskanie aktualnej hodnoty a pripocitanie ku celkovej hodnote
		actualAmount = mPipesOut[i]->putGas(coeficient, fake);
		amount += actualAmount;

		// ulozenie statistiky
		mStats->addOutcomeFlow(mPipesOut[i]->getDestination(), actualAmount, mSummer);
	}

	// vratenie celkoveho mnozstva odolasneho plynu
	return amount;
}
//----------------------------------------------------------------------------------------
// metoda vygeneruje mnozstvo vyprodukovaneho plynu statom za hodinu
// @return mnozstvo vyprodukovaneho plynu
double cState::product(void)
{
	// ak stat nema dennu produkciu nie je potrebne ju generovat
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
// metoda vygeneruje spotrebu statu v danej hodine
// @return mnozstvo plynu spotrebovaneho statom
double cState::consum(void)
{
	// ak ma stat v danom obdobi nulovu spotrebu, nie je potrebne generovat aktualnu spotrebu
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
// metoda oznami statu ze nastalo letne obdobie a rekurzivne to oznami vsetkym potrubiam
void cState::setSummer(void)
{
	// nastavenie leta
	mSummer = true;

	// ak v letnom obdobi dany stat ma nejaku spotrebu, zmeni sa distributor hodnot na letne hodnoty
	if (mConsumSummer > 0)
	{
		std::poisson_distribution<int> tmpCons(mConsumSummer);
		mDistributionConsumption = tmpCons;
	}

	// oznamenie vsetkym vstupnym potrubiam ze nastalo leto
	for (unsigned i = 0; i < mPipesIn.size(); i++)
	{
		mPipesIn[i]->setSummer();
	}

	// oznamenie vsetkym vystupnym potrubiam ze nastalo leto
	for (unsigned i = 0; i < mPipesOut.size(); i++)
	{
		mPipesOut[i]->setSummer();
	}
}
//----------------------------------------------------------------------------------------
// metoda oznami statu ze nastalo zimne obdobie a stat to rekurzivne oznami vsetkym svojim potrubiam
void cState::setWinter(void)
{
	// nastavneie zimy
	mSummer = false;
	
	// ak stat ma v zime nejaku spotrebu, vygeneruje sa novy distributor hodnot
	if (mConsumWinter > 0)
	{
		std::poisson_distribution<int> tmpCons(mConsumWinter);
		mDistributionConsumption = tmpCons;
	}

	// oznamenie o tom ze nastala zima vsetkym vstupnym potrubiam
	for (unsigned i = 0; i < mPipesIn.size(); i++)
	{
		mPipesIn[i]->setWinter();
	}

	// oznamenie o tom ze nastala azimu vsetkym vystupnym potrubiam
	for (unsigned i = 0; i < mPipesOut.size(); i++)
	{
		mPipesOut[i]->setWinter();
	}
}
//----------------------------------------------------------------------------------------
// metoda zmeni mesacny koeficient spotreby statu
// @value aktualny koeficient
void cState::changeCoeficient(double value)
{
	// ak je zima a stat ma nejaku zimnu spotrebu
	if (mConsumWinter > 0 && mSummer == false)
	{
		// vygenerovanie noveho koeficientu distributoru
		std::poisson_distribution<int> tmpCons(mConsumWinter * value);
		mDistributionConsumption = tmpCons;
	}
	// ak je leto a stat ma nejaku letnu spotrebu
	else if (mConsumSummer > 0 && mSummer == true)
	{
		// vygenerovanie noveho koeficientu statu
		std::poisson_distribution<int> tmpCons(mConsumSummer * value);
		mDistributionConsumption = tmpCons;
	}
	// inak sa nic nedeje
	else
	{
		return;
	}
}
//----------------------------------------------------------------------------------------
// ziskanie celkovych statistik o state
// @total			indikator ci sa maju vypisovat totalne statisktiky
// @summer			indikator ci sa maju vypisovat statisktiky o lete
// @winter			indikator ci sa maju vypisovat statisktiky o zime
// @consumption		indikator ci sa maju vypisovat statisktiky o spotrebe plynu
// @production		indikator ci sa maju vypisovat statisktiky o vyprodukovanom plyne
// @storage			indikator ci sa maju vypisovat statisktiky o zasobnikoch
// @overflow		indikator ci sa maju vypisovat statisktiky o prebytkoch plynu
// @deficit			indikator ci sa maju vypisovat statisktiky o nedostatkoch plynu
// @incomeFlows		indikator ci sa maju vypisovat statisktiky o pritokoch
// @outcomeFlows	indikator ci sa maju vypisovat statisktiky o odtokoch
std::string cState::getStats(bool total, bool summer, bool winter, bool consumption, bool production, bool storage, bool overflow, bool deficit, bool incomeFlows, bool outcomeFlows)
{
	std::string retStr;
	retStr = mStats->getStats(total, summer, winter, consumption, production, storage, overflow, deficit, incomeFlows, outcomeFlows);
	
	// denni statistiky
	std::ofstream out(consts::outputFolder + scenarioFile + '_' + this->getName() + consts::outputStateExt);
	if (!out.is_open()){
		std::cerr << inout::ShowError("Nelze otevrit soubor " + consts::outputFolder + scenarioFile + '_' + this->getName() + ".csv");
		return "";
	}

	// hlavicka souboru pro stat
	std::vector<std::string> header = { "Day", "Income", "Outcome", "Production", "Consumption", "Overflow", "Deficit", "StorageStat" };

	for (auto h : header) out << '"' << h << '"' << csvDelimiter;
	out << std::endl;

	for (auto st : dayConstumptStats){
		out << '"' << st.first << '"' << csvDelimiter;
		out << '"' << st.second.income << '"' << csvDelimiter;
		out << '"' << st.second.outcome << '"' << csvDelimiter;
		out << '"' << st.second.production << '"' << csvDelimiter;
		out << '"' << st.second.consumption << '"' << csvDelimiter;
		out << '"' << st.second.overflow << '"' << csvDelimiter;
		out << '"' << st.second.deficit << '"' << csvDelimiter;
		out << '"' << st.second.storageStat << '"' << csvDelimiter;
		out << std::endl;
	}

	return retStr;
}
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
// class cFakeState
//----------------------------------------------------------------------------------------
// konstruktor fakoveho statu ktory vola konstruktor normalneho statu
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
// fakovy stat len ziskava a vklada hodnoty na potrubie
// @actDataTime aktualny cas simulacie
void cFakeState::behaviour(cDateTime * actDateTime)
{
	getGasFromPipes();
	pushGasIntoPipes(1, true);
}
//----------------------------------------------------------------------------------------
// pretazenie metody na vypis statistik aby sa fakove staty neuvadzali do statistik
std::string cFakeState::getStats(bool total, bool summer, bool winter, bool consumption, bool production, bool storage, bool overflow, bool deficit, bool incomeFlows, bool outcomeFlows)
{
	return "";
}
//----------------------------------------------------------------------------------------