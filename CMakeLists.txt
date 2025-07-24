cmake_minimum_required(VERSION 3.10)
project(FrameStream VERSION 1.0 LANGUAGES CXX C)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} 
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

  # Actually search for the library
find_package(Readline)


add_subdirectory(src)
