cmake_minimum_required(VERSION 3.8)
project(MIPSAssemblerSimulator)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp codegen.cpp)
add_executable(MIPSAssemblerSimulator ${SOURCE_FILES})