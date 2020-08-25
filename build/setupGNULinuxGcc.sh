#!/bin/bash

###############
### Options ###
###############

#####################
## Choose your IDE ##
#####################

#ide="Unix Makefiles"
#ide="Green Hills MULTI"
#ide="Ninja"
#ide="Watcom WMake"
#ide="CodeBlocks - Ninja"
#ide="CodeBlocks - Unix Makefiles"
#ide="CodeLite - Ninja"
#ide="CodeLite - Unix Makefiles"
#ide="Sublime Text 2 - Ninja"
#ide="Sublime Text 2 - Unix Makefiles"
#ide="Kate - Ninja"
#ide="Kate - Unix Makefiles"
#ide="Eclipse CDT4 - Ninja"
ide="Eclipse CDT4 - Unix Makefiles"

############################
## Release or Debug mode? ##
############################
dr="Debug"
#dr="Release"

###############################################
### Running the build and dependency solver ###
###############################################

##############################
## Running depedency solver ##
##############################

conan profile new default --detect
conan profile update settings.compiler.libcxx=libstdc++11 default
conan install .

#######################
## Building software ##
#######################
cmake . -G "$ide" -DCMAKE_BUILD_TYPE=$dr
cmake --build . 
