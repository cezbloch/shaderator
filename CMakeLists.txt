cmake_minimum_required(VERSION 3.10)
project(Shaderator)
#project(recipe-07 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include(GNUInstallDirs)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY
  ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY
  ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
  ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})


# defines targets and sources
add_subdirectory(Shaderator)

# Include directories for Shaderator
target_include_directories(Shaderator
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/glm
)

# contains an "external" library we will link to
add_subdirectory(external) # this does not work yet

# Add an option to build tests
option(BUILD_TESTS "Build Shaderator tests" ON)
# enable testing and define tests
# if(BUILD_TESTS)
#     enable_testing()
#     add_subdirectory(ShaderatorTests)
# endif()

enable_testing()
add_subdirectory(ShaderatorTests)
