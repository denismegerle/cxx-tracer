# CMakeList.txt : CMake project for tracer, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
project(tracer)
set(CMAKE_CXX_STANDARD 14)
set(THREADS_PREFER_PTHREAD_FLAG ON)
set(CMAKE_CXX_FLAGS "-O3")

find_package(Threads REQUIRED)
find_package(Git REQUIRED)

include(ExternalProject)
include(FetchContent)

### STB DEP : single file public domain libraries, we need the write image code (could use cimg, but for training...)
FetchContent_Declare(stblib
	GIT_REPOSITORY https://github.com/nothings/stb
    GIT_TAG f54acd4e13430c5122cab4ca657705c84aa61b08 # ver. 19.06.2020 
)
FetchContent_MakeAvailable(stblib)
include_directories(${stblib_SOURCE_DIR})
add_definitions(-DSTB_IMAGE_WRITE_IMPLEMENTATION)

### CIMG DEP : cool image library, display, read and write images
FetchContent_Declare(cimglib
	GIT_REPOSITORY https://github.com/dtschump/CImg
    GIT_TAG 052a45af8aa1c847f8d2649f5927cbee9b89be7c # ver. 19.06.2020 (2.9.1)
)
FetchContent_MakeAvailable(cimglib)
include_directories(${cimglib_SOURCE_DIR})




### TRACER BUILD
# Add source to this project's executable.
add_executable (tracer "tracer.cpp" "tracer.h" "src/light/point_light.h")

target_link_libraries(tracer PRIVATE maths)