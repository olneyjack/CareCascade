//
//  eventQ.h
//  priorityQ
//
//  Created by Jack Olney on 08/10/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#ifndef __priorityQ__eventQ__
#define __priorityQ__eventQ__

#include <stdio.h>
#include "event.h"
#include <queue>

using namespace std;

/* Define operator() for comparison class */
struct timeComparison {bool operator()(const event *lhs, const event *rhs) const;};

/* Define eventQ class */
class eventQ {
public:
	eventQ(const double theStartTime, const double theStopTime); //constructor
	~eventQ(); //destructor
	
	/* Methods */
	void AddEvent(event * const theEvent);
	void RunEvents();
	
	/* Accessor methods */
	size_t Size() const; //size_t is a type able to represent the size of any object in bytes.
	bool Empty() const;
	double GetTime() const { return currentTime; }
	double GetIncrementalTime() const { return incrementalTime; }
	
	/* Methods */
	event * GetTop();
	void UpdateTime(const double theTime);
	
private:
	priority_queue<event*, vector<event*>, timeComparison> iQ;
	double currentTime;
	double stopTime;
	double incrementalTime;
};

#endif /* defined(__priorityQ__eventQ__) */
