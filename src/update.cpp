//
//  update.cpp
//  priorityQ
//
//  Created by Jack Olney on 16/10/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#include <iostream>
#include "update.h"
#include "cascadeUpdate.h"
#include "person.h"
#include "event.h"
#include "events.h"
#include "cascadeEvents.h"
#include "rng.h"
#include "eventQ.h"

extern Rng * theRng;
extern eventQ * theQ;

using namespace std;

////////////////////
////////////////////

void SeedTreatmentUpdate(person * const thePerson, const double theTime)
{
	if(theTime > 12418.5)
	    new SeedInitialHivTests(thePerson,theTime);
	else
	    new SeedInitialHivTests(thePerson,12418.5);
	 
	if(theTime > 14975.25)
	    new SeedTreatmentGuidelinesUpdate(thePerson,theTime);
	else
	    new SeedTreatmentGuidelinesUpdate(thePerson,14975.25);
	 
	// if(theTime > 16436.25)
	//     new SeedTreatmentGuidelinesUpdate(thePerson,theTime);
	// else
	//     new SeedTreatmentGuidelinesUpdate(thePerson,16436.25);
}

////////////////////
////////////////////

void ScheduleCd4Update(person * const thePerson, const double theTime)
{
	//Cd4Time [WHO-1] [CD4-2 (4,3,2)]
	const double Cd4DeclineTime [4] [3] =
	{
		{5.13562000,4.16995000,6.58904000},
		{5.13562000,4.16995000,6.58904000},
		{3.78948223,3.07693159,4.86193487},
		{0.51460820,0.41784448,0.66024628}
	};
	
	//Cd4TimeArt [WHO-1] [CD4-1 (1,2)]
	const double Cd4RecoverTimeArt [4] [2] =
	{
		{0.20215333,0.44804333},
		{0.20215333,0.44804333},
		{0.34424606,0.76297110},
		{0.82203553,1.82192167}
	};
	
	if((!thePerson->GetArtInitiationState() || (thePerson->GetArtInitiationState() && !thePerson->GetArtAdherenceState())) && thePerson->GetCurrentCd4() > 1) {
		new Cd4Decline(thePerson, theTime + theRng->SampleExpDist(Cd4DeclineTime [thePerson->GetCurrentWho()-1] [thePerson->GetCurrentCd4()-2] * 365.25));
	}
	else if(thePerson->GetArtInitiationState() && thePerson->GetArtAdherenceState() && thePerson->GetCurrentCd4() < 3) {
		new Cd4Recover(thePerson, theTime + theRng->SampleExpDist(Cd4RecoverTimeArt [thePerson->GetCurrentWho()-1] [thePerson->GetCurrentCd4()-1] * 365.25));
	}
	
}

////////////////////
////////////////////

void ScheduleWhoUpdate(person * const thePerson, const double theTime)
{
	//WhoTime [WHO-1][CD4-1]
	const double WhoDeclineTime [3][4] =
	{
		{0.37411092,3.25215000,3.25215000,3.25215000},
		{0.52457204,4.56011000,4.56011000,4.56011000},
		{0.27840069,2.42014000,2.42014000,2.42014000}
	};
	
	//WhoTimeArt [WHO-1][CD4-1]
	const double WhoDeclineTimeArt [3][4] =
	{
		{0.41895362,3.64196805,3.64196805,3.64196805},
		{0.58744972,5.10670631,5.10670631,5.10670631},
		{0.31177111,2.71022940,2.71022940,2.71022940}
	};
	
	//WhoRecoverTime [WHO from->to] = {2->1,3->2,4->3}
	const double WhoRecoverTime [3] = {0.32760300,14.38530000,3.36363000};
	const double WhoRecoverTimeArt [3] = {0.65476400,0.32730800,0.04945540};

	if((!thePerson->GetArtInitiationState() || (thePerson->GetArtInitiationState() && !thePerson->GetArtAdherenceState()))) {
		if(thePerson->GetCurrentWho() < 4) {
			new WhoDecline(thePerson, theTime + theRng->SampleExpDist(WhoDeclineTime [thePerson->GetCurrentWho()-1] [thePerson->GetCurrentCd4()-1] * 365.25));	
		}
		if(thePerson->GetCurrentWho() > 1) {
			new WhoRecover(thePerson, theTime + theRng->SampleExpDist(WhoRecoverTime [thePerson->GetCurrentWho()-2] * 365.25));
		}
	} else if(thePerson->GetArtInitiationState() && thePerson->GetArtAdherenceState()) {
		if(thePerson->GetCurrentWho() < 4) {
			new WhoDecline(thePerson, theTime + theRng->SampleExpDist(WhoDeclineTimeArt [thePerson->GetCurrentWho()-1] [thePerson->GetCurrentCd4()-1] * 365.25));
		}	
		if(thePerson->GetCurrentWho() > 1) {
			new WhoRecover(thePerson, theTime + theRng->SampleExpDist(WhoRecoverTimeArt [thePerson->GetCurrentWho()-2] * 365.25));
		}
	}
}

////////////////////
////////////////////

void ScheduleVectorUpdate(person * const thePerson, const double theTime)
{
	new VectorUpdate(thePerson,theTime + 1); //+1 to get into the next time bracket.
}

////////////////////
////////////////////

void ScheduleIncidence(population * thePopulation)
{
	for(size_t i=0; i<66; i++)
		new Incidence(thePopulation,i * 365.25,i);
}

////////////////////
////////////////////

void ScheduleBetaCalculation(population * thePopulation)
{
	if(theQ->GetTime() < thePopulation->GetReferenceYear() - 1)
		new BetaCalculation(thePopulation,thePopulation->GetReferenceYear() - 1);
}

////////////////////
////////////////////
