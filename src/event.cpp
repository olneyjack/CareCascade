//
//  event.cpp
//  priorityQ
//
//  Created by Jack Olney on 08/10/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#include "event.h"
#include "eventQ.h"

extern eventQ * theQ;

/* Define constructor */
event::event(const double Time) :
eventTime(Time),
cancelled(false)
{
	theQ->AddEvent(this);
}

/* Define desctructor */
event::~event()
{}
