@echo off

conan profile new default --detect
conan profile update settings.compiler.libcxx=libstdc++11 default
conan install ..
cmake .. -G "Visual Studio 16"
REM cmake --build . --config Release
cmake --build . --config Debug
