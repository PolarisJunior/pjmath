cmake_minimum_required(VERSION 3.15.2)

# Change `MY_PROJECT_NAME` to the name of your project
project(pjmath)

set(LIB_NAME ${PROJECT_NAME})
set(BIN_NAME ${PROJECT_NAME}bin)
# Name of the output binary executable.
# We have this separate so we can have the executable and library have the same name
set(BIN_OUTPUT_NAME ${PROJECT_NAME})

set(ALL_TARGETS ${LIB_NAME} ${BIN_NAME})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

set(SRC_DIR src)

find_package(GTest QUIET)
option(TEST_ENABLED "" ${GTEST_FOUND})

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_compile_options(-Wall -Wextra)

add_library(
    ${LIB_NAME}
    # Path to the project's source files go here
    src/pjmath/math_funcs.cpp
)

target_include_directories(
    ${LIB_NAME}
    PUBLIC
    include
)

target_link_libraries(
    ${LIB_NAME}
    PRIVATE
    Threads::Threads
)

add_executable(
    ${BIN_NAME}
    # Path to the cpp file containing your main function
    ${SRC_DIR}/main.cpp
)

target_link_libraries(
    ${BIN_NAME}
    PRIVATE
    ${LIB_NAME}
)

set_target_properties(
    ${BIN_NAME}
    PROPERTIES
    OUTPUT_NAME ${BIN_OUTPUT_NAME}
)

foreach(TARGET_NAME ${ALL_TARGETS})
    target_compile_options(
        ${TARGET_NAME}
        PRIVATE
        $<$<COMPILE_LANGUAGE:CXX>:-Weffc++>
    )
    target_compile_features(
        ${TARGET_NAME}
        PRIVATE
        cxx_std_17
    )
endforeach()

if (${TEST_ENABLED})
    enable_testing()
    add_subdirectory(test)
endif()
