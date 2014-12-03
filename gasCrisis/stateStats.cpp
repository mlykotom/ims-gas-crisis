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
	std::ostringstream out;
	const unsigned maxOnLine = 100;
	
	out << std::string(maxOnLine, '-') << '\n';
	out << "state: " << mName << std::endl;
	out << std::string(maxOnLine, '-') << '\n';

	if (total == true)
	{
		out << "\ttotal:\n";

		if (consumption == true)
		{
			out << "\t" << std::string(maxOnLine, '-') << '\n';
			out << "\t\tconsumption:\n";
			out << "\t\t\ttot: " <<  mTotalConsumption.total;
			out << " | ";
			out << "min: " <<  mTotalConsumption.min;
			out << " | ";
			out << "max: " <<  mTotalConsumption.max;
			out << " | ";
			out << "avg: " <<  mTotalConsumption.total / mTotalEntries << '\n';
		}

		if (production == true)
		{
			out << "\t\t" << std::string(maxOnLine, '-') << '\n';
			out << "\t\tproduction:\n";
			out << "\t\t\ttot: " <<  mTotalProduction.total;
			out << " | ";
			out << "min: " <<  mTotalProduction.min;
			out << " | ";
			out << "max: " <<  mTotalProduction.max;
			out << " | ";
			out << "avg: " <<  mTotalProduction.total / mTotalEntries << '\n';
		}

		if (storage == true)
		{
			out << "\t\t" << std::string(maxOnLine, '-') << '\n';
			out << "\t\tstorage:\n";
			out << "\t\t\ttot: " <<  mTotalStorage.total;
			out << " | ";
			out << "min: " <<  mTotalStorage.min;
			out << " | ";
			out << "max: " <<  mTotalStorage.max;
			out << " | ";
			out << "avg: " <<  mTotalStorage.total / mTotalEntries << '\n';
		}

		if (overflow == true)
		{
			out << "\t\t" << std::string(maxOnLine, '-') << '\n';
			out << "\t\toverflow:\n";
			out << "\t\t\ttot: " <<  mTotalOverflow.total;
			out << " | ";
			out << "min: " <<  mTotalOverflow.min;
			out << " | ";
			out << "max: " <<  mTotalOverflow.max;
			out << " | ";
			out << "avg: " <<  mTotalOverflow.total / mTotalEntries << '\n';
		}

		if (deficit == true)
		{
			out << "\t\t" << std::string(maxOnLine, '-') << '\n';
			out << "\t\tdeficit:\n";
			out << "\t\t\ttot: " <<  mTotalDeficit.total;
			out << " | ";
			out << "min: " <<  mTotalDeficit.min;
			out << " | ";
			out << "max: " <<  mTotalDeficit.max;
			out << " | ";
			out << "avg: " <<  mTotalDeficit.total / mTotalEntries << '\n';
		}

		for (auto state : mTotalStatesIncome)
		{
			out << "\t\t" << std::string(maxOnLine, '-') << '\n';
			out << "\t\twith: " << state.first << '\n';
			if (incomeFlows == true)
			{
				out << "\t\t\tincome:\n";
				out << "\t\t\t\ttot: " <<  state.second.total;
				out << " | ";
				out << "min: " <<  state.second.min;
				out << " | ";
				out << "max: " <<  state.second.max;
				out << " | ";
				out << "avg: " <<  state.second.total / mTotalEntries << "\n\n";
			}

			if (outcomeFlows == true)
			{
				out << "\t\t\toutcome:\n";
				out << "\t\t\t\ttot: " <<  mTotalStatesOutcome[state.first].total;
				out << " | ";
				out << "min: " <<  mTotalStatesOutcome[state.first].min;
				out << " | ";
				out << "max: " <<  mTotalStatesOutcome[state.first].max;
				out << " | ";
				out << "avg: " <<  mTotalStatesOutcome[state.first].total / mTotalEntries << "\n\n";
			}
		}
	}

	if (summer == true)
	{
		out << "\t" << std::string(maxOnLine, '-') << '\n';
		out << "\tsummer:\n";

		if (consumption == true)
		{
			out << "\t" << std::string(maxOnLine, '-') << '\n';
			out << "\t\tconsumption:\n";
			out << "\t\t\ttot: " <<  mSummerConsumption.total;
			out << " | ";
			out << "min: " <<  mSummerConsumption.min;
			out << " | ";
			out << "max: " <<  mSummerConsumption.max;
			out << " | ";
			out << "avg: " <<  mSummerConsumption.total / mSummerEntries << '\n';
		}

		if (production == true)
		{
			out << "\t\t" << std::string(maxOnLine, '-') << '\n';
			out << "\t\tproduction:\n";
			out << "\t\t\ttot: " <<  mSummerProduction.total;
			out << " | ";
			out << "min: " <<  mSummerProduction.min;
			out << " | ";
			out << "max: " <<  mSummerProduction.max;
			out << " | ";
			out << "avg: " <<  mSummerProduction.total / mSummerEntries << '\n';
		}

		if (storage == true)
		{
			out << "\t\t" << std::string(maxOnLine, '-') << '\n';
			out << "\t\tstorage:\n";
			out << "\t\t\ttot: " <<  mSummerStorage.total;
			out << " | ";
			out << "min: " <<  mSummerStorage.min;
			out << " | ";
			out << "max: " <<  mSummerStorage.max;
			out << " | ";
			out << "avg: " <<  mSummerStorage.total / mSummerEntries << '\n';
		}

		if (overflow == true)
		{
			out << "\t\t" << std::string(maxOnLine, '-') << '\n';
			out << "\t\toverflow:\n";
			out << "\t\t\ttot: " <<  mSummerOverflow.total;
			out << " | ";
			out << "min: " <<  mSummerOverflow.min;
			out << " | ";
			out << "max: " <<  mSummerOverflow.max;
			out << " | ";
			out << "avg: " <<  mSummerOverflow.total / mSummerEntries << '\n';
		}

		if (deficit == true)
		{
			out << "\t\t" << std::string(maxOnLine, '-') << '\n';
			out << "\t\tdeficit:\n";
			out << "\t\t\ttot: " <<  mSummerDeficit.total;
			out << " | ";
			out << "min: " <<  mSummerDeficit.min;
			out << " | ";
			out << "max: " <<  mSummerDeficit.max;
			out << " | ";
			out << "avg: " <<  mSummerDeficit.total / mSummerEntries << '\n';
		}

		for (auto state : mSummerStatesIncome)
		{
			out << "\t\t" << std::string(maxOnLine, '-') << '\n';
			out << "\t\twith: " << state.first << '\n';
			if (incomeFlows == true)
			{
				out << "\t\t\tincome:\n";
				out << "\t\t\t\ttot: " <<  state.second.total;
				out << " | ";
				out << "min: " <<  state.second.min;
				out << " | ";
				out << "max: " <<  state.second.max;
				out << " | ";
				out << "avg: " <<  state.second.total / mSummerEntries << "\n\n";
			}

			if (outcomeFlows == true)
			{
				out << "\t\t\toutcome:\n";
				out << "\t\t\t\ttot: " <<  mSummerStatesOutcome[state.first].total;
				out << " | ";
				out << "min: " <<  mSummerStatesOutcome[state.first].min;
				out << " | ";
				out << "max: " <<  mSummerStatesOutcome[state.first].max;
				out << " | ";
				out << "avg: " <<  mSummerStatesOutcome[state.first].total / mSummerEntries << "\n\n";
			}
		}
	}

	if (winter == true)
	{
		out << "\t" << std::string(maxOnLine, '-') << '\n';
		out << "\twinter:\n";

		if (consumption == true)
		{
			out << "\t" << std::string(maxOnLine, '-') << '\n';
			out << "\t\tconsumption:\n";
			out << "\t\t\ttot: " <<  mWinterConsumption.total;
			out << " | ";
			out << "min: " <<  mWinterConsumption.min;
			out << " | ";
			out << "max: " <<  mWinterConsumption.max;
			out << " | ";
			out << "avg: " <<  mWinterConsumption.total / mWinterEntries << '\n';
		}

		if (production == true)
		{
			out << "\t\t" << std::string(maxOnLine, '-') << '\n';
			out << "\t\tproduction:\n";
			out << "\t\t\ttot: " <<  mWinterProduction.total;
			out << " | ";
			out << "min: " <<  mWinterProduction.min;
			out << " | ";
			out << "max: " <<  mWinterProduction.max;
			out << " | ";
			out << "avg: " <<  mWinterProduction.total / mWinterEntries << '\n';
		}

		if (storage == true)
		{
			out << "\t\t" << std::string(maxOnLine, '-') << '\n';
			out << "\t\tstorage:\n";
			out << "\t\t\ttot: " <<  mWinterStorage.total;
			out << " | ";
			out << "min: " <<  mWinterStorage.min;
			out << " | ";
			out << "max: " <<  mWinterStorage.max;
			out << " | ";
			out << "avg: " <<  mWinterStorage.total / mWinterEntries << '\n';
		}

		if (overflow == true)
		{
			out << "\t\t" << std::string(maxOnLine, '-') << '\n';
			out << "\t\toverflow:\n";
			out << "\t\t\ttot: " <<  mWinterOverflow.total;
			out << " | ";
			out << "min: " <<  mWinterOverflow.min;
			out << " | ";
			out << "max: " <<  mWinterOverflow.max;
			out << " | ";
			out << "avg: " <<  mWinterOverflow.total / mWinterEntries << '\n';
		}

		if (deficit == true)
		{
			out << "\t\t" << std::string(maxOnLine, '-') << '\n';
			out << "\t\tdeficit:\n";
			out << "\t\t\ttot: " <<  mWinterDeficit.total;
			out << " | ";
			out << "min: " <<  mWinterDeficit.min;
			out << " | ";
			out << "max: " <<  mWinterDeficit.max;
			out << " | ";
			out << "avg: " <<  mWinterDeficit.total / mWinterEntries << '\n';
		}

		for (auto state : mWinterStatesIncome)
		{
			out << "\t\t" << std::string(maxOnLine, '-') << '\n';
			out << "\t\twith: " << state.first << '\n';
			if (incomeFlows == true)
			{
				out << "\t\t\tincome:\n";
				out << "\t\t\t\ttot: " <<  state.second.total;
				out << " | ";
				out << "min: " <<  state.second.min;
				out << " | ";
				out << "max: " <<  state.second.max;
				out << " | ";
				out << "avg: " <<  state.second.total / mWinterEntries << "\n\n";
			}

			if (outcomeFlows == true)
			{
				out << "\t\t\toutcome:\n";
				out << "\t\t\t\ttot: " <<  mWinterStatesOutcome[state.first].total;
				out << " | ";
				out << "min: " <<  mWinterStatesOutcome[state.first].min;
				out << " | ";
				out << "max: " <<  mWinterStatesOutcome[state.first].max;
				out << " | ";
				out << "avg: " <<  mWinterStatesOutcome[state.first].total / mWinterEntries << "\n\n";
			}
		}
	}

	return out.str();
}
//----------------------------------------------------------------------------------------