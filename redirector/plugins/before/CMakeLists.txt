cmake_minimum_required(VERSION 3.5)

project(before LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(../..)

add_library(before SHARED
    main.cpp
    BeforeCondition.cpp BeforeCondition.h
)
