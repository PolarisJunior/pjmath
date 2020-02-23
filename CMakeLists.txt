cmake_minimum_required(VERSION 3.10.0)
project(pjmath)

include(GoogleTest)

set(CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED True)

set(VECTOR3_TEST vector3_tests)

add_compile_options(-Wall -Wextra -pedantic)

add_executable(${VECTOR3_TEST} test/vector3_tests.cpp)
set_property(TARGET ${VECTOR3_TEST} PROPERTY CXX_STANDARD 17)

add_subdirectory(googletest)

target_link_libraries(${VECTOR3_TEST} gtest)
target_include_directories(${VECTOR3_TEST} PUBLIC include googletest/googletest/include)
