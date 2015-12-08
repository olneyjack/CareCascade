//
//  interventions.cpp
//  priorityQ
//
//  Created by Jack Olney on 31/10/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#include <iostream>
#include "macro.h"
#include "interventions.h"
#include "interventionUpdate.h"
#include "interventionEvents.h"
#include "cascadeEvents.h"
#include "cascadeUpdate.h"
#include "outputUpdate.h"
#include "toolbox.h"

using namespace std;

/* Intervention Pointers */
extern int const * p_Hbct;
extern int const * p_Vct;
extern int const * p_HbctPocCd4;
extern int const * p_Linkage;
extern int const * p_PreOutreach;
extern int const * p_ImprovedCare;
extern int const * p_PocCd4;
extern int const * p_VctPocCd4;
extern int const * p_ArtOutreach;
extern int const * p_ImmediateArt;
extern int const * p_UniversalTestAndTreat;
extern int const * p_Adherence;
extern int const * p_Calibration;

/////////////////////
/////////////////////

void SeedInterventions(person * const thePerson)
{
	if(*p_Hbct || *p_Vct || *p_HbctPocCd4 || *p_Linkage || *p_PreOutreach || *p_ImprovedCare || *p_PocCd4 || *p_VctPocCd4 || *p_ArtOutreach || *p_ImmediateArt || *p_UniversalTestAndTreat || *p_Adherence || *p_Calibration) {
		if(thePerson->GetBirthDay() < 14610)
			new Interventions(thePerson,14610);
		else
			new Interventions(thePerson,thePerson->GetBirthDay());
	}
}

/////////////////////
/////////////////////

Interventions::Interventions(person * const thePerson, const double Time) :
event(Time),
pPerson(thePerson)
{
	D(cout << "Interventions scheduled for " << Time << " (year = " << Time / 365.25 << ")" << endl);
	if(Time >= thePerson->GetNatDeathDate()) { Cancel(); }	
}

Interventions::~Interventions()
{}

bool Interventions::CheckValid()
{
	return pPerson->Alive();
}

void Interventions::Execute()
{
	
	/////////////////////
	/////////////////////
	/* Hbct */
	
	if(*p_Hbct) {
		for(size_t i=0;i<5;i++)
			if(GetTime() <= 14610 + (i * 1461))
				new SeedHct(pPerson,14610 + (i * 1461),false);
		
		if(*p_Hbct == 1) {
			hctProbLink = 1;
			hctProbLinkPreviouslyDiagnosed = 1;
		}
	}
	
	/////////////////////
	/* Vct */
	
	if(*p_Vct) {
		if(*p_Vct == 1)
			vctHivTestTime = vctHivTestTimeOriginal * 0.5;
		else
			vctHivTestTime = vctHivTestTimeOriginal * (1/1.25);
		D(cout << "VctHivTest Intervention. vctHivTestTime = " << vctHivTestTime << endl);
		ScheduleVctHivTest(pPerson,GetTime());
	}
	
	/////////////////////
	/* HbctPocCd4 */
	
	if(*p_HbctPocCd4) {
		D(cout << "HbctPocCd4 Intervention." << endl);
		for(size_t i=0;i<5;i++)
			if(GetTime() <= 14610 + (i * 1461))
				new SeedHct(pPerson,14610 + (i * 1461),true);
		
		if(*p_HbctPocCd4 == 1) {
			hctProbLink = 1;
			hctProbLinkPreviouslyDiagnosed = 1;
		} else {
			hctProbLink = ((1-hctProbLinkOriginal) * 0.5) + hctProbLinkOriginal;
			hctProbLinkPreviouslyDiagnosed = ((1-hctProbLinkPreviouslyDiagnosedOriginal) * 0.5) + hctProbLinkPreviouslyDiagnosedOriginal;
		}
	}
	
	/////////////////////
	/* Linkage */
	
	if(*p_Linkage) {
		D(cout << "Linkage intervention." << endl);
		linkageFlag = true;
		if(*p_Linkage == 1) {
			hctProbLink = 1;
			hctProbLinkPreviouslyDiagnosed = 1;
			vctProbLink = 1;
			pictProbLink = 1;
		} else {
			hctProbLink = ((1-hctProbLinkOriginal) * 0.5) + hctProbLinkOriginal;
			hctProbLinkPreviouslyDiagnosed = ((1-hctProbLinkPreviouslyDiagnosedOriginal) * 0.5) + hctProbLinkPreviouslyDiagnosedOriginal;
			vctProbLink = ((1-vctProbLinkOriginal) * 0.5) + vctProbLinkOriginal;
			pictProbLink = ((1-pictProbLinkOriginal) * 0.5) + pictProbLinkOriginal;
		}
	}
	
	/////////////////////
	/* PreOutreach */
	
	if(*p_PreOutreach) {
		double k = 0;
		if(*p_PreOutreach == 1) { k = 1; } else { k = 0.2; }
		
		for(size_t i=0;i<20;i++)
			if(GetTime() <= 14792.625 + (i * 365.25))
				new PreArtOutreach(pPerson,14792.625 + (i * 365.25),k);
	}
	
	/////////////////////
	/* ImprovedCare */
	
	if(*p_ImprovedCare) {
		D(cout << "ImprovedCare intervention." << endl);
		impCareFlag = true;
		if(*p_ImprovedCare == 1) {
			cd4ResultProbAttend = 1;
			hctShortTermRetention = 1;
			hctLongTermRetention = 1;
			vctShortTermRetention = 1;
			vctLongTermRetention = 1;
			pictShortTermRetention = 1;
			pictLongTermRetention = 1;
			hctProbSecondaryCd4Test = 1;
			vctProbSecondaryCd4Test = 1;
			pictProbSecondaryCd4Test = 1;
		} else {
			cd4ResultProbAttend = 0.9743416;
			hctShortTermRetention = 0.9743416;
			hctLongTermRetention = 0.9743416;
			vctShortTermRetention = 0.9743416;
			vctLongTermRetention = 0.9743416;
			pictShortTermRetention = 0.9743416;
			pictLongTermRetention = 0.9743416;
			hctProbSecondaryCd4Test = 0.875;
			vctProbSecondaryCd4Test = 0.875;
			pictProbSecondaryCd4Test = 0.875;
		}
	}
	
	/////////////////////
	/* PocCd4 */
	
	if(*p_PocCd4)
		pocFlag = true;
	
	/////////////////////
	/* VctPocCd4 */
	
	if(*p_VctPocCd4) {
		vctPocFlag = true;
		ScheduleVctHivTest(pPerson,GetTime());
	}
	
	/////////////////////
	/* ArtOutreach */
	
	if(*p_ArtOutreach) {
		double k = 0;
		if(*p_ArtOutreach == 1) { k = 1; } else { k = 0.4; }
		
		for(size_t i=0;i<20;i++)
			if(GetTime() <= 14792.625 + (i * 365.25))
				new ArtOutreach(pPerson,14792.625 + (i * 365.25),k);
	}
	
	/////////////////////
	/* ImmediateArt */
	
	if(*p_ImmediateArt) {
		D(cout << "ImmediateArt intervention." << endl);
		immediateArtFlag = true;
		UpdateTreatmentGuidelines(pPerson,4,1);
	}
	
	/////////////////////
	/* UniversalTestAndTreat */
	
	if(*p_UniversalTestAndTreat) {
		D(cout << "UniversalTestAndTreat intervention." << endl);
		immediateArtFlag = true;
		UpdateTreatmentGuidelines(pPerson,4,1);
		
		for(size_t i=0;i<5;i++)
			if(GetTime() <= 14610 + (i * 1461))
				new SeedHct(pPerson,14610 + (i * 1461),false);
		
		if(*p_UniversalTestAndTreat == 1) {
			hctProbLink = 1;
			hctProbLinkPreviouslyDiagnosed = 1;
		}
	}
	
	/////////////////////
	/* Adherence */
	
	if(*p_Adherence) {
		D(cout << "Adherence intervention." << endl);
		adherenceFlag = true;
		if(*p_Adherence == 1)
			pPerson->SetArtAdherenceState(1);
		else
			pPerson->SetArtAdherenceState(0.93);
	}
	
	/////////////////////
	/* Calibration */
	
	if(*p_Calibration) {
		for(size_t i=0;i<20;i++)
			if(GetTime() <= 14610 + (i * 365.25))
				new SeedPerpetualHct(pPerson, 14610 + (i * 365.25));
	}
	
	/////////////////////

	// Person-time calculation
	UpdateCarePersonTime(pPerson,GetTime());
	
}

/////////////////////
/////////////////////
