cmake_minimum_required(VERSION 3.12)
project(gopnik2_test)

include(FetchContent)
FetchContent_Declare(googletest URL https://github.com/google/googletest/archive/refs/tags/v1.13.0.zip)
FetchContent_MakeAvailable(googletest)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

enable_testing()

add_executable(
    gopnik2_test
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/game.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/hero.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/list.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/utils.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/comm/r.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/comm/_clsc.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/comm/sav.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/comm/sstay.cpp
    r_check.cpp
)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    # using GCC
    target_compile_options(gopnik2_test PRIVATE -g)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    # using Visual Studio C++
    target_compile_options(gopnik2_test PRIVATE /MT)
endif()

target_link_libraries(
    gopnik2_test
    PRIVATE 
    fmt::fmt
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(gopnik2_test)

add_custom_command(TARGET gopnik2_test POST_BUILD COMMAND gopnik2_test)
