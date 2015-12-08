//
//  discount.cpp
//  priorityQ
//
//  Created by Jack Olney on 05/11/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#include <iostream>
#include "discount.h"
#include "toolbox.h"

using namespace std;

/////////////////////
/////////////////////

void SeedDiscount()
{
	for(size_t i=0;i<25;i++)
		new AnnualDiscount(14975.25 + 0.000001 +  (i * 365.25)); // + 0.01 so that discounting occurs the day after costs are collected.
}

/////////////////////
/////////////////////

AnnualDiscount::AnnualDiscount(const double Time) :
event(Time)
{}

AnnualDiscount::~AnnualDiscount()
{}

bool AnnualDiscount::CheckValid()
{
	return true;
}

void AnnualDiscount::Execute()
{
	Discount();
}

/////////////////////
/////////////////////

void Discount()
{
	/* DALY weights */
	dalyWeight_Cd4_3 *= 0.94;
	dalyWeight_Cd4_2 *= 0.94;
	dalyWeight_Cd4_1 *= 0.94;
	dalyWeightArt *= 0.94;
	
	/* Hiv care unit costs */
	hctVisitCost *= 0.94;
	rapidHivTestCost *= 0.94;
	preArtClinicVisitCost *= 0.94;
	labCd4TestCost *= 0.94;
	pocCd4TestCost *= 0.94;
	annualArtCost *= 0.94;
	
	/* Intervention costs */
	annualAdherenceCost *= 0.94;
	outreachCost *= 0.94;
	annualLinkageCost *= 0.94;
	impCareCost *= 0.94;
}

/////////////////////
/////////////////////