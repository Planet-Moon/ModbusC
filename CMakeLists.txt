cmake_minimum_required(VERSION 3.20)

set(CMAKE_TOOLCHAIN_FILE "E:/Users/Andreas/Andreas/Private Elektronik/Cpp/vcpkg/scripts/buildsystems/vcpkg.cmake")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

project(main)

add_library(
    hello
    hello/hello.h
    hello/hello.cpp
)
target_include_directories(hello PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/hello)

add_subdirectory(modbus)

add_subdirectory(SMA)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE hello)
target_link_libraries(main PRIVATE SMADevice)
target_link_libraries(main PRIVATE SMAStorageBoy)

add_subdirectory(TemplateTests)
