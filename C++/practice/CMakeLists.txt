cmake_minimum_required(VERSION 3.9)
project(practice_1)

set(CMAKE_CXX_STANDARD 11)
set( CMAKE_BUILD_TYPE Debug )

include_directories("include")

#add_executable(practice_1 test/strStr_test.cpp include/strStr.h src/strStr.cpp src/Solution.cpp include/Solution.h include/closestNumber.cpp include/closestNumber.h)

#add_executable(practice_1 src/closestNumber.cpp include/closestNumber.h test/closestNumber_test.cpp)

add_executable(practice_1 test/lastPosition_test.cpp include/lastPosition.h src/lastPosition.cpp)
