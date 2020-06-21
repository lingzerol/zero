#ifndef ZERONET_COMMON_H
#define ZERONET_COMMON_H
#include <iostream>


#define _ZERONET_BEGIN namespace zeronet{
#define _ZERONET_END }
#define _ZERONET ::zeronet::


_ZERONET_BEGIN
typedef int8_t				int8;
typedef int16_t				int16;
typedef int32_t				int32;
typedef int64_t				int64;
typedef uint8_t				uint8;
typedef uint16_t			uint16;
typedef uint32_t			uint32;
typedef uint64_t			uint64;

typedef float float32;
typedef double float64;

_ZERONET_END

#endif