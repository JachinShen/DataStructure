PROJECT(DataStructure)         

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
if(COMMAND cmake_policy)
      cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)
SET(CMAKE_BUILD_TYPE "Debug") 
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
# Declare the target (an executable)
include_directories( ${PROJECT_SOURCE_DIR}/include)
ADD_EXECUTABLE(1-1  
  src/1-1.cpp)
ADD_EXECUTABLE(1-2 
  src/1-2.cpp)
ADD_EXECUTABLE(1-3
  src/1-3.cpp)
ADD_EXECUTABLE(1-4
  src/1-4.cpp)
#MESSAGE(STATUS "OpenCV_LIBS: ${OpenCV_LIBS}")     
