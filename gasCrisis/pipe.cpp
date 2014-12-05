/**
** IMS - Modelovani a simulace
**
** projekt: Plynova krize v Evrope
** autori:	Jakub Tutko, xtutko00@stud.fit.vutbr.cz
**			Tomas Mlynaric, xmlyna06@stud.fit.vutbr.cz
** rok:		2014/2015
**/

//----------------------------------------------------------------------------------------
#include "pipe.h"
//----------------------------------------------------------------------------------------
// konstruktor potrubia ktory nastavy vsetky pozadovane parametre potrubia
cPipe::cPipe(unsigned id, const std::string& source, const std::string& destination, unsigned lenght, double flowSummer, double flowWinter):
	mId(id),
	mSource(source),
	mDestination(destination),
	mLenght(lenght),
	mFlowSummer(flowSummer),
	mFlowWinter(flowWinter)
{
	// na zaciatku simulacie budu rurky prazdne
	for (unsigned i = 0; i < mLenght; i++)
	{
		mFlows.push_front(0);
	}

	// vygenerovanie seedu pre generator
	std::random_device rd;
	std::default_random_engine tmpGen(rd());
	mGenerator = tmpGen;
}
//----------------------------------------------------------------------------------------
cPipe::~cPipe(void)
{
	// EMPTY
}
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
// metoda ziska poslednu hodnotu na potruby a vymaze ju
// @return vratenie poslednej hodnoty na potruby
double cPipe::getGas(void)
{
	double value;

	value = mFlows.back();
	mFlows.pop_back();
	
	return value;
}
//----------------------------------------------------------------------------------------
// metoda vygeneruje a vlozi hodnotu na potrubie
// @coeficient koeficient pre pridavanie hodnoty na potrubie
double cPipe::putGas(double coeficient, bool fake)
{
	double value = 0;

	if (fake == true)
	// ak sa v danom rocnom obdobi nieco generuje tak sa to vygeneruje
	if ((mSummer && (mFlowSummer > 0)) || (!mSummer && (mFlowWinter > 0)))
	{
		value = mDistribution(mGenerator) * coeficient;
	}
	else
	{
		value = 0;
	}
	else
	{
		if (mSummer == true)
		{
			value = mFlowSummer * coeficient;
		}
		else
		{
			value = mFlowWinter * coeficient;
		}
	}
	// vlozenie hodnoty do potrubia
	mFlows.push_front(value);

	return value;
}
//----------------------------------------------------------------------------------------
// oznamenie potrubiu ze nastalo leto
void cPipe::setSummer(void)
{
	mSummer = true;

	// vygenerovanie noveho distributoru podla rocneho obdobia
	if (mFlowSummer > 0)
	{
		std::poisson_distribution<int> tmp(mFlowSummer);
		mDistribution = tmp;
	}
}
//----------------------------------------------------------------------------------------
// oznamenie potrubiu ze nastala zima
void cPipe::setWinter(void)
{
	mSummer = false;

	// vygenerovanie noveho distributoru podla rocneho obdobia
	if (mFlowWinter > 0)
	{
		std::poisson_distribution<int> tmp(mFlowWinter);
		mDistribution = tmp;
	}
}
//----------------------------------------------------------------------------------------
// ziskanie id potrubia
// @return id potrubia
unsigned cPipe::getId(void)
{
	return mId;
}
//----------------------------------------------------------------------------------------
// ziskanie letneho priemerneho toku
// @return letny priemerny tok
double cPipe::getSummerFlow(void)
{
	return mFlowSummer;
}
//----------------------------------------------------------------------------------------
// ziskanie zimenho priemerneho toku
// @return zimny priemerny tok
double cPipe::getWinterFlow(void)
{
	return mFlowWinter;
}
//----------------------------------------------------------------------------------------