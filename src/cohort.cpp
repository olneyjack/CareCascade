//
//  cohort.cpp
//  priorityQ
//
//  Created by Jack Olney on 15/10/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#include <iostream>
#include "cohort.h"
#include "person.h"
#include "event.h"
#include "events.h"
#include "rng.h"

extern Rng * theRng;

cohort::cohort(population * const thePop, const unsigned int Size, const unsigned int StartTime) :
iPop(thePop),
cohortSize(Size),
cohortStartTime(StartTime)
{
	new CohortStart(this,cohortStartTime);
}

cohort::~cohort()
{}

unsigned int cohort::GetCohortSize() const
{
	return cohortSize;
}

void cohort::GenerateCohort(const double theTime)
{
	for(size_t i = 0; i < cohortSize; i++)
		ScheduleNewPerson(theRng->doub() * 365.25 + theTime); //The arguement here specifies when an individual will enter the model.
	
	SelfDestruct(); // This kills the cohort instance.
}

void cohort::ScheduleNewPerson(const double Time)
{
	new PersonStart(iPop,Time);
}

void cohort::SelfDestruct()
{
	delete this;
}
