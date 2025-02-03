cmake_minimum_required(VERSION 3.22.1)
project(TESTE)

add_compile_options(-Wall -Werror)

set(LIBRARY_DIR "${CMAKE_SOURCE_DIR}/libs")
include_directories(${LIBRARY_DIR})

# Add your executable or library target
add_executable(
    TestFiles 
    tests/tests.c
    src/Files.c
)

# Specify the directory where the shared library is located
target_link_directories(TestFiles PRIVATE ${LIBRARY_DIR})

# Link the shared library to your executable
target_link_libraries(TestFiles PRIVATE Strings LinkedList)

# export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:${CMAKE_SOURCE_DIR}/libs
