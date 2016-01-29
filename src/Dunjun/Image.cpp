#include <Dunjun/common.hpp>
#include <Dunjun/Image.hpp>

#define STB_IMAGE_STATIC
#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_JPEG
#include <STB/stb_image.h>

namespace Dunjun {

Image::Image() {}

Image::Image(const char* fileName) {
  int width, height, format;
  m_pixels   = nullptr;
  u8* pixels = stbi_load(fileName, &width, &height, &format, 0);
  if (!pixels) throw std::runtime_error(stbi_failure_reason());
  loadFromMemory(width, height, format, pixels);
  stbi_image_free(pixels);
}

Image::Image(u32 width, u32 height, u32 format, const u8* pixels) {
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
  u8* pixels = stbi_load(fileName, &width, &height, &format, 0);
  if (!pixels) throw std::runtime_error(stbi_failure_reason());
  loadFromMemory(width, height, format, pixels);
  stbi_image_free(pixels);
}

void Image::loadFromMemory(u32 w, u32 h, u32 f, const u8* pixels) {
  if (w == 0) throw std::runtime_error("Image has 0 width");
  if (h == 0) throw std::runtime_error("Image has 0 height");
  if (f <= 0 || f >= 4) throw std::runtime_error("Invalid Image Format");

  m_width               = w;
  m_height              = h;
  m_format              = f;
  std::size_t imageSize = w * h * f;

  if (m_pixels) delete[] m_pixels;
  m_pixels = new u8[imageSize];
  if (m_pixels) memcpy(m_pixels, pixels, imageSize);
}

void Image::flipVertically() {
  std::size_t pitch = m_width * m_format;
  u32 halfRows      = m_height / 2;
  u8* rowBuffer = new u8[pitch];
  for (u32 i = 0; i < halfRows; i++) {
    u8* row      = m_pixels + i * pitch;
    u8* opposite = m_pixels + (m_height - i - 1) * pitch;
    memcpy(rowBuffer, row, pitch);
    memcpy(row, opposite, pitch);
    memcpy(opposite, rowBuffer, pitch);
  }
  delete[] rowBuffer;
}

void Image::rotateCCW() { return; }

void Image::copyRectFromImage(const Image& src, u32 sc, u32 sr, u32 tc, u32 tr,
                              u32 w, u32 h) {
  return;
}

u8* Image::getPixel(u32 c, u32 r) const {
  if (c >= m_width || r >= m_height) return nullptr;
  return m_pixels + (r * m_width + c) * m_format;
}

void Image::setPixel(u32 c, u32 r, const u32* pixel) {
  if (c >= m_width || r >= m_height) return;
  u8* p = getPixel(c, r);
  memcpy(p, pixel, m_format);
}

} // namespace Dunjun
