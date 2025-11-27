cmake_minimum_required(VERSION 3.16)

project(Batalha_de_Laponia
    VERSION 1.0
    LANGUAGES CXX
)

# Require a modern C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Put all compiler output in /build/bin and /build/obj for cleanliness
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Collect source files
file(GLOB_RECURSE SOURCES
    src/*.cpp
    src/*.c
    src/*.h
    src/*.hpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME}
    sfml-system
    sfml-window
    sfml-graphics
)