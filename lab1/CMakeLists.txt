cmake_minimum_required(VERSION 3.20)

project(main LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(ENABLE_COVERAGE "Enable code coverage" OFF)

if(ENABLE_COVERAGE)
    message(STATUS "Coverage is enabled")
    add_compile_options(--coverage -O0 -g)
    add_link_options(--coverage)
endif()

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

set(APP_ENTRY_POINT
    "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp"
)

if(NOT EXISTS "${APP_ENTRY_POINT}")
    message(FATAL_ERROR "src/main.cpp not found")
endif()

file(GLOB_RECURSE LIB_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

list(REMOVE_ITEM LIB_SOURCES "${APP_ENTRY_POINT}")

if(NOT LIB_SOURCES)
    message(FATAL_ERROR "No library sources found in src/")
endif()

add_library(Tests ${LIB_SOURCES})

target_include_directories(Tests PUBLIC
    ${MAIN_INCLUDE_PATHS}
)

# Main application
add_executable(main ${APP_ENTRY_POINT})

target_link_libraries(main PRIVATE Tests)

# UnitTest++
include(FetchContent)

set(UTPP_INCLUDE_TESTS_IN_BUILD OFF CACHE BOOL "" FORCE)
set(UTPP_AMPLIFY_WARNINGS OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    unittestpp
    GIT_REPOSITORY https://github.com/unittest-cpp/unittest-cpp.git
    GIT_TAG v2.0.0
)

FetchContent_MakeAvailable(unittestpp)

# Test sources
file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp"
)

if(TEST_SOURCES)
    add_executable(test ${TEST_SOURCES})

    target_link_libraries(test PRIVATE
        Tests
        UnitTest++
    )

    target_include_directories(test PRIVATE
        "${unittestpp_SOURCE_DIR}"
    )
else()
    message(STATUS "No test sources found")
endif()

# Doxygen
find_program(DOXYGEN_EXECUTABLE NAMES doxygen)

if(DOXYGEN_EXECUTABLE)
    add_custom_target(docs
        COMMAND "${DOXYGEN_EXECUTABLE}" "${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile"
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
        COMMENT "Generating Doxygen documentation"
        VERBATIM
    )
endif()
