#include <Dunjun/Image.hpp>

#include <iostream>
#include <cstring>

#include <STB/stb_image.h>

namespace Dunjun {

Image::Image() {}

Image::Image(const char* fileName) {
  int width, height, format;
  uint8* pixels = stbi_load(fileName, &width, &height, &format, 0);
  if (!pixels) {
    std::cerr << stbi_failure_reason() << std::endl;
    std::exit(1);
  }
  loadFromMemory(width, height, format, pixels);
  stbi_image_free(pixels);
}

Image::Image(uint32 width, uint32 height, uint32 format, const uint8* pixels) {
  loadFromMemory(width, height, format, pixels);
}

Image::Image(const Image& other) {
  loadFromMemory(other.m_width, other.m_height, other.m_format, other.m_pixels);
}

Image& Image::operator=(const Image& other) {
  loadFromMemory(other.m_width, other.m_height, other.m_format, other.m_pixels);
  return *this;
}

Image::~Image() {
  if (m_pixels) delete[] m_pixels;
}

void Image::loadFromFile(const char* fileName) {
  int width, height, format;
  uint8* pixels = stbi_load(fileName, &width, &height, &format, 0);
  if (!pixels) {
    std::cerr << stbi_failure_reason() << std::endl;
    std::exit(1);
  }

  loadFromMemory(width, height, format, pixels);
  stbi_image_free(pixels);
}

void Image::loadFromMemory(uint32 w, uint32 h, uint32 f, const uint8* pixels) {
  if (w == 0) {
    std::cerr << "Image with 0 width" << std::endl;
    std::exit(1);
  } else if (h == 0) {
    std::cerr << "Image with 0 height" << std::endl;
    std::exit(1);
  } else if (f <= 0 || f >= 4) {
    std::cerr << "Invalid Texture Format" << std::endl;
    std::exit(1);
  }

  m_width        = w;
  m_height       = h;
  m_format       = f;
  size imageSize = w * h * f;

  if (m_pixels) delete[] m_pixels;
  m_pixels = new uint8[imageSize];
  if (m_pixels) memcpy(m_pixels, pixels, imageSize);
}

void Image::flipVertically() {
  size pitch       = m_width * m_format;
  uint32 halfRows  = m_height / 2;
  uint8* rowBuffer = new uint8[pitch];
  for (uint32 i = 0; i < halfRows; i++) {
    uint8* row      = m_pixels + i * pitch;
    uint8* opposite = m_pixels + (m_height - i - 1) * pitch;
    memcpy(rowBuffer, row, pitch);
    memcpy(row, opposite, pitch);
    memcpy(opposite, rowBuffer, pitch);
  }
  delete[] rowBuffer;
}

void Image::rotateCCW() { return; }

void Image::copyRectFromImage(const Image& src, uint32 sc, uint32 sr, uint32 tc,
                              uint32 tr, uint32 w, uint32 h) {
  return;
}

uint8* Image::getPixel(uint32 c, uint32 r) const {
  if (c >= m_width || r >= m_height) return nullptr;
  return m_pixels + (r * m_width + c) * m_format;
}

void Image::setPixel(uint32 c, uint32 r, const uint32* pixel) {
  if (c >= m_width || r >= m_height) return;
  uint8* p = getPixel(c, r);
  memcpy(p, pixel, m_format);
}

} // namespace Dunjun
