#pragma once
#ifndef DUNJUN_COMMON_HPP
#define DUNJUN_COMMON_HPP

#define GLOBAL static
#define INTERNAL static
#define LOCAL_PERSIST static

#include <iostream>
#include <string>
#include <stdexcept>
#include <sstream>
#include <cstring>
#include <cstddef>
#include <limits>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <OpenGL/gl.h>

#include <Dunjun/types.hpp>

// Constant literals
GLOBAL const float F_EPSILON  = std::numeric_limits< float >::epsilon();
GLOBAL const double D_EPSILON = std::numeric_limits< double >::epsilon();

#endif
