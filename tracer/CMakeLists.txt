# CMakeList.txt : CMake project for tracer, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

find_package( OpenCV REQUIRED )
add_definitions(-DSTB_IMAGE_WRITE_IMPLEMENTATION)

# Add source to this project's executable.
add_executable (tracer "tracer.cpp" "tracer.h")

target_link_libraries(tracer PRIVATE maths)