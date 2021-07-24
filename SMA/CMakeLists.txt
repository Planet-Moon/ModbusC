cmake_minimum_required(VERSION 3.20)

set(CMAKE_TOOLCHAIN_FILE "E:/Users/Andreas/Andreas/Private Elektronik/Cpp/vcpkg/scripts/buildsystems/vcpkg.cmake")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

project(sma)

add_library(
    SMADevice
    SMADevice.h
    SMADevice.cpp
)
target_link_libraries(SMADevice PUBLIC ModbusDevice)
target_include_directories(SMADevice PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_library(
    SMAStorageBoy
    SMAStorageBoy.h
    SMAStorageBoy.cpp
)
target_link_libraries(SMAStorageBoy PUBLIC SMADevice)
