#pragma once

class cDateTime{
public:
	cDateTime() :mYear(0), mMonth(0), mDay(0), mHour(0){}

	cDateTime(int year, int month, int day, int hour = 0){
		this->mYear = (unsigned)year;
		this->mMonth = (unsigned)month;
		this->mDay = (unsigned)day;
		this->mHour = (unsigned)hour;
	}

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

	void addHour();

	bool equal(cDateTime& date);
	bool isSummer(void);

private:
	unsigned getMonthLenght(void);
};