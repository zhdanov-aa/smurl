cmake_minimum_required(VERSION 3.5)

project(smurl LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

add_subdirectory(httpsvr)
add_subdirectory(redirector)
add_subdirectory(IoC.test)
add_subdirectory(commands.test)


