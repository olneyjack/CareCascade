//
//  person.cpp
//  priorityQ
//
//  Created by Jack Olney on 09/10/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#include <iostream>
#include "rng.h"
#include "person.h"
#include "event.h"
#include "events.h"
#include "cohort.h"
#include "update.h"
#include "cascadeUpdate.h"
#include "cascadeEvents.h"
#include "output.h"
#include "interventions.h"
#include "calibration.h"
#include "outputUpdate.h"
#include "wp19Update.h"
#include "wp19.h"

extern Rng * theRng;

using namespace std;

person::person(population * thePop,const double Time) : //can use Time to specify the start time for the individual.
gender(0),
currentAge(0),
initialAge(0),
seroStatus(false),
seroconversionDay(0),
currentCd4(0),
initialCd4(0),
currentWho(0),
initialWho(0),
deathDay(0),
birthDay(Time),
artDay(0),
artTime(0),
diagDay(0),
careDay(0),
initArtDay(0),
lostArtDay(0),
lastUpdateTime(0),
diagNotLinkedTime(0),
hivDate(0),
hivDeathDate(0),
cd4DeclineDate(0),
cd4RecoverDate(0),
whoDeclineDate(0),
whoRecoverDate(0),
hctHivTestDate(0),
vctHivTestDate(0),
pictHivTestDate(0),
diagnosed(false),
diagnosisCount(0),
diagnosisRoute(0),
lastDiagnosisRoute(0),
lastDiagnosisDay(0),
inCare(false),
everCare(false),
everCd4Test(false),
cd4TestCount(0),
everCd4TestResult(false),
cd4TestResultCount(0),
secondaryCd4(0),
everLostPreArtCare(false),
everReturnPreArtCare(false),
eligibleAtReturnPreArtCare(false),
art(false),
everArt(false),
artAtEnrollment(false),
artCount(0),
everLostArt(false),
everReturnArt(false),
adherence(theRng->Sample(0.86)),
cd4AtArt(0),
hivDeath(false),
artDeath(false),
cd4Tx(0),
whoTx(0),
iDALY(0),
iDALY_OffArt(0),
iDALY_OnArt(0),
iDALY_LYL(0),
iHctVisitCost(0),
iRapidHivTestCost(0),
iPreArtClinicVisitCost(0),
iLabCd4TestCost(0),
iPocCd4TestCost(0),
iAnnualArtCost(0),
iAdherenceCost(0),
iArtOutreachCost(0),
iPreArtOutreachCost(0),
iLinkageCost(0),
iImpCareCost(0),
iHctVisitUnit(0),
iRapidHivTestUnit(0),
iPreArtClinicVisitUnit(0),
iLabCd4TestUnit(0),
iPocCd4TestUnit(0),
iAnnualArtUnit(0),
iAdherenceUnit(0),
iArtOutreachUnit(0),
iPreArtOutreachUnit(0),
iLinkageUnit(0),
iImpCareUnit(0),
iPop(thePop),
personIndex(0),
rowIndex(0),
infectiousnessIndex(5),
calEverDiag(false),
calDiagDay(0),
calDiagRoute(0),
calEverCare(false),
calCareDay(0),
calCareRoute(0),
calCd4EntryCare(0),
calCd4TestCount(0),
calEverArt(false),
calArtDay(0),
calCd4AtArt(0),
calAtArtCareRoute(0),
calAtArtPreArtVisitCount(0),
calAtArtEverReturnPreArtCare(false),
calAtArtEligibleAtReturnPreArtCare(false),
calEverReturnArt(false),
calEligibleAtEnrollment(false)
{
	gender = AssignGender();
	AssignInitialAge(Time);
	natDeathDate = AssignNatDeathDate(Time);
	iPop->AddPerson(this);
	SeedOutput(this);
	SeedGuidelinesOutput(this);
	SeedCalibration(this,13514.25,14609,14974,16225);
	SeedInterventions(this);
	SeedTreatmentUpdate(this,Time);
	
	// For person-time calculations
	if(Time > 14610) {
		lastUpdateTime = Time;
	} else {
		lastUpdateTime = 14610;
	}
}

person::~person()
{}

/////////////////////
/////////////////////

bool person::GetGender() const
{
	return gender;
}

/////////////////////
/////////////////////

void person::AssignInitialAge(const double Time)
{
	//Assign age as per Kenya in 1970 if Time = 1970.
	if(Time < 365.25) {
		const double ageKenya1970 [36] = {0.101640654,0.18074287,0.24488321,0.296843465,0.33534196,0.362704406,0.387709503,0.411405909,0.43137522,0.447971405,0.461838232,0.473612273,0.4832219,0.490165978,0.494779544,0.497326542,0.49881466,0.49881466,0.60001381,0.679748066,0.744514936,0.797175037,0.836087485,0.863900411,0.889576027,0.913307092,0.932633878,0.948053875,0.961023832,0.971869188,0.981102987,0.988755443,0.994329865,0.997681397,1,1};
		
		const double u = theRng->doub();
		unsigned int i = 0;
		
		while(u > ageKenya1970[i])
			i++;
		
		if(i < 18) {
			gender = true; //reassigns gender to Male.
			initialAge = (i * 5 + (theRng->doub() * 5)) * 365.25;
		} else {
			gender = false; //reassigns gender to Female.
			initialAge = ((i - 18) * 5 + (theRng->doub() * 5)) * 365.25;
		}
	} else {
		initialAge = theRng->doub() * 365.25;
	}
	
	currentAge = initialAge;
}

/////////////////////
/////////////////////

double person::GetNatDeathDate() const
{
	return natDeathDate;
}

/////////////////////
/////////////////////

bool person::Alive() const
{
	int aliveStatus = false;
	
	if(deathDay == 0)
		aliveStatus = true;
	
	return aliveStatus;
}

/////////////////////
/////////////////////

bool person::AssignGender()
{
	return theRng->Sample(0.5);
}

/////////////////////
/////////////////////

double person::GenerateNatDeathAge()
{
	/* Declare survival distribution */
	const double surv [2] [100] =
	{
		{1.00000000,0.98145100,0.97214488,0.96582011,0.96110208,0.95738742,0.95433431,0.95172039,0.94944006,0.94743295,0.94566314,0.94407159,0.94257429,0.94109068,0.93954823,0.93789463,0.93611357,0.93421700,0.93221778,0.93012122,0.92792613,0.92562952,0.92323584,0.92075326,0.91818804,0.91554641,0.91283182,0.91004768,0.90719923,0.90429347,0.90133553,0.89832326,0.89525190,0.89211762,0.88891849,0.88565704,0.88232609,0.87890355,0.87535805,0.87164828,0.86773807,0.86361718,0.85931118,0.85485995,0.85030953,0.84569490,0.84100722,0.83618908,0.83115774,0.82582087,0.82009380,0.81394228,0.80738516,0.80046345,0.79322486,0.78569636,0.77784411,0.76957485,0.76077014,0.75131225,0.74109365,0.73003579,0.71808146,0.70517538,0.69126156,0.67627985,0.66016140,0.64283084,0.62421767,0.60426456,0.58293160,0.56020659,0.53611211,0.51070683,0.48408726,0.45637810,0.42769291,0.39813334,0.36782505,0.33694613,0.28555679,0.24200510,0.20509569,0.17381552,0.14730605,0.12483967,0.10579974,0.08966370,0.07598864,0.06439923,0.05457738,0.04625351,0.03919916,0.03322070,0.02815404,0.02386013,0.02022110,0.01713708,0.01452342,0.01230838},
		{1.000000000,0.976467000,0.966046144,0.958746700,0.953199391,0.948735558,0.944982360,0.941727841,0.938893240,0.936442729,0.934351652,0.932540879,0.930875361,0.929216541,0.927437091,0.925445884,0.923207230,0.920726573,0.918003063,0.915014045,0.911739210,0.908207132,0.904499831,0.900709072,0.896908080,0.893136581,0.889395232,0.885657993,0.881901032,0.878108858,0.874271522,0.870384511,0.866447762,0.862458636,0.858417155,0.854321647,0.850162809,0.845919646,0.841563160,0.837059956,0.832375768,0.827492220,0.822411417,0.817144695,0.811711500,0.806126113,0.800368760,0.794378000,0.788066667,0.781331849,0.774082652,0.766288414,0.757990277,0.749259745,0.740177218,0.730796952,0.721091969,0.710951252,0.700235084,0.688800245,0.676527891,0.663353187,0.649261575,0.634252595,0.618327147,0.601472786,0.583654756,0.564822551,0.544935714,0.523978032,0.501953139,0.478879357,0.454788373,0.429735901,0.403808215,0.377126587,0.349838839,0.322116910,0.294164893,0.266221287,0.222382095,0.185761991,0.155172192,0.129619677,0.108274946,0.090445094,0.075551319,0.063110132,0.052717661,0.044036538,0.036784953,0.030727501,0.025667542,0.021440817,0.017910115,0.014960820,0.012497192,0.010439254,0.008720202,0.007284228}
	};
	
	int i = gender;
	int j = 0;
	double random = theRng->doub();
	
	/* Walk up distribution to find the correct year of death */
	while (random < surv [i] [j] && j < 100)
		j++;
	
	/* Finds closest death year */
	if(j > 0) {
		double a = (random - surv [i] [j]);
		double b = (surv [i] [j] - a);
		if(a != b && a > b)
			j -= 1;
	}
	else if(j == 0)
		j = 1;
	
	/* convert j into days */
	j *= 365.25;
	
	return j;
}

/////////////////////
/////////////////////

double person::AssignNatDeathDate(const double Time)
{
	double deathAge = 0;
	/* Ensure that deathAge is not < initialAge */
	while(deathAge < initialAge)
		deathAge = GenerateNatDeathAge();
	
	/* Create Natural Death Date Event & Add to eventQ */
	new Death(this,Time + deathAge - initialAge,false);
	return Time + deathAge - initialAge;
}

/////////////////////
/////////////////////

void person::Kill(const double theTime, const bool theCause)
{
	deathDay = theTime;
	hivDeath = theCause;
	artDeath = art;
	iPop->RemovePerson(this);
	if(GetHivDate() && !GetSeroStatus())
		iPop->PassInfection(GetRowIndex(),theTime);
	return;
}

/////////////////////
/////////////////////

double person::GetAge(const double theTime)
{
	SetAge(theTime);
	return currentAge;
}

/////////////////////
/////////////////////

void person::SetAge(const double theTime)
{
	currentAge = initialAge + (theTime - birthDay);
}

/////////////////////
/////////////////////

void person::Hiv(const double theTime)
{
	SetSeroStatus(true);
	SetSeroconversionDay(theTime);
	SetHivIndicators();
	AssignHivDeathDate(theTime);
	ScheduleHivIndicatorUpdate(theTime);
	WriteGuidelinesNewInfection(this);
	UpdatePopulation();
	iPop->AddCase();
	iPop->UpdateArray(this);
}

/////////////////////
/////////////////////

void person::SetHivIndicators()
{
	SetInitialCd4Count();
	SetInitialWhoStage();
}

/////////////////////
/////////////////////

void person::SetInitialCd4Count()
{
	double uniformSample = theRng->doub();
	
	const double Cd4CatMax [5] = {0,0.03,0.19,0.42,1};
	
	unsigned int i = 0;
	
	while(uniformSample > Cd4CatMax[i])
		i++;
	
	currentCd4 = i;
	initialCd4 = i;
}

/////////////////////
/////////////////////

void person::SetInitialWhoStage()
{
	currentWho = 1;
	initialWho = 1;
}

/////////////////////
/////////////////////

void person::AssignHivDeathDate(const double theTime)
{
	new Death(this,GenerateHivDeathDate(theTime),true); // true flag signifies that it is an HIV-related death.
}

/////////////////////
/////////////////////

double person::GenerateHivDeathDate(const double theTime)
{
	//HivMortalityTime [ART] [WHO-1] [CD4-1];
	const double HivMortalityTime [2] [4] [4] =
	{
		{
			{17.18386669,26.93036884,163.91486393,833.52754525},
			{8.23354279,23.80904763,35.03608717,46.80780155},
			{3.81526196,7.21250938,15.90774020,22.92211067},
			{1.78259220,2.25749941,7.62232304,9.72800877}
		},
		
		{
			{18.08856633,28.34820428,172.54468642,877.41126992},
			{8.66702400,25.06255112,36.88067408,49.27214803},
			{4.01612864,7.59223501,16.74525408,24.12891853},
			{1.87644247,2.37635269,8.02362463,10.24017091}
		}
	};
	
	if(GetArtAdherenceState())
		return theTime + theRng->SampleExpDist(HivMortalityTime[art][currentWho-1][currentCd4-1] * 365.25);
	else
		return theTime + theRng->SampleExpDist(HivMortalityTime[0][currentWho-1][currentCd4-1] * 365.25);
}

/////////////////////
/////////////////////

void person::ScheduleHivIndicatorUpdate(const double theTime)
{
	ScheduleCd4Update(this,theTime);
	ScheduleWhoUpdate(this,theTime);
}

/////////////////////
/////////////////////

void person::SetDiagnosedState(const bool theState, unsigned int theRoute, const double theTime)
{
	if(!GetDiagnosedState()) {
		diagnosed = theState;
		diagnosisRoute = theRoute;
		calEverDiag = theState;
		calDiagRoute = theRoute;
		calDiagDay = theTime;
		diagDay = theTime;
		WriteGuidelinesNewDiagnosis();
	}
	diagnosisCount++;
	lastDiagnosisRoute = theRoute;
	lastDiagnosisDay = theTime;
}

/////////////////////
/////////////////////

void person::SetInCareState(const bool theState, const double theTime)
{
	if(theState) {
		if(everLostPreArtCare) {
			everReturnPreArtCare = true;
			if(GetEligible())
				eligibleAtReturnPreArtCare = true;
		}
		// Diagnosed but not linked to care time (for linkage intervention and annual linkage cost)
		if(theTime > 14610 && !GetEverArt()) {
			if(everLostPreArtCare)
				diagNotLinkedTime += theTime - lastDiagnosisDay;
			else
				diagNotLinkedTime += theTime - diagDay;
		}
	} else if(!GetEverArt()) {
		everLostPreArtCare = true;
		WriteGuidelinesPreArtDropout();
	}
	if(theState && !GetInCareState()) {
		everCare = theState;
		calEverCare = theState;
		calCareDay = theTime;
		calCareRoute = lastDiagnosisRoute;
		calCd4EntryCare = currentCd4;
		if(GetEligible())
			calEligibleAtEnrollment = true;
	}
	inCare = theState;
}

/////////////////////
/////////////////////

void person::SetEverCd4TestResultState(const bool theState)
{
	everCd4TestResult = theState;
	cd4TestResultCount++;
	if(cd4TestCount > 1)
		switch(currentCd4) {
			case 1: secondaryCd4 += 100; break;
			case 2: secondaryCd4 += 275; break;
			case 3: secondaryCd4 += 425; break;
			case 4: secondaryCd4 += 750; break;
			default: break;
		}
}

/////////////////////
/////////////////////

void person::SetArtInitiationState(const bool theState, const double theTime)
{
	art = theState;
	if(theState) {
		everArt = true;
		artDay = theTime;
		cd4AtArt = currentCd4;
		artCount++;
		if(everLostArt) { everReturnArt = true; calEverReturnArt = true; }
		if(!inCare) { SetInCareState(theState,theTime); }

		/* Calibration */
		calEverArt = true;
		calArtDay = theTime;
		calCd4AtArt = currentCd4;
		calAtArtCareRoute = lastDiagnosisRoute;
		calAtArtPreArtVisitCount = cd4TestCount + cd4TestResultCount;
		calAtArtEverReturnPreArtCare = everReturnPreArtCare;
		calAtArtEligibleAtReturnPreArtCare = eligibleAtReturnPreArtCare;
		
	} else if(theTime > 14610) {
		everLostArt = true;
		double yr [27];
		for(size_t i=0; i<27; i++)
			yr[i] = 14610 + (i * 365.25);
		
		unsigned int i=0;
		while(theTime > yr[i] && i<27)
			i++;
		
		if(artDay > yr[i-1])
			artTime += theTime - artDay;
		else
			artTime += theTime - yr[i-1];
	}
	if(!theState)
		SetInCareState(theState,theTime);
}

/////////////////////
/////////////////////

void person::SetArtAdherenceState(const double theProb)
{
	adherence = theRng->Sample(theProb);
}

/////////////////////
/////////////////////

void person::ResetCalibration()
{
	calEverCare = false;
	calCareDay = 0;
	calCareRoute = 0;
	calCd4EntryCare = 0;
	calCd4TestCount = 0;
	calEverArt = false;
	calArtDay = 0;
	calCd4AtArt = 0;
	calAtArtCareRoute = 0;
	calAtArtPreArtVisitCount = 0;
	calAtArtEverReturnPreArtCare = false;
	calAtArtEligibleAtReturnPreArtCare = false;
	calEverReturnArt = false;
	calEligibleAtEnrollment = false;
}

/////////////////////
/////////////////////
