cmake_minimum_required(VERSION 3.14)
project(gop2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wpedantic -Wextra -Os -funsigned-char")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /Os /J")
endif()

include(FetchContent)

# Fetch fmt library
FetchContent_Declare(
    fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG 9.1.0
)
FetchContent_MakeAvailable(fmt)

# Fetch Catch2 library
FetchContent_Declare(
    catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.3.2
)
FetchContent_MakeAvailable(catch2)

# Main executable
file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/src/include
)

add_executable(gop2 ${SOURCE_FILES})
target_link_libraries(gop2 PRIVATE fmt::fmt)

# Tests executable
file(GLOB_RECURSE TESTS_SOURCE_FILES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp
)
set(TESTS_SOURCE ${TESTS_SOURCE_FILES})

add_executable(gop2_tests
    ${CMAKE_CURRENT_SOURCE_DIR}/src/game.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/hero.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/list.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/utils.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/comm/r.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/comm/_clsc.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/comm/sav.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/comm/sstay.cpp
    ${TESTS_SOURCE})
target_link_libraries(gop2_tests PRIVATE fmt::fmt Catch2::Catch2WithMain)

include(CTest)
include(Catch)
catch_discover_tests(gop2_tests)
