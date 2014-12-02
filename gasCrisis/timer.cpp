//----------------------------------------------------------------------------------------
#include "timer.h"
//----------------------------------------------------------------------------------------
void cTimer::start(void)
{
	// ziskanie leta/zimy
	mSummer = mActualTime.isSummer();

	// nastavenie vsetkym statom leto/zima
	for (int i = 0; i < mStates.size(); i++)
	{
		if (mSummer == true)
		{
			mStates[i]->setSummer();
		}
		else
		{
			mStates[i]->setWinter();
		}
	}
	
	// spustenie simulacie
	while (mActualTime.equal(mEndTime) != true)
	{
		// kazdy stat spracuje svoje stavy za jednu hodinu
		for (int i = 0; i < mStates.size(); i++)
		{
			mStates[i]->behaviour();
		}

		// inkrementovanie casu
		mActualTime.addHour();

		// ak sa zmenilo rocne obdobie ohlasi sa to vsetkym statom
		if (mSummer != mActualTime.isSummer())
		{
			// ulozenie aktualneho rocneho obdobia
			mSummer = mActualTime.isSummer();

			// ohlasenie vsetkym statom o zmene obdobia
			for (int i = 0; i < mStates.size(); i++)
			{
				if (mSummer == true)
				{
					mStates[i]->setSummer();
				}
				else
				{
					mStates[i]->setWinter();
				}
			}
		}
	}
}
//----------------------------------------------------------------------------------------