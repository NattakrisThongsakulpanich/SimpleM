cmake_minimum_required(VERSION 3.22)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(SimpleMath LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)  
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRC 
    "main.cpp"
)

add_executable(test
    ${SRC}
)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_compile_options(test PRIVATE -O3 -mavx2 -fopt-info-vec-optimized)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(test PRIVATE /O2 /arch:AVX2)
else()
    target_compile_options(test PRIVATE -O3)
endif()
