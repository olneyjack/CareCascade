//
//  population.h
//  priorityQ
//
//  Created by Jack Olney on 17/10/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#ifndef __priorityQ__population__
#define __priorityQ__population__

#include <stdio.h>
#include <vector>

class person;

using namespace std;

class population {
public:
	population(const double theSize); //constructor
	~population(); //destructor
	
	/* Methods */
	void Generate();
	
	/* Vector Methods */
	void InitialiseVector();
	void AddPerson(person * thePerson);
	void RemovePerson(person * thePerson);
	void UpdateVector(person * thePerson);
	void PushInVector(person * thePerson);
	void SwapOutVector(person * thePerson);
	
	/* Infectiousness Methods */
	void InitialiseArray();
	void UpdateArray(person * const thePerson);
	void PushInArray(person * const thePerson);
	void SwapOutArray(person * const thePerson);
	
	/* Accessor Methods */
	double GetReferenceYear() const { return referenceYear; }
	double GetBeta() const { return beta; }
	
	/* Incidence Calculation */
	double GetWeightedTotal() const;
	unsigned int GetInfectedCases();
	void CalculateBeta();
	double CalculateLambda(const double * theIRR, const double theTime);
	void CalculateIncidence(const size_t theIndex, const double theTime);
	void RandomiseInfection(const size_t theSize, const size_t theRow, vector<person *> theVector, const double theTime);
	void PassInfection(const size_t theRow, const double theTime);
	void AddCase() { incidentCases++; }
	
	/* Clear population */
	void Clear();
	
private:
	const double sizeAdjustment;
	unsigned int populationSize;
	unsigned int incidentCases;
	double const referenceYear;
	double beta;
	
	/* VectorVector */
	vector<vector<person *> > people;
	
	/* Infectiousness Array */
	unsigned int infectiousness[5];
};

#endif /* defined(__priorityQ__population__) */
