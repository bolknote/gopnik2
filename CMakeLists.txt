cmake_minimum_required(VERSION 3.12)

project(gop2)

file(GLOB SRC_FILES CONFIGURE_DEPENDS 
    "*.h"
    "*.cpp"
    "comm/*.h"
    "comm/*.cpp"
    "pltl/*.h"
    "pltl/*.cpp"
)

add_executable(gop2 ${SRC_FILES})
