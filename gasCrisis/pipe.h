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
#include <deque>
#include <random>

class cPipe
{
public:
	cPipe(unsigned id, const std::string& source, const std::string& destination, unsigned lenght, double flowSummer, double flowWinter);
	~cPipe(void);

private:
	unsigned mId;

	std::default_random_engine mGenerator;
	std::poisson_distribution<int> mDistribution;

	std::string mSource;
	std::string mDestination;

	unsigned mLenght;

	double mFlowSummer;
	double mFlowWinter;

	bool mSummer;

	std::deque<double> mFlows;

public:
	double getGas(void);
	double putGas(double coeficient);

	unsigned getId(void);
	double getSummerFlow(void);
	double getWinterFlow(void);

	void setSummer(void);
	void setWinter(void);

	std::string getSource(){ return mSource; }
	std::string getDestination(){ return mDestination; }

	unsigned getLength()	{ return mLenght; }
	double getFlowSummer()	{ return mFlowSummer; }
	double getFlowWinter()	{ return mFlowWinter; }
};