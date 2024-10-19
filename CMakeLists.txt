cmake_minimum_required(VERSION 3.5)
project(WindowsActivator)

add_executable(WindowsActivator WIN32 WindowsActivate.cpp)

set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
set(BUILD_SHARED_LIBRARIES OFF)
set(CMAKE_EXE_LINKER_FLAGS "-static")
