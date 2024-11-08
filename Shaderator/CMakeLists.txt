add_library(Shaderator "")

target_sources(Shaderator
  PRIVATE
    cpp_functions.cpp
    Engine.cpp
    CpuTimeMeasurement.cpp
    opencl_support.cpp
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/access_counting_container.h
    ${CMAKE_CURRENT_LIST_DIR}/Barrier.h
    ${CMAKE_CURRENT_LIST_DIR}/cpp_include.h
    ${CMAKE_CURRENT_LIST_DIR}/element.h
    ${CMAKE_CURRENT_LIST_DIR}/Engine.h
    ${CMAKE_CURRENT_LIST_DIR}/CpuTimeMeasurement.h
    ${CMAKE_CURRENT_LIST_DIR}/glsl_include.h
    ${CMAKE_CURRENT_LIST_DIR}/hlsl_include.h
    ${CMAKE_CURRENT_LIST_DIR}/OpenCLEngine.h
    ${CMAKE_CURRENT_LIST_DIR}/opencl_support.h
    ${CMAKE_CURRENT_LIST_DIR}/opencl_types.h
    ${CMAKE_CURRENT_LIST_DIR}/thread_joiner.h
    ${CMAKE_CURRENT_LIST_DIR}/shaderator.h
    ${CMAKE_CURRENT_LIST_DIR}/shader_types.h
    ${CMAKE_CURRENT_LIST_DIR}/texture_2d.h
    ${CMAKE_CURRENT_LIST_DIR}/thread_pool.h
    ${CMAKE_CURRENT_LIST_DIR}/threadsafe_queue.h

  )

target_include_directories(Shaderator
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
  )