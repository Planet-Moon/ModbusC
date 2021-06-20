cmake_minimum_required(VERSION 3.20)

set(CMAKE_TOOLCHAIN_FILE "E:/Users/Andreas/Andreas/Private Elektronik/Cpp/vcpkg/scripts/buildsystems/vcpkg.cmake")

project(main)

add_library(
    hello
    hello.h
    hello.cpp
)

add_library(
    ModbusConversions
    Conversions.h
    Conversions.cpp
)

add_library(
    ModbusDevice
    ModbusDataTypes.h
    ModbusDevice.h
    ModbusDevice.cpp
)

add_library(
    ModbusRegister
    ModbusDataTypes.h
    ModbusRegister.h
    ModbusRegister.cpp
)

add_library(
    SMADevice
    SMADevice.h
    SMADevice.cpp
)

find_package(libmodbus CONFIG REQUIRED)

target_link_libraries(ModbusDevice PUBLIC modbus)
target_link_libraries(ModbusDevice PUBLIC ModbusRegister)

target_link_libraries(ModbusRegister PUBLIC modbus)
target_link_libraries(ModbusRegister PRIVATE ModbusConversions)

target_link_libraries(SMADevice PUBLIC ModbusDevice)

add_executable(main main.cpp)

target_link_libraries(main PRIVATE hello)
target_link_libraries(main PRIVATE ModbusDevice)
target_link_libraries(main PRIVATE SMADevice)

