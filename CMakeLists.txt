cmake_minimum_required(VERSION 3.0.0)

# name of project
project(start)

# compile directory ./logic_lib
add_subdirectory(logic_lib)

set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-lm -pthread -g")

message("COSIN_DIST_LIB_INCLUDE_DIRS = ${COSIN_DIST_LIB_INCLUDE_DIRS}")
message("COSIN_DIST_LIB_LIBRARIES = ${COSIN_DIST_LIB_LIBRARIES}")


add_executable(${PROJECT_NAME} thread.c)

# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )

target_include_directories(${PROJECT_NAME} PUBLIC ${COSIN_DIST_LIB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${COSIN_DIST_LIB_LIBRARIES})

# add directory with tests
add_subdirectory(tests)