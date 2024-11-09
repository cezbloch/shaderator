add_executable(basic_direct_compute_11_tests
    basic_compute_executor.cpp
    basic_compute_tests.cpp
)

target_link_libraries(basic_direct_compute_11_tests Shaderator pthread gtest_main)

add_test(NAME basic_direct_compute_11_tests COMMAND basic_direct_compute_11_tests)