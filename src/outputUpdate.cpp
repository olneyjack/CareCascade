//
//  outputUpdate.cpp
//  priorityQ
//
//  Created by Jack Olney on 30/10/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#include <iostream>
#include "outputUpdate.h"

using namespace std;

extern double * theCARE;
extern double * theCARE_PT;
extern double * thePOP;
extern double * theHIV;
extern double * thePOP_15to49;
extern double * theHIV_15to49;
extern double * theART_15to49;
extern double * thePOP_15plus;
extern double * theAidsDeath_15plus;
extern double * thePOP_AgeSex_2007;
extern double * theHIV_AgeSex_2007;
extern double * thePOP_NoArtCd4_2007;
extern double * thePOP_AgeSex_2012;
extern double * theHIV_AgeSex_2012;
extern double * thePOP_AgeSex_2014;
extern double * theHIV_AgeSex_2014;
extern double * theCD4_200;
extern double * theCD4_200350;
extern double * theCD4_350500;
extern double * theCD4_500;
extern double * theCD4_200_Art;
extern double * theCD4_200350_Art;
extern double * theCD4_350500_Art;
extern double * theCD4_500_Art;
extern double * theWHO_1;
extern double * theWHO_2;
extern double * theWHO_3;
extern double * theWHO_4;
extern double * theWHO_1_Art;
extern double * theWHO_2_Art;
extern double * theWHO_3_Art;
extern double * theWHO_4_Art;
extern double * theINCIDENCE;
extern double * thePreArtCOST;
extern double * theArtCOST;
extern double * thePreArtCOST_Hiv;
extern double * theArtCOST_Hiv;
extern double * theCLINIC;
extern double * theDeath;
extern double * theAidsDeath;
extern double * theDeath_2010_Age;
extern double * theAidsDeath_2010_Age;

/////////////////////
/////////////////////

void WritePop(person * const thePerson, const double theTime, const size_t theIndex)
{
	if((theIndex + 1) * 365.25 > thePerson->GetBirthDay()) {
		thePOP[theIndex] += thePerson->Alive();
		if(thePerson->GetAge(theTime) > 15 * 365.25)
			thePOP_15plus[theIndex] += thePerson->Alive();
		if(thePerson->GetAge(theTime) > 15 * 365.25 && thePerson->GetAge(theTime) <= 49 * 365.25)
			thePOP_15to49[theIndex] += thePerson->Alive();
	}
}

/////////////////////
/////////////////////

void WriteHiv(person * const thePerson, const double theTime, const size_t theIndex)
{
	if(thePerson->Alive()) {
		theHIV[theIndex] += thePerson->GetSeroStatus();
		if(thePerson->GetAge(theTime) > 15 * 365.25 && thePerson->GetAge(theTime) <= 49 * 365.25)
			theHIV_15to49[theIndex] += thePerson->GetSeroStatus();
	}
}

/////////////////////
/////////////////////

void WriteArt(person * const thePerson, const double theTime, const size_t theIndex)
{
	if(thePerson->Alive()) {
		if(thePerson->GetAge(theTime) > 15 * 365.25 && thePerson->GetAge(theTime) <= 49 * 365.25)
			theART_15to49[theIndex] += thePerson->GetArtInitiationState();
	}
}

/////////////////////
/////////////////////

void WriteCare(person * const thePerson, const double theTime)
{
	if(thePerson->GetHivDeath() && theTime >= 14610 && theTime < 21915) {
		// NeverDiagnosed
		theCARE[0] += !thePerson->GetDiagnosedState();
		// DiagnosedButNeverLinkedToCare
		theCARE[1] += (thePerson->GetDiagnosedState() && !thePerson->GetEverCd4TestState() && !thePerson->GetEverArt());
		// DiagnosedLinkedButNeverInitiatedArt
		theCARE[2] += (thePerson->GetDiagnosedState() && thePerson->GetEverCd4TestState() && !thePerson->GetEverArt());
		// ArtLate
		theCARE[3] += (thePerson->GetEverArt() && thePerson->GetArtDeath() && thePerson->GetCd4AtArt() == 1);
		// ArtButDiedOffArt
		theCARE[4] += (thePerson->GetEverArt() && !thePerson->GetArtDeath());
		// ArtEarly
		theCARE[5] += (thePerson->GetEverArt() && thePerson->GetArtDeath() && thePerson->GetCd4AtArt() > 1);
	}
}

/////////////////////
/////////////////////

void UpdateCarePersonTime(person * const thePerson, const double theTime)
{
	if(thePerson->Alive() && thePerson->GetSeroStatus() && theTime >= 14610 && theTime < 21915) {
		if(!thePerson->GetDiagnosedState())
			theCARE_PT[0] += (theTime - thePerson->GetLastUpdateTime()) / 365.25;
		else if(thePerson->GetDiagnosedState() && !thePerson->GetEverCd4TestState() && !thePerson->GetEverArt())
			theCARE_PT[1] += (theTime - thePerson->GetLastUpdateTime()) / 365.25;
		else if(thePerson->GetDiagnosedState() && thePerson->GetEverCd4TestState() && !thePerson->GetEverArt())
			theCARE_PT[2] += (theTime - thePerson->GetLastUpdateTime()) / 365.25;
		else if(thePerson->GetArtInitiationState() && thePerson->GetCd4AtArt() == 1)
			theCARE_PT[3] += (theTime - thePerson->GetLastUpdateTime()) / 365.25;
		else if(thePerson->GetEverArt() && !thePerson->GetArtInitiationState())
			theCARE_PT[4] += (theTime - thePerson->GetLastUpdateTime()) / 365.25;
		else if(thePerson->GetArtInitiationState() && thePerson->GetCd4AtArt() > 1)
			theCARE_PT[5] += (theTime - thePerson->GetLastUpdateTime()) / 365.25;

		thePerson->SetLastUpdateTime(theTime);
	}

}

/////////////////////
/////////////////////

void WriteClinic(person * const thePerson, const double theTime)
{
	if(thePerson->GetEverCd4TestState() && thePerson->GetHivDeath() && theTime >= 14610 && theTime < 21915) {
		// NeverDiagnosed
		theCLINIC[0] += !thePerson->GetDiagnosedState();
		// DiagnosedButNeverInitiatedArt
		theCLINIC[1] += (thePerson->GetDiagnosedState() && !thePerson->GetEverArt());
		// ArtLate
		theCLINIC[2] += (thePerson->GetEverArt() && thePerson->GetArtDeath() && thePerson->GetCd4AtArt() == 1);
		// ArtButDiedOffArt
		theCLINIC[3] += (thePerson->GetEverArt() && !thePerson->GetArtDeath());
		// ArtEarly
		theCLINIC[4] += (thePerson->GetEverArt() && thePerson->GetArtDeath() && thePerson->GetCd4AtArt() > 1);
	}
}

/////////////////////
/////////////////////

void WriteDeath(person * const thePerson, const double theTime)
{
	double yr [66];
	for(size_t i = 0; i<66; i++)
		yr[i] = 365.25 + (i * 365.25);

	unsigned int i = 0;
	while(theTime > yr[i] && i<66)
		i++;
	
	theDeath[i]++;
	
	// Age stratification for 2010 only
	if(theTime > 14610 && theTime <= (14610 + 365.25)) {
		const int ageCatMax[20] = {5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,100};
		unsigned int j = 0;
		while(thePerson->GetAge(theTime) / 365.25 > ageCatMax[j] && j < 19)
			j++;
		
		theDeath_2010_Age[j]++;
	}
}

/////////////////////
/////////////////////

void WriteAidsDeath(person * const thePerson, const double theTime)
{
	double yr [66];
	for(size_t i = 0; i<66; i++)
		yr[i] = 365.25 + (i * 365.25);

	unsigned int i = 0;
	while(theTime > yr[i] && i<66)
		i++;
	
	theAidsDeath[i] += thePerson->GetSeroStatus();
	
	if(thePerson->GetAge(theTime) > 15 * 365.25)
		theAidsDeath_15plus[i] += thePerson->GetSeroStatus();
	
	// Age stratification for 2010 only
	if(theTime > 14610 && theTime <= (14610 + 365.25)) {
		const int ageCatMax[20] = {5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,100};
		unsigned int j = 0;
		while(thePerson->GetAge(theTime) / 365.25 > ageCatMax[j] && j < 19)
			j++;
		
		theAidsDeath_2010_Age[j]++;
	}
}

/////////////////////
/////////////////////

void Write2007(person * const thePerson)
{
	if(13879.5 > thePerson->GetBirthDay()) {
		if(thePerson->GetAge(13879.5) > 15 * 365.25 && thePerson->GetAge(13879.5) <= 64 * 365.25) {
			const unsigned int ageCatMax [10] = {19,24,29,34,39,44,49,54,59,64};
			unsigned int i = 0;
			while(thePerson->GetAge(13879.5) / 365.25 > ageCatMax[i] && i < 9)
				i++;
			
			if(thePerson->GetGender())
				i += 10;
			
			thePOP_AgeSex_2007[i] += thePerson->Alive();
			if(thePerson->Alive()) {
				theHIV_AgeSex_2007[i] += thePerson->GetSeroStatus();
				if(!thePerson->GetArtInitiationState()) {
					if(thePerson->GetCurrentCd4() == 1)
						thePOP_NoArtCd4_2007[0]++;
					else if(thePerson->GetCurrentCd4() == 2)
						thePOP_NoArtCd4_2007[1]++;
					else if(thePerson->GetCurrentCd4() == 3)
						thePOP_NoArtCd4_2007[2]++;
					else if(thePerson->GetCurrentCd4() == 4)
						thePOP_NoArtCd4_2007[3]++;
				}
			}
		}
	}
}

/////////////////////
/////////////////////

void Write2012(person * const thePerson)
{
	if(15705.75 > thePerson->GetBirthDay()) {
		if(thePerson->GetAge(15705.75) > 15 * 365.25 && thePerson->GetAge(15705.75) <= 64 * 365.25) {
			const unsigned int ageCatMax [8] = {19,24,29,34,39,44,49,64};
			unsigned int i = 0;
			while(thePerson->GetAge(15705.75) / 365.25 > ageCatMax[i] && i < 7)
				i++;
			
			if(thePerson->GetGender())
				i += 8;
			
			thePOP_AgeSex_2012[i] += thePerson->Alive();
			if(thePerson->Alive())
				theHIV_AgeSex_2012[i] += thePerson->GetSeroStatus();
		}
	}
}

/////////////////////
/////////////////////

void Write2014(person * const thePerson)
{
	if(16436.25 > thePerson->GetBirthDay()) {
		const unsigned int ageCatMax [5] = {14,21,29,46,200};
		unsigned int i = 0;
		while(thePerson->GetAge(16436.25) / 365.25 > ageCatMax[i] && i < 4)
			i++;
		
		if(thePerson->GetGender())
			i += 5;
		
		thePOP_AgeSex_2014[i] += thePerson->Alive();
		if(thePerson->Alive())
			theHIV_AgeSex_2014[i] += thePerson->GetSeroStatus();
	}
}

/////////////////////
/////////////////////

void WriteCd4(person * const thePerson, const size_t theIndex)
{
	if((theIndex + 1) * 365.25 > thePerson->GetBirthDay()) {
		if(thePerson->GetCurrentCd4() == 1)
			theCD4_200[theIndex] += thePerson->Alive();
		else if(thePerson->GetCurrentCd4() == 2)
			theCD4_200350[theIndex] += thePerson->Alive();
		else if(thePerson->GetCurrentCd4() == 3)
			theCD4_350500[theIndex] += thePerson->Alive();
		else if(thePerson->GetCurrentCd4() == 4)
			theCD4_500[theIndex] += thePerson->Alive();
	}
	
	
	if((theIndex + 1) * 365.25 > thePerson->GetBirthDay() && thePerson->Alive()) {
		if(thePerson->GetCurrentCd4() == 1)
			theCD4_200_Art[theIndex] += thePerson->GetArtInitiationState();
		else if(thePerson->GetCurrentCd4() == 2)
			theCD4_200350_Art[theIndex] += thePerson->GetArtInitiationState();
		else if(thePerson->GetCurrentCd4() == 3)
			theCD4_350500_Art[theIndex] += thePerson->GetArtInitiationState();
		else if(thePerson->GetCurrentCd4() == 4)
			theCD4_500_Art[theIndex] += thePerson->GetArtInitiationState();
	}
}

/////////////////////
/////////////////////

void WriteWho(person * const thePerson, const size_t theIndex)
{
	if((theIndex + 1) * 365.25 > thePerson->GetBirthDay()) {
		if(thePerson->GetCurrentWho() == 1)
			theWHO_1[theIndex] += thePerson->Alive();
		else if(thePerson->GetCurrentWho() == 2)
			theWHO_2[theIndex] += thePerson->Alive();
		else if(thePerson->GetCurrentWho() == 3)
			theWHO_3[theIndex] += thePerson->Alive();
		else if(thePerson->GetCurrentWho() == 4)
			theWHO_4[theIndex] += thePerson->Alive();
	}
	
	if((theIndex + 1) * 365.25 > thePerson->GetBirthDay() && thePerson->Alive()) {
		if(thePerson->GetCurrentWho() == 1)
			theWHO_1_Art[theIndex] += thePerson->GetArtInitiationState();
		else if(thePerson->GetCurrentWho() == 2)
			theWHO_2_Art[theIndex] += thePerson->GetArtInitiationState();
		else if(thePerson->GetCurrentWho() == 3)
			theWHO_3_Art[theIndex] += thePerson->GetArtInitiationState();
		else if(thePerson->GetCurrentWho() == 4)
			theWHO_4_Art[theIndex] += thePerson->GetArtInitiationState();
	}
}

/////////////////////
/////////////////////

void WriteIncidence(unsigned int const &theIncidentCases, const size_t theIndex)
{
	theINCIDENCE[theIndex] = theIncidentCases;
}
/////////////////////
/////////////////////
