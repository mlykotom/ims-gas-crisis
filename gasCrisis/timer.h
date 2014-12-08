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
#include <vector>
#include <map>
#include "consts.h"
#include "date_time.h"
#include "state.h"
#include "errors.h"

class cTimer
{
public:
	cTimer(int startY = 0, int startM = 0, int startD = 0, int endY = 0, int endM = 0, int endD = 0):
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
	double mCoeficient;

	cDateTime mStartTime;
	cDateTime mEndTime;
	cDateTime mActualTime;

public:
	void start(void);

	void addState(cState *state){
		if (this->mStates.find(state->getName()) != this->mStates.end()) throw PrgException(consts::E_CFG_DUPLICATE_STATES);
		this->mStates[state->getName()] = state;
	}

	void setStartTime(int startY, int startM, int startD){
		mActualTime = *(mStartTime.setTime(startY, startM, startD));		
	}

	void setEndTime(int endY, int endM, int endD){
		mEndTime.setTime(endY, endM, endD);
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