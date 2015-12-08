//
//  eventQ.cpp
//  priorityQ
//
//  Created by Jack Olney on 08/10/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#include <iostream>
#include "macro.h"
#include "event.h"
#include "events.h"
#include "eventQ.h"
#include "rng.h"
#include "person.h"
#include "cohort.h"
#include "update.h"
#include "toolbox.h"

extern Rng * theRng;
extern eventQ * theQ;

using namespace std;

/* Define operator for timeComparison */
bool timeComparison::operator()(const event *lhs, const event *rhs) const
{
	return lhs->GetTime() > rhs->GetTime();
}

/* Define constructor */
eventQ::eventQ(const double theStartTime, const double theStopTime) :
currentTime(theStartTime),
stopTime(theStopTime),
incrementalTime(0)
{}

/* Define destructor */
eventQ::~eventQ()
{}

/* Define AddEvent() */
void eventQ::AddEvent(event * const theEvent)
{
	iQ.push(theEvent);
}

/* Define RunEvents() */
void eventQ::RunEvents()
{
	while(!Empty() && currentTime < stopTime) {
		event * nextEvent = GetTop();
		UpdateTime(nextEvent->GetTime());
		if(!nextEvent->Cancelled())
			if(nextEvent->CheckValid())
				nextEvent->Execute();
		delete nextEvent;
		D(cout << "\tcurrentTime is = " << currentTime << " (year = " << currentTime / 365.25 << ")" <<  endl);
		D(cout << "\ttheQ size is = " << theQ->Size() << endl);
	}
	while(!Empty())
		delete GetTop();
	return;
}

/* Define Empty() */
bool eventQ::Empty() const
{
	return iQ.empty();
}

/* Define GetTop() */
event * eventQ::GetTop()
{
	event * theEvent = iQ.top();
	iQ.pop();
	return theEvent;
}

/* Define Size() */
size_t eventQ::Size() const
{
	return iQ.size();
}

/* Define UpdateTime() */
void eventQ::UpdateTime(const double theTime)
{
	incrementalTime = theTime - currentTime;
	currentTime = theTime;
}
