cmake_minimum_required(VERSION 3.12)
project(gop2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wpedantic -Wextra -Os -funsigned-char")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /Os /J")
endif()

if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
    file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/0.18.1/conan.cmake"
            "${CMAKE_BINARY_DIR}/conan.cmake"
            TLS_VERIFY ON)
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

conan_cmake_autodetect(settings CPPSTD 17)

conan_cmake_configure(REQUIRES fmt/9.1.0
        GENERATORS cmake_find_package
        REQUIRES catch2/3.3.2
        GENERATORS cmake_find_package)

conan_cmake_install(PATH_OR_REFERENCE .
        BUILD missing
        REMOTE conancenter
        SETTINGS ${settings})

set(CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR} ${CMAKE_MODULE_PATH})
set(CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR} ${CMAKE_PREFIX_PATH})

find_package(fmt REQUIRED)

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

set(SOURCE ${SOURCE_FILES})

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/src/include
)

add_executable(gop2 ${SOURCE})
target_link_libraries(gop2 PRIVATE fmt::fmt)

file(GLOB_RECURSE TESTS_SOURCE_FILES CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp)
set(TESTS_SOURCE ${TESTS_SOURCE_FILES})

find_package(Catch2 REQUIRED)
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
