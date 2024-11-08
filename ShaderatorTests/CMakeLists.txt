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

add_executable(cpp_test thread_pool_tests.cpp)
#target_link_libraries(cpp_test Shaderator)
# Link the Shaderator library and pthread and Gtest
target_link_libraries(cpp_test Shaderator pthread)
#target_link_libraries(cpp_test gtest gtest_main)
target_link_libraries(cpp_test gtest_main)

# Include GoogleTest headers
include_directories(${CMAKE_SOURCE_DIR}/external)

add_test(NAME example_test COMMAND cpp_test)
# add_test(
#   NAME
#     test_shaderator
#   COMMAND
#     $<TARGET_FILE:cpp_test>
#   )