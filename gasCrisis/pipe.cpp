//----------------------------------------------------------------------------------------
#include "pipe.h"
//----------------------------------------------------------------------------------------
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
double cPipe::getGas(void)
{
	double value;

	value = mFlows.back();
	mFlows.pop_back();
	
	return value;
}
//----------------------------------------------------------------------------------------
double cPipe::putGas(void)
{
	double value;

	if ((mSummer && (mFlowSummer > 0)) || (!mSummer && (mFlowWinter > 0)))
	{
		value = mDistribution(mGenerator);
	}
	else
	{
		value = 0;
	}

	mFlows.push_front(value);

	return value;
}
//----------------------------------------------------------------------------------------
void cPipe::setSummer(void)
{
	mSummer = true;

	if (mFlowSummer > 0)
	{
		std::poisson_distribution<int> tmp(mFlowSummer);
		mDistribution = tmp;
	}
}
//----------------------------------------------------------------------------------------
void cPipe::setWinter(void)
{
	mSummer = false;
	
	if (mFlowWinter > 0)
	{
		std::poisson_distribution<int> tmp(mFlowWinter);
		mDistribution = tmp;
	}
}
//----------------------------------------------------------------------------------------
unsigned cPipe::getId(void)
{
	return mId;
}
//----------------------------------------------------------------------------------------