//
//  calibration.h
//  priorityQ
//
//  Created by Jack Olney on 01/12/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#ifndef __priorityQ__calibration__
#define __priorityQ__calibration__

#include <stdio.h>
#include "person.h"
#include "event.h"

void SeedCalibration(person * const thePerson, const double theTimeZero, const double theTimeOne, const double theTimeTwo, const double theTimeThree);

/////////////////////
/////////////////////

class TimeSplit : public event {
public:
	TimeSplit(person * const thePerson, const double Time); //constructor
	~TimeSplit(); //destructor
	
	/* Methods */
	bool CheckValid();
	void Execute();
	
private:
	person * const pPerson;
};

/////////////////////
/////////////////////

void CreateCalibrationArray();

void UpdateCalibrationArray(person * const thePerson, const unsigned int theTimeIndex);

#endif /* defined(__priorityQ__calibration__) */
