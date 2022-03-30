cmake_minimum_required(VERSION 3.14)
project(test_cosin_dist)

set(CMAKE_CXX_STANDARD 11)
# it will not build without -lm -pthread 
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-fprofile-arcs -ftest-coverage -O0 -lm -pthread ")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )


file(GLOB SOURCES *.cpp)

find_package(GTest REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${COSIN_DIST_LIB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${COSIN_DIST_LIB_LIBRARIES} GTest::gtest_main)