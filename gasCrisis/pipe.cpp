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

	value = mDistribution(mGenerator);

	mFlows.push_front(value);

	return value;
}
//----------------------------------------------------------------------------------------
void cPipe::setSummer(void)
{
	std::poisson_distribution<int> tmp(mFlowSummer);
	mDistribution = tmp;
}
//----------------------------------------------------------------------------------------
void cPipe::setWinter(void)
{
	std::poisson_distribution<int> tmp(mFlowWinter);
	mDistribution = tmp;
}
//----------------------------------------------------------------------------------------
unsigned cPipe::getId(void)
{
	return mId;
}
//----------------------------------------------------------------------------------------