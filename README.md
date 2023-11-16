# Gray-Scott Reaction-Diffusion System Simulation

#### Table of Contents:
1. [Description](#description)
2. [Build Guide](#build-guide)
    1. [Requirements](#requirements)
    2. [Manual Build Process](#manual-build-process)
    3. [Automatic Build Process](#automatic-build-process)
3. [Run Guide](#run-guide)
    1. [Running Manually](#running-manually)
    2. [Running Automatically](#running-automatically)
    3. [Parameter Guide](#parameter-guide)

## Description
This project contains a file that runs a simulation of the gray-scott
reaction-diffusion system given some initial parameters. If no parameters
are given, default values are used. The output of each step of the
simulation comes in the form of generated *.vtk files.

## Build Guide
### Requirements:
1. CMake version 3.22 or higher (download [here](https://cmake.org/download/))
2. Git (download [here](https://git-scm.com/downloads))
3. Docker (download [here](https://docs.docker.com/get-docker/))

There are two ways to build the application. One is using `cmake` and the other
using `docker`. If you use `docker` you will not need to use `git` or `cmake`
yourself, as `docker` will take care of that for you. However, the `docker` method
is not useful for running simulations, as the generated files disappear after the
script it runs terminates. You should therefore only use `docker` for testing (for now).
Also note that it is very likely you will need admin privileges for the `docker`
method.

Henceforth, the `cmake` method will be referred to as the manual method,
and the `docker` method as the automatic method (since it does most of the work for you).

### Manual Build Process
1. [Download](https://github.com/stefanos-larkou/comp51915-cw1/archive/refs/heads/main.zip)
   the main branch and extract the resulting .zip file. You should then have a
   folder called comp51915-cw1-main.
2. Open a terminal window inside the extracted folder.
3. Run `git clone https://github.com/google/googletest.git`. This will
   download the [googletest framework](https://github.com/google/googletest),
   needed for running unit tests which check that the application is working
   correctly.
4. Create a new directory called `build` (or whatever else you choose, but
   the instructions assume you have given the name `build`).
   You can do this either in the file explorer or from the terminal by running
   `mkdir build`.
5. Move into that folder in the terminal by running `cd build`.
6. Run `cmake ../sim`. The application will now be built inside this folder.
7. Run `make`.

### Automatic Build Process
1. [Download](https://github.com/stefanos-larkou/comp51915-cw1/archive/refs/heads/main.zip)
   the main branch and extract the resulting .zip file. You should then have a
   folder called comp51915-cw1-main. (skip if already done)
2. Open a terminal window inside the extracted folder.
3. Run `docker build -t gs .`. If you get a permission-related error, run the
   command again, adding  the `sudo` keyword. (You do not have to call the docker image
   gs, but this is what the instructions assume that you have called it)

Note: You can actually skip this whole section, building is not required in the
automatic method, you can run it from the get go (see [Running Automatically](#running-automatically)).

## Run Guide
In both cases, the output *.vtk files will be generated inside the `build/output/output_files{x}` 
directory, where `x` corresponds to how many times you ran a simulation minus one. So the first time 
you run a simulation the files will be in `build/output/output_files_0`.

### Running Manually
After building the application using the manual method, you may run a simulation or
the tests by opening a terminal inside the `build` directory and running:
* `./gs` to run the simulation with the default values for the parameters
* `./gs <Du> <Dv> <F> <k> <threshold>` to run the simulation with custom values
  for the parameters.
* `./tests/tests` to run the tests with the default values for the parameters
* `./tests/tests <Du> <Dv> <F> <k> <threshold>` to run the tests with custom

### Running Automatically
You may run a simulation or the tests by opening a terminal inside the <i>root</i> directory
and running:

`docker run -it gs`

If you get a permission-related error, run the command again, adding the `sudo`
keyword.

An interactive shell script will run. Simply follow the instructions to run a
simulation or the tests using either the default or custom values for the parameters.
Remember, while the simulation works, you will not get to see the files it outputs,
so there is little point in using this method to run simulations.

### Parameter Guide
The parameters are the following:
* <b><i>Du</i></b>: Diffusion rate of <b><i>U</i></b>
* <b><i>Dv</i></b>:Diffusion rate of <b><i>V</i></b>
* <b><i>F</i></b>: Feed rate
* <b><i>k</i></b>: Kill rate
* <b><i>threshold</i></b>: The application contains a function which counts the number
  of elements in <b><i>V</i></b> that are above a certain threshold. That threshold is
  defined by this parameter.
