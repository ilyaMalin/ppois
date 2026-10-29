cmake_minimum_required(VERSION 3.20)

project(main LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE MAIN_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

if(NOT MAIN_SOURCES)
    message(FATAL_ERROR "No source files found in src/")
endif()

add_executable(main ${MAIN_SOURCES})

file(GLOB_RECURSE MAIN_INCLUDE_DIRS
    LIST_DIRECTORIES true
    "${CMAKE_CURRENT_SOURCE_DIR}/include/*"
)

set(MAIN_INCLUDE_PATHS
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

foreach(dir IN LISTS MAIN_INCLUDE_DIRS)
    if(IS_DIRECTORY "${dir}")
        list(APPEND MAIN_INCLUDE_PATHS "${dir}")
    endif()
endforeach()

list(REMOVE_DUPLICATES MAIN_INCLUDE_PATHS)

target_include_directories(main PRIVATE
    ${MAIN_INCLUDE_PATHS}
)

find_program(DOXYGEN_EXECUTABLE NAMES doxygen)

if(DOXYGEN_EXECUTABLE)
    add_custom_target(docs
        COMMAND "${DOXYGEN_EXECUTABLE}" "${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile"
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
        COMMENT "Generating Doxygen documentation"
        VERBATIM
    )
endif()