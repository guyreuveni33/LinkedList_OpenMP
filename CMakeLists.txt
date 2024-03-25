cmake_minimum_required(VERSION 3.23)
project(ex3_newParallel C)

set(CMAKE_C_STANDARD 99)

# Find the OpenMP package
find_package(OpenMP REQUIRED)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address -fno-omit-frame-pointer -g")
set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} -fsanitize=address")

# Add executable
add_executable(ex3_newParallel main.c linkedList.c)

# Link your executable with OpenMP
if(OpenMP_C_FOUND)
    target_link_libraries(ex3_newParallel PUBLIC OpenMP::OpenMP_C)
endif()
