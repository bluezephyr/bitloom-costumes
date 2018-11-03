cmake_minimum_required(VERSION 3.12)
project(Costumes C)

set(CMAKE_C_STANDARD 99)
set(UNITY_HOME $ENV{UNITY_HOME})

include_directories(${UNITY_HOME}/src)
include_directories(${UNITY_HOME}/extras/fixture/src)

set(UNITY_FILES
        ${UNITY_HOME}/extras/fixture/src/unity_fixture.c
        ${UNITY_HOME}/src/unity.c
        )

add_executable(bitloom-costumes-test
        ${UNITY_FILES}
        include/costumes.h
        tests/costumes/costumes_defines.h
        src/costumes.c
        tests/test_main.c
        tests/costumes/test_costumes.c
        )

target_include_directories(bitloom-costumes-test PUBLIC include)
target_include_directories(bitloom-costumes-test PRIVATE src)
target_include_directories(bitloom-costumes-test PRIVATE tests)
target_include_directories(bitloom-costumes-test PRIVATE tests/costumes)
