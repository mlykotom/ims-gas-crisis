//----------------------------------------------------------------------------------------
#include "date_time.h"
//----------------------------------------------------------------------------------------
void cDateTime::addHour(void)
{
	mHour++;
	
	if (mHour <= 23)
	{
		return;
	}
	else
	{
		mHour = 0;
		mDay++;
	}

	if (mDay <= getMonthLenght())
	{ 
		return;
	}
	else
	{
		mDay = 1;
		mMonth++;
	}

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
unsigned cDateTime::getMonthLenght(void)
{
	switch (mMonth)
	{
	case 1:
		return 31;

	case 2:
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
bool cDateTime::isSummer(void)
{
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
double cDateTime::getCoeficient()
{
	if (mMonth <= 3)
	{
		return (200 - (mMonth * 50)) / 100.0;
	}
	else if (mMonth <= 6)
	{
		return (200 - ((mMonth - 3) * 50)) / 100.0;
	}
	else if (mMonth <= 9)
	{
		return (0 + ((mMonth - 6) * 50)) / 100.0;
	}
	else
	{
		return (0 + ((mMonth - 9) * 50)) / 100.0;
	}
}
//----------------------------------------------------------------------------------------