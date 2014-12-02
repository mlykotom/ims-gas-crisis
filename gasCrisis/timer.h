/**
** IMS projekt
*/

#pragma once

#include <string>
#include <vector>
#include "state.h"

class cTimer
{
public:
	cTimer(unsigned startTime, unsigned endTime) : mStartTime(startTime), mEndTime(endTime) {}

private:
	std::vector<cState *> mStates;

	unsigned mStartTime;
	unsigned mEndTime;
	unsigned mActualTime;

public:
	void start(void);

	void addState(cState state);

	void setStartTime(unsigned time);
	void setEndTime(unsigned time);

	unsigned getActualTime(void);
};