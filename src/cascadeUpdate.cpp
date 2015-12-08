//
//  updateCascade.cpp
//  priorityQ
//
//  Created by Jack Olney on 22/10/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#include <iostream>
#include "toolbox.h"
#include "cascadeUpdate.h"
#include "person.h"
#include "event.h"
#include "events.h"
#include "cascadeEvents.h"
#include "interventionEvents.h"
#include "rng.h"

extern Rng * theRng;

using namespace std;

////////////////////
////////////////////

void UpdateTreatmentGuidelines(person * const thePerson, unsigned int theCd4, unsigned int theWho)
{
	thePerson->UpdateTxGuidelines(theCd4,theWho);
}

////////////////////
////////////////////

void ScheduleVctHivTest(person * const thePerson, const double theTime)
{
	if(thePerson->GetBirthDay() != 0 && theTime >= 12418.5)
		new VctHivTest(thePerson,theTime + theRng->SampleExpDist(vctHivTestTime),vctPocFlag);
}
////////////////////
////////////////////

void SchedulePictHivTest(person * const thePerson, const double theTime)
{
	if(thePerson->GetBirthDay() != 0 && theTime >= 12418.5) {
		if(thePerson->GetCurrentWho() < 3) {
			if(!thePerson->GetDiagnosedState())
				new PictHivTest(thePerson,theTime + theRng->SampleExpDist(pictHivTestTime_AsymptomaticOblivious));
			else if(thePerson->GetDiagnosedState() && !thePerson->GetEverCd4TestResultState())
				new PictHivTest(thePerson,theTime + theRng->SampleExpDist(pictHivTestTime_AsymptomaticNoCd4Result));
			else if(thePerson->GetEverCd4TestResultState() && (thePerson->GetCurrentCd4() > thePerson->GetCd4TxGuideline() || thePerson->GetCurrentWho() < thePerson->GetWhoTxGuideline()))
				new PictHivTest(thePerson,theTime + theRng->SampleExpDist(pictHivTestTime_AsymptomaticCd4ResultNotEligible));
			else if(thePerson->GetEverCd4TestResultState() && (thePerson->GetCurrentCd4() <= thePerson->GetCd4TxGuideline() || thePerson->GetCurrentWho() >= thePerson->GetWhoTxGuideline()))
				new PictHivTest(thePerson,theTime + theRng->SampleExpDist(pictHivTestTime_AsymptomaticCd4ResultEligible));
		} else {
			if(!thePerson->GetDiagnosedState())
				new PictHivTest(thePerson,theTime + theRng->SampleExpDist(pictHivTestTime_SymptomaticOblivious));
			else if(thePerson->GetDiagnosedState() && !thePerson->GetEverCd4TestResultState())
				new PictHivTest(thePerson,theTime + theRng->SampleExpDist(pictHivTestTime_SymptomaticNoCd4Result));
			else if(thePerson->GetEverCd4TestResultState())
				new PictHivTest(thePerson,theTime + theRng->SampleExpDist(pictHivTestTime_SymptomaticCd4Result));
		}
	}
}

////////////////////
////////////////////

bool VctLinkage(person * const thePerson)
{
	if(theRng->Sample(vctProbLink))
		return true;
	else
		return false;
}

////////////////////
////////////////////

bool PictLinkage(person * const thePerson)
{
	if(theRng->Sample(pictProbLink))
		return true;
	else
		return false;
}

////////////////////
////////////////////

void ScheduleInitialCd4TestAfterHct(person * const thePerson, const double theTime)
{
	new Cd4Test(thePerson,theTime + theRng->SampleExpDist(hctCd4TestTime[thePerson->GetCurrentCd4()-1]));
}

////////////////////
////////////////////

void SchedulePreArtCd4Test(person * const thePerson, const double theTime)
{
	new Cd4Test(thePerson,theTime + theRng->SampleExpDist(cd4TestTime));
}

////////////////////
////////////////////

void ScheduleCd4TestResult(person * const thePerson, const double theTime)
{
	new Cd4TestResult(thePerson,theTime + theRng->SampleExpDist(cd4ResultTime));
}

////////////////////
////////////////////

void SchedulePreArtResultDropout(person * const thePerson, const double theTime)
{
	new PreArtDropout(thePerson,theTime + theRng->SampleExpDist(cd4ResultTime));
}

////////////////////
////////////////////

void SchedulePreArtTestDropout(person * const thePerson, const double theTime)
{	
	new PreArtDropout(thePerson,theTime + theRng->SampleExpDist(cd4TestTime));
}

////////////////////
////////////////////

bool ReceiveCd4TestResult(person * const thePerson, const double theTime)
{
	if(thePerson->GetCd4TestCount() <= 1) {
	 	switch(thePerson->GetDiagnosisRoute()) {
			case 1: return theRng->Sample(hctShortTermRetention);  break;
		 	case 2: return theRng->Sample(vctShortTermRetention);  break;
		 	case 3: return theRng->Sample(pictShortTermRetention); break;
		 	default: thePerson->SetInCareState(false,theTime); return false;
	 	}
	} else {
		switch(thePerson->GetDiagnosisRoute()) {
			case 1: return theRng->Sample(hctLongTermRetention);  break;
		 	case 2: return theRng->Sample(vctLongTermRetention);  break;
		 	case 3: return theRng->Sample(pictLongTermRetention); break;
		 	default: thePerson->SetInCareState(false,theTime); return false;
	 	}
	}
}

////////////////////
////////////////////

bool AttendCd4TestResult(person * const thePerson, const double theTime)
{
	if(theRng->Sample(cd4ResultProbAttend) && !thePerson->GetEverArt())
		return thePerson->Alive();
	else {
		thePerson->SetInCareState(false,theTime);
		return false;
	}
}

////////////////////
////////////////////

bool SecondaryCd4Test(person * const thePerson, const double theTime)
{
	switch(thePerson->GetDiagnosisRoute()) {
		case 1: return theRng->Sample(hctProbSecondaryCd4Test); break;
		case 2: return theRng->Sample(vctProbSecondaryCd4Test); break;
		case 3: return theRng->Sample(pictProbSecondaryCd4Test); break;
		default: thePerson->SetInCareState(false,theTime); return false;
	}
	
}

////////////////////
////////////////////

void FastTrackArt(person * const thePerson, const double theTime)
{
	thePerson->SetArtAtEnrollment(true);
	new ArtInitiation(thePerson,theTime);
}

////////////////////
////////////////////

void ScheduleArtInitiation(person * const thePerson, const double theTime)
{
	new ArtInitiation(thePerson,theTime + theRng->SampleExpDist(artInitiationTime));
}

////////////////////
////////////////////

void ScheduleArtDropout(person * const thePerson, const double theTime)
{
	const double artDropoutDate = theRng->SampleExpDist(artDropoutTimeOneYear);
	
	if(artDropoutDate < 365.25)
		new ArtDropout(thePerson,theTime + artDropoutDate);
	else
		new ArtDropout(thePerson,theTime + 365.25 + theRng->SampleExpDist(artDropoutTimeTwoYear));
	
}

////////////////////
////////////////////
