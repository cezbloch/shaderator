add_executable(opencl_intel_bitonic_sort_tests
    intel_bitonic_sort_executor.cpp
    intel_bitonic_sort_tests.cpp
)

target_link_libraries(opencl_intel_bitonic_sort_tests Shaderator gtest_main)

set_source_files_properties(BitonicSort.cl PROPERTIES HEADER_FILE_ONLY TRUE)

target_sources(opencl_intel_bitonic_sort_tests
  PRIVATE
    #${CMAKE_CURRENT_LIST_DIR}/../IntelBitonicSort/BitonicSort/BitonicSort.cl
    BitonicSort.cl
    intel_bitonic_sort_executor.h
  )

add_test(NAME opencl_intel_bitonic_sort_tests COMMAND opencl_intel_bitonic_sort_tests)