#######################################################
# Example Script for Running 'CareCascade' Simulation #
#                 Author: Jack Olney                  #
#                  Copyright, 2015                    #
#       Contact: jack.olney11@imperial.ac.uk          #
#######################################################

# Clear all
rm(list=ls())

# Set working directory
setwd("~/git/CareCascade")

# Load the compiled model as a shared object (ensure that 'main.so' is in the current directory)
dyn.load("./main.so")

# Set the population fraction denominator
# (i.e. a larger number equals a faster simulation as the model simulates fewer individuals, but stochastic error is increased)
# e.g. 1000 means the model simulates 1/1000th of the population of Kenya.
popSize = 1000

##################
# THE SIMULATION #
##################

Baseline <-  .Call("CallCascade",popSize,
                0, # Implement HBCT Intervention (switch to 1 to implement from 2010)
                0, # Implement CT Intervention (switch to 1 to implement from 2010)
                0, # Implement HBCT (POC CD4) Intervention (switch to 1 to implement from 2010)
                0, # Implement Linkage Intervention (switch to 1 to implement from 2010)
                0, # Implement VCT POC CD4 Intervention (switch to 1 to implement from 2010)
                0, # Implement Pre-ART Outreach Intervention (switch to 1 to implement from 2010)
                0, # Implement Improved Care Intervention (switch to 1 to implement from 2010)
                0, # Implement POC CD4 Intervention (switch to 1 to implement from 2010)
                0, # Implement On-ART Outreach Intervention (switch to 1 to implement from 2010)
                0, # Implement Adherence Intervention (switch to 1 to implement from 2010)
                0, # Implement Immediate ART Intervention (switch to 1 to implement from 2010)
                0, # Implement Universal Test & Treat Intervention (switch to 1 to implement from 2010)
                0) # Calibration Flag (If this is switched to 1 the model simulates 100% coverage of HBCT from 2010 onwards.

# This variable now contains all the output arrays from the model and can be used to generate figures using the scripts in ./figures/
Baseline
