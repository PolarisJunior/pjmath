# Add executables by specifying the name of the test without the .cpp extension
set(
    ALL_TESTS 
    vector3_tests
    mat_tests
)

function(add_test_binary TEST_NAME)
    set(TEST_TARGET ${TEST_NAME})

    add_executable(
        ${TEST_TARGET}
        ${TEST_NAME}.cpp
    )

    target_compile_features(
        ${TEST_TARGET}
        PRIVATE
        cxx_std_17
    )

    target_link_libraries(
        ${TEST_TARGET}
        GTest::GTest
        ${LIB_NAME}
    )

    gtest_add_tests(
        TARGET
        ${TEST_TARGET}
    )
endfunction(add_test_binary)

foreach(TEST_NAME ${ALL_TESTS})
    add_test_binary(${TEST_NAME})
endforeach()