cmake_minimum_required (VERSION 3.8)
project(maths LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_RELEASE "/O2")

file(GLOB PUBLIC_MATH_HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/inc/maths/*.h)
file(GLOB PRIVATE_MATH_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/tpp/*.tpp)

add_library(
	maths
	${PUBLIC_MATH_HEADER_FILES}
	${PRIVATE_MATH_SOURCE_FILES}
)

target_include_directories(maths PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/tpp)	# these are template definitions
target_include_directories(maths PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)

target_compile_definitions(maths INTERFACE MATHS_VERSION=1003)