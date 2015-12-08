//
//  output.cpp
//  priorityQ
//
//  Created by Jack Olney on 28/10/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#include <iostream>
#include "output.h"
#include "impact.h"
#include "cost.h"
#include "outputUpdate.h"

using namespace std;

double * theCARE;
double * theCARE_PT;
double * theDALY;
double * theCOST;
double * thePOP;
double * theHIV;
double * thePOP_15to49;
double * theHIV_15to49;
double * theART_15to49;
double * thePOP_15plus;
double * theAidsDeath_15plus;
double * thePOP_AgeSex_2007;
double * theHIV_AgeSex_2007;
double * thePOP_NoArtCd4_2007;
double * thePOP_AgeSex_2012;
double * theHIV_AgeSex_2012;
double * thePOP_AgeSex_2014;
double * theHIV_AgeSex_2014;
double * theCD4_200;
double * theCD4_200350;
double * theCD4_350500;
double * theCD4_500;
double * theCD4_200_Art;
double * theCD4_200350_Art;
double * theCD4_350500_Art;
double * theCD4_500_Art;
double * theWHO_1;
double * theWHO_2;
double * theWHO_3;
double * theWHO_4;
double * theWHO_1_Art;
double * theWHO_2_Art;
double * theWHO_3_Art;
double * theWHO_4_Art;
double * theINCIDENCE;
double * thePreArtCOST;
double * theArtCOST;
double * thePreArtCOST_Hiv;
double * theArtCOST_Hiv;
double * theCLINIC;
double * theDeath;
double * theAidsDeath;
double * theDeath_2010_Age;
double * theAidsDeath_2010_Age;
double * theDALY_OffArt;
double * theDALY_OnArt;
double * theDALY_LYL;

/* COST UNITS (values which we multiply by unit cost to arrive at COST) */
double * theUNIT_HctVisitCost;
double * theUNIT_RapidHivTestCost;
double * theUNIT_LinkageCost;
double * theUNIT_ImpCareCost;
double * theUNIT_PreArtClinicVisitCost;
double * theUNIT_LabCd4TestCost;
double * theUNIT_PocCd4TestCost;
double * theUNIT_AnnualArtCost;
double * theUNIT_AnnualAdherenceCost;
double * theUNIT_OutreachCost;

/* Unit Costs (the unit cost which is multiplied by the Cost Unit to arrive at COST) */
double * theUnitCost_HctVisitCost;
double * theUnitCost_RapidHivTestCost;
double * theUnitCost_LinkageCost;
double * theUnitCost_ImpCareCost;
double * theUnitCost_PreArtClinicVisitCost;
double * theUnitCost_LabCd4TestCost;
double * theUnitCost_PocCd4TestCost;
double * theUnitCost_AnnualArtCost;
double * theUnitCost_AnnualAdherenceCost;
double * theUnitCost_OutreachCost;

/////////////////////
/////////////////////

void SeedOutput(person * const thePerson)
{
	double yr [66];
	for(size_t i=0; i<66; i++) {
		yr[i] = 365.25 + (i * 365.25);
		if(thePerson->GetBirthDay() < yr[i])
			new Output(thePerson,yr[i],i);
	}
}

/////////////////////
/////////////////////

Output::Output(person * const thePerson, const double Time, const size_t theIndex) :
event(Time),
pPerson(thePerson),
index(theIndex)
{
	if(Time >= thePerson->GetNatDeathDate()) { Cancel(); }
}

Output::~Output()
{}

bool Output::CheckValid()
{
	return true;
}

void Output::Execute()
{
	if(GetTime() >= 14610 && GetTime() < 21916) {
		WriteDaly(pPerson,index);
		WriteCost(pPerson,GetTime());
	}
	WritePop(pPerson,GetTime(),index);
	WriteHiv(pPerson,GetTime(),index);
	WriteArt(pPerson,GetTime(),index);
	WriteCd4(pPerson,index);
	WriteWho(pPerson,index);
	if(GetTime() == 13879.5)
		Write2007(pPerson);
	if(GetTime() == 15705.75)
		Write2012(pPerson);
	if(GetTime() == 16436.25)
		Write2014(pPerson);
	// Person-time calculation
	UpdateCarePersonTime(pPerson,GetTime());
}

/////////////////////
/////////////////////

void CreateOutputArray()
{
	theCARE = new double[6]; // NeverDiagnosed, DiagnosedButNeverLinkedToCare, DiagnosedLinkedButNeverInitiatedArt, ArtLate, ArtButDiedOffArt, ArtEarly.
	theCARE_PT = new double[6]; // Person-time tracker for each category.
	theDALY = new double[20];
	theCOST = new double[20];
	thePOP = new double[66];
	theHIV = new double[66];
	thePOP_15to49 = new double[66];
	theHIV_15to49 = new double[66];
	theART_15to49 = new double[66];
	thePOP_15plus = new double[66];
	theAidsDeath_15plus = new double[66];
	thePOP_AgeSex_2007 = new double[20];
	theHIV_AgeSex_2007 = new double[20];
	thePOP_NoArtCd4_2007 = new double[4];
	thePOP_AgeSex_2012 = new double[16];
	theHIV_AgeSex_2012 = new double[16];
	thePOP_AgeSex_2014 = new double[10];
	theHIV_AgeSex_2014 = new double[10];
	theCD4_200 = new double[66];
	theCD4_200350 = new double[66];
	theCD4_350500 = new double[66];
	theCD4_500 = new double[66];
	theCD4_200_Art = new double[66];
	theCD4_200350_Art = new double[66];
	theCD4_350500_Art = new double[66];
	theCD4_500_Art = new double[66];
	theWHO_1 = new double[66];
	theWHO_2 = new double[66];
	theWHO_3 = new double[66];
	theWHO_4 = new double[66];
	theWHO_1_Art = new double[66];
	theWHO_2_Art = new double[66];
	theWHO_3_Art = new double[66];
	theWHO_4_Art = new double[66];
	theINCIDENCE = new double[66];
	thePreArtCOST = new double[20];
	theArtCOST = new double[20];
	thePreArtCOST_Hiv = new double[20];
	theArtCOST_Hiv = new double[20];
	theCLINIC = new double[5]; // NeverDiagnosed, DiagnosedButNeverInitiatedArt, ArtLate, ArtButDiedOffArt, ArtEarly.
	theDeath = new double[66];
	theAidsDeath = new double[66];
	theDeath_2010_Age = new double[20];
	theAidsDeath_2010_Age = new double[20];
	theDALY_OffArt = new double[20];
	theDALY_OnArt = new double[20];
	theDALY_LYL = new double[20];
	theUNIT_HctVisitCost = new double[20];
	theUNIT_RapidHivTestCost = new double[20];
	theUNIT_LinkageCost = new double[20];
	theUNIT_ImpCareCost = new double[20];
	theUNIT_PreArtClinicVisitCost = new double[20];
	theUNIT_LabCd4TestCost = new double[20];
	theUNIT_PocCd4TestCost = new double[20];
	theUNIT_AnnualArtCost = new double[20];
	theUNIT_AnnualAdherenceCost = new double[20];
	theUNIT_OutreachCost = new double[20];
	theUnitCost_HctVisitCost = new double[20];
	theUnitCost_RapidHivTestCost = new double[20];
	theUnitCost_LinkageCost = new double[20];
	theUnitCost_ImpCareCost = new double[20];
	theUnitCost_PreArtClinicVisitCost = new double[20];
	theUnitCost_LabCd4TestCost = new double[20];
	theUnitCost_PocCd4TestCost = new double[20];
	theUnitCost_AnnualArtCost = new double[20];
	theUnitCost_AnnualAdherenceCost = new double[20];
	theUnitCost_OutreachCost = new double[20];

	for(size_t i=0;i<66;i++) {
		if(i<4)
			thePOP_NoArtCd4_2007[i] = 0;
		if(i<5)
			theCLINIC[i] = 0;
		if(i<6) {
			theCARE[i] = 0;
			theCARE_PT[i] = 0;
		}
		if(i<10) {
			thePOP_AgeSex_2014[i] = 0;
			theHIV_AgeSex_2014[i] = 0;
		}
		if(i<16) {
			thePOP_AgeSex_2012[i] = 0;
			theHIV_AgeSex_2012[i] = 0;
		}
		if(i<20) {
			thePOP_AgeSex_2007[i] = 0;
			theHIV_AgeSex_2007[i] = 0;
			theDeath_2010_Age[i] = 0;
			theAidsDeath_2010_Age[i] = 0;
			theDALY[i] = 0;
			theCOST[i] = 0;
			thePreArtCOST[i] = 0;
			theArtCOST[i] = 0;
			thePreArtCOST_Hiv[i] = 0;
			theArtCOST_Hiv[i] = 0;
			theDALY_OffArt[i] = 0;
			theDALY_OnArt[i] = 0;
			theDALY_LYL[i] = 0;
			theUNIT_HctVisitCost[i] = 0;
			theUNIT_RapidHivTestCost[i] = 0;
			theUNIT_LinkageCost[i] = 0;
			theUNIT_ImpCareCost[i] = 0;
			theUNIT_PreArtClinicVisitCost[i] = 0;
			theUNIT_LabCd4TestCost[i] = 0;
			theUNIT_PocCd4TestCost[i] = 0;
			theUNIT_AnnualArtCost[i] = 0;
			theUNIT_AnnualAdherenceCost[i] = 0;
			theUNIT_OutreachCost[i] = 0;
			theUnitCost_HctVisitCost[i] = 0;
			theUnitCost_RapidHivTestCost[i] = 0;
			theUnitCost_LinkageCost[i] = 0;
			theUnitCost_ImpCareCost[i] = 0;
			theUnitCost_PreArtClinicVisitCost[i] = 0;
			theUnitCost_LabCd4TestCost[i] = 0;
			theUnitCost_PocCd4TestCost[i] = 0;
			theUnitCost_AnnualArtCost[i] = 0;
			theUnitCost_AnnualAdherenceCost[i] = 0;
			theUnitCost_OutreachCost[i] = 0;
		}
		thePOP[i] = 0;
		thePOP_15to49[i] = 0;
		thePOP_15plus[i] = 0;
		theHIV[i] = 0;
		theHIV_15to49[i] = 0;
		theART_15to49[i] = 0;
		theCD4_200[i] = 0;
		theCD4_200350[i] = 0;
		theCD4_350500[i] = 0;
		theCD4_500[i] = 0;
		theCD4_200_Art[i] = 0;
		theCD4_200350_Art[i] = 0;
		theCD4_350500_Art[i] = 0;
		theCD4_500_Art[i] = 0;
		theWHO_1[i] = 0;
		theWHO_2[i] = 0;
		theWHO_3[i] = 0;
		theWHO_4[i] = 0;
		theWHO_1_Art[i] = 0;
		theWHO_2_Art[i] = 0;
		theWHO_3_Art[i] = 0;
		theWHO_4_Art[i] = 0;
		theDeath[i] = 0;
		theAidsDeath_15plus[i] = 0;
		theAidsDeath[i] = 0;
		theINCIDENCE[i] = 0;
	}
}

/////////////////////
/////////////////////
