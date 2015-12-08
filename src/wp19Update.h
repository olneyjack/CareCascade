//
//  wp19Update.h
//  priorityQ
//
//  Created by Jack Olney on 12/03/2015.
//  Copyright (c) 2015 Jack Olney. All rights reserved.
//

#ifndef __priorityQ__wp19Update__
#define __priorityQ__wp19Update__

#include <stdio.h>
#include "person.h"

void WriteGuidelinesPopDist(person * const thePerson, const size_t theIndex);

void WriteGuidelinesDeath(person * const thePerson);

void WriteGuidelinesArtInitiation(person * const thePerson);

void WriteGuidelinesNewInfection(person * const thePerson);

void WriteGuidelinesNewDiagnosis();

void WriteGuidelinesPreArtDropout();

void WriteGuidelinesArtDropout();

#endif /* defined(__priorityQ__wp19Update__) */
