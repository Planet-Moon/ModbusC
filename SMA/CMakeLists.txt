cmake_minimum_required(VERSION 3.20)

set(CMAKE_TOOLCHAIN_FILE "E:/vcpkg/scripts/buildsystems/vcpkg.cmake")

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

add_library(
    SMAMqttInterface
    SMAMqttInterface.h
    SMAMqttInterface.cpp
)
target_link_libraries(SMAMqttInterface PUBLIC mqtt)
target_link_libraries(SMAMqttInterface PUBLIC ObserverModel)

add_library(
    SMADeviceMqtt
    SMADeviceMqtt.h
    SMADeviceMqtt.cpp
)
target_link_libraries(SMADeviceMqtt PUBLIC SMADevice)
target_link_libraries(SMADeviceMqtt PUBLIC SMAMqttInterface)

add_library(
    SMAMainsMqtt
    SMAMainsMqtt.h
    SMAMainsMqtt.cpp
)
target_link_libraries(SMAMainsMqtt PUBLIC SMADevice)
target_link_libraries(SMAMainsMqtt PUBLIC SMAMqttInterface)

add_library(
    SMAStorageBoyMqtt
    SMAStorageBoyMqtt.h
    SMAStorageBoyMqtt.cpp
)
target_link_libraries(SMAStorageBoyMqtt PUBLIC SMAStorageBoy)
target_link_libraries(SMAStorageBoyMqtt PUBLIC SMAMqttInterface)

add_library(SMAMqtt INTERFACE)
target_link_libraries(SMAMqtt INTERFACE SMADeviceMqtt SMAMainsMqtt SMAStorageBoyMqtt)

add_library(
    SMAModbusRelayInterface
    SMAModbusRelayInterface.h
    SMAModbusRelayInterface.cpp
)
target_link_libraries(SMAModbusRelayInterface PUBLIC ObserverModel)
target_link_libraries(SMAModbusRelayInterface PUBLIC ModbusDevice)

add_library(
    SMAModbusRelayDevice
    SMAModbusRelayDevice.h
    SMAModbusRelayDevice.cpp
)
target_link_libraries(SMAModbusRelayDevice PUBLIC SMAModbusRelayInterface)
target_link_libraries(SMAModbusRelayDevice PUBLIC SMADevice)

add_library(
    SMAModbusRelayMains
    SMAModbusRelayMains.h
    SMAModbusRelayMains.cpp
)
target_link_libraries(SMAModbusRelayMains PUBLIC SMAModbusRelayInterface)
target_link_libraries(SMAModbusRelayMains PUBLIC SMADevice)

add_library(
    SMAModbusRelayStorageBoy
    SMAModbusRelayStorageBoy.h
    SMAModbusRelayStorageBoy.cpp
)
target_link_libraries(SMAModbusRelayStorageBoy PUBLIC SMAModbusRelayInterface)
target_link_libraries(SMAModbusRelayStorageBoy PUBLIC SMAStorageBoy)

add_library(SMAModbusRelay INTERFACE)
target_link_libraries(SMAModbusRelay INTERFACE SMAModbusRelayDevice SMAModbusRelayMains SMAModbusRelayStorageBoy)

add_library(SMALIB INTERFACE)
target_link_libraries(SMALIB INTERFACE SMAMqtt SMAModbusRelay)
