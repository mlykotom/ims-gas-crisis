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
}
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

}
//----------------------------------------------------------------------------------------
void cPipe::setSummer(void)
{
	delete mDistribution;
	mDistribution = new std::poisson_distribution<double>(mFlowSummer);
}
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------