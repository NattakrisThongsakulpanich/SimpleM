cmake_minimum_required(VERSION 3.22)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")

project(SimpleMath)

set(CMAKE_CXX_STANDARD 20)  
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRC 
    test/main.cpp
)

add_executable(test
    ${SRC}
)

# Add -ffast-math to unlock Fused Multiply-Add (FMA)
target_compile_options(test PRIVATE -O3 -mavx2 -fopt-info-vec-optimized)

