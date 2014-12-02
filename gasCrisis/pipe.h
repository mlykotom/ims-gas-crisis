/**
** IMS projekt
*/

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

	std::deque<double> mFlows;

public:
	double getGas(void);
	double putGas(void);

	unsigned getId(void);

	void setSummer(void);
	void setWinter(void);

	unsigned getLength()	{ return mLenght; }
	double getFlowSummer()	{ return mFlowSummer; }
	double getFlowWinter()	{ return mFlowWinter; }
};