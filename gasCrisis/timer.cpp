/**
** IMS - Modelovani a simulace
**
** projekt: Plynova krize v Evrope
** autori:	Jakub Tutko, xtutko00@stud.fit.vutbr.cz
**			Tomas Mlynaric, xmlyna06@stud.fit.vutbr.cz
** rok:		2014/2015
**/

//----------------------------------------------------------------------------------------
#include "timer.h"
//----------------------------------------------------------------------------------------
// metoda spusti simulaciu
void cTimer::start(void)
{
	// ziskanie leta/zimy
	mSummer = mActualTime.isSummer();

	// ziskanie koeficientu mesiaca
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
	
	// vypis o zacati simulacie
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

		// zmena koeficientov mesiacov
		if (mCoeficient != mActualTime.getCoeficient())
		{
			// ziskanie koeficientu mesiaca
			mCoeficient = mActualTime.getCoeficient();
			
			// oznameneie kazdemu statu o zmene koeficientu
			for (auto state : mStates)
			{
				state.second->changeCoeficient(mCoeficient);
			}
		}
	}

	// otvorenie suboru pre vypisanie statistik
	std::ofstream outSummary(consts::outputSummary);
	if (!outSummary.is_open()){
		std::cerr << inout::ShowError("Nelze otevrit soubor " + consts::outputSummary);
		return;
	}

	// vypisanie statistik
	for (auto state : mStates)
	{
		outSummary << state.second->getStats(true, true, true, true, true, true, true, true, true, true);
	}

	// oznameneie o ukonceni simulacie
	std::cout << "Simulation ended..." << std::endl;
}
//----------------------------------------------------------------------------------------