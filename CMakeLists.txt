cmake_minimum_required(VERSION 2.8)
project(cminus)
file(GLOB CPP_SOURCE_FILES src/*.cpp)
file(GLOB C_SOURCE_FILES src/*.c)
add_executable(cminus ${CPP_SOURCE_FILES} ${C_SOURCE_FILES})
target_include_directories(cminus
    PUBLIC 
        ${PROJECT_SOURCE_DIR}/include
)
