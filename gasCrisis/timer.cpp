//----------------------------------------------------------------------------------------
#include "timer.h"
//----------------------------------------------------------------------------------------
void cTimer::start(void)
{
	// ziskanie leta/zimy
	mSummer = mActualTime.isSummer();

	// ziskanie koeficientu
	mCoeficient = mActualTime.getCoeficient();

	// nastavenie vsetkym statom leto/zima
	for (auto state : mStates)
	{	
		if (mSummer == true)
		{
			state.second->setSummer();
		}
		else
		{
			state.second->setWinter();
		}

		state.second->changeCoeficient(mCoeficient);
	}
	
	std::cout << "Simulation started..." << std::endl;

	// spustenie simulacie
	while (mActualTime.equal(mEndTime) != true)
	{
		// kazdy stat spracuje svoje stavy za jednu hodinu
		for (auto state : mStates)
		{
			state.second->behaviour(&mActualTime);
		}

		// inkrementovanie casu
		mActualTime.addHour();

		// ak sa zmenilo rocne obdobie ohlasi sa to vsetkym statom
		if (mSummer != mActualTime.isSummer())
		{
			// ulozenie aktualneho rocneho obdobia
			mSummer = mActualTime.isSummer();

			// ohlasenie vsetkym statom o zmene obdobia
			for (auto state : mStates)
			{
				if (mSummer == true)
				{
					state.second->setSummer();
				}
				else
				{
					state.second->setWinter();
				}
			}
		}

		// zmenie koeficientov mesiacov
		if (mCoeficient != mActualTime.getCoeficient())
		{
			mCoeficient = mActualTime.getCoeficient();
			
			for (auto state : mStates)
			{
				state.second->changeCoeficient(mCoeficient);
			}
		}
	}

	// vypisanie statistik
	for (auto state : mStates)
	{
		std::cout << state.second->getStats(true, true, true, true, true, true, true, true, true, true);
	}

	std::cout << "Simulation ended..." << std::endl;
}
//----------------------------------------------------------------------------------------