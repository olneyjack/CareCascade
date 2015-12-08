//
//  cost.cpp
//  priorityQ
//
//  Created by Jack Olney on 27/10/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#include <iostream>
#include "cost.h"
#include "person.h"
#include "toolbox.h"

using namespace std;

extern double * theCOST;
extern double * thePreArtCOST;
extern double * theArtCOST;
extern double * thePreArtCOST_Hiv;
extern double * theArtCOST_Hiv;

/* COST UNITS */
extern double * theUNIT_HctVisitCost;
extern double * theUNIT_RapidHivTestCost;
extern double * theUNIT_LinkageCost;
extern double * theUNIT_ImpCareCost;
extern double * theUNIT_PreArtClinicVisitCost;
extern double * theUNIT_LabCd4TestCost;
extern double * theUNIT_PocCd4TestCost;
extern double * theUNIT_AnnualArtCost;
extern double * theUNIT_AnnualAdherenceCost;
extern double * theUNIT_OutreachCost;

/* UNIT COSTS */
extern double * theUnitCost_HctVisitCost;
extern double * theUnitCost_RapidHivTestCost;
extern double * theUnitCost_LinkageCost;
extern double * theUnitCost_ImpCareCost;
extern double * theUnitCost_PreArtClinicVisitCost;
extern double * theUnitCost_LabCd4TestCost;
extern double * theUnitCost_PocCd4TestCost;
extern double * theUnitCost_AnnualArtCost;
extern double * theUnitCost_AnnualAdherenceCost;
extern double * theUnitCost_OutreachCost;

/////////////////////
/////////////////////

void ChargeHctVisit(person * const thePerson)
{
	thePerson->SetHctVisitCost(hctVisitCost);
	thePerson->SetRapidHivTestCost(rapidHivTestCost);

	/* Cost Units  */
	/* Pass these values 1 if an event occurs, else pass them the person-time */
	thePerson->SetHctVisitUnit(1);
	thePerson->SetRapidHivTestUnit(1);
}

/////////////////////
/////////////////////

void ChargeVctPictHivTest(person * const thePerson)
{
	thePerson->SetRapidHivTestCost(rapidHivTestCost);
	thePerson->SetRapidHivTestUnit(1);
}

/////////////////////
/////////////////////

void ChargePreArtClinicVisit(person * const thePerson)
{
	thePerson->SetPreArtClinicVisitCost(preArtClinicVisitCost);
	thePerson->SetPreArtClinicVisitUnit(1);
}

/////////////////////
/////////////////////

void ChargePreArtClinicCd4Test(person * const thePerson)
{
	thePerson->SetLabCd4TestCost(labCd4TestCost);
	thePerson->SetLabCd4TestUnit(1);
}

/////////////////////
/////////////////////

void ChargePreArtClinicCd4ResultVisit(person * const thePerson)
{
	thePerson->SetPreArtClinicVisitCost(preArtClinicVisitCost);
	thePerson->SetPreArtClinicVisitUnit(1);
}

/////////////////////
/////////////////////

void ChargePocCd4Test(person * const thePerson)
{
	thePerson->SetPocCd4TestCost(pocCd4TestCost);
	thePerson->SetPocCd4TestUnit(1);
}

/////////////////////
/////////////////////

void ChargeArtCare(person * const thePerson, const double theTime, const double theArrayTime)
{
	// Minimize calls to the thePerson;
	double theArtTime = thePerson->GetArtTime();
	double theArtDay = thePerson->GetArtDay();

	if(thePerson->GetArtInitiationState()) {
		if(theArtDay <= theArrayTime) {
			thePerson->SetAnnualArtCost((((theTime - theArrayTime) + theArtTime) / 365.25) * annualArtCost);
			thePerson->SetAnnualArtUnit(((theTime - theArrayTime) + theArtTime) / 365.25);
		} else {
			thePerson->SetAnnualArtCost((((theTime - theArtDay) + theArtTime) / 365.25) * annualArtCost);
			thePerson->SetAnnualArtUnit(((theTime - theArtDay) + theArtTime) / 365.25);
		}
	} else {
		thePerson->SetAnnualArtCost((theArtTime / 365.25) * annualArtCost);
		thePerson->SetAnnualArtUnit(theArtTime / 365.25);
	}
}


/////////////////////
/////////////////////

void ChargeLinkageInt(person * const thePerson)
{
	if(linkageFlag && thePerson->GetDiagnosedState()) {
		thePerson->SetLinkageCost((thePerson->GetDiagNotLinkedTime() / 365.25) * annualLinkageCost);
		thePerson->SetLinkageUnit(thePerson->GetDiagNotLinkedTime() / 365.25);
	}
}

/////////////////////
/////////////////////

void ChargeImprovedCareInt(person * const thePerson)
{
	if(impCareFlag) {
		thePerson->SetImpCareCost(impCareCost);
		thePerson->SetImpCareUnit(1);
	}
}

/////////////////////
/////////////////////

void ChargeAdherence(person * const thePerson, const double theTime, const double theArrayTime)
{
	// Minimize calls to thePerson;
	double theArtTime = thePerson->GetArtTime();
	double theArtDay = thePerson->GetArtDay();

	if(adherenceFlag) {
		if(thePerson->GetArtInitiationState()) {
			if(theArtDay <= theArrayTime) {
				thePerson->SetAnnualAdherenceCost((((theTime - theArrayTime) + theArtTime) / 365.25) * annualAdherenceCost);
				thePerson->SetAnnualAdherenceUnit(((theTime - theArrayTime) + theArtTime) / 365.25);
			} else {
				thePerson->SetAnnualAdherenceCost((((theTime - theArtDay) + theArtTime) / 365.25) * annualAdherenceCost);
				thePerson->SetAnnualAdherenceUnit(((theTime - theArtDay) + theArtTime) / 365.25);
			}
		} else {
			thePerson->SetAnnualAdherenceCost((theArtTime / 365.25) * annualAdherenceCost);
			thePerson->SetAnnualAdherenceUnit(theArtTime / 365.25);
		}
	}
}

/////////////////////
/////////////////////

void ChargePreArtOutreach(person * const thePerson)
{
	thePerson->SetPreArtOutreachCost(outreachCost);
	thePerson->SetPreArtOutreachUnit(1);
}

/////////////////////
/////////////////////

void ChargeArtOutreach(person * const thePerson)
{
	thePerson->SetArtOutreachCost(outreachCost);
	thePerson->SetArtOutreachUnit(1);
}

/////////////////////
/////////////////////

void WriteCost(person * const thePerson, const double theTime)
{
	if(thePerson->Alive()) {
		if(theTime > 14610) {
			/* Create array with dates from 2011 to 2030 (to allow us to capture DALYs at year end between 2010 and 2030). */
			double yr [26]; // 26 is a hangover from WP19 work - although the model is stopped after 60 years + 1 day so these are never called.
			for(size_t i = 0; i<26; i++)
				yr[i] = 14975.25 + (i * 365.25);

			unsigned int i = 0;
			while(theTime > yr[i] && i < 26)
				i++;

			// Annual Cost Functions to call
			ChargeArtCare(thePerson,theTime,yr[i] - 365.25);
			ChargeAdherence(thePerson,theTime,yr[i] - 365.25);
			ChargeLinkageInt(thePerson);

			theCOST[i] += thePerson->GetHctVisitCost() + thePerson->GetRapidHivTestCost() + thePerson->GetLinkageCost() + thePerson->GetImpCareCost() + thePerson->GetPreArtClinicVisitCost() + thePerson->GetLabCd4TestCost() + thePerson->GetPocCd4TestCost() + thePerson->GetAnnualArtCost() + thePerson->GetAnnualAdherenceCost() + thePerson->GetArtOutreachCost() + thePerson->GetPreArtOutreachCost();
			thePreArtCOST[i] += thePerson->GetHctVisitCost() + thePerson->GetRapidHivTestCost() + thePerson->GetLinkageCost() + thePerson->GetImpCareCost() + thePerson->GetPreArtClinicVisitCost() + thePerson->GetLabCd4TestCost() + thePerson->GetPocCd4TestCost() + thePerson->GetPreArtOutreachCost();
			theArtCOST[i] += thePerson->GetAnnualArtCost() + thePerson->GetAnnualAdherenceCost() + thePerson->GetArtOutreachCost() + thePerson->GetPreArtOutreachCost();

			// Cost Unit Feedback from thePerson to theUNIT output arrays.
			theUNIT_HctVisitCost[i] += thePerson->GetHctVisitUnit();
			theUNIT_RapidHivTestCost[i] += thePerson->GetRapidHivTestUnit();
			theUNIT_LinkageCost[i] += thePerson->GetLinkageUnit();
			theUNIT_ImpCareCost[i] += thePerson->GetImpCareUnit();
			theUNIT_PreArtClinicVisitCost[i] += thePerson->GetPreArtClinicVisitUnit();
			theUNIT_LabCd4TestCost[i] += thePerson->GetLabCd4TestUnit();
			theUNIT_PocCd4TestCost[i] += thePerson->GetPocCd4TestUnit();
			theUNIT_AnnualArtCost[i] += thePerson->GetAnnualArtUnit();
			theUNIT_AnnualAdherenceCost[i] += thePerson->GetAnnualAdherenceUnit();
			theUNIT_OutreachCost[i] += thePerson->GetArtOutreachUnit() + thePerson->GetPreArtOutreachUnit();

			// Store Unit Costs - e.g. annualArtCost etc.
			// The if == 0 stops the values being overwritten and additionally fixes an issue where the first index was being overwritten (suspect another piece of memory overrunning into [0] of array).
			if(theUnitCost_HctVisitCost[i] == 0)
				theUnitCost_HctVisitCost[i] = hctVisitCost;
			if(theUnitCost_RapidHivTestCost[i] == 0)
				theUnitCost_RapidHivTestCost[i] = rapidHivTestCost;
			if(theUnitCost_LinkageCost[i] == 0)
				theUnitCost_LinkageCost[i] = annualLinkageCost;
			if(theUnitCost_ImpCareCost[i] == 0)
				theUnitCost_ImpCareCost[i] = impCareCost;
			if(theUnitCost_PreArtClinicVisitCost[i] == 0)
				theUnitCost_PreArtClinicVisitCost[i] = preArtClinicVisitCost;
			if(theUnitCost_LabCd4TestCost[i] == 0)
				theUnitCost_LabCd4TestCost[i] = labCd4TestCost;
			if(theUnitCost_PocCd4TestCost[i] == 0)
				theUnitCost_PocCd4TestCost[i] = pocCd4TestCost;
			if(theUnitCost_AnnualArtCost[i] == 0)
				theUnitCost_AnnualArtCost[i] = annualArtCost;
			if(theUnitCost_AnnualAdherenceCost[i] == 0)
				theUnitCost_AnnualAdherenceCost[i] = annualAdherenceCost;
			if(theUnitCost_OutreachCost[i] == 0)
				theUnitCost_OutreachCost[i] = outreachCost;
			
			if(thePerson->GetSeroStatus()) {
				thePreArtCOST_Hiv[i] += thePerson->GetHctVisitCost() + thePerson->GetRapidHivTestCost() + thePerson->GetLinkageCost() + thePerson->GetImpCareCost() + thePerson->GetPreArtClinicVisitCost() + thePerson->GetLabCd4TestCost() + thePerson->GetPocCd4TestCost() + thePerson->GetPreArtOutreachCost();
				theArtCOST_Hiv[i] += thePerson->GetAnnualArtCost() + thePerson->GetAnnualAdherenceCost() + thePerson->GetArtOutreachCost() + thePerson->GetPreArtOutreachCost();
			}
		}
		thePerson->ResetCost();
		thePerson->ResetUnit();
	}
}

/////////////////////
/////////////////////
