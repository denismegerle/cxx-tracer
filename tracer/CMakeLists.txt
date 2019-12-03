# CMakeList.txt : CMake project for tracer, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (tracer "tracer.cpp" "tracer.h")

target_link_libraries(tracer PRIVATE maths)