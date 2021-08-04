cmake_minimum_required(VERSION 3.10)
project(arbitrary_prec_calculator LANGUAGES CXX)

include_directories(include)

# UNCOMMENT TO COMPILE LIBRARY TEST PROGRAM
#find_package(Catch2 REQUIRED)
#link_libraries(Catch2::Catch2)
#add_executable(test_ap_calculator app/Arithmetic.cpp app/TestArithmetic.cpp)
#set_property(TARGET test_ap_calculator PROPERTY CXX_STANDARD 20)
#install(TARGETS test_ap_calculator DESTINATION bin)

add_executable(ap_calculator app/Arithmetic.cpp app/APCalculator.cpp)
set_property(TARGET ap_calculator PROPERTY CXX_STANDARD 20)

install(TARGETS ap_calculator DESTINATION bin)

install(PROGRAMS demo DESTINATION bin)