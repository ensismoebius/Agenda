#!/bin/bash
conan profile new default --detect
conan profile update settings.compiler.libcxx=libstdc++11 default
conan install ..
cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug
#cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
cmake --build .
