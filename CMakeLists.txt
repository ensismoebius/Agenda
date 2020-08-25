cmake_minimum_required(VERSION 2.8.1)

project(Agenda)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -std=c++14")
set (build_dir "${PROJECT_SOURCE_DIR}/build")
set (source_dir "${PROJECT_SOURCE_DIR}/src")

file (GLOB source_files "${source_dir}/*.cpp")

include(./conanbuildinfo.cmake)
conan_basic_setup()

add_executable(agenda ${source_files})
target_link_libraries(agenda ${CONAN_LIBS})
