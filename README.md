## "Evaluating Strategies to Improve HIV Care Outcomes in Kenya"
#### C++ Model Repository

This repository provides the source code for the mathematical model described in the manuscript: 
- Olney JJ _et al._ Evaluating Strategies to Improve HIV Care Outcomes in Kenya. (submitted)


#####  Source Code
The directory `./src/` includes the code required for creating the model. The mathematical model is implemented in C++, but the compiled C++ code is not designed to be run natively. Simulations are run by calling the C++ code through the statistical language [R](https://www.r-project.org/). The relevant scripts for calling the model and running simulations are found in the directory `./scripts/`.

##### Compiling the Model
To compile the model and access it through R has some platform specific requirements:

- For Unix / Mac OS X Users, ensure that that latest version of R is [installed](https://cran.r-project.org/src/base/R-3/) (v3.2.3 "Wooden Christmas-Tree" is the latest version, as of 10/12/2015), then follow the instructions below.

- For Windows Users, ensure that the latest version of R is [installed](https://cran.r-project.org/bin/windows/base/), and also [Rtools](http://cran.r-project.org/bin/windows/Rtools/), then follow the instructions below.
 
Compiling the model to create an R shared object file can be done by using the following command in the `./src/` directory:
```shell
R CMD SHLIB -o main.so *.cpp
````
Alternatively, the `./makefile` can be called by running the command `make`, this performs the same proccess as above and creates a `./main.so` shared object or `./main.dll` (Windows). This is then loaded by the `./scripts/run.R`, which defines wrapper R functions to call the model.

#####  Running the Model
Simulations were run on computing resources maintained by the [MRC Centre for Outbreak Analysis and Modelling, Imperial College London](https://www1.imperial.ac.uk/publichealth/departments/ide/outbreaks/). Multiple simulations were deployed simultaneously through use of a Python script `./scripts/control.py`, which handles directory creation, Rscript creation and management, job submission and subsequent analyses. These simulations were run by scaling down the population size in the model by 1/100th. However, these simulations were still computationally intensive: utilising 73 compute-hours and >5GB of memory on a 20-core cluster node.

Running simulations by scaling the population down further will reduce compute-time, but will increase stochastic error in the results. (For a test case, suggest a `popSize` of 1000 be specified in `./scripts/Run.R`, this will allow a single simulation to run in <2 minutes and produce a baseline set of results.)

#####  Figures
The directory `./figures/` contains R scripts for running model analyses and creating figures reported in the manuscript. Analyses in the manuscript rely on a scaled population size of 1/100th and 10 repeat simulations, the mean is then computed by the `./scripts/analysis.R` script before figures were generated.

---

For questions please contact Jack Olney: jack.olney11@imperial.ac.uk.

Created: 10th December, 2015