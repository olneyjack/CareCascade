//
//  impact.cpp
//  priorityQ
//
//  Created by Jack Olney on 27/10/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#include <iostream>
#include "impact.h"
#include "person.h"
#include "toolbox.h"
#include "eventQ.h"

using namespace std;

extern eventQ * theQ;
extern double * theDALY;
extern double * theDALY_OffArt;
extern double * theDALY_OnArt;
extern double * theDALY_LYL;

/////////////////////
/////////////////////

void UpdateDaly(person * const thePerson, const double theTime)
{
	/* Daly calculation for within a year. */
	if(thePerson->Alive()) {
		if(thePerson->GetArtInitiationState()) {
			thePerson->SetDalys((theQ->GetIncrementalTime() / 365.25) * dalyWeightArt);
			thePerson->SetDalys_OnArt((theQ->GetIncrementalTime() / 365.25) * dalyWeightArt);
		} else if(thePerson->GetCurrentCd4() >= 3) {
			thePerson->SetDalys((theQ->GetIncrementalTime() / 365.25) * dalyWeight_Cd4_3);
			thePerson->SetDalys_OffArt((theQ->GetIncrementalTime() / 365.25) * dalyWeight_Cd4_3);
		} else if(thePerson->GetCurrentCd4() == 2) {
			thePerson->SetDalys((theQ->GetIncrementalTime() / 365.25) * dalyWeight_Cd4_2);
			thePerson->SetDalys_OffArt((theQ->GetIncrementalTime() / 365.25) * dalyWeight_Cd4_2);
		} else if(thePerson->GetCurrentCd4() == 1) {
			thePerson->SetDalys((theQ->GetIncrementalTime() / 365.25) * dalyWeight_Cd4_1);
			thePerson->SetDalys_OffArt((theQ->GetIncrementalTime() / 365.25) * dalyWeight_Cd4_1);
		}
	} else if(theTime <= thePerson->GetNatDeathDate()) {
		if((theTime - thePerson->GetHivDeathDate()) <= 365.35) {
			thePerson->SetDalys((theTime - thePerson->GetHivDeathDate()) / 365.25);
			thePerson->SetDalys_LYL((theTime - thePerson->GetHivDeathDate()) / 365.25);
		} else {
			thePerson->SetDalys(1);
			thePerson->SetDalys_LYL(1);
		}
	}
}

/////////////////////
/////////////////////

void WriteDaly(person * const thePerson, const size_t theIndex)
{
	UpdateDaly(thePerson,(theIndex + 1) * 365.25);
	
	if((theIndex + 1) * 365.25 > 14610) {
		theDALY[theIndex - 40] += thePerson->GetDalys();
		theDALY_OffArt[theIndex - 40] += thePerson->GetDalys_OffArt();
		theDALY_OnArt[theIndex - 40] += thePerson->GetDalys_OnArt();
		theDALY_LYL[theIndex - 40] += thePerson->GetDalys_LYL();
	}
	
	thePerson->ResetDalys();
}

/////////////////////
/////////////////////
