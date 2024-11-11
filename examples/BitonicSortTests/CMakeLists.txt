add_executable(bitonic_sort_tests
    bitonic_sort_tests.cpp
)

target_link_libraries(bitonic_sort_tests Shaderator BitonicSort gtest_main)

add_test(NAME bitonic_sort_tests COMMAND bitonic_sort_tests)