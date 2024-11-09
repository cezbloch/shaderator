add_library(BitonicSort "")

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
