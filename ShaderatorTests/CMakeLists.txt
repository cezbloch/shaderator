# Download GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# ----------------------------------------
# Define the ShaderatorTests executable

add_executable(shaderator_tests 
    access_counting_container_tests.cpp
    barrier_tests.cpp
    hlsl_syntax_tests.cpp
    thread_pool_tests.cpp
    threadsafe_queue_tests.cpp
)

target_link_libraries(shaderator_tests Shaderator gtest_main)

add_test(NAME shaderator_tests COMMAND shaderator_tests)
