cmake_minimum_required(VERSION 3.20)

set(CMAKE_TOOLCHAIN_FILE "E:/vcpkg/scripts/buildsystems/vcpkg.cmake")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

project(ObserverModel)

add_library(ObserverModel
    Observer.h
    Observer.cpp
    Subject.h
    Subject.cpp
)
target_include_directories(ObserverModel PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(TestObserver TestObserver.cpp)
target_link_libraries(TestObserver ObserverModel)
