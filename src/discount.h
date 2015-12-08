//
//  discount.h
//  priorityQ
//
//  Created by Jack Olney on 05/11/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#ifndef __priorityQ__discount__
#define __priorityQ__discount__

#include <stdio.h>
#include "event.h"

/////////////////////
/////////////////////

void SeedDiscount();

/////////////////////
/////////////////////

class AnnualDiscount : public event {
public:
	AnnualDiscount(const double Time); //constructor
	~AnnualDiscount(); //destructor
	
	/* Methods */
	bool CheckValid();
	void Execute();
};

/////////////////////
/////////////////////

void Discount();

/////////////////////
/////////////////////

#endif /* defined(__priorityQ__discount__) */
