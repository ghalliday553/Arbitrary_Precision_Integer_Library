cmake_minimum_required(VERSION 3.10)
project(arbitrary_prec_calculator LANGUAGES CXX)

find_package(Catch2 REQUIRED)

include_directories(include)
link_libraries(Catch2::Catch2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -frounding-math")

add_executable(ap_calculator app/Arithmetic.cpp app/TestArithmetic.cpp)

set_property(TARGET ap_calculator PROPERTY CXX_STANDARD 20)