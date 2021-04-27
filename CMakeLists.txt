cmake_minimum_required(VERSION 3.0.0)

cmake_policy(SET CMP0015 NEW)

set(PROJECT_NAME dxFeedCAPISample)
project(${PROJECT_NAME} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)

set(TARGET_PLATFORM "x64" CACHE STRING "Target platform specification")
set(DISABLE_TLS on CACHE BOOL "Build without the TLS support")

if("${CMAKE_SIZEOF_VOID_P}" STREQUAL "4")
  set(TARGET_PLATFORM "x86")
endif()

set(LIB_C_API dxfeed-c-api)
set(LIB_C_API_PROJ DXFeed)

include_directories(${LIB_C_API}/include)

add_executable(${PROJECT_NAME}
    src/main.cpp
)

add_subdirectory(${LIB_C_API})
add_dependencies(${PROJECT_NAME} ${LIB_C_API_PROJ})

target_link_libraries(${PROJECT_NAME} ${LIB_C_API_PROJ})
