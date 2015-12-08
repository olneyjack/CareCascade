//
//  interventions.h
//  priorityQ
//
//  Created by Jack Olney on 31/10/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#ifndef __priorityQ__interventions__
#define __priorityQ__interventions__

#include <stdio.h>
#include "person.h"
#include "event.h"

/////////////////////
/////////////////////

void SeedInterventions(person * const thePerson);

/////////////////////
/////////////////////

class Interventions : public event { //For reporting Outputs annually.
public:
	Interventions(person * const thePerson, const double Time); //constructor
	~Interventions(); //destructor
	
	/* Methods */
	bool CheckValid();
	void Execute();
	
private:
	person * const pPerson;
};

/////////////////////
/////////////////////

#endif /* defined(__priorityQ__interventions__) */
