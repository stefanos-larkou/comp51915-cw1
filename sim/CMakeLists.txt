# Set minimum cmake version
cmake_minimum_required(VERSION 3.22)

# Set project name to variable so it can be changed easily
# Note: this name is used in the CMakeLists.txt file in the
# tests directory, if this name changes, that file will need
# to be modified as well
set(This comp51915-cw1)

# Set project name and language
project(${This} CXX)

# Set C++ version
set(CMAKE_CXX_STANDARD 17)

# Enable testing
enable_testing()

# Add subdirectories (run CMakeLists.txt files from those subdirectories)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../googletest ${CMAKE_CURRENT_BINARY_DIR}/googletest)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../tests ${CMAKE_CURRENT_BINARY_DIR}/tests)

# Set all header files and source files to a corresponding variable
# Makes life easier if there were to be more files later on
set(Headers
	gs.hpp
)
set(Sources
	gs.cpp
)

# Create a static library from the source and header files
add_library(${This} STATIC ${Sources} ${Headers})

# Create simulation executable
add_executable(gs gs.cpp)