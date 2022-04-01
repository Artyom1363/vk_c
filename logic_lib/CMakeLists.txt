cmake_minimum_required(VERSION 3.0.0)
# this is name of project
project(cosin_dist)

set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-fprofile-arcs -ftest-coverage -fPIC -O0 -g")
# set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-lm -pthread -g")


# set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-g")
# adds all ".c" files 
file(GLOB SOURCES *.c)
file(GLOB INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR})

add_library(${PROJECT_NAME} ${SOURCES})

set(COSIN_DIST_LIB_LIBRARIES ${PROJECT_NAME} PARENT_SCOPE)
set(COSIN_DIST_LIB_INCLUDE_DIRS ${INCLUDE_DIRS} PARENT_SCOPE)