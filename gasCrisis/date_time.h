/**
** IMS - Modelovani a simulace
**
** projekt: Plynova krize v Evrope
** autori:	Jakub Tutko, xtutko00@stud.fit.vutbr.cz
**			Tomas Mlynaric, xmlyna06@stud.fit.vutbr.cz
** rok:		2014/2015
**/

#pragma once

#include <string>
#include <sstream>

class cDateTime{
public:
	cDateTime() :mYear(0), mMonth(0), mDay(0), mHour(0){}

	cDateTime(int year, int month, int day, int hour = 0):
		mYear((unsigned)year),
		mMonth((unsigned)month),
		mDay((unsigned)day),
		mHour((unsigned)hour)
	{}

private:	
	unsigned int mYear;
	unsigned int mMonth;
	unsigned int mDay;
	unsigned int mHour;

public:
	unsigned getYear() { return this->mYear; }
	unsigned getMonth(){ return this->mMonth; }
	unsigned getDay() { return this->mDay; }
	unsigned getHour(){ return this->mHour; }

	cDateTime * setTime(int y, int m, int d, int h = 0){
		mYear = (unsigned)y;
		mMonth = (unsigned)m;
		mDay = (unsigned)d;
		mHour = (unsigned)h;

		return this;
	}



	std::string render(bool h = false){
		std::ostringstream ret;
		if (mDay < 10) ret << '0';
		ret << mDay;
			ret << '.';			
		if (mMonth < 10) ret << '0';
		ret << mMonth;
			ret << '.';
		ret << mYear;

		if (h) ret << ' ' << mHour;

		return ret.str();
	}

	void addHour();

	bool equal(cDateTime& date);
	bool isSummer(void);
	double getCoeficient();

private:
	unsigned getMonthLenght(void);
};