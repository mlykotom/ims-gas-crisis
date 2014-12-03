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
// prida jednu hodnotu do statistik o Consumption
// @value	aktualna hodnota ktora sa ma zapisat
// @summer	indikator ci je leto/zima
void cStateStats::addConsumption(double value, bool summer)
{
	// ak sa jedna o prvy hodnotu
	if (mTotalEntries == 1)
	{
		mTotalConsumption.total = value;
		mTotalConsumption.max = value;
		mTotalConsumption.min = value;
	}

	// ak sa jedna o prvy letnu hodnotu
	if (mSummerEntries == 1 && summer == true)
	{
		mSummerConsumption.total = value;
		mSummerConsumption.max = value;
		mSummerConsumption.min = value;
	}
	// ak sa jedna o prvu zimnu hodnotu
	else if (mWinterEntries == 1 && summer == false)
	{
		mWinterConsumption.total = value;
		mWinterConsumption.max = value;
		mWinterConsumption.min = value;
	}
	else
	{
		// ulozenie celkovych statistik
		mTotalConsumption.total += value;
		if (value > mTotalConsumption.max)
			mTotalConsumption.max = value;
		if (value < mTotalConsumption.min)
			mTotalConsumption.min = value;

		// ulozenie letnych statistik
		if (summer == true)
		{
			mSummerConsumption.total += value;
			if (value > mSummerConsumption.max)
				mSummerConsumption.max = value;
			if (value < mSummerConsumption.min)
				mSummerConsumption.min = value;
		}
		// ulozenie zimnych statistik
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
// prida jednu hodnotu do statistik o Production
// @value	aktualna hodnota ktora sa ma zapisat
// @summer	indikator ci je leto/zima
void cStateStats::addProduction(double value, bool summer)
{
	// ak sa jedna o prvy hodnotu
	if (mTotalEntries == 1)
	{
		mTotalProduction.set(value, value, value);
	}

	// ak sa jedna o prvy letnu hodnotu
	if (mSummerEntries == 1 && summer == true)
	{
		mSummerProduction.set(value, value, value);
	}
	// ak sa jedna o prvu zimnu hodnotu
	else if (mWinterEntries == 1 && summer == false)
	{
		mWinterProduction.set(value, value, value);
	}
	else
	{
		// ulozenie celkovych statistik
		mTotalProduction.total += value;
		if (value > mTotalProduction.max)
			mTotalProduction.max = value;
		if (value < mTotalProduction.min)
			mTotalProduction.min = value;

		// ulozenie letnych statistik
		if (summer == true)
		{
			mSummerProduction.total += value;
			if (value > mSummerProduction.max)
				mSummerProduction.max = value;
			if (value < mSummerProduction.min)
				mSummerProduction.min = value;
		}
		// ulozenie zimnych statistik
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
// prida jednu hodnotu do statistik o Storage
// @value	aktualna hodnota ktora sa ma zapisat
// @summer	indikator ci je leto/zima
void cStateStats::addStorage(double value, bool summer)
{
	// ak sa jedna o prvy hodnotu
	if (mTotalEntries == 1)
	{
		mTotalStorage.total = value;
		mTotalStorage.max = value;
		mTotalStorage.min = value;
	}

	// ak sa jedna o prvy letnu hodnotu
	if (mSummerEntries == 1 && summer == true)
	{
		mSummerStorage.total = value;
		mSummerStorage.max = value;
		mSummerStorage.min = value;
	}
	// ak sa jedna o prvu zimnu hodnotu
	else if (mWinterEntries == 1 && summer == false)
	{
		mWinterStorage.total = value;
		mWinterStorage.max = value;
		mWinterStorage.min = value;
	}
	else
	{
		// ulozenie celkovych statistik
		mTotalStorage.total += value;
		if (value > mTotalStorage.max)
			mTotalStorage.max = value;
		if (value < mTotalStorage.min)
			mTotalStorage.min = value;

		// ulozenie letnych statistik
		if (summer == true)
		{
			mSummerStorage.total += value;
			if (value > mSummerStorage.max)
				mSummerStorage.max = value;
			if (value < mSummerStorage.min)
				mSummerStorage.min = value;
		}
		// ulozenie zimnych statistik
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
// prida jednu hodnotu do statistik o prebytku plynu
// @value	aktualna hodnota ktora sa ma zapisat
// @summer	indikator ci je leto/zima
void cStateStats::addOverflow(double value, bool summer)
{
	// ak sa jedna o prvy hodnotu
	if (mTotalEntries == 1)
	{
		mTotalOverflow.total = value;
		mTotalOverflow.max = value;
		mTotalOverflow.min = value;
	}

	// ak sa jedna o prvy letnu hodnotu
	if (mSummerEntries == 1 && summer == true)
	{
		mSummerOverflow.total = value;
		mSummerOverflow.max = value;
		mSummerOverflow.min = value;
	}
	// ak sa jedna o prvu zimnu hodnotu
	else if (mWinterEntries == 1 && summer == false)
	{
		mWinterOverflow.total = value;
		mWinterOverflow.max = value;
		mWinterOverflow.min = value;
	}
	else
	{
		// ulozenie celkovych statistik
		mTotalOverflow.total += value;
		if (value > mTotalOverflow.max)
			mTotalOverflow.max = value;
		if (value < mTotalOverflow.min)
			mTotalOverflow.min = value;

		// ulozenie letnych statistik
		if (summer == true)
		{
			mSummerOverflow.total += value;
			if (value > mSummerOverflow.max)
				mSummerOverflow.max = value;
			if (value < mSummerOverflow.min)
				mSummerOverflow.min = value;
		}
		// ulozenie zimnych statistik
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
// prida jednu hodnotu do statistik o nedostatku plynu
// @value	aktualna hodnota ktora sa ma zapisat
// @summer	indikator ci je leto/zima
void cStateStats::addDeficit(double value, bool summer)
{
	// ak sa jedna o prvy hodnotu
	if (mTotalEntries == 1)
	{
		mTotalDeficit.total = value;
		mTotalDeficit.max = value;
		mTotalDeficit.min = value;
	}

	// ak sa jedna o prvy letnu hodnotu
	if (mSummerEntries == 1 && summer == true)
	{
		mSummerDeficit.total = value;
		mSummerDeficit.max = value;
		mSummerDeficit.min = value;
	}
	// ak sa jedna o prvu zimnu hodnotu
	else if (mWinterEntries == 1 && summer == false)
	{
		mWinterDeficit.total = value;
		mWinterDeficit.max = value;
		mWinterDeficit.min = value;
	}
	else
	{
		// ulozenie celkovych statistik
		mTotalDeficit.total += value;
		if (value > mTotalDeficit.max)
			mTotalDeficit.max = value;
		if (value < mTotalDeficit.min)
			mTotalDeficit.min = value;

		// ulozenie letnych statistik
		if (summer == true)
		{
			mSummerDeficit.total += value;
			if (value > mSummerDeficit.max)
				mSummerDeficit.max = value;
			if (value < mSummerDeficit.min)
				mSummerDeficit.min = value;
		}
		// ulozenie zimnych statistik
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
// prida jednu hodnotu do statistik o vstupnom toku
// @name	meno statu kam ide tok
// @value	aktualna hodnota ktora sa ma zapisat
// @summer	indikator ci je leto/zima
void cStateStats::addIncomeFlow(const std::string& name, double value, bool summer)
{
	// ak sa jedna o prvy hodnotu
	if (mTotalEntries == 1)
	{
		mTotalStatesIncome[name].total = value;
		mTotalStatesIncome[name].max = value;
		mTotalStatesIncome[name].min = value;
	}

	// ak sa jedna o prvy letnu hodnotu
	if (mSummerEntries == 1 && summer == true)
	{
		mSummerStatesIncome[name].total = value;
		mSummerStatesIncome[name].max = value;
		mSummerStatesIncome[name].min = value;
	}
	// ak sa jedna o prvu zimnu hodnotu
	else if (mWinterEntries == 1 && summer == false)
	{
		mWinterStatesIncome[name].total = value;
		mWinterStatesIncome[name].max = value;
		mWinterStatesIncome[name].min = value;
	}
	else
	{
		// ulozenie celkovych statistik
		mTotalStatesIncome[name].total += value;
		if (value > mTotalStatesIncome[name].max)
			mTotalStatesIncome[name].max = value;
		if (value < mTotalStatesIncome[name].min)
			mTotalStatesIncome[name].min = value;

		// ulozenie letnych statistik
		if (summer == true)
		{
			mSummerStatesIncome[name].total += value;
			if (value > mSummerStatesIncome[name].max)
				mSummerStatesIncome[name].max = value;
			if (value < mSummerStatesIncome[name].min)
				mSummerStatesIncome[name].min = value;
		}
		// ulozenie zimnych statistik
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
// prida jednu hodnotu do statistik o vystupnom toku
// @name	meno statu odkial prisiel tok
// @value	aktualna hodnota ktora sa ma zapisat
// @summer	indikator ci je leto/zima
void cStateStats::addOutcomeFlow(const std::string& name, double value, bool summer)
{
	// ak sa jedna o prvy hodnotu
	if (mTotalEntries == 1)
	{
		mTotalStatesOutcome[name].total = value;
		mTotalStatesOutcome[name].max = value;
		mTotalStatesOutcome[name].min = value;
	}

	// ak sa jedna o prvy letnu hodnotu
	if (mSummerEntries == 1 && summer == true)
	{
		mSummerStatesOutcome[name].total = value;
		mSummerStatesOutcome[name].max = value;
		mSummerStatesOutcome[name].min = value;
	}
	// ak sa jedna o prvu zimnu hodnotu
	else if (mWinterEntries == 1 && summer == false)
	{
		mWinterStatesOutcome[name].total = value;
		mWinterStatesOutcome[name].max = value;
		mWinterStatesOutcome[name].min = value;
	}
	else
	{
		// ulozenie celkovych statistik
		mTotalStatesOutcome[name].total += value;
		if (value > mTotalStatesOutcome[name].max)
			mTotalStatesOutcome[name].max = value;
		if (value < mTotalStatesOutcome[name].min)
			mTotalStatesOutcome[name].min = value;

		// ulozenie letnych statistik
		if (summer == true)
		{
			mSummerStatesOutcome[name].total += value;
			if (value > mSummerStatesOutcome[name].max)
				mSummerStatesOutcome[name].max = value;
			if (value < mSummerStatesOutcome[name].min)
				mSummerStatesOutcome[name].min = value;
		}
		// ulozenie zimnych statistik
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
// incrementovanie pocitadiel vstupov
// @summer	indikator ci sa jedna o leto alebo zimu
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
// vytlacenie celkovych statistik a vratenie ich ako string
// @total			indikator ci sa maju vypisovat totalne statisktiky
// @summer			indikator ci sa maju vypisovat statisktiky o lete
// @winter			indikator ci sa maju vypisovat statisktiky o zime
// @consumption		indikator ci sa maju vypisovat statisktiky o spotrebe plynu
// @production		indikator ci sa maju vypisovat statisktiky o vyprodukovanom plyne
// @storage			indikator ci sa maju vypisovat statisktiky o zasobnikoch
// @overflow		indikator ci sa maju vypisovat statisktiky o prebytkoch plynu
// @deficit			indikator ci sa maju vypisovat statisktiky o nedostatkoch plynu
// @incomeFlows		indikator ci sa maju vypisovat statisktiky o pritokoch
// @outcomeFlows	indikator ci sa maju vypisovat statisktiky o odtokoch
std::string cStateStats::getStats(bool total, bool summer, bool winter, bool consumption, bool production, bool storage, bool overflow, bool deficit, bool incomeFlows, bool outcomeFlows)
{
	std::ostringstream out;
	
	out << std::string(consts::defaultSizeOfPrint, '-') << '\n';
	out << "state: " << mName << std::endl;
	out << std::string(consts::defaultSizeOfPrint, '-') << '\n';

	if (total == true)
	{
		out << "\ttotal:\n";

		if (consumption == true)
		{
			out << "\t" << std::string(consts::defaultSizeOfPrint, '-') << '\n';
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
			out << "\t\t" << std::string(consts::defaultSizeOfPrint, '-') << '\n';
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
			out << "\t\t" << std::string(consts::defaultSizeOfPrint, '-') << '\n';
			out << "\t\tstorage:\n";
			out << "\t\t\tmin: " <<  mTotalStorage.min;
			out << " | ";
			out << "max: " <<  mTotalStorage.max;
			out << " | ";
			out << "avg: " <<  mTotalStorage.total / mTotalEntries << '\n';
		}

		if (overflow == true)
		{
			out << "\t\t" << std::string(consts::defaultSizeOfPrint, '-') << '\n';
			out << "\t\toverflow:\n";
			out << "\t\t\ttot: " <<  mTotalOverflow.total;
			out << " | ";
			out << "max: " <<  mTotalOverflow.max << '\n';
		}

		if (deficit == true)
		{
			out << "\t\t" << std::string(consts::defaultSizeOfPrint, '-') << '\n';
			out << "\t\tdeficit:\n";
			out << "\t\t\ttot: " <<  mTotalDeficit.total;
			out << " | ";
			out << "max: " <<  mTotalDeficit.max << '\n';
		}

		if (incomeFlows == true)
		{
			out << "\t\t" << std::string(consts::defaultSizeOfPrint, '-') << '\n';
			out << "\t\tincome \n";
			for (auto state : mTotalStatesIncome)
			{
				out << "\t\t\t" << state.first << " => ";
				out << " tot: " << state.second.total;
				out << " | ";
				out << "min: " << state.second.min;
				out << " | ";
				out << "max: " << state.second.max;
				out << " | ";
				out << "avg: " << state.second.total / mTotalEntries << "\n\n";
			}
		}

		if (outcomeFlows == true)
		{
			out << "\t\t" << std::string(consts::defaultSizeOfPrint, '-') << '\n';
			out << "\t\toutcome \n";
			for (auto state : mTotalStatesOutcome)
			{
				out << "\t\t\t" << state.first << " <= ";
				out << " tot: " << mTotalStatesOutcome[state.first].total;
				out << " | ";
				out << "min: " << mTotalStatesOutcome[state.first].min;
				out << " | ";
				out << "max: " << mTotalStatesOutcome[state.first].max;
				out << " | ";
				out << "avg: " << mTotalStatesOutcome[state.first].total / mTotalEntries << "\n\n";
			}
		}
	}

	if (summer == true)
	{
		out << "\tsummer:\n";

		if (consumption == true)
		{
			out << "\t" << std::string(consts::defaultSizeOfPrint, '-') << '\n';
			out << "\t\tconsumption:\n";
			out << "\t\t\ttot: " << mSummerConsumption.total;
			out << " | ";
			out << "min: " << mSummerConsumption.min;
			out << " | ";
			out << "max: " << mSummerConsumption.max;
			out << " | ";
			out << "avg: " << mSummerConsumption.total / mSummerEntries << '\n';
		}

		if (production == true)
		{
			out << "\t\t" << std::string(consts::defaultSizeOfPrint, '-') << '\n';
			out << "\t\tproduction:\n";
			out << "\t\t\ttot: " << mSummerProduction.total;
			out << " | ";
			out << "min: " << mSummerProduction.min;
			out << " | ";
			out << "max: " << mSummerProduction.max;
			out << " | ";
			out << "avg: " << mSummerProduction.total / mSummerEntries << '\n';
		}

		if (storage == true)
		{
			out << "\t\t" << std::string(consts::defaultSizeOfPrint, '-') << '\n';
			out << "\t\tstorage:\n";
			out << "\t\t\tmin: " << mSummerStorage.min;
			out << " | ";
			out << "max: " << mSummerStorage.max;
			out << " | ";
			out << "avg: " << mSummerStorage.total / mSummerEntries << '\n';
		}

		if (overflow == true)
		{
			out << "\t\t" << std::string(consts::defaultSizeOfPrint, '-') << '\n';
			out << "\t\toverflow:\n";
			out << "\t\t\ttot: " << mSummerOverflow.total;
			out << " | ";
			out << "max: " << mSummerOverflow.max << '\n';
		}

		if (deficit == true)
		{
			out << "\t\t" << std::string(consts::defaultSizeOfPrint, '-') << '\n';
			out << "\t\tdeficit:\n";
			out << "\t\t\ttot: " << mSummerDeficit.total;
			out << " | ";
			out << "max: " << mSummerDeficit.max << '\n';
		}

		if (incomeFlows == true)
		{
			out << "\t\t" << std::string(consts::defaultSizeOfPrint, '-') << '\n';
			out << "\t\tincome \n";
			for (auto state : mSummerStatesIncome)
			{
				out << "\t\t\t" << state.first << " => ";
				out << " tot: " << state.second.total;
				out << " | ";
				out << "min: " << state.second.min;
				out << " | ";
				out << "max: " << state.second.max;
				out << " | ";
				out << "avg: " << state.second.total / mSummerEntries << "\n\n";
			}
		}

		if (outcomeFlows == true)
		{
			out << "\t\t" << std::string(consts::defaultSizeOfPrint, '-') << '\n';
			out << "\t\toutcome \n";
			for (auto state : mSummerStatesOutcome)
			{
				out << "\t\t\t" << state.first << " <= ";
				out << " tot: " << mSummerStatesOutcome[state.first].total;
				out << " | ";
				out << "min: " << mSummerStatesOutcome[state.first].min;
				out << " | ";
				out << "max: " << mSummerStatesOutcome[state.first].max;
				out << " | ";
				out << "avg: " << mSummerStatesOutcome[state.first].total / mSummerEntries << "\n\n";
			}
		}
	}

	if (winter == true)
	{
		out << "\twinter:\n";

		if (consumption == true)
		{
			out << "\t" << std::string(consts::defaultSizeOfPrint, '-') << '\n';
			out << "\t\tconsumption:\n";
			out << "\t\t\ttot: " << mWinterConsumption.total;
			out << " | ";
			out << "min: " << mWinterConsumption.min;
			out << " | ";
			out << "max: " << mWinterConsumption.max;
			out << " | ";
			out << "avg: " << mWinterConsumption.total / mWinterEntries << '\n';
		}

		if (production == true)
		{
			out << "\t\t" << std::string(consts::defaultSizeOfPrint, '-') << '\n';
			out << "\t\tproduction:\n";
			out << "\t\t\ttot: " << mWinterProduction.total;
			out << " | ";
			out << "min: " << mWinterProduction.min;
			out << " | ";
			out << "max: " << mWinterProduction.max;
			out << " | ";
			out << "avg: " << mWinterProduction.total / mWinterEntries << '\n';
		}

		if (storage == true)
		{
			out << "\t\t" << std::string(consts::defaultSizeOfPrint, '-') << '\n';
			out << "\t\tstorage:\n";
			out << "\t\t\tmin: " << mWinterStorage.min;
			out << " | ";
			out << "max: " << mWinterStorage.max;
			out << " | ";
			out << "avg: " << mWinterStorage.total / mWinterEntries << '\n';
		}

		if (overflow == true)
		{
			out << "\t\t" << std::string(consts::defaultSizeOfPrint, '-') << '\n';
			out << "\t\toverflow:\n";
			out << "\t\t\ttot: " << mWinterOverflow.total;
			out << " | ";
			out << "max: " << mWinterOverflow.max << '\n';
		}

		if (deficit == true)
		{
			out << "\t\t" << std::string(consts::defaultSizeOfPrint, '-') << '\n';
			out << "\t\tdeficit:\n";
			out << "\t\t\ttot: " << mWinterDeficit.total;
			out << " | ";
			out << "max: " << mWinterDeficit.max << '\n';
		}

		if (incomeFlows == true)
		{
			out << "\t\t" << std::string(consts::defaultSizeOfPrint, '-') << '\n';
			out << "\t\tincome \n";
			for (auto state : mWinterStatesIncome)
			{
				out << "\t\t\t" << state.first << " => ";
				out << " tot: " << state.second.total;
				out << " | ";
				out << "min: " << state.second.min;
				out << " | ";
				out << "max: " << state.second.max;
				out << " | ";
				out << "avg: " << state.second.total / mWinterEntries << "\n\n";
			}
		}

		if (outcomeFlows == true)
		{
			out << "\t\t" << std::string(consts::defaultSizeOfPrint, '-') << '\n';
			out << "\t\toutcome \n";
			for (auto state : mWinterStatesOutcome)
			{
				out << "\t\t\t" << state.first << " <= ";
				out << " tot: " << mWinterStatesOutcome[state.first].total;
				out << " | ";
				out << "min: " << mWinterStatesOutcome[state.first].min;
				out << " | ";
				out << "max: " << mWinterStatesOutcome[state.first].max;
				out << " | ";
				out << "avg: " << mWinterStatesOutcome[state.first].total / mWinterEntries << "\n\n";
			}
		}
	}

	return out.str();
}
//----------------------------------------------------------------------------------------