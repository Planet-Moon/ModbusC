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

add_library(
    ModbusConversions
    Conversions/Conversions.h
    Conversions/Conversions.cpp
)
target_include_directories(ModbusConversions PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Conversions)

add_library(
    ModbusDevice
    modbus/ModbusDevice.h
    modbus/ModbusDevice.cpp
    modbus/ModbusRegister.h
    modbus/ModbusRegister.cpp
)
target_include_directories(ModbusDevice PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/modbus)
find_package(libmodbus CONFIG REQUIRED)
target_link_libraries(ModbusDevice PUBLIC modbus)
target_link_libraries(ModbusDevice PUBLIC ModbusConversions)

add_library(
    SMADevice
    SMA/SMADevice.h
    SMA/SMADevice.cpp
)
target_link_libraries(SMADevice PUBLIC ModbusDevice)
target_include_directories(SMADevice PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/SMA)

add_library(
    SMAStorageBoy
    SMA/SMAStorageBoy.h
    SMA/SMAStorageBoy.cpp
)
target_link_libraries(SMAStorageBoy PUBLIC SMADevice)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE hello)
target_link_libraries(main PRIVATE SMADevice)
target_link_libraries(main PRIVATE SMAStorageBoy)

add_subdirectory(TemplateTests)
