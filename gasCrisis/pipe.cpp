//----------------------------------------------------------------------------------------
#include "pipe.h"
//----------------------------------------------------------------------------------------
cPipe::cPipe(unsigned id, const std::string& source, const std::string& destination, unsigned lenght, double flowSummer, double flowWinter)
{
	mId = id;
	mSource = source;
	mDestionation = destination;
	mLenght = lenght;
	mFlowSummer = flowSummer;
	mFlowWinter = flowWinter;

	mGenerator = new std::default_random_engine();

	// na zaciatku simulacie budu rurky prazdne
	for (unsigned i = 0; i < mLenght; i++)
	{
		mFlows.push_front(0);
	}
}
//----------------------------------------------------------------------------------------
cPipe::~cPipe(void)
{
	delete mGenerator;
	delete mDistribution;
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

	value = (*mDistribution)(mGenerator);

	mFlows.push_front(value);

	return value;
}
//----------------------------------------------------------------------------------------
void cPipe::setSummer(void)
{
	delete mDistribution;
	mDistribution = new std::poisson_distribution<double>(mFlowSummer);
}
//----------------------------------------------------------------------------------------
void cPipe::setWinter(void)
{
	delete mDistribution;
	mDistribution = new std::poisson_distribution<double>(mFlowWinter);
}
//----------------------------------------------------------------------------------------
unsigned cPipe::getId(void)
{
	return mId;
}
//----------------------------------------------------------------------------------------