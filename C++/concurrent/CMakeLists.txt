cmake_minimum_required(VERSION 3.8)
project(C__11Concurrent)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost)
IF (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIR})
endif()

#find_package (Boost COMPONENTS REQUIRED filesystem)

#set (Boost_USE_STATIC_LIBS OFF) # enable dynamic linking
#set (Boost_USE_MULTITHREAD ON)  # enable multithreading

set(SOURCE_FILES main.cpp)
add_executable(C__11Concurrent ${SOURCE_FILES})
target_link_libraries (C__11Concurrent ${Boost_LIBRARIES})