//----------------------------------------------------------------------------------------
#include "timer.h"
//----------------------------------------------------------------------------------------
void cTimer::start(void)
{
	// ziskanie leta/zimy
	mSummer = mActualTime.isSummer();

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
	}
	
	// spustenie simulacie
	while (mActualTime.equal(mEndTime) != true)
	{
		// kazdy stat spracuje svoje stavy za jednu hodinu
		for (auto state : mStates)
		{
			state.second->behaviour();
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
	}
}
//----------------------------------------------------------------------------------------