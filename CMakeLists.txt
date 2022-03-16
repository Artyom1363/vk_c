cmake_minimum_required(VERSION 3.0.0)
project(fib)

add_subdirectory(home1)

add_executable(${PROJECT_NAME} it.c)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )

target_include_directories(${PROJECT_NAME} PUBLIC ${HOME1_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${HOME1_LIBRARIES})

add_subdirectory(tests)