//----------------------------------------------------------------------------------------
#include "stateStats.h"
//----------------------------------------------------------------------------------------
cStateStats::cStateStats(const std::string& name) :
	mName(name),
	mTotalEntries(1),
	mSummerEntries(1),
	mWinterEntries(1)
{
	// EMPTY
}
//----------------------------------------------------------------------------------------
cStateStats::~cStateStats(void)
{
	// EMPTY
}
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
void cStateStats::addConsumption(double value, bool summer)
{
	if (mTotalEntries == 1)
	{
		mTotalConsumption.total = value;
		mTotalConsumption.max = value;
		mTotalConsumption.min = value;
	}

	if (mSummerEntries == 1 && summer == true)
	{
		mSummerConsumption.total = value;
		mSummerConsumption.max = value;
		mSummerConsumption.min = value;
	}
	else if (mWinterEntries == 1 && summer == false)
	{
		mWinterConsumption.total = value;
		mWinterConsumption.max = value;
		mWinterConsumption.min = value;
	}
	else
	{
		mTotalConsumption.total += value;
		if (value > mTotalConsumption.max)
			mTotalConsumption.max = value;
		if (value < mTotalConsumption.min)
			mTotalConsumption.min = value;

		if (summer == true)
		{
			mSummerConsumption.total += value;
			if (value > mSummerConsumption.max)
				mSummerConsumption.max = value;
			if (value < mSummerConsumption.min)
				mSummerConsumption.min = value;
		}
		else
		{
			mWinterConsumption.total += value;
			if (value > mWinterConsumption.max)
				mWinterConsumption.max = value;
			if (value < mWinterConsumption.min)
				mWinterConsumption.min = value;
		}
	}
}
//----------------------------------------------------------------------------------------
void cStateStats::addProduction(double value, bool summer)
{
	if (mTotalEntries == 1)
	{
		mTotalProduction.total = value;
		mTotalProduction.max = value;
		mTotalProduction.min = value;
	}

	if (mSummerEntries == 1 && summer == true)
	{
		mSummerProduction.total = value;
		mSummerProduction.max = value;
		mSummerProduction.min = value;
	}
	else if (mWinterEntries == 1 && summer == false)
	{
		mWinterProduction.total = value;
		mWinterProduction.max = value;
		mWinterProduction.min = value;
	}
	else
	{
		mTotalProduction.total += value;
		if (value > mTotalProduction.max)
			mTotalProduction.max = value;
		if (value < mTotalProduction.min)
			mTotalProduction.min = value;

		if (summer == true)
		{
			mSummerProduction.total += value;
			if (value > mSummerProduction.max)
				mSummerProduction.max = value;
			if (value < mSummerProduction.min)
				mSummerProduction.min = value;
		}
		else
		{
			mWinterProduction.total += value;
			if (value > mWinterProduction.max)
				mWinterProduction.max = value;
			if (value < mWinterProduction.min)
				mWinterProduction.min = value;
		}
	}
}
//----------------------------------------------------------------------------------------
void cStateStats::addStorage(double value, bool summer)
{
	if (mTotalEntries == 1)
	{
		mTotalStorage.total = value;
		mTotalStorage.max = value;
		mTotalStorage.min = value;
	}

	if (mSummerEntries == 1 && summer == true)
	{
		mSummerStorage.total = value;
		mSummerStorage.max = value;
		mSummerStorage.min = value;
	}
	else if (mWinterEntries == 1 && summer == false)
	{
		mWinterStorage.total = value;
		mWinterStorage.max = value;
		mWinterStorage.min = value;
	}
	else
	{
		mTotalStorage.total += value;
		if (value > mTotalStorage.max)
			mTotalStorage.max = value;
		if (value < mTotalStorage.min)
			mTotalStorage.min = value;

		if (summer == true)
		{
			mSummerStorage.total += value;
			if (value > mSummerStorage.max)
				mSummerStorage.max = value;
			if (value < mSummerStorage.min)
				mSummerStorage.min = value;
		}
		else
		{
			mWinterStorage.total += value;
			if (value > mWinterStorage.max)
				mWinterStorage.max = value;
			if (value < mWinterStorage.min)
				mWinterStorage.min = value;
		}
	}
}
//----------------------------------------------------------------------------------------
void cStateStats::addOverflow(double value, bool summer)
{
	if (mTotalEntries == 1)
	{
		mTotalOverflow.total = value;
		mTotalOverflow.max = value;
		mTotalOverflow.min = value;
	}

	if (mSummerEntries == 1 && summer == true)
	{
		mSummerOverflow.total = value;
		mSummerOverflow.max = value;
		mSummerOverflow.min = value;
	}
	else if (mWinterEntries == 1 && summer == false)
	{
		mWinterOverflow.total = value;
		mWinterOverflow.max = value;
		mWinterOverflow.min = value;
	}
	else
	{
		mTotalOverflow.total += value;
		if (value > mTotalOverflow.max)
			mTotalOverflow.max = value;
		if (value < mTotalOverflow.min)
			mTotalOverflow.min = value;

		if (summer == true)
		{
			mSummerOverflow.total += value;
			if (value > mSummerOverflow.max)
				mSummerOverflow.max = value;
			if (value < mSummerOverflow.min)
				mSummerOverflow.min = value;
		}
		else
		{
			mWinterOverflow.total += value;
			if (value > mWinterOverflow.max)
				mWinterOverflow.max = value;
			if (value < mWinterOverflow.min)
				mWinterOverflow.min = value;
		}
	}
}
//----------------------------------------------------------------------------------------
void cStateStats::addDeficit(double value, bool summer)
{
	if (mTotalEntries == 1)
	{
		mTotalDeficit.total = value;
		mTotalDeficit.max = value;
		mTotalDeficit.min = value;
	}

	if (mSummerEntries == 1 && summer == true)
	{
		mSummerDeficit.total = value;
		mSummerDeficit.max = value;
		mSummerDeficit.min = value;
	}
	else if (mWinterEntries == 1 && summer == false)
	{
		mWinterDeficit.total = value;
		mWinterDeficit.max = value;
		mWinterDeficit.min = value;
	}
	else
	{
		mTotalDeficit.total += value;
		if (value > mTotalDeficit.max)
			mTotalDeficit.max = value;
		if (value < mTotalDeficit.min)
			mTotalDeficit.min = value;

		if (summer == true)
		{
			mSummerDeficit.total += value;
			if (value > mSummerDeficit.max)
				mSummerDeficit.max = value;
			if (value < mSummerDeficit.min)
				mSummerDeficit.min = value;
		}
		else
		{
			mWinterDeficit.total += value;
			if (value > mWinterDeficit.max)
				mWinterDeficit.max = value;
			if (value < mWinterDeficit.min)
				mWinterDeficit.min = value;
		}
	}
}
//----------------------------------------------------------------------------------------
void cStateStats::addIncomeFlow(const std::string& name, double value, bool summer)
{
	if (mTotalEntries == 1)
	{
		mTotalStatesIncome[name].total = value;
		mTotalStatesIncome[name].max = value;
		mTotalStatesIncome[name].min = value;
	}

	if (mSummerEntries == 1 && summer == true)
	{
		mSummerStatesIncome[name].total = value;
		mSummerStatesIncome[name].max = value;
		mSummerStatesIncome[name].min = value;
	}
	else if (mWinterEntries == 1 && summer == false)
	{
		mWinterStatesIncome[name].total = value;
		mWinterStatesIncome[name].max = value;
		mWinterStatesIncome[name].min = value;
	}
	else
	{
		mTotalStatesIncome[name].total += value;
		if (value > mTotalStatesIncome[name].max)
			mTotalStatesIncome[name].max = value;
		if (value < mTotalStatesIncome[name].min)
			mTotalStatesIncome[name].min = value;

		if (summer == true)
		{
			mSummerStatesIncome[name].total += value;
			if (value > mSummerStatesIncome[name].max)
				mSummerStatesIncome[name].max = value;
			if (value < mSummerStatesIncome[name].min)
				mSummerStatesIncome[name].min = value;
		}
		else
		{
			mWinterStatesIncome[name].total += value;
			if (value > mWinterStatesIncome[name].max)
				mWinterStatesIncome[name].max = value;
			if (value < mWinterStatesIncome[name].min)
				mWinterStatesIncome[name].min = value;
		}
	}
}
//----------------------------------------------------------------------------------------
void cStateStats::addOutcomeFlow(const std::string& name, double value, bool summer)
{
	if (mTotalEntries == 1)
	{
		mTotalStatesOutcome[name].total = value;
		mTotalStatesOutcome[name].max = value;
		mTotalStatesOutcome[name].min = value;
	}

	if (mSummerEntries == 1 && summer == true)
	{
		mSummerStatesOutcome[name].total = value;
		mSummerStatesOutcome[name].max = value;
		mSummerStatesOutcome[name].min = value;
	}
	else if (mWinterEntries == 1 && summer == false)
	{
		mWinterStatesOutcome[name].total = value;
		mWinterStatesOutcome[name].max = value;
		mWinterStatesOutcome[name].min = value;
	}
	else
	{
		mTotalStatesOutcome[name].total += value;
		if (value > mTotalStatesOutcome[name].max)
			mTotalStatesOutcome[name].max = value;
		if (value < mTotalStatesOutcome[name].min)
			mTotalStatesOutcome[name].min = value;

		if (summer == true)
		{
			mSummerStatesOutcome[name].total += value;
			if (value > mSummerStatesOutcome[name].max)
				mSummerStatesOutcome[name].max = value;
			if (value < mSummerStatesOutcome[name].min)
				mSummerStatesOutcome[name].min = value;
		}
		else
		{
			mWinterStatesOutcome[name].total += value;
			if (value > mWinterStatesOutcome[name].max)
				mWinterStatesOutcome[name].max = value;
			if (value < mWinterStatesOutcome[name].min)
				mWinterStatesOutcome[name].min = value;
		}
	}
}
//----------------------------------------------------------------------------------------
void cStateStats::incEntrie(bool summer)
{
	mTotalEntries++;

	if (summer == true)
	{
		mSummerEntries++;
	}
	else
	{
		mWinterEntries++;
	}
}
//----------------------------------------------------------------------------------------
std::string cStateStats::getStats(bool total, bool summer, bool winter, bool consumption, bool production, bool storage, bool overflow, bool deficit, bool incomeFlows, bool outcomeFlows)
{
	std::string output("");
	output += std::string(100, '-') + '\n';
	output += std::string(100, '-') + '\n';
	output += std::string(100, '-') + '\n';
	output += "state: " + mName;

	if (total == true)
	{
		output += "\t" + std::string(100, '-') + '\n';
		output += "\ttotal:\n";

		if (consumption == true)
		{
			output += "\t\t" + std::string(100, '-') + '\n';
			output += "\t\tconsumption:\n";
			output += "\t\t\ttot: " + std::to_string(mTotalConsumption.total);
			output += " | ";
			output += "min: " + std::to_string(mTotalConsumption.min);
			output += " | ";
			output += "max: " + std::to_string(mTotalConsumption.max);
			output += " | ";
			output += "avg: " + std::to_string(mTotalConsumption.total / mTotalEntries) + '\n';
		}

		if (production == true)
		{
			output += "\t\t" + std::string(100, '-') + '\n';
			output += "\t\tproduction:\n";
			output += "\t\t\ttot: " + std::to_string(mTotalProduction.total);
			output += " | ";
			output += "min: " + std::to_string(mTotalProduction.min);
			output += " | ";
			output += "max: " + std::to_string(mTotalProduction.max);
			output += " | ";
			output += "avg: " + std::to_string(mTotalProduction.total / mTotalEntries) + '\n';
		}

		if (storage == true)
		{
			output += "\t\t" + std::string(100, '-') + '\n';
			output += "\t\tstorage:\n";
			output += "\t\t\ttot: " + std::to_string(mTotalStorage.total);
			output += " | ";
			output += "min: " + std::to_string(mTotalStorage.min);
			output += " | ";
			output += "max: " + std::to_string(mTotalStorage.max);
			output += " | ";
			output += "avg: " + std::to_string(mTotalStorage.total / mTotalEntries) + '\n';
		}

		if (overflow == true)
		{
			output += "\t\t" + std::string(100, '-') + '\n';
			output += "\t\toverflow:\n";
			output += "\t\t\ttot: " + std::to_string(mTotalOverflow.total);
			output += " | ";
			output += "min: " + std::to_string(mTotalOverflow.min);
			output += " | ";
			output += "max: " + std::to_string(mTotalOverflow.max);
			output += " | ";
			output += "avg: " + std::to_string(mTotalOverflow.total / mTotalEntries) + '\n';
		}

		if (deficit == true)
		{
			output += "\t\t" + std::string(100, '-') + '\n';
			output += "\t\tdeficit:\n";
			output += "\t\t\ttot: " + std::to_string(mTotalDeficit.total);
			output += " | ";
			output += "min: " + std::to_string(mTotalDeficit.min);
			output += " | ";
			output += "max: " + std::to_string(mTotalDeficit.max);
			output += " | ";
			output += "avg: " + std::to_string(mTotalDeficit.total / mTotalEntries) + '\n';
		}

		for (auto state : mTotalStatesIncome)
		{
			output += "\t\t" + std::string(100, '-') + '\n';
			output += "\t\twith: " + state.first + '\n';
			if (incomeFlows == true)
			{
				output += "\t\t\tincome:\n";
				output += "\t\t\t\ttot: " + std::to_string(state.second.total);
				output += " | ";
				output += "min: " + std::to_string(state.second.min);
				output += " | ";
				output += "max: " + std::to_string(state.second.max);
				output += " | ";
				output += "avg: " + std::to_string(state.second.total / mTotalEntries) + "\n\n";
			}

			if (outcomeFlows == true)
			{
				output += "\t\t\toutcome:\n";
				output += "\t\t\t\ttot: " + std::to_string(mTotalStatesOutcome[state.first].total);
				output += " | ";
				output += "min: " + std::to_string(mTotalStatesOutcome[state.first].min);
				output += " | ";
				output += "max: " + std::to_string(mTotalStatesOutcome[state.first].max);
				output += " | ";
				output += "avg: " + std::to_string(mTotalStatesOutcome[state.first].total / mTotalEntries) + "\n\n";
			}
		}
	}

	if (summer == true)
	{
		output += "\t" + std::string(100, '-') + '\n';
		output += "\tsummer:\n";

		if (consumption == true)
		{
			output += "\t\t" + std::string(100, '-') + '\n';
			output += "\t\tconsumption:\n";
			output += "\t\t\ttot: " + std::to_string(mSummerConsumption.total);
			output += " | ";
			output += "min: " + std::to_string(mSummerConsumption.min);
			output += " | ";
			output += "max: " + std::to_string(mSummerConsumption.max);
			output += " | ";
			output += "avg: " + std::to_string(mSummerConsumption.total / mSummerEntries) + '\n';
		}

		if (production == true)
		{
			output += "\t\t" + std::string(100, '-') + '\n';
			output += "\t\tproduction:\n";
			output += "\t\t\ttot: " + std::to_string(mSummerProduction.total);
			output += " | ";
			output += "min: " + std::to_string(mSummerProduction.min);
			output += " | ";
			output += "max: " + std::to_string(mSummerProduction.max);
			output += " | ";
			output += "avg: " + std::to_string(mSummerProduction.total / mSummerEntries) + '\n';
		}

		if (storage == true)
		{
			output += "\t\t" + std::string(100, '-') + '\n';
			output += "\t\tstorage:\n";
			output += "\t\t\ttot: " + std::to_string(mSummerStorage.total);
			output += " | ";
			output += "min: " + std::to_string(mSummerStorage.min);
			output += " | ";
			output += "max: " + std::to_string(mSummerStorage.max);
			output += " | ";
			output += "avg: " + std::to_string(mSummerStorage.total / mSummerEntries) + '\n';
		}

		if (overflow == true)
		{
			output += "\t\t" + std::string(100, '-') + '\n';
			output += "\t\toverflow:\n";
			output += "\t\t\ttot: " + std::to_string(mSummerOverflow.total);
			output += " | ";
			output += "min: " + std::to_string(mSummerOverflow.min);
			output += " | ";
			output += "max: " + std::to_string(mSummerOverflow.max);
			output += " | ";
			output += "avg: " + std::to_string(mSummerOverflow.total / mSummerEntries) + '\n';
		}

		if (deficit == true)
		{
			output += "\t\t" + std::string(100, '-') + '\n';
			output += "\t\tdeficit:\n";
			output += "\t\t\ttot: " + std::to_string(mSummerDeficit.total);
			output += " | ";
			output += "min: " + std::to_string(mSummerDeficit.min);
			output += " | ";
			output += "max: " + std::to_string(mSummerDeficit.max);
			output += " | ";
			output += "avg: " + std::to_string(mSummerDeficit.total / mSummerEntries) + '\n';
		}

		for (auto state : mSummerStatesIncome)
		{
			output += "\t\t" + std::string(100, '-') + '\n';
			output += "\t\twith: " + state.first + '\n';
			if (incomeFlows == true)
			{
				output += "\t\t\tincome:\n";
				output += "\t\t\t\ttot: " + std::to_string(state.second.total);
				output += " | ";
				output += "min: " + std::to_string(state.second.min);
				output += " | ";
				output += "max: " + std::to_string(state.second.max);
				output += " | ";
				output += "avg: " + std::to_string(state.second.total / mSummerEntries) + "\n\n";
			}

			if (outcomeFlows == true)
			{
				output += "\t\t\toutcome:\n";
				output += "\t\t\t\ttot: " + std::to_string(mSummerStatesOutcome[state.first].total);
				output += " | ";
				output += "min: " + std::to_string(mSummerStatesOutcome[state.first].min);
				output += " | ";
				output += "max: " + std::to_string(mSummerStatesOutcome[state.first].max);
				output += " | ";
				output += "avg: " + std::to_string(mSummerStatesOutcome[state.first].total / mSummerEntries) + "\n\n";
			}
		}
	}

	if (winter == true)
	{
		output += "\t" + std::string(100, '-') + '\n';
		output += "\twinter:\n";

		if (consumption == true)
		{
			output += "\t\t" + std::string(100, '-') + '\n';
			output += "\t\tconsumption:\n";
			output += "\t\t\ttot: " + std::to_string(mWinterConsumption.total);
			output += " | ";
			output += "min: " + std::to_string(mWinterConsumption.min);
			output += " | ";
			output += "max: " + std::to_string(mWinterConsumption.max);
			output += " | ";
			output += "avg: " + std::to_string(mWinterConsumption.total / mWinterEntries) + '\n';
		}

		if (production == true)
		{
			output += "\t\t" + std::string(100, '-') + '\n';
			output += "\t\tproduction:\n";
			output += "\t\t\ttot: " + std::to_string(mWinterProduction.total);
			output += " | ";
			output += "min: " + std::to_string(mWinterProduction.min);
			output += " | ";
			output += "max: " + std::to_string(mWinterProduction.max);
			output += " | ";
			output += "avg: " + std::to_string(mWinterProduction.total / mWinterEntries) + '\n';
		}

		if (storage == true)
		{
			output += "\t\t" + std::string(100, '-') + '\n';
			output += "\t\tstorage:\n";
			output += "\t\t\ttot: " + std::to_string(mWinterStorage.total);
			output += " | ";
			output += "min: " + std::to_string(mWinterStorage.min);
			output += " | ";
			output += "max: " + std::to_string(mWinterStorage.max);
			output += " | ";
			output += "avg: " + std::to_string(mWinterStorage.total / mWinterEntries) + '\n';
		}

		if (overflow == true)
		{
			output += "\t\t" + std::string(100, '-') + '\n';
			output += "\t\toverflow:\n";
			output += "\t\t\ttot: " + std::to_string(mWinterOverflow.total);
			output += " | ";
			output += "min: " + std::to_string(mWinterOverflow.min);
			output += " | ";
			output += "max: " + std::to_string(mWinterOverflow.max);
			output += " | ";
			output += "avg: " + std::to_string(mWinterOverflow.total / mWinterEntries) + '\n';
		}

		if (deficit == true)
		{
			output += "\t\t" + std::string(100, '-') + '\n';
			output += "\t\tdeficit:\n";
			output += "\t\t\ttot: " + std::to_string(mWinterDeficit.total);
			output += " | ";
			output += "min: " + std::to_string(mWinterDeficit.min);
			output += " | ";
			output += "max: " + std::to_string(mWinterDeficit.max);
			output += " | ";
			output += "avg: " + std::to_string(mWinterDeficit.total / mWinterEntries) + '\n';
		}

		for (auto state : mWinterStatesIncome)
		{
			output += "\t\t" + std::string(100, '-') + '\n';
			output += "\t\twith: " + state.first + '\n';
			if (incomeFlows == true)
			{
				output += "\t\t\tincome:\n";
				output += "\t\t\t\ttot: " + std::to_string(state.second.total);
				output += " | ";
				output += "min: " + std::to_string(state.second.min);
				output += " | ";
				output += "max: " + std::to_string(state.second.max);
				output += " | ";
				output += "avg: " + std::to_string(state.second.total / mWinterEntries) + "\n\n";
			}

			if (outcomeFlows == true)
			{
				output += "\t\t\toutcome:\n";
				output += "\t\t\t\ttot: " + std::to_string(mWinterStatesOutcome[state.first].total);
				output += " | ";
				output += "min: " + std::to_string(mWinterStatesOutcome[state.first].min);
				output += " | ";
				output += "max: " + std::to_string(mWinterStatesOutcome[state.first].max);
				output += " | ";
				output += "avg: " + std::to_string(mWinterStatesOutcome[state.first].total / mWinterEntries) + "\n\n";
			}
		}
	}

	output += std::string(100, '-') + '\n';

	return output;
}
//----------------------------------------------------------------------------------------