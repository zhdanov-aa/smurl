cmake_minimum_required(VERSION 3.5)

project(browser LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(../..)

add_library(browser SHARED
    main.cpp
    BrowserCondition.h BrowserCondition.cpp
)

add_custom_command(
    TARGET browser
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:browser> ${CMAKE_BINARY_DIR}/bin/
)
