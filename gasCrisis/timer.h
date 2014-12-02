/**
** IMS projekt
*/

#pragma once

#include <string>
#include <vector>
#include "consts.h"
#include "date_time.h"
#include "state.h"

class cTimer
{
public:
	cTimer(int startY, int startM, int startD, int endY, int endM, int endD):
		mStartTime(startY, startM, startD), mEndTime(endY, endM, endD)
	{}

private:
	std::vector<cState *> mStates;

	cDateTime mStartTime;
	cDateTime mEndTime;
	cDateTime mActualTime;

public:
	void start(void);

	void addState(cState state);

	void setStartTime(unsigned time);
	void setEndTime(unsigned time);

	// TODO zmenit na actualTime
	cDateTime getActualTime(void){ return mStartTime; }
};