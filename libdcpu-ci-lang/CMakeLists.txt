cmake_minimum_required (VERSION 2.6)
project(libdcpu-ci-lang)

# Check to ensure that we are running as part of the
# root CMakeLists.txt file.
if(NOT DEFINED IS_ROOT)
  message(FATAL_ERROR "You must generate the CMake files as part of the root directory.")
endif(NOT DEFINED IS_ROOT)

# Define the libdcc project.
dt_project(library nodes)
