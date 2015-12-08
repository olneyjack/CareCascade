//
//  toolbox.cpp
//  priorityQ
//
//  Created by Jack Olney on 31/10/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#include <stdio.h>
#include "toolbox.h"
#include "rng.h"

extern Rng * theRng;

////////////////////
//PARAMETER VALUES//
////////////////////

/* Hiv testing times */
double hctHivTestTime = 0.4342945 * 365.25;
double vctHivTestTimeOriginal = 7.8 * 365.25;
double vctHivTestTime = vctHivTestTimeOriginal;
double pictHivTestTime_AsymptomaticOblivious = 40 * 365.25;
double pictHivTestTime_AsymptomaticNoCd4Result = 30 * 365.25;
double pictHivTestTime_AsymptomaticCd4ResultNotEligible = 10 * 365.25;
double pictHivTestTime_AsymptomaticCd4ResultEligible = 10 * 365.25;
double pictHivTestTime_SymptomaticOblivious = 1.525 * 365.25;
double pictHivTestTime_SymptomaticNoCd4Result = 0.1 * 365.25;
double pictHivTestTime_SymptomaticCd4Result = 0.1 * 365.25;

/* Linkage probabilities */
double hctProbLinkRollOutOriginal = 0.054;
double hctProbLinkPreviouslyDiagnosedRollOutOriginal = 0.054;
double hctProbLinkOriginal = 0.3;
double hctProbLinkPreviouslyDiagnosedOriginal = 0.4;

double vctProbLinkOriginal = 0.95;
double pictProbLinkOriginal = 0.7;

double hctProbLinkRollOut = hctProbLinkRollOutOriginal;
double hctProbLinkPreviouslyDiagnosedRollOut = hctProbLinkPreviouslyDiagnosedRollOutOriginal;
double hctProbLink = hctProbLinkOriginal;
double hctProbLinkPreviouslyDiagnosed = hctProbLinkPreviouslyDiagnosedOriginal;
double vctProbLink = vctProbLinkOriginal;
double pictProbLink = pictProbLinkOriginal;

/* HCT time between Hiv test and Cd4 test [CD4-1] */
double hctCd4TestTime [4] = {252.04,175.78,174.59,116.34};

/* Time between Cd4 test and receiving results */
double cd4ResultTime = 30;

/* Time between receiving result Cd4 test and subsequent Cd4 test */
double cd4TestTime = 278.88;

/* Probability of attending Cd4 Test result visit */
double cd4ResultProbAttend = 0.9486833;

/* Pre-Art retention probability (between test and result) */
double hctShortTermRetention = 0.9486833;
double hctLongTermRetention = 0.9486833;

double vctShortTermRetention = 0.9486833;
double vctLongTermRetention = 0.9486833;

double pictShortTermRetention = 0.9486833;
double pictLongTermRetention = 0.9486833;

/* Proportion returning for secondary Cd4 testing  */
double hctProbSecondaryCd4Test = 0.75;
double vctProbSecondaryCd4Test = 0.75;
double pictProbSecondaryCd4Test = 0.75;

/* Time between eligiblity and Art initiation */
double artInitiationTime = 145.12;

/* Art dropout times */
double artDropoutTimeOneYear = 21.72 * 365.25; //0.045 py
double artDropoutTimeTwoYear = 52.13 * 365.25; //0.019 py

//////////////////////
//Intervention Flags//
//////////////////////

bool pocFlag = false;
bool vctPocFlag = false;
bool immediateArtFlag = false;
bool adherenceFlag = false;
bool linkageFlag = false;
bool impCareFlag = false;

////////////////
//DALY WEIGHTS//
////////////////

/* DALY weights */
double dalyWeight_Cd4_3 = 0.053;
double dalyWeight_Cd4_2 = 0.221;
double dalyWeight_Cd4_1 = 0.547;
double dalyWeightArt = 0.053;

//////////////
//UNIT COSTS//
//////////////

/* Hiv care unit costs */
double hctVisitCost = 8.00;
double rapidHivTestCost = 10.00;
double preArtClinicVisitCost = 28.00;
double labCd4TestCost = 12.00;
double pocCd4TestCost = 42.00;
double annualArtCost = 367.00;


/* Intervention costs */
double annualAdherenceCost = 33.54;
double outreachCost = 19.55;
double annualLinkageCost = 2.61;
double impCareCost = 7.05;

//How to use:
/* HBCT */
//HCT visit + HIV-test = 8 + 10 = $18
//HCT visit + HIV-test + POC-CD4 test = 8 + 10 + 42 = $60

/* VCT or PICT */
//Clinic visit + HIV-test + lab-CD4 test = 28 + 10 + 12 = $50 (Test visit)
//Clinic visit = $28 (Result visit)
//Clinic visit + HIV-test + POC-CD4 test = 28 + 10 + 42 = $80

/* Pre-ART Care */
//Clinic visit + lab-CD4 test = 28 + 12 = $40 (Test visit)
//Clinic visit = $28 (Result visit)
//Clinic visit + POC-CD4 test = 28 + 42 = $70

/* Random */
double Random(const int i)
{
	unsigned long long r = theRng->int64();
	return r % i;
}


int Round(const double theDouble)
{
	if((theDouble + 0.5) >= (int(theDouble) + 1))
		return int(theDouble) + 1;
	else
		return int(theDouble);
}