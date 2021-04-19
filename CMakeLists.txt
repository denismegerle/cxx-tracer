# CMakeList.txt : Top-level CMake project file
cmake_minimum_required (VERSION 3.8)

project ("tracer")

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

# Include sub-projects.
add_subdirectory ("tracer")
add_subdirectory("tracer/docs")
add_subdirectory ("maths")