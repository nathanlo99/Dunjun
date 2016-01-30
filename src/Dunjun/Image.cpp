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
  loadFromMemory(width, height, (ImageFormat)format, pixels);
  stbi_image_free(pixels);
}

Image::Image(const u32 width, const u32 height, const ImageFormat format,
             const u8* pixels) {
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
  loadFromMemory(width, height, (ImageFormat)format, pixels);
  stbi_image_free(pixels);
}

void Image::loadFromMemory(const u32 w, const u32 h, const ImageFormat f,
                           const u8* pixels) {
  if (w == 0) throw std::runtime_error("Image has 0 width");
  if (h == 0) throw std::runtime_error("Image has 0 height");

  m_width       = w;
  m_height      = h;
  m_format      = f;
  u32 imageSize = w * h * (u32)f;

  if (m_pixels) delete[] m_pixels;
  m_pixels = new u8[imageSize];
  if (m_pixels) memcpy(m_pixels, pixels, imageSize);
}

void Image::flipVertically() {
  std::size_t pitch = m_width * (u32)m_format;
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

void Image::copyRectFromImage(const Image& src, const u32 sc, const u32 sr,
                              const u32 tc, const u32 tr, const u32 w,
                              const u32 h) {
  return;
}

u8* Image::getPixel(const u32 c, const u32 r) const {
  if (c >= m_width || r >= m_height) return nullptr;
  return m_pixels + (r * m_width + c) * (u32)m_format;
}

void Image::setPixel(const u32 c, const u32 r, const u32* pixel) {
  if (c >= m_width || r >= m_height) return;
  u8* p = getPixel(c, r);
  memcpy(p, pixel, (u32)m_format);
}

} // namespace Dunjun
