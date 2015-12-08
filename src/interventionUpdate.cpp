//
//  interventionUpdate.cpp
//  priorityQ
//
//  Created by Jack Olney on 03/11/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#include <iostream>
#include "interventionUpdate.h"
#include "interventionEvents.h"
#include "cascadeUpdate.h"
#include "cascadeEvents.h"
#include "rng.h"
#include "toolbox.h"

extern Rng * theRng;

using namespace std;

////////////////////
////////////////////

void ScheduleHctHivTest(person * const thePerson, const double theTime, const bool poc)
{
	if(thePerson->GetBirthDay() != 0 && theTime >= 14610 && theTime < 21915) {
		const double diagDay = theRng->SampleExpDist(hctHivTestTime);
		if(diagDay <= 365.25)
			new HctHivTest(thePerson,theTime + diagDay,poc);
	}
}

////////////////////
////////////////////

void SchedulePerpetualHctHivTest(person * const thePerson, const double theTime)
{
	if(thePerson->GetBirthDay() != 0 && theTime >= 14610 && theTime < 21915)
		new HctHivTest(thePerson,theTime + (theRng->doub() * 365.25),0);
}

////////////////////
////////////////////

bool HctLinkage(person * const thePerson, const double theTime)
{
    if(theTime < 14975.25) {
        if(thePerson->GetDiagnosisCount() > 1) {
            if(theRng->Sample(hctProbLinkPreviouslyDiagnosedRollOut))
                return true;
            else
                return false;
        } else {
            if(theRng->Sample(hctProbLinkRollOut))
                return true;
            else
                return false;
        }
    } else {
        if(thePerson->GetDiagnosisCount() > 1) {
            if(theRng->Sample(hctProbLinkPreviouslyDiagnosed))
                return true;
            else
                return false;
        } else {
            if(theRng->Sample(hctProbLink))
                return true;
            else
                return false;
        }
    }
}

////////////////////
////////////////////

void ScheduleImmediateArt(person * const thePerson, const double theTime)
{
	new ArtInitiation(thePerson,theTime);
}

////////////////////
////////////////////
