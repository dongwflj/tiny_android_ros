cmake_minimum_required(VERSION 2.6)
INCLUDE_DIRECTORIES(include)
INCLUDE_DIRECTORIES(/usr/local/include/tomato)
INCLUDE_DIRECTORIES(../../algorithm)

SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb -std=c++11")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall -std=c++11")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
add_library(tomatonavi SHARED
    src/NaviAlgorithm.cpp
    src/SlamController.cpp
    src/Astar.cpp
    src/NaviRobot.cpp
    src/Object.cpp
    src/NaviState.cpp
    src/NaviStopped.cpp
    src/NaviMoving.cpp
    src/NaviFinish.cpp
    src/NaviRecovery.cpp
    src/OpticalFlow.cpp
        )

TARGET_LINK_LIBRARIES(tomatonavi log4cplus tomatoslam) 
