cmake_minimum_required(VERSION 3.27)

project(RayTracingInOneWeekend)

set(CMAKE_CXX_STANDARD 17)

file(GLOB RENDERCORE_SOURCES ${CMAKE_SOURCE_DIR}/src/*.h )

add_executable(raytracing ${CMAKE_SOURCE_DIR}/main.cpp ${RENDERCORE_SOURCES})

# add header folder
target_include_directories(raytracing PRIVATE ${CMAKE_SOURCE_DIR}/src)
