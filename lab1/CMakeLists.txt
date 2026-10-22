cmake_minimum_required(VERSION 3.20)

project(lab1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE LAB1_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

if(NOT LAB1_SOURCES)
    message(FATAL_ERROR "No source files found in src/")
endif()

add_executable(lab1 ${LAB1_SOURCES})

target_include_directories(lab1 PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/multiset"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/postMachine"
)

file(GLOB_RECURSE LAB1_INCLUDE_DIRS
    LIST_DIRECTORIES true
    "${CMAKE_CURRENT_SOURCE_DIR}/include/*"
)

set(LAB1_INCLUDE_PATHS
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

foreach(dir IN LISTS LAB1_INCLUDE_DIRS)
    if(IS_DIRECTORY "${dir}")
        list(APPEND LAB1_INCLUDE_PATHS "${dir}")
    endif()
endforeach()

list(REMOVE_DUPLICATES LAB1_INCLUDE_PATHS)

target_include_directories(lab1 PRIVATE
    ${LAB1_INCLUDE_PATHS}
)

if(MSVC)
    target_compile_options(lab1 PRIVATE /W4)
else()
    target_compile_options(lab1 PRIVATE
        -Wall
        -Wextra
        -Wpedantic
    )
endif()

find_program(DOXYGEN_EXECUTABLE NAMES doxygen)

if(DOXYGEN_EXECUTABLE)
    add_custom_target(docs
        COMMAND "${DOXYGEN_EXECUTABLE}" "${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile"
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
        COMMENT "Generating Doxygen documentation"
        VERBATIM
    )
endif()