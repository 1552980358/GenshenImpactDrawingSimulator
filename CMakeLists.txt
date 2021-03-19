cmake_minimum_required(VERSION 3.17)
project(GenshenImpactDrawingSimulator)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

add_executable(GenshenImpactDrawingSimulator main.cpp record.cpp record.h draw.cpp draw.h)