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
		mStartTime(startY, startM, startD), 
		mEndTime(endY, endM, endD), 
		mActualTime(startY, startM, startD)
	{}

	~cTimer(void)
	{
		for (int i = 0; i < mStates.size(); ++i)
			delete mStates[i];
	}

private:
	std::vector<cState *> mStates;

	bool mSummer;

	cDateTime mStartTime;
	cDateTime mEndTime;
	cDateTime mActualTime;

public:
	void start(void);

	void addState(cState *state)
	{
		this->mStates.push_back(state);
	}
};