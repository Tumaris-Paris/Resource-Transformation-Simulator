cmake_minimum_required(VERSION 3.26)
project(P2)

set(CMAKE_CXX_STANDARD 17)

add_executable(simulator formula.cpp
        plan.cpp
        plan.h
        formula.h
        simulator.cpp
        executablePlan.h
        executablePlan.cpp
        stockpile.h
        stockpile.cpp)
