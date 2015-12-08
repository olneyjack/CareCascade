//
//  toolbox.h
//  priorityQ
//
//  Created by Jack Olney on 23/10/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#ifndef priorityQ_toolbox_h
#define priorityQ_toolbox_h

////////////////////
//PARAMETER VALUES//
////////////////////

////////////////////
/* Hiv testing times */
extern double hctHivTestTime;
extern double vctHivTestTimeOriginal;
extern double vctHivTestTime;
extern double pictHivTestTime_AsymptomaticOblivious;
extern double pictHivTestTime_AsymptomaticNoCd4Result;
extern double pictHivTestTime_AsymptomaticCd4ResultNotEligible;
extern double pictHivTestTime_AsymptomaticCd4ResultEligible;
extern double pictHivTestTime_SymptomaticOblivious;
extern double pictHivTestTime_SymptomaticNoCd4Result;
extern double pictHivTestTime_SymptomaticCd4Result;

/* Linkage probabilities */
extern double hctProbLinkRollOutOriginal;
extern double hctProbLinkRollOut;
extern double hctProbLinkPreviouslyDiagnosedRollOutOriginal;
extern double hctProbLinkPreviouslyDiagnosedRollOut;
extern double hctProbLinkOriginal;
extern double hctProbLink;
extern double hctProbLinkPreviouslyDiagnosedOriginal;
extern double hctProbLinkPreviouslyDiagnosed;
extern double vctProbLinkOriginal;
extern double vctProbLink;
extern double pictProbLinkOriginal;
extern double pictProbLink;

/* HCT time between Hiv test and Cd4 test [CD4-1] */
extern double hctCd4TestTime [4];

/* Time between Cd4 test and receiving results */
extern double cd4ResultTime;

/* Time between receiving result Cd4 test and subsequent Cd4 test */
extern double cd4TestTime;

/* Probability of attending Cd4 Test result visit */
extern double cd4ResultProbAttend;

/* Pre-Art retention probability (between test and result) */
extern double hctShortTermRetention;
extern double hctLongTermRetention;

extern double vctShortTermRetention;
extern double vctLongTermRetention;

extern double pictShortTermRetention;
extern double pictLongTermRetention;

/* Proportion returning for secondary Cd4 testing  */
extern double hctProbSecondaryCd4Test;
extern double vctProbSecondaryCd4Test;
extern double pictProbSecondaryCd4Test;

/* Time between eligiblity and Art initiation */
extern double artInitiationTime;

/* Art dropout times */
extern double artDropoutTimeOneYear;
extern double artDropoutTimeTwoYear;

////////////////
/* Intervention Flags */
extern bool pocFlag;
extern bool vctPocFlag;
extern bool immediateArtFlag;
extern bool adherenceFlag;
extern bool linkageFlag;
extern bool impCareFlag;

////////////////

////////////////
//DALY WEIGHTS//
////////////////

/* DALY weights */
extern double dalyWeight_Cd4_3;
extern double dalyWeight_Cd4_2;
extern double dalyWeight_Cd4_1;
extern double dalyWeightArt;

//////////////
//UNIT COSTS//
//////////////

/* Hiv care unit costs */
extern double hctVisitCost;
extern double rapidHivTestCost;
extern double preArtClinicVisitCost;
extern double labCd4TestCost;
extern double pocCd4TestCost;
extern double annualArtCost;

/* Intervention costs */
extern double annualAdherenceCost;
extern double outreachCost;
extern double annualLinkageCost;
extern double impCareCost;

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

/* Fun Functions */
double Random(const int i);

int Round(const double theDouble);

#endif