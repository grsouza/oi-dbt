cmake_minimum_required(VERSION 3.5)
project(openisa-dbt)

find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

#-Werror -DNDEGUG -O3 -Wextra -Wall  
set(CMAKE_CXX_FLAGS "-O3 -g -DNDEBUG -Wno-unused-function -std=c++17 -fno-rtti -flto -L/usr/local/lib/ -L/usr/lib/llvm-7/lib/ -I/usr/include/llvm-c-7/ -I/usr/local/include/llvm-c/ -I/usr/local/include/llvm -I/usr/local/include -I/usr/include/llvm-7 -fPIC -fvisibility-inlines-hidden -ffunction-sections -fdata-sections -D_GNU_SOURCE -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS ")
#-O3
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -flto -fno-rtti")

set(CMAKE_AR  "gcc-ar")
set(CMAKE_CXX_ARCHIVE_CREATE "<CMAKE_AR> qcs <TARGET> <LINK_FLAGS> <OBJECTS>")
set(CMAKE_CXX_ARCHIVE_FINISH   true)
#CMAKE_CXX_ARCHIVE_CREATE ( = <CMAKE_AR> qcs <TARGET> <LINK_FLAGS> <OBJECTS>)
#CMAKE_CXX_ARCHIVE_FINISH ( = true) # Or any other no-op command
#SET(CMAKE_AR  "gcc-ar-7")
#add_definitions(-D_GLIBCXX_USE_CXX11_ABI=0)

include_directories(include)

add_subdirectory(AOS)
add_subdirectory(RFT)
add_subdirectory(arglib)

add_library(dbt 
  regionMerge.cpp
  IREmitter.cpp 
  IRUtils.cpp 
  IROpt.cpp 
  OIDecoder.cpp
  interpreter.cpp 
  machine.cpp 
  manager.cpp 
  syscallIREmitter.cpp 
  syscall.cpp)

add_executable(oi-dbt main.cpp)

install(TARGETS oi-dbt RUNTIME DESTINATION bin)

llvm_map_components_to_libnames(llvm_libs support core irreader)

target_link_libraries(oi-dbt PUBLIC "LLVM-7" ${llvm_libs}
  papi 
  AOS
  RFT 
  dbt 
  arglib 
  pthread
  z
  dl
  curses
  stdc++fs
)
