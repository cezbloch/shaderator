add_library(BitonicSort "")

set_source_files_properties(ComputeShaderSort11.hlsl PROPERTIES HEADER_FILE_ONLY TRUE)

target_sources(BitonicSort
  PRIVATE
    bitonic_sort_executor.cpp
    ComputeShaderSort11.hlsl
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/bitonic_sort_executor.h
  )

target_include_directories(BitonicSort
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
  )

target_link_libraries(BitonicSort Shaderator)
