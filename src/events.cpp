//
//  events.cpp
//  priorityQ
//
//  Created by Jack Olney on 09/10/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#include <iostream>
#include "events.h"
#include "event.h"
#include "person.h"
#include "update.h"
#include "cascadeUpdate.h"
#include "cohort.h"
#include "impact.h"
#include "outputUpdate.h"
#include "cost.h"
#include "wp19Update.h"

using namespace std;

/////////////////////
/////////////////////

CohortStart::CohortStart(cohort * const iCohort, const double Time) :
event(Time),
pCohort(iCohort)
{}

CohortStart::~CohortStart()
{}

bool CohortStart::CheckValid()
{
	return true;
}

void CohortStart::Execute()
{
	pCohort->GenerateCohort(GetTime());
}

/////////////////////
/////////////////////

VectorUpdate::VectorUpdate(person * const thePerson, const double Time) :
event(Time),
pPerson(thePerson)
{
	pPerson->SetVectorUpdateDate(Time);
	if(Time >= thePerson->GetNatDeathDate()) { Cancel(); }
}

VectorUpdate::~VectorUpdate()
{}

bool VectorUpdate::CheckValid()
{
	if(pPerson->GetVectorUpdateDate() == GetTime())
		return pPerson->Alive();
	else
		return false;
}

void VectorUpdate::Execute()
{
	pPerson->UpdatePopulation();
	// Person-time calculation
	UpdateCarePersonTime(pPerson,GetTime());
}

/////////////////////
/////////////////////

Incidence::Incidence(population * const thePopulation, const double Time, const size_t theIndex) :
event(Time),
pPopulation(thePopulation),
index(theIndex)
{}

Incidence::~Incidence()
{}

bool Incidence::CheckValid()
{
	return true;
}

void Incidence::Execute()
{
	pPopulation->CalculateIncidence(index,GetTime());
}

/////////////////////
/////////////////////

BetaCalculation::BetaCalculation(population * const thePopulation, const double Time) :
event(Time),
pPopulation(thePopulation)
{}

BetaCalculation::~BetaCalculation()
{}

bool BetaCalculation::CheckValid()
{
	return true;
}

void BetaCalculation::Execute()
{
	pPopulation->CalculateBeta();
}

/////////////////////
/////////////////////

Infection::Infection(person * const thePerson, const double Time) :
event(Time),
pPerson(thePerson)
{
	pPerson->SetHivDate(Time);
	if(Time >= thePerson->GetNatDeathDate()) { Cancel(); }
}

Infection::~Infection()
{}

bool Infection::CheckValid()
{
	return pPerson->Alive();
}

void Infection::Execute()
{
	pPerson->Hiv(GetTime());
	// Person-time calculation
	UpdateCarePersonTime(pPerson,GetTime());
}

/////////////////////
/////////////////////

PersonStart::PersonStart(population * const iPop, const double Time) :
event(Time),
pPop(iPop)
{}

PersonStart::~PersonStart()
{}

bool PersonStart::CheckValid()
{
	return true;
}

void PersonStart::Execute()
{
	new person(pPop,GetTime());
}

/////////////////////
/////////////////////

Death::Death(person * const thePerson, const double Time, const bool hivCause) :
event(Time),
pPerson(thePerson),
hivRelated(hivCause)
{
	if(hivCause)
		pPerson->SetHivDeathDate(Time);
}

Death::~Death()
{}

bool Death::CheckValid()
{
	if(hivRelated) {
		if(pPerson->GetHivDeathDate() == GetTime())
			return pPerson->Alive();
		else
			return false;
	} else if(pPerson->Alive()) {
		return true;
	} else {
		delete pPerson;
		return false;
	}
}

void Death::Execute()
{
	// Person-time calculation
	UpdateCarePersonTime(pPerson,GetTime());
	UpdateDaly(pPerson,GetTime());
	WriteCost(pPerson,GetTime());
	pPerson->Kill(GetTime(),hivRelated);
	WriteCare(pPerson,GetTime());
	WriteDeath(pPerson,GetTime());
	if(hivRelated) {
		WriteGuidelinesDeath(pPerson);
		WriteAidsDeath(pPerson,GetTime());
		WriteClinic(pPerson,GetTime());
	} else
		delete pPerson;
}

/////////////////////
/////////////////////

Cd4Decline::Cd4Decline(person * const thePerson, const double Time) :
event(Time),
pPerson(thePerson)
{
	pPerson->SetCd4DeclineDate(Time);
	if(Time >= thePerson->GetNatDeathDate()) { Cancel(); }
}

Cd4Decline::~Cd4Decline()
{}

bool Cd4Decline::CheckValid()
{
	if((!pPerson->GetArtInitiationState() || (pPerson->GetArtInitiationState() && !pPerson->GetArtAdherenceState())) && pPerson->GetCd4DeclineDate() == GetTime())
		return pPerson->Alive();
	else
		return false;
}

void Cd4Decline::Execute()
{
	UpdateDaly(pPerson,GetTime());
	pPerson->SetCurrentCd4Count(pPerson->GetCurrentCd4()-1);
	ScheduleCd4Update(pPerson,GetTime());
	pPerson->AssignHivDeathDate(GetTime());
	pPerson->UpdateInfectiousnessArray();
	// if(pPerson->GetCurrentCd4() == 1)
	// 	SchedulePictHivTest(pPerson,GetTime());
	// Person-time calculation
	UpdateCarePersonTime(pPerson,GetTime());
}

/////////////////////
/////////////////////

Cd4Recover::Cd4Recover(person * const thePerson, const double Time) :
event(Time),
pPerson(thePerson)
{
	pPerson->SetCd4RecoverDate(Time);
	if(Time >= thePerson->GetNatDeathDate()) { Cancel(); }
}

Cd4Recover::~Cd4Recover()
{}

bool Cd4Recover::CheckValid()
{
	if(pPerson->GetArtInitiationState() && pPerson->GetArtAdherenceState() && pPerson->GetCd4RecoverDate() == GetTime())
		return pPerson->Alive();
	else
		return false;
}

void Cd4Recover::Execute()
{
	UpdateDaly(pPerson,GetTime());
	pPerson->SetCurrentCd4Count(pPerson->GetCurrentCd4()+1);
	ScheduleCd4Update(pPerson,GetTime());
	pPerson->AssignHivDeathDate(GetTime());
	pPerson->UpdateInfectiousnessArray();
	// Person-time calculation
	UpdateCarePersonTime(pPerson,GetTime());
}

/////////////////////
/////////////////////

WhoDecline::WhoDecline(person * const thePerson, const double Time) :
event(Time),
pPerson(thePerson)
{
	pPerson->SetWhoDeclineDate(Time);
	if(Time >= thePerson->GetNatDeathDate()) { Cancel(); }
}

WhoDecline::~WhoDecline()
{}

bool WhoDecline::CheckValid()
{
	if(pPerson->GetWhoDeclineDate() == GetTime())
		return pPerson->Alive();
	else
		return false;
}

void WhoDecline::Execute()
{
	UpdateDaly(pPerson,GetTime());
	pPerson->SetCurrentWhoStage(pPerson->GetCurrentWho()+1);
	ScheduleWhoUpdate(pPerson,GetTime());
	pPerson->AssignHivDeathDate(GetTime());
	if(pPerson->GetCurrentWho() > 2)
		SchedulePictHivTest(pPerson,GetTime());
	// Person-time calculation
	UpdateCarePersonTime(pPerson,GetTime());
}

/////////////////////
/////////////////////

WhoRecover::WhoRecover(person * const thePerson, const double Time) :
event(Time),
pPerson(thePerson)
{
	pPerson->SetWhoRecoverDate(Time);
	if(Time >= thePerson->GetNatDeathDate()) { Cancel(); }	
}

WhoRecover::~WhoRecover()
{}

bool WhoRecover::CheckValid()
{
	if(pPerson->GetWhoRecoverDate() == GetTime())
		return pPerson->Alive();
	else
		return false;
}

void WhoRecover::Execute()
{
	UpdateDaly(pPerson,GetTime());
	pPerson->SetCurrentWhoStage(pPerson->GetCurrentWho()-1);
	ScheduleWhoUpdate(pPerson,GetTime());
	pPerson->AssignHivDeathDate(GetTime());
	if(pPerson->GetCurrentWho() > 2)
		SchedulePictHivTest(pPerson,GetTime());
	// Person-time calculation
	UpdateCarePersonTime(pPerson,GetTime());
}

/////////////////////
/////////////////////
