//
//  update.h
//  priorityQ
//
//  Created by Jack Olney on 16/10/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#ifndef __priorityQ__update__
#define __priorityQ__update__

#include <stdio.h>
#include "person.h"
#include "population.h"

void SeedTreatmentUpdate(person * const thePerson, const double theTime);

void ScheduleCd4Update(person * const thePerson, const double theTime);

void ScheduleWhoUpdate(person * const thePerson, const double theTime);

void ScheduleVectorUpdate(person * const thePerson, const double theTime);

void ScheduleIncidence(population * thePopulation);

void ScheduleBetaCalculation(population * thePopulation);

#endif /* defined(__priorityQ__update__) */
