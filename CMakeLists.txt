cmake_minimum_required(VERSION 3.22)

set(This comp51915-cw1)

project(${This} CXX)

set(CMAKE_CXX_STANDARD 17)

enable_testing()

add_subdirectory(googletest)

set(Headers
	gs.hpp
)

set(Sources
	gs.cpp
)

add_library(${This} STATIC ${Sources} ${Headers})
add_executable(gs gs.cpp)

add_subdirectory(tests)
