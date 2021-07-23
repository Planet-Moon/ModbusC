cmake_minimum_required(VERSION 3.20)

set(CMAKE_TOOLCHAIN_FILE "E:/Users/Andreas/Andreas/Private Elektronik/Cpp/vcpkg/scripts/buildsystems/vcpkg.cmake")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

project(main)

add_library(
    hello
    hello/hello.h
    hello/hello.cpp
)

add_library(
    ModbusConversions
    Conversions/Conversions.h
    Conversions/Conversions.cpp
)

add_library(
    ModbusDevice
    
    ModbusDevice/ModbusDevice.h
    ModbusDevice/ModbusDevice.cpp
)

add_library(
    ModbusRegister
    
    ModbusRegister/ModbusRegister.h
    ModbusRegister/ModbusRegister.cpp
)

add_library(
    SMADevice
    SMA/SMADevice.h
    SMA/SMADevice.cpp
)

add_library(
    SMAStorageBoy
    SMA/SMAStorageBoy.h
    SMA/SMAStorageBoy.cpp
)

find_package(libmodbus CONFIG REQUIRED)

target_link_libraries(ModbusDevice PUBLIC modbus)

target_link_libraries(ModbusRegister PUBLIC modbus)
target_link_libraries(ModbusRegister PUBLIC ModbusDevice)
target_link_libraries(ModbusRegister PRIVATE ModbusConversions)

target_link_libraries(SMADevice PUBLIC ModbusDevice)
target_link_libraries(SMADevice PUBLIC ModbusRegister)

target_link_libraries(SMAStorageBoy PUBLIC SMADevice)

add_executable(main main.cpp)

target_link_libraries(main PRIVATE hello)
target_link_libraries(main PRIVATE ModbusDevice)
target_link_libraries(main PRIVATE ModbusRegister)
target_link_libraries(main PRIVATE SMADevice)
target_link_libraries(main PRIVATE SMAStorageBoy)

add_subdirectory(TemplateTests)
