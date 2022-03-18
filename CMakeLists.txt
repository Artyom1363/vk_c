cmake_minimum_required(VERSION 3.0.0)
project(notebook)

add_subdirectory(user_lib)

message("USER_LIB_INCLUDE_DIRS = ${USER_LIB_INCLUDE_DIRS}")
message("USER_LIB_LIBRARIES = ${USER_LIB_LIBRARIES}")

add_executable(${PROJECT_NAME} it.c)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )

target_include_directories(${PROJECT_NAME} PUBLIC ${USER_LIB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${USER_LIB_LIBRARIES})

add_subdirectory(tests)
