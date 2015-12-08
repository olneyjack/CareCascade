//
//  wp19.h
//  priorityQ
//
//  Created by Jack Olney on 12/03/2015.
//  Copyright (c) 2015 Jack Olney. All rights reserved.
//

#ifndef __priorityQ__wp19__
#define __priorityQ__wp19__

#include <stdio.h>
#include "person.h"
#include "event.h"

void SeedGuidelinesOutput(person * const thePerson);

/////////////////////
/////////////////////

class GuidelinesOutput : public event { //For reporting GuidelinesOutput from 2000 to 2035.
public:
	GuidelinesOutput(person * const thePerson, const double Time, const size_t theIndex); //constructor
	~GuidelinesOutput(); //destructor
	
	/* Methods */
	bool CheckValid();
	void Execute();
	
private:
	person * const pPerson;
	const size_t index;
};

/////////////////////
/////////////////////

/* Population.cpp uses these functions. */

void CreateGuidelinesArray();

/////////////////////
/////////////////////

#endif /* defined(__priorityQ__wp19__) */
