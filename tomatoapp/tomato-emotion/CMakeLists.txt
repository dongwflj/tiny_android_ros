cmake_minimum_required(VERSION 2.6)
INCLUDE_DIRECTORIES(include)
INCLUDE_DIRECTORIES(/usr/local/include/tomato)

SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb -std=c++11")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall -std=c++11")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
add_library(tomatoemotion SHARED
    src/RobotEmotionEngine.cpp
    src/Robot.cpp
    src/RobotStateStop.cpp
    src/RobotStateHappy.cpp
    src/RobotStateHungry.cpp
    src/RobotStateTired.cpp
        )

TARGET_LINK_LIBRARIES(tomatoemotion log4cplus tomatosdk) 
