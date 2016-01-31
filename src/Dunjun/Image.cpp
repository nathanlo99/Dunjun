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
  unsigned char* pixels = stbi_load(fileName, &width, &height, &format, 0);
  if (!pixels) throw std::runtime_error(stbi_failure_reason());
  loadFromMemory(width, height, (ImageFormat)format, pixels);
  stbi_image_free(pixels);
}

Image::Image(const unsigned int width, const unsigned int height, const ImageFormat format,
             const unsigned char* pixels) {
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
  unsigned char* pixels = stbi_load(fileName, &width, &height, &format, 0);
  if (!pixels) throw std::runtime_error(stbi_failure_reason());
  loadFromMemory(width, height, (ImageFormat)format, pixels);
  stbi_image_free(pixels);
}

void Image::loadFromMemory(const unsigned int w, const unsigned int h, const ImageFormat f,
                           const unsigned char* pixels) {
  if (w == 0) throw std::runtime_error("Image has 0 width");
  if (h == 0) throw std::runtime_error("Image has 0 height");

  m_width       = w;
  m_height      = h;
  m_format      = f;
  unsigned int imageSize = w * h * (unsigned int)f;

  if (m_pixels) delete[] m_pixels;
  m_pixels = new unsigned char[imageSize];
  if (m_pixels) memcpy(m_pixels, pixels, imageSize);
}

void Image::flipVertically() {
  std::size_t pitch = m_width * (unsigned int)m_format;
  unsigned int halfRows      = m_height / 2;
  unsigned char* rowBuffer = new unsigned char[pitch];
  for (unsigned int i = 0; i < halfRows; i++) {
    unsigned char* row      = m_pixels + i * pitch;
    unsigned char* opposite = m_pixels + (m_height - i - 1) * pitch;
    memcpy(rowBuffer, row, pitch);
    memcpy(row, opposite, pitch);
    memcpy(opposite, rowBuffer, pitch);
  }
  delete[] rowBuffer;
}

void Image::rotateCCW() { return; }

void Image::copyRectFromImage(const Image& src, const unsigned int sc, const unsigned int sr,
                              const unsigned int tc, const unsigned int tr, const unsigned int w,
                              const unsigned int h) {
  return;
}

unsigned char* Image::getPixel(const unsigned int c, const unsigned int r) const {
  if (c >= m_width || r >= m_height) return nullptr;
  return m_pixels + (r * m_width + c) * (unsigned int)m_format;
}

void Image::setPixel(const unsigned int c, const unsigned int r, const unsigned int* pixel) {
  if (c >= m_width || r >= m_height) return;
  unsigned char* p = getPixel(c, r);
  memcpy(p, pixel, (unsigned int)m_format);
}

} // namespace Dunjun
