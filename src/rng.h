//
//  rng.h
//  priorityQ
//
//  Created by Jack Olney on 10/10/2014.
//  Copyright (c) 2014 Jack Olney. All rights reserved.
//

#ifndef priorityQ_rng_h
#define priorityQ_rng_h

#include <iostream>
#include <Rmath.h>
#include <R.h>

using namespace std;

/* Transitioning to R's RNG */
struct Rng {
    Rng(int) {};
    inline double Sample(double prob) { return unif_rand() <= prob ? 1 : 0; } // probably you should return bool here or int, but not double...
    inline double SampleExpDist(double mean) { return rexp(mean); }
};

#endif
