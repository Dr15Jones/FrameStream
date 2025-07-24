# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Set the project name
project(HeteroContainer)

add_library(HeteroContainer INTERFACE)
target_include_directories(
  HeteroContainer
  INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
            $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)
