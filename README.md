# Gray-Scott Reaction-Diffusion System Simulation

Table of Contents:
1. [Description](#description)
2. [Build Guide](#build-guide)
   1. [Requirements](#requirements)
   1. [Build Process](#build-process)
3. [Run Guide](#run-guide)
   1. [Running the Simulation](#running-the-simulation)
   1. [Running the Tests](#running-the-tests)
   1. [Parameter Guide](#parameter-guide)

## Description
This project contains a file that runs a simulation of the gray-scott 
reaction-diffusion system given some initial parameters. If no parameters
are given, default values are used. The output of each step of the 
simulation comes in the form of generated *.vtk files.

## Build Guide
### Requirements:
1. G++ compiler
1. CMake version 3.22 or higher (download [here](https://cmake.org/download/))
1. Git (download [here](https://git-scm.com/downloads))

### Build Process
To build the application locally:
1. [Download](https://github.com/stefanos-larkou/comp51915-cw1/archive/refs/heads/main.zip) 
the main branch and extract the resulting .zip file. You should then have a 
folder called comp51915-cw1-main.
1. Open a terminal window inside the extracted folder.
1. Run `git clone https://github.com/google/googletest.git`. This will 
download the [googletest framework](https://github.com/google/googletest), 
needed for running unit tests which check that the application is working 
correctly.
1. Create a new directory called `build` (or whatever else you choose, but 
the instructions assume you have given the name `build`). 
You can do this either in the file explorer or from the terminal by running
`mkdir build`.
1. Move into that folder in the terminal by running `cd build`.
1. Run `cmake ..`. The application will now be built inside this folder.
1. Run `make`.

## Run Guide
### Running the Simulation
After building the application, you may run the simulation by opening 
a terminal inside the `build` directory and running:
* `./gs` to run the simulation with the default values for the parameters
* `./gs <Du> <Dv> <F> <k> <threshold>` to run the simulation with custom
parameters.

The output *.vtk files will be generated inside the `build` directory.

### Running the Tests
After building the application, you may run the tests by opening a terminal
inside the `build` directory and running:
* `./tests/tests` to run the tests with the default values for the parameters
* `./tests/tests <Du> <Dv> <F> <k> <threshold>` to run the tests with custom 
parameters.

### Parameter Guide
The parameters are the following:
* <b><i>Du</i></b>: Diffusion rate of <b><i>U</i></b>
* <b><i>Dv</i></b>:Diffusion rate of <b><i>V</i></b>
* <b><i>F</i></b>: Feed rate
* <b><i>k</i></b>: Kill rate
* <b><i>threshold</i></b>: The application contains a function which counts the number
of elements in <b><i>V</i></b> that are above a certain threshold. That threshold is 
defined by this parameter.