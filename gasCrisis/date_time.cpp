/**
** IMS - Modelovani a simulace
**
** projekt: Plynova krize v Evrope
** autori:	Jakub Tutko, xtutko00@stud.fit.vutbr.cz
**			Tomas Mlynaric, xmlyna06@stud.fit.vutbr.cz
** rok:		2014/2015
**/


//----------------------------------------------------------------------------------------
#include "date_time.h"
//----------------------------------------------------------------------------------------
// inkrementovanie casu o hodinu v objekte
void cDateTime::addHour(void)
{
	mHour++;
	
	// ak presiel jeden den ikrementuje sa den
	if (mHour <= 23)
	{
		return;
	}
	else
	{
		mHour = 0;
		mDay++;
	}

	// ak presiel cely mesiac inkrementuje sa mesiac
	if (mDay <= getMonthLenght())
	{ 
		return;
	}
	else
	{
		mDay = 1;
		mMonth++;
	}

	// ak presiel cely rok inkrementuje sa rok
	if (mMonth <= 12)
	{
		return;
	}
	else
	{
		mMonth = 1;
		mYear++;
	}
}
//----------------------------------------------------------------------------------------
// metoda vrati dlzku mesiaca ktory je aktualny v objekte
// @return dlzka aktualneho mesiaca
unsigned cDateTime::getMonthLenght(void)
{
	switch (mMonth)
	{
	case 1:
		return 31;

	case 2:
		// zistovanie ci sa jedna o prestupny rok
		if (((mYear % 4) == 0) && ((mYear % 100) == 0) && ((mYear % 400) == 0))
			return 29;
		else
			return 28;

	case 3:
		return 31;

	case 4:
		return 30;

	case 5:
		return 31;

	case 6:
		return 30;

	case 7:
		return 31;

	case 8:
		return 31;

	case 9:
		return 30;

	case 10:
		return 31;

	case 11:
		return 30;

	case 12:
		return 31;

	default:
		return 0;
	}
}
//----------------------------------------------------------------------------------------
// metoda porovna dva casy i su totozne
// @date datum na porovnanie
// @return true => su rovnake, false => nie su rovnake
bool cDateTime::equal(cDateTime& date)
{
	if (mHour != date.getHour())
	{
		return false;
	}
	else if (mDay != date.getDay())
	{
		return false;
	}
	else if (mMonth != date.getMonth())
	{
		return false;
	}
	else if (mYear != date.getYear())
	{
		return false;
	}
	else
	{
		return true;
	}
}
//----------------------------------------------------------------------------------------
// metoda oznami ake rocne obdobie je aktualne
// @eturn leto => true, zima => false
bool cDateTime::isSummer(void)
{
	// leto sa berie od 1.4. do 31.9.
	if ((mMonth <= 3) || (mMonth >= 10))
	{
		return false;
	}
	else
	{
		return true;
	}
}
//----------------------------------------------------------------------------------------
// metoda ziska aktualny koeficient daneho mesiaca
// koeficienty:
//		 1 => 110
//		 2 => 100
//		 3 => 90
//		 4 => 110
//		 5 => 100
//		 6 => 90
//		 7 => 90
//		 8 => 100
//		 9 => 110
//		10 => 90
//		11 => 100
//		12 => 110
double cDateTime::getCoeficient()
{
	if (mMonth <= 3)
	{
		return (120 - (mMonth * 10)) / 100.0;
	}
	else if (mMonth <= 6)
	{
		return (120 - ((mMonth - 3) * 10)) / 100.0;
	}
	else if (mMonth <= 9)
	{
		return (80 + ((mMonth - 6) * 10)) / 100.0;
	}
	else
	{
		return (80 + ((mMonth - 9) * 10)) / 100.0;
	}
}
//----------------------------------------------------------------------------------------