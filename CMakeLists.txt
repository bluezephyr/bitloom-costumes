cmake_minimum_required(VERSION 3.12)
project(Costumes C)

set(CMAKE_C_STANDARD 99)
set(UNITY_HOME $ENV{UNITY_HOME})

set(UNITY_FILES
        ${UNITY_HOME}/extras/fixture/src/unity_fixture.c
        ${UNITY_HOME}/extras/memory/src/unity_memory.c
        ${UNITY_HOME}/src/unity.c
        )

add_library(bitloom-costumes STATIC
        ${UNITY_FILES}
        include/costumes.h
        include/costumes_defines.h
        src/costumes.c
        )

target_include_directories(bitloom-costumes PUBLIC include)
target_include_directories(bitloom-costumes PRIVATE ${UNITY_HOME}/src)
target_include_directories(bitloom-costumes PRIVATE ${UNITY_HOME}/extras/fixture/src)
target_include_directories(bitloom-costumes PRIVATE ${UNITY_HOME}/extras/memory/src)


# Unit test
add_executable(bitloom-costumes-test
        ${UNITY_FILES}
        include/costumes.h
        include/costumes_defines.h
        src/costumes.c
        tests/config/costumes_config.h
        tests/test_main.c
        tests/costumes/test_costumes.c
        )

target_include_directories(bitloom-costumes-test PRIVATE include)
target_include_directories(bitloom-costumes-test PRIVATE ${UNITY_HOME}/src)
target_include_directories(bitloom-costumes-test PRIVATE ${UNITY_HOME}/extras/fixture/src)
target_include_directories(bitloom-costumes-test PRIVATE ${UNITY_HOME}/extras/memory/src)
target_include_directories(bitloom-costumes-test PRIVATE tests)
target_include_directories(bitloom-costumes-test PRIVATE tests/costumes)
target_include_directories(bitloom-costumes-test PRIVATE tests/config)

