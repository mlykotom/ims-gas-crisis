/**
** IMS projekt
*/

#pragma once

#include <string>
#include <map>

typedef struct
{
	double total;
	double max;
	double min;
} sStatictic;

class cStateStats
{
public:
	cStateStats(const std::string& name);
	~cStateStats(void);

private:
	std::string mName;

	double mTotalEntries;
	sStatictic mTotalConsumption;
	sStatictic mTotalProduction;
	sStatictic mTotalStorage;
	sStatictic mTotalOverflow;
	sStatictic mTotalDeficit;
	std::map<std::string, sStatictic> mTotalStatesIncome;
	std::map<std::string, sStatictic> mTotalStatesOutcome;

	double mSummerEntries;
	sStatictic mSummerConsumption;
	sStatictic mSummerProduction;
	sStatictic mSummerStorage;
	sStatictic mSummerOverflow;
	sStatictic mSummerDeficit;
	std::map<std::string, sStatictic> mSummerStatesIncome;
	std::map<std::string, sStatictic> mSummerStatesOutcome;

	double mWinterEntries;
	sStatictic mWinterConsumption;
	sStatictic mWinterProduction;
	sStatictic mWinterStorage;
	sStatictic mWinterOverflow;
	sStatictic mWinterDeficit;
	std::map<std::string, sStatictic> mWinterStatesIncome;
	std::map<std::string, sStatictic> mWinterStatesOutcome;

public:
	void addConsumption(double value, bool summer);
	void addProduction(double value, bool summer);
	void addStorage(double value, bool summer);
	void addOverflow(double value, bool summer);
	void addDeficit(double value, bool summer);
	void addIncomeFlow(const std::string& name, double value, bool summer);
	void addOutcomeFlow(const std::string& name, double value, bool summer);

	void incEntrie(bool summer);

	std::string getStats(bool total, bool summer, bool winter, bool consumption, bool production, bool storage, bool overflow, bool deficit, bool incomeFlows, bool outcomeFlows);
};