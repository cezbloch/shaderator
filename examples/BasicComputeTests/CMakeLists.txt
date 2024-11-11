add_executable(basic_direct_compute_11_tests
    basic_compute_executor.cpp
    basic_compute_tests.cpp
)

target_link_libraries(basic_direct_compute_11_tests Shaderator gtest_main)

set_source_files_properties(basic_compute_structured_buffer.hlsl PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties(basic_compute_byte_address_buffer.hlsl PROPERTIES HEADER_FILE_ONLY TRUE)

target_sources(basic_direct_compute_11_tests
  PRIVATE
    basic_compute_executor.h
    basic_compute_byte_address_buffer.hlsl
    basic_compute_structured_buffer.hlsl
    shared_types.h
  )

add_test(NAME basic_direct_compute_11_tests COMMAND basic_direct_compute_11_tests)