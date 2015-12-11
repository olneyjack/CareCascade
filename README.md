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
 
Compiling the model to create an R shared object file can be done by using the following command in the `./src/` directory (note Windows uses replace `.so` with `.dll`:
```shell
R CMD SHLIB -o main.so *.cpp
````
Alternatively, the `./makefile` can be called by running the command `make`, this performs the same proccess as above and creates a `./main.so` shared object or `./main.dll` (Windows). This is then loaded by the `./scripts/run.R`, which defines wrapper R functions to call the model.

#####  Running the Model
Simulations were run on computing resources maintained by the [MRC Centre for Outbreak Analysis and Modelling, Imperial College London](https://www1.imperial.ac.uk/publichealth/departments/ide/outbreaks/). Multiple simulations were deployed simultaneously through use of a Python script. The file `./scripts/control.py`, contains an editable version of the Python control script which is controlled by calling `sh ./scripts/control.sh` or running `./scripts/control.bat` (Windows). The `control.py` script needs setting up by filling in the appropriate parent directory paths and specifying the path to a relevant cluster. Once complete, the `control.py` will handle directory creation, Rscript creation, job submission and subsequent analyses for all interventions. These simulations were still computationally intensive: utilising 73 compute-hours and >5GB of memory on a 20-core cluster node.

Running simulations by scaling the population down further will reduce compute-time, but will increase stochastic error in the results. (For a test case, suggest a `popSize` of 1000 be specified in `./scripts/Run.R`, this will allow a single simulation to run in <2 minutes and produce a baseline set of results.)

For a test case, It is suggested that `./scripts/Run.R` is used on a local machine running R. This will allow a single simulation to be run to <2 minutes and produce a baseline set of results (_caution:_ there will be a large degree of stochastic error in this quick simulation).

#####  Figures
The directory `./figures/` contains the R script `figures.R` for running model analyses and creating figures reported in the manuscript. Analyses in the manuscript rely on a scaled population size of 1/10th and 10 repeat simulations. Additionally, the multivariate analysis must be complete to generate figure 3 and figure 4; this can be accomplished by running the multivariate Python control script `./scripts/multivariate-control.py`.

---

For questions please contact Jack Olney: jack.olney11@imperial.ac.uk.

Created: 10th December, 2015