@echo off

conan profile new default --detect
conan install .. -s build_type=Debug 
REM conan install .. -s build_type=Release
