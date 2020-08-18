 cmake_minimum_required(VERSION 2.8.1)
 project(agenda)

 include(build/conanbuildinfo.cmake)
 conan_basic_setup()

 add_executable(agenda main.cpp)
 target_link_libraries(agenda ${CONAN_LIBS})
