cmake_minimum_required(VERSION 3.20)

set(VCPKG_TARGET_TRIPLET x64-windows)
# set(VCPKG_TARGET_TRIPLET x64-windows-static)

set(CMAKE_TOOLCHAIN_FILE "E:/vcpkg/scripts/buildsystems/vcpkg.cmake")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)

project(main)

add_library(
    hello
    hello/hello.h
    hello/hello.cpp
)
target_include_directories(hello PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/hello)

add_subdirectory(modbus)

add_subdirectory(SMA)

add_subdirectory(Mqtt)

add_subdirectory(ObserverModel)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE hello)
target_link_libraries(main PRIVATE SMALIB)

add_subdirectory(TemplateTests)

add_subdirectory(thread_test)

find_package(Doxygen
    REQUIRED dot
    OPTIONAL_COMPONENTS mscgen dia
)
set(DOXYGEN_EXTRACT_PRIVATE TRUE)
set(DOXYGEN_WARN_IF_UNDOCUMENTED FALSE)
set(DOXYGEN_OPTIMIZE_OUTPUT_FOR_C TRUE)
set(DOXYGEN_EXCLUDE_PATTERNS */build/*)

doxygen_add_docs(doxygen_target
    ${CMAKE_SOURCE_DIR}
    ALL
    COMMENT "Run doxygen_target"
)
