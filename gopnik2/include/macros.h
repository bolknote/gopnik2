#pragma once

#ifdef _MSC_VER
#  define PACKED_STRUCT(ALIGN_SIZE, NAME) __pragma(pack(push, 1)) __declspec(align(ALIGN_SIZE)) struct NAME __pragma(pack(pop))
#elif defined(__GNUC__)
#  define PACKED_STRUCT(ALIGN_SIZE, NAME) struct __attribute__((__packed__, aligned(ALIGN_SIZE))) NAME
#endif
