//
//  outputUpdate.h
//  priorityQ
//
//  Created by Jack Olney on 30/10/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#ifndef __priorityQ__outputUpdate__
#define __priorityQ__outputUpdate__

#include <stdio.h>
#include "person.h"

void WritePop(person * const thePerson, const double theTime, const size_t theIndex);

void WriteHiv(person * const thePerson, const double theTime, const size_t theIndex);

void WriteArt(person * const thePerson, const double theTime, const size_t theIndex);

void WriteCare(person * const thePerson, const double theTime);

void UpdateCarePersonTime(person * const thePerson, const double theTime);

void WriteClinic(person * const thePerson, const double theTime);

void WriteDeath(person * const thePerson, const double theTime);

void WriteAidsDeath(person * const thePerson, const double theTime);

void Write2007(person * const thePerson);

void Write2012(person * const thePerson);

void Write2014(person * const thePerson);

void WriteCd4(person * const thePerson, const size_t theIndex);

void WriteWho(person * const thePerson, const size_t theIndex);

void WriteIncidence(unsigned int const &theIncidentCases, const size_t theIndex);

#endif /* defined(__priorityQ__outputUpdate__) */
