# Set minimum cmake version
cmake_minimum_required(VERSION 3.22)

# The name tests will be used several times so it
# helps to have it in a variable
set(This tests)

# Set all test source files to a variable
# Makes life easier if there were to be more files later on
set(Sources
	tests.cpp
)

# Create testing executable
add_executable(${This} ${Sources})

# Link the googletest library and the library created
# in the root directory so that the googletest framework
# can be used
target_link_libraries(${This} PUBLIC 
	gtest_main
	comp51915-cw1
)

# Create the test
add_test(
	NAME ${This}
	COMMAND ${This}
)