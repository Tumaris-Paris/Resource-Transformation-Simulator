cmake_minimum_required(VERSION 3.26)
project(P2)

set(CMAKE_CXX_STANDARD 17)

add_executable(P2 formula.cpp
        plan.cpp
        plan.h
        formula.h
        resource_transformation_simulator.cpp
        executablePlan.h
        executablePlan.cpp
        stockpile.h
        stockpile.cpp)
