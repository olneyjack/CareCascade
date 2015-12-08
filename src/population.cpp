//
//  population.cpp
//  priorityQ
//
//  Created by Jack Olney on 17/10/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#include <iostream>
#include "rng.h"
#include "population.h"
#include "cohort.h"
#include "output.h"
#include "update.h"
#include "events.h"
#include "toolbox.h"
#include "outputUpdate.h"
#include "discount.h"
#include "calibration.h"
#include "eventQ.h"
#include "wp19.h"

using namespace std;

extern Rng * theRng;
extern eventQ * theQ;

population::population(const double theSize) :
sizeAdjustment(theSize),
populationSize(0),
incidentCases(0),
referenceYear(11688),
beta(1)
{
	Generate();
	InitialiseVector();
	CreateOutputArray();
	CreateGuidelinesArray();
	CreateCalibrationArray();
	ScheduleIncidence(this);
	ScheduleBetaCalculation(this);
	SeedDiscount();
	InitialiseArray();
}

population::~population()
{
	Clear();
}

/////////////
// METHODS //
/////////////

void population::Generate()
{	
		/* Function to schedule cohorts over time (not being used until I scale everything up) */
	const double popSize[66] = {11252466,400695,419630,440241,460305,481118,502226,523708,546673,570847,594209,619182,644442,667076,682797,695625,709410,722491,731131,734908,765901,776599,784373,783075,765226,722958,718529,708110,715455,729361,750663,775364,799972,814589,845603,856064,881087,915869,946729,983062,1028592,1055553,1080443,1096579,1106563,1112580,1117645,1126043,1136366,1148139,1163788,1191180,1219216,1247912,1277283,1307346,1338116,1369610,1401846,1434841,1468612,1503177,1538557,1574769,1611833,1649770};
	
	for(int i=0; i<66; i++)
		new cohort(this,popSize[i] / sizeAdjustment,i * 365.25);
}

////////////////////
// VECTOR METHODS //
////////////////////

void population::InitialiseVector()
{
	// Rows 0 to 33 are Susceptible. Rows 34 to 67 are Infected.
	people.resize(68,vector<person *>(0));
}

void population::AddPerson(person * thePerson)
{
	PushInVector(thePerson);
	populationSize++;
}

void population::RemovePerson(person * thePerson)
{
	SwapOutVector(thePerson);
	SwapOutArray(thePerson);
	populationSize--;
}

void population::UpdateVector(person * thePerson)
{
	SwapOutVector(thePerson);
	PushInVector(thePerson);
}

/////////////////////
/////////////////////

void population::PushInVector(person * thePerson)
{
	// 0to4,5to9,10to14,15to19,20to24,25to29,30to34,35to39,40to44,45to49,50to54,55to59,60to64,64to69,70to74,75to79,>80
	unsigned int ageCatMax[17] = {4,9,14,19,24,29,34,39,44,49,54,59,64,69,74,79,200};
	unsigned int i = 0;
	const double currentTime = theQ->GetTime();
	const double theAge = thePerson->GetAge(currentTime) / 365.25;
	
	while(theAge > ageCatMax[i] && i < 17)
		i++;
	
	if(i < 16)
		ScheduleVectorUpdate(thePerson,currentTime + ((ageCatMax[i] - theAge) * 365.25));
	
	if(thePerson->GetGender()) // If Male then i += 17;
		i += 17;
	
	if(thePerson->GetSeroStatus()) // If HIV-positive then i += 34;
		i += 34;
	
	thePerson->SetPersonIndex(people.at(i).size());
	thePerson->SetRowIndex(i);
	people.at(i).push_back(thePerson);
}

/////////////////////
/////////////////////

void population::SwapOutVector(person * thePerson)
{
	people.at(thePerson->GetRowIndex()).back()->SetRowIndex(thePerson->GetRowIndex());
	people.at(thePerson->GetRowIndex()).back()->SetPersonIndex(thePerson->GetPersonIndex());
	people.at(thePerson->GetRowIndex()).at(thePerson->GetPersonIndex()) = people.at(thePerson->GetRowIndex()).back();
	people.at(thePerson->GetRowIndex()).pop_back();
}

////////////////////////////
// INFECTIOUSNESS METHODS //
////////////////////////////

void population::InitialiseArray()
{
	for(size_t i=0;i<5;i++)
		infectiousness[i] = 0;
}

void population::UpdateArray(person * const thePerson)
{
	SwapOutArray(thePerson);
	PushInArray(thePerson);
}

void population::PushInArray(person * const thePerson)
{
	if(thePerson->Alive() && thePerson->GetSeroStatus()) {
		size_t index = 0;
		if(thePerson->GetArtInitiationState())
			index = 0;
		else switch(thePerson->GetCurrentCd4()) {
			case 1: index = 1; break;
			case 2: index = 2; break;
			case 3: index = 3; break;
			case 4: index = 4; break;
		}
		infectiousness[index]++;
		thePerson->SetInfectiousnessIndex(index);
	}
}

void population::SwapOutArray(person * const thePerson)
{
	if(thePerson->GetInfectiousnessIndex() < 5)
		infectiousness[thePerson->GetInfectiousnessIndex()]--;
}

///////////////////////////
// INCIDENCE CALCULATION //
///////////////////////////

double population::GetWeightedTotal() const
{
	/* Infectiousness weights */
	double wArt = 0.1;
	double w500 = 1.35;
	double w350500 = 1;
	double w200350 = 1.64;
	double w200 = 5.17;
	
	/* Calculate individual weights */
	double tArt = wArt * infectiousness[0];
	double t200 = w200 * infectiousness[1];
	double t200350 = w200350 * infectiousness[2];
	double t350500 = w350500 * infectiousness[3];
	double t500 = w500 * infectiousness[4];
	
	return(tArt + t500 + t350500 + t200350 + t200);
}

/////////////////////
/////////////////////

void population::CalculateBeta()
{
	beta = incidentCases / GetWeightedTotal();
}

/////////////////////
/////////////////////

double population::CalculateLambda(const double * theIRR, const double theTime)
{
	/* IncidenceCases (M+F Total - Spectrum2014) & IRR (0 to 16 are Female, 17 to 33 are Male */
	const double SpectrumIncidence[32] = {0,0,0,0,0,0,0,0,0,0,140,355,1134,1791,3418,6444,11887,21704,38623,66784,108993,165074,226131,269547,275327,243681,195612,152571,121318,101327,99767,93594};
	
	/* Find total number of infected (I) */
	double I = 0;
	if(theTime < 32 * 365.25) {
		
		double yr [32];
		for(size_t i=0; i<32; i++)
			yr[i] = i * 365.25;
		
		unsigned int j = 0;
		while(theTime > yr[j] && j < 32)
			j++;
		
		I = SpectrumIncidence[j] / sizeAdjustment;
	} else
		I = GetWeightedTotal();
	
	/* Calculate sum of S(a,s) and IRR(a,s) */
	double S = 0;
	for(size_t j=0; j<34; j++)
		S += people.at(j).size() * theIRR[j];
	
	/* Calculate and return lambda */
	if(S)
		return (GetBeta() * I) / S;
	else
		return 0;
}

/////////////////////
/////////////////////

void population::CalculateIncidence(const size_t theIndex, const double theTime)
{
	/* Define IRR's */
	const double IRR[34] = {0.000000,0.000000,0.000000,0.431475,0.979206,1.000000,0.848891,0.684447,0.550791,0.440263,0.336719,0.239474,0.167890,0.146594,0.171352,0.000000,0.000000,0.000000,0.000000,0.000000,0.244859,0.790423,1.000000,0.989385,0.854318,0.670484,0.493512,0.358977,0.282399,0.259244,0.264922,0.254788,0.164143,0.000000};
	
	/* Create incidence array (contains age and sex) */
	double incidence[34];
	for(size_t j=0; j<34; j++)
		incidence[j] = 0;
	
	/* Get lambda */
	double lambda = CalculateLambda(IRR,theTime);
	
	/* Find Incidence(a,s) */
	for(size_t j=0; j<34; j++)
		incidence[j] = Round(lambda * people.at(j).size() * IRR[j]);
	
	/* Randomly pick cases */
	for(size_t j=0; j<34; j++)
		if(incidence[j] != 0 && incidence[j] < people.at(j).size())
			RandomiseInfection(incidence[j],j,people.at(j),theTime);
	
	/* Record incidence and reset */
	WriteIncidence(incidentCases,theIndex);
	incidentCases = 0;
	cout << "Year " << 1970 + (theQ->GetTime() / 365.25) << endl;
}

/////////////////////
/////////////////////

void population::RandomiseInfection(const size_t theSize, const size_t theRow, vector<person *> theVector, const double theTime)
{
	/* Shuffle theVector (by value ONLY, not by reference) */
	random_shuffle(theVector.begin(),theVector.end(),Random);
	
	for(size_t i=0;i<theSize;i++)
		new Infection(people.at(theRow).at(theVector.at(i)->GetPersonIndex()),theTime + (theRng->doub() * 365.25));
}

/////////////////////
/////////////////////

void population::PassInfection(const size_t theRow, const double theTime)
{
	vector<person *> theVector = people.at(theRow);
	random_shuffle(theVector.begin(),theVector.end(),Random);
	
	unsigned int i = 0;
	while(people.at(theRow).at(theVector.at(i)->GetPersonIndex())->GetHivDate() != 0 && i < people.at(theRow).size())
		i++;
	
	new Infection(people.at(theRow).at(theVector.at(i)->GetPersonIndex()),theTime);
}

/////////////////////
/////////////////////

void population::Clear()
{
	for(size_t i=0;i<people.size();i++)
		for(size_t j=people.at(i).size();j > 0;j--) {
			delete people.at(i).at(j-1);
			people.at(i).pop_back();
		}
	people.clear();
}

/////////////////////
/////////////////////

