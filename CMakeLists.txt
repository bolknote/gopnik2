cmake_minimum_required(VERSION 3.12)
project(gop2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB SRC_FILES CONFIGURE_DEPENDS 
    "*.h"
    "*.cpp"
    "comm/*.h"
    "comm/*.cpp"
    "pltl/*.h"
    "pltl/*.cpp"
)

add_subdirectory(fmt)

include_directories("fmt/include")

add_executable(gop2 ${SRC_FILES})
target_link_libraries(gop2 PRIVATE fmt::fmt)
