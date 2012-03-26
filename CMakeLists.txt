cmake_minimum_required(VERSION 2.6)
project(alg)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

set(CMAKE_CXX_FLAGS "-g -Wall")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

find_package(SFML REQUIRED)

include_directories(${SFML_INCLUDE_DIR})

set(mainLibs ${SFML_LIBRARY})

file(
	GLOB_RECURSE
	MAIN_SOURCES
	src/*
)

add_executable(alg ${MAIN_SOURCES})

target_link_libraries(alg ${mainLibs})
