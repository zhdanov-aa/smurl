cmake_minimum_required(VERSION 3.5)

project(commands.test)

find_package(Threads REQUIRED)
find_package(GTest REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS False)

# Настройка сбора покрытия
include(CTest)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")

# include_directories(../IoC)
include_directories(../exceptions)
include_directories(../interface)
include_directories(../interface.mock)
include_directories(../commands)
# include_directories(mock)

add_executable(commands_test
    FallbackCommand_test.cpp
    MacroCommand_test.cpp
    ../commands/FallbackCommand.cpp ../commands/FallbackCommand.h
    ../commands/MacroCommand.cpp ../commands/MacroCommand.h
    ../exceptions/CommandException.cpp ../exceptions/CommandException.h
    ../exceptions/RuntimeError.cpp ../exceptions/RuntimeError.h
)

target_link_libraries(commands_test PRIVATE ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} GTest::gmock Threads::Threads)

add_test(NAME commands.test COMMAND commands_test)
