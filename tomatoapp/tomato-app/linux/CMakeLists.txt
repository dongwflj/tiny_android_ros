cmake_minimum_required(VERSION 2.6)
INCLUDE_DIRECTORIES(/usr/local/include/tomato)
INCLUDE_DIRECTORIES(../../tomato-emotion/include)

SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb -std=c++11")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall -std=c++11")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
# Check C++11 or C++0x support
#include(CheckCXXCompilerFlag)
#CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
#CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
#if(COMPILER_SUPPORTS_CXX11)
#   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
#   add_definitions(-DCOMPILEDWITHC11)
#   message(STATUS "Using flag -std=c++11.")
#elseif(COMPILER_SUPPORTS_CXX0X)
#   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
#   add_definitions(-DCOMPILEDWITHC0X)
#   message(STATUS "Using flag -std=c++0x.")
#else()
#   message(FATAL_ERROR "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
#endif()

SET(SRC_LIST main.cpp
             RobotServiceObserver.cpp
             RobotEvent.cpp
           )
ADD_EXECUTABLE(tomatoapp ${SRC_LIST})
LINK_DIRECTORIES("/usr/local/lib")
TARGET_LINK_LIBRARIES(tomatoapp log4cplus tomatosdk tomatoemotion) 


SET(CMAKE_INSTALL_PREFIX /opt/tomato)
INSTALL(TARGETS tomatoapp DESTINATION tomatoapp)
