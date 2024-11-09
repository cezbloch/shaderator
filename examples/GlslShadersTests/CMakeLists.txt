add_executable(glsl_shaders_tests
    ray_tracer_tests.cpp
)

target_link_libraries(glsl_shaders_tests Shaderator gtest_main)

add_test(NAME glsl_shaders_tests COMMAND glsl_shaders_tests)