cmake_minimum_required(VERSION 3.20)

set(VCPKG_TARGET_TRIPLET x64-windows)
# set(VCPKG_TARGET_TRIPLET x64-windows-static)

set(CMAKE_TOOLCHAIN_FILE "E:/vcpkg/scripts/buildsystems/vcpkg.cmake")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)

project(main)

add_definitions(-DDEBUG=1)

add_library(
    hello
    hello/hello.h
    hello/hello.cpp
)
target_include_directories(hello PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/hello)

add_subdirectory(modbus)

add_subdirectory(SMA)

add_subdirectory(Mqtt)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE hello)
target_link_libraries(main PRIVATE SMADevice)
target_link_libraries(main PRIVATE SMADeviceMqtt)
target_link_libraries(main PRIVATE SMAMainsMqtt)
target_link_libraries(main PRIVATE SMAStorageBoy)
target_link_libraries(main PRIVATE SMAStorageBoyMqtt)
target_link_libraries(main PRIVATE mqtt)

add_subdirectory(TemplateTests)

add_subdirectory(thread_test)
