cmake_minimum_required(VERSION 2.8)
project(cminus)
# Search all the .cpp files in the directory where CMakeLists lies and set them to ${SOURCE_FILES}.
# Search all the .h files in the directory where CMakeLists lies and set them to ${INCLUDE_FILES}.
file(GLOB SOURCE_FILES *.cpp)
# Add the executable Example to be built from the source files
add_executable(cminus ${SOURCE_FILES})
# Link the executable to the libraries