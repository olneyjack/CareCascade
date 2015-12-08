//
//  cascadeEvents.h
//  priorityQ
//
//  Created by Jack Olney on 22/10/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#ifndef __priorityQ__cascadeEvents__
#define __priorityQ__cascadeEvents__

#include <stdio.h>
#include "person.h"
#include "cohort.h"
#include "event.h"

/////////////////////
/////////////////////

class SeedInitialHivTests : public event {
public:
	SeedInitialHivTests(person * const thePerson, const double Time); //constructor
	~SeedInitialHivTests(); //destructor
	
	/* Methods */
	bool CheckValid();
	void Execute();
	
private:
	person * const pPerson;
};

/////////////////////
/////////////////////

class SeedTreatmentGuidelinesUpdate : public event {
public:
	SeedTreatmentGuidelinesUpdate(person * const thePerson, const double Time); //constructor
	~SeedTreatmentGuidelinesUpdate(); //destructor
	
	/* Methods */
	bool CheckValid();
	void Execute();
	
private:
	person * const pPerson;
};

/////////////////////
/////////////////////

class VctHivTest : public event {
public:
	VctHivTest(person * const thePerson, const double Time, const bool poc); //constructor
	~VctHivTest(); //destructor
	
	/* Methods */
	bool CheckValid();
	void Execute();
	
private:
	person * const pPerson;
	const bool pointOfCare;
};

/////////////////////
/////////////////////

class PictHivTest : public event {
public:
	PictHivTest(person * const thePerson, const double Time); //constructor
	~PictHivTest(); //destructor
	
	/* Methods */
	bool CheckValid();
	void Execute();
	
private:
	person * const pPerson;
};

/////////////////////
/////////////////////

class Cd4Test : public event {
public:
	Cd4Test(person * const thePerson, const double Time); //constructor
	~Cd4Test(); //destructor
	
	/* Methods */
	bool CheckValid();
	void Execute();
	
private:
	person * const pPerson;
};

/////////////////////
/////////////////////

class Cd4TestResult : public event {
public:
	Cd4TestResult(person * const thePerson, const double Time); //constructor
	~Cd4TestResult(); //destructor
	
	/* Methods */
	bool CheckValid();
	void Execute();
	
private:
	person * const pPerson;
};

/////////////////////
/////////////////////

class PreArtDropout : public event {
public:
	PreArtDropout(person * const thePerson, const double Time); //constructor
	~PreArtDropout(); //destructor

	/* Methods */
	bool CheckValid();
	void Execute();

private:
	person * const pPerson;
};

/////////////////////
/////////////////////

class ArtInitiation : public event {
public:
	ArtInitiation(person * const thePerson, const double Time); //constructor
	~ArtInitiation(); //destructor
	
	/* Methods */
	bool CheckValid();
	void Execute();
	
private:
	person * const pPerson;
};

/////////////////////
/////////////////////

class ArtDropout : public event {
public:
	ArtDropout(person * const thePerson, const double Time); //constructor
	~ArtDropout(); //destructor
	
	/* Methods */
	bool CheckValid();
	void Execute();
	
private:
	person * const pPerson;
};

/////////////////////
/////////////////////


#endif /* defined(__priorityQ__cascadeEvents__) */
