
cmake_minimum_required(VERSION 3.6.0)

project(TP-HW1)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
set(PROJECT_DIR ${CMAKE_SOURCE_DIR}/project)
add_compile_definitions(_POSIX_C_SOURCE _GNU_SOURCE _TESTING)

include_directories(project/include)
set(HW_SRC ${PROJECT_DIR}/include/data_management.h
           ${PROJECT_DIR}/src/data_management.c
           ${PROJECT_DIR}/include/operations.h
           ${PROJECT_DIR}/src/operations.c
           ${PROJECT_DIR}/testing/include/utils.h)
add_executable(${PROJECT_NAME} project/src/main.c ${HW_SRC})

enable_testing()

set(EXE_NAME TP-TESTING-HW1)
set(TEST_SEED 42)
set(TEST_DATA_DIR ${CMAKE_SOURCE_DIR}/project/testing/data)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS} include)

add_executable(${EXE_NAME} project/testing/src/main.cpp ${HW_SRC}
               project/testing/src/operations_tests.cpp project/testing/src/utils.cpp project/testing/src/management_tests.cpp)
target_link_libraries(${EXE_NAME} ${GTEST_BOTH_LIBRARIES} pthread stdc++fs)

add_test(NAME IOTest COMMAND ${EXE_NAME} ${TEST_DATA_DIR} ${TEST_SEED} --gtest_filter=OPERATIONS_TEST.*)
add_test(NAME ManageTest COMMAND ${EXE_NAME} ${TEST_DATA_DIR} ${TEST_SEED} --gtest_filter=MANAGEMENT_TEST.*)
