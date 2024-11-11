add_executable(glsl_shaders_tests
    ray_tracer_tests.cpp
)

target_link_libraries(glsl_shaders_tests Shaderator gtest_main)

set_source_files_properties(ray_tracer.glsl PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties(sample_shader.glsl PROPERTIES HEADER_FILE_ONLY TRUE)

target_sources(glsl_shaders_tests
  PRIVATE
    ray_tracer.glsl
    sample_shader.glsl
  )

add_test(NAME glsl_shaders_tests COMMAND glsl_shaders_tests)