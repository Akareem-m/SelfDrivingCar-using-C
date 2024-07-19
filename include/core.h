/**
 * @file core.h
 * @brief Defines core macros
 * @version 0.1
 * @date 2023-05-12
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef __CORE_H__
#define __CORE_H__

#define _USE_MATH_DEFINES
#include <math.h>

#define TO_DEGREES(x) x * 180.0 / M_PI
#define TO_RAD(x) x *M_PI / 180.0
#define PIXEL_TO_METER(x) x / 0.02f
#define METER_TO_PIXEL(x) x * 0.02f

#endif // __CORE_H__