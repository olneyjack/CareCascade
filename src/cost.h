//
//  cost.h
//  priorityQ
//
//  Created by Jack Olney on 27/10/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#ifndef __priorityQ__cost__
#define __priorityQ__cost__

#include <stdio.h>
#include "person.h"
#include "event.h"

/////////////////////
/////////////////////

void ChargeHctVisit(person * const thePerson);

void ChargeVctPictHivTest(person * const thePerson);

void ChargePreArtClinicVisit(person * const thePerson);

void ChargePreArtClinicCd4Test(person * const thePerson);

void ChargePreArtClinicCd4ResultVisit(person * const thePerson);

void ChargePocCd4Test(person * const thePerson);

void ChargeArtCare(person * const thePerson, const double theTime, const double	theArrayTime);

void ChargeLinkageInt(person * const thePerson);

void ChargeImprovedCareInt(person * const thePerson);

/////////////////////
/////////////////////

void ChargeAdherence(person * const thePerson, const double theTime, const double theArrayTime);

void ChargePreArtOutreach(person * const thePerson);

void ChargeArtOutreach(person * const thePerson);

/////////////////////
/////////////////////

void WriteCost(person * const thePerson, const double theTime);

/////////////////////
/////////////////////

#endif /* defined(__priorityQ__cost__) */
