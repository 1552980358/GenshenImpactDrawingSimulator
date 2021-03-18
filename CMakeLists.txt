cmake_minimum_required(VERSION 3.17)
project(GenshenImpactDrawingSimulator)

set(CMAKE_CXX_STANDARD 20)

add_executable(GenshenImpactDrawingSimulator main.cpp record.cpp record.h draw.cpp draw.h)