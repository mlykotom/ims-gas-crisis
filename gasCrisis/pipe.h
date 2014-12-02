/**
** IMS projekt
*/

#pragma once

#include <string>
#include <vector>

class cPipe
{
public:
	cPipe(void);
	cPipe(unsigned id, const std::string& source, const std::string& destination, unsigned lenght, double flowSummer, double flowWinter);
	~cPipe(void);

private:
	unsigned mId;

	bool mSummer;

	std::string mSource;
	std::string mDestionation;

	unsigned mLenght;

	double mFlowSummer;
	double mFlowWinter;

	std::vector<double> mFlows;

public:
	double getGas(void);
	double putGas(void);

	unsigned getId(void);

	void setId(unsigned id);
	void setSource(const std::string& source);
	void setDestination(const std::string& destination);
	void setLenght(unsigned lenght);
	void setFlowSummer(double flow);
	void setFlowWinter(double flow);
	void setSummer(void);
	void setWinter(void);
};