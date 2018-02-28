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
ADD_EXECUTABLE(1077 
  src/1077.cpp)
  ADD_EXECUTABLE(1258
  src/1258.cpp)
  ADD_EXECUTABLE(1212
  src/1212.cpp)
  ADD_EXECUTABLE(1530
  src/1530.cpp)
#MESSAGE(STATUS "OpenCV_LIBS: ${OpenCV_LIBS}")     
