cmake_minimum_required (VERSION 2.6)

file(GLOB headers *.h)
file(GLOB sources *.c)

add_library(seqalign ${sources} ${headers})