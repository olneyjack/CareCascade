//
//  calibration.cpp
//  priorityQ
//
//  Created by Jack Olney on 01/12/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#include <iostream>
#include "calibration.h"

using namespace std;

/* Calibration Pointers */
double * C1;
double * L21;
double * R3;
double * R8;
double * ART1;
double * ART4;
double * ART5;
double * ART6;
double * ART9;
double * ART10;
double * ART11;
double * ART12;
double * ART13;
double * ART14;
double * Pre2010;
unsigned int * In2014;
unsigned int * HivArray;
unsigned int * DiagArray;
unsigned int * ArtArray;
unsigned int * R3_Counter;
unsigned int * R8_Counter;
unsigned int * ART6_Counter;
unsigned int * ART10_Counter;
unsigned int * ART12_Counter;

unsigned int * Pie_1;
unsigned int * Pie_2;
unsigned int * Pie_3;

void SeedCalibration(person * const thePerson, const double theTimeZero, const double theTimeOne, const double theTimeTwo, const double theTimeThree)
{
	if(thePerson->GetBirthDay() < theTimeZero)
		new TimeSplit(thePerson,theTimeZero);
	
	if(thePerson->GetBirthDay() < theTimeOne)
		new TimeSplit(thePerson,theTimeOne);
	
	if(thePerson->GetBirthDay() < theTimeTwo)
		new TimeSplit(thePerson,theTimeTwo);
	
	if(thePerson->GetBirthDay() < theTimeThree)
		new TimeSplit(thePerson,theTimeThree);
}

/////////////////////
/////////////////////

TimeSplit::TimeSplit(person * const thePerson, const double Time) :
event(Time),
pPerson(thePerson)
{
	if(Time >= thePerson->GetNatDeathDate()) { Cancel(); }
}

TimeSplit::~TimeSplit()
{}

bool TimeSplit::CheckValid()
{
	return true;
}

void TimeSplit::Execute()
{
	if(GetTime() == 13514.25)
		pPerson->ResetCalibration();
	else if(GetTime() == 14609) {
		UpdateCalibrationArray(pPerson,0);
		pPerson->ResetCalibration();
	} else if(GetTime() == 14974) {
		UpdateCalibrationArray(pPerson,1);
		pPerson->ResetCalibration();
	} else if(GetTime() == 16225) {
		UpdateCalibrationArray(pPerson,2);
		pPerson->ResetCalibration();
	}
}

/////////////////////
/////////////////////

void CreateCalibrationArray()
{
	C1 = new double[9];
	L21 = new double[36];
	R3 = new double[9];
	R8 = new double[9];
	ART1 = new double[48];
	ART4 = new double[3];
	ART5 = new double[9];
	ART6 = new double[3];
	ART9 = new double[9];
	ART10 = new double[3];
	ART11 = new double[9];
	ART12 = new double[3];
	ART13 = new double[9];
	ART14 = new double[9];
	Pre2010 = new double[3];
	In2014 = new unsigned int[2];
	HivArray = new unsigned int[3];
	DiagArray = new unsigned int[3];
	ArtArray = new unsigned int[3];
	R3_Counter = new unsigned int[9];
	R8_Counter = new unsigned int[9];
	ART6_Counter = new unsigned int[3];
	ART10_Counter = new unsigned int[3];
	ART12_Counter = new unsigned int[3];

	Pie_1 = new unsigned int[3];
	Pie_2 = new unsigned int[3];
	Pie_3 = new unsigned int[6];
	
	for(size_t i=0;i<48;i++) {
		if(i<2)
			In2014[i] = 0;
		if(i<3) {
			ART4[i] = 0;
			ART6[i] = 0;
			ART10[i] = 0;
			ART12[i] = 0;
			Pre2010[i] = 0;
			HivArray[i] = 0;
			DiagArray[i] = 0;
			ArtArray[i] = 0;
			ART6_Counter[i] = 0;
			ART10_Counter[i] = 0;
			ART12_Counter[i] = 0;
			Pie_1[i] = 0;
			Pie_2[i] = 0;
		}
		if(i<6)
			Pie_3[i] = 0;
		if(i<9) {
			C1[i] = 0;
			R3[i] = 0;
			R8[i] = 0;
			ART5[i] = 0;
			ART9[i] = 0;
			ART11[i] = 0;
			ART13[i] = 0;
			ART14[i] = 0;
			R3_Counter[i] = 0;
			R8_Counter[i] = 0;
		}
		if(i<36)
			L21[i] = 0;
		ART1[i] = 0;
	}
}

/////////////////////
/////////////////////

void UpdateCalibrationArray(person * const thePerson, const unsigned int theTimeIndex)
{
	// C1 - Proportion of individuals that ever enter care.
	if(thePerson->GetCalEverCare())
		C1[(theTimeIndex * 3) + (thePerson->GetCalCareRoute()-1)]++; //1 = Hct, 2 = Vct, 3 = Pict.
	
	// L2.1 - CD4 count at first CD4 measurement.
	if(thePerson->GetCalEverCare()) {
		unsigned int i = 0;
		switch(thePerson->GetCalCd4EntryCare()) {
			case 1: i = 3; break;
			case 2: i = 2; break;
			case 3: i = 1; break;
			case 4: i = 0; break;
			default: break;
		}
		i += (thePerson->GetCalCareRoute()-1) * 4;
		L21[(theTimeIndex * 12) + i]++;
	}
	
	// R3 - Mean number of secondary CD4 appointments prior to becoming eligible for ART.
	if(thePerson->GetCalEverArt() && thePerson->GetCd4TestCount() > 1) {
		R3[(theTimeIndex * 3) + (thePerson->GetCalAtArtCareRoute()-1)] += thePerson->GetCd4TestCount() - 1;
		R3_Counter[(theTimeIndex * 3) + (thePerson->GetCalAtArtCareRoute()-1)]++;
	}
	
	// R8 - Mean CD4 count when receiving secondary CD4 test results.
	if(thePerson->GetCalEverCare() && thePerson->GetCd4TestCount() > 1) {
		R8[(theTimeIndex * 3) + (thePerson->GetCalCareRoute()-1)] += thePerson->GetSecondaryCd4();
		R8_Counter[(theTimeIndex * 3) + (thePerson->GetCalCareRoute()-1)] += thePerson->GetCd4TestCount() - 1;
	}
	
	// ART1 - CD4 count at ART initiation.
	if(thePerson->GetCalEverArt()) {
		unsigned int i = 0;
		switch(thePerson->GetCalCd4AtArt()) {
			case 1: i = 3; break;
			case 2: i = 2; break;
			case 3: i = 1; break;
			case 4: i = 0; break;
			default: break;
		}
		ART1[(theTimeIndex * 16) + 12 + i]++;
		i += (thePerson->GetCalAtArtCareRoute()-1) * 4;
		ART1[(theTimeIndex * 16) + i]++;
	}
	
	// ART4 - Mean number of pre-ART clinic visits prior to ART initiation.
	if(thePerson->GetCalEverArt())
		ART4[theTimeIndex] += thePerson->GetCalAtArtPreArtVisitCount();
	
	// ART5 - Proportion of ppl initiating ART after diagnosis and successful retention in care until becoming eligible for treatment.
	if(thePerson->GetCalEverArt() && !thePerson->GetCalAtArtEverReturnCare() && !thePerson->GetArtAtEnrollment())
		ART5[(theTimeIndex * 3) + (thePerson->GetCalAtArtCareRoute()-1)]++;
	
	// ART6 - Mean time from diagnosis to ART initiation for ppl successfully retained in care. (HCT ONLY)
	if(thePerson->GetCalEverArt() && !thePerson->GetCalAtArtEverReturnCare() && thePerson->GetCalCareRoute() == 1 && !thePerson->GetArtAtEnrollment()) {
		ART6[theTimeIndex] += thePerson->GetCalArtDay() - thePerson->GetCalDiagDay();
		ART6_Counter[theTimeIndex]++;
	}
	
	// ART9 - Proportion of ppl initiating ART, loss but return prior to becoming eligible.
	if(thePerson->GetCalEverArt() && !thePerson->GetArtAtEnrollment() && thePerson->GetCalAtArtEverReturnCare() && !thePerson->GetCalAtArtEligibleAtReturnCare())
		ART9[(theTimeIndex * 3) + (thePerson->GetCalAtArtCareRoute()-1)]++;
	
	// ART10 - Mean time from diagnosis to ART initiation for ppl lost but returned prior to becoming eligible.
	if(thePerson->GetCalEverArt() && !thePerson->GetArtAtEnrollment() && thePerson->GetCalAtArtEverReturnCare() && !thePerson->GetCalAtArtEligibleAtReturnCare()) {
		ART10[theTimeIndex] += thePerson->GetCalArtDay() - thePerson->GetCalDiagDay();
		ART10_Counter[theTimeIndex]++;
	}
	
	// ART11 - Proportion of ppl initiating ART, loss andd return when eligible.
	if(thePerson->GetCalEverArt() && !thePerson->GetArtAtEnrollment() && thePerson->GetCalAtArtEverReturnCare() && thePerson->GetCalAtArtEligibleAtReturnCare())
		ART11[(theTimeIndex * 3) + (thePerson->GetCalAtArtCareRoute()-1)]++;
	
	
	// ART12 - Mean time from diagnosis to ART initiation for ppl lost and returned when eligible.
	if(thePerson->GetCalEverArt() && !thePerson->GetArtAtEnrollment() && thePerson->GetCalAtArtEverReturnCare() && thePerson->GetCalAtArtEligibleAtReturnCare()) {
		ART12[theTimeIndex] += thePerson->GetCalArtDay() - thePerson->GetCalDiagDay();
		ART12_Counter[theTimeIndex]++;
	}
	
	// ART13 - Proportion of ppl initiating ART who had already been on it.
	if(thePerson->GetCalEverArt() && thePerson->GetCalEverReturnArt())
		ART13[(theTimeIndex * 3) + (thePerson->GetCalAtArtCareRoute()-1)]++;
	
	// ART14 - Proportion of ppl initiating ART at enrollment visit (FastTrackArt).
	if(thePerson->GetCalEverArt() && thePerson->GetArtAtEnrollment())
		ART14[(theTimeIndex * 3) + (thePerson->GetCalAtArtCareRoute()-1)]++;
	
	// HIV-positive individuals initiating ART per year;
	if(thePerson->GetSeroStatus() && thePerson->Alive())
		HivArray[theTimeIndex]++;
	if(thePerson->GetDiagnosedState())
		DiagArray[theTimeIndex]++;
	if(thePerson->GetEverArt())
		ArtArray[theTimeIndex]++;
	
	// Pre2010 - Dx levels pre-2010. (don't run this code after 2010)
	if(theTimeIndex == 0 && thePerson->Alive()) {
		if(thePerson->GetDiagnosedState()) {
			Pre2010[0]++;
			if(thePerson->GetDiagnosisRoute() == 2)
				Pre2010[1]++;
			else if(thePerson->GetDiagnosisRoute() == 3)
				Pre2010[2]++;
		}
	}
	if(theTimeIndex == 2 && thePerson->Alive()) {
		if(thePerson->GetInCareState()) {
			In2014[0]++;
		if(thePerson->GetArtInitiationState())
			In2014[1]++;
		}
	}

	/* Pie Charts */
	// Previously thePerson->GetCalEligibleAtEnrollment();

	if(theTimeIndex == 0) {
		if(thePerson->GetCalEverArt() && thePerson->GetArtAtEnrollment())
			Pie_1[0]++;
		else if(thePerson->GetCalEverArt() && !thePerson->GetArtAtEnrollment())
			Pie_1[1]++;
		else if(thePerson->GetCalEverArt() && thePerson->GetCalEverReturnArt())
			Pie_1[2]++;
	}

	if(theTimeIndex == 1) {
		if(thePerson->GetCalEverArt() && thePerson->GetArtAtEnrollment())
			Pie_2[0]++;
		else if(thePerson->GetCalEverArt() && !thePerson->GetArtAtEnrollment())
			Pie_2[1]++;
		else if(thePerson->GetCalEverArt() && thePerson->GetCalEverReturnArt())
			Pie_2[2]++;
	}

	if(theTimeIndex == 2) { // not discrete.
		if(thePerson->GetCalEverArt() && thePerson->GetArtAtEnrollment() && ((thePerson->GetCalArtDay() - thePerson->GetCalDiagDay()) <= 90))
			Pie_3[0]++;
		else if(thePerson->GetCalEverArt() && thePerson->GetArtAtEnrollment() && ((thePerson->GetCalArtDay() - thePerson->GetCalDiagDay()) > 90))
			Pie_3[1]++;
		else if(thePerson->GetCalEverArt() && !thePerson->GetArtAtEnrollment() && !thePerson->GetCalAtArtEverReturnCare())
			Pie_3[2]++;
		else if(thePerson->GetCalEverArt() && !thePerson->GetArtAtEnrollment() && thePerson->GetCalAtArtEverReturnCare() && !thePerson->GetCalAtArtEligibleAtReturnCare())
			Pie_3[3]++;
		else if(thePerson->GetCalEverArt() && !thePerson->GetArtAtEnrollment() && thePerson->GetCalAtArtEverReturnCare() && thePerson->GetCalAtArtEligibleAtReturnCare())
			Pie_3[4]++;
		else if(thePerson->GetCalEverArt() && thePerson->GetCalEverReturnArt())
			Pie_3[5]++;
	}

}

/////////////////////
/////////////////////
