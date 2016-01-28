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

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <OpenGL/gl.h>

#include <Dunjun/types.hpp>

namespace Dunjun {} // namespace Dunjun

#endif
