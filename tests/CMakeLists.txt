cmake_minimum_required(VERSION 3.22)

set(This tests)

set(Sources
	tests.cpp
)

add_executable(${This} ${Sources})
target_link_libraries(${This} PUBLIC 
	gtest_main
	comp51915-cw1
)

add_test(
	NAME ${This}
	COMMAND ${This}
)