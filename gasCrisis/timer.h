/**
** IMS projekt
*/

#pragma once

#include <string>
#include <vector>
#include <map>
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
		for (auto st : mStates){
			delete st.second;
		}
		mStates.clear();
	}

private:
	std::map<std::string, cState *> mStates;

	bool mSummer;

	cDateTime mStartTime;
	cDateTime mEndTime;
	cDateTime mActualTime;

public:
	void start(void);

	void addState(cState *state){
		if (this->mStates.find(state->getName()) != this->mStates.end()) throw PrgException(consts::E_CFG_DUPLICATE_STATES);
		this->mStates[state->getName()] = state;
	}


	std::map<std::string, cState *> getAllStates(){
		return this->mStates;
	}

	cState *getState(const std::string name) try{
		return this->getAllStates().at(name);
	}
	catch (std::out_of_range){
		return nullptr;
	}


};