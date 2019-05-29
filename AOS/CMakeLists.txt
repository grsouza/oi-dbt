cmake_minimum_required (VERSION 2.6)

file(GLOB headers *.hpp)
file(GLOB sources *.cpp)

add_library(AOS ${sources} ${headers})