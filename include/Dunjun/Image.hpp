#pragma once
#ifndef DUNJUN_IMAGE_HPP
#define DUNJUN_IMAGE_HPP

#include <Dunjun/common.hpp>

namespace Dunjun {
enum class ImageFormat { NONE, GREYSCALE, GREYSCALE_ALPHA, RGB, RGBA };
class Image {
  public:
  Image();
  Image(const char* fileName);
  Image(unsigned int width, unsigned int height, ImageFormat format, const unsigned char* pixels = nullptr);
  Image(const Image& other);
  Image& operator=(const Image& other);
  virtual ~Image();

  void loadFromFile(const char* fileName);
  void loadFromMemory(unsigned int width, unsigned int height, ImageFormat format,
                      const unsigned char* pixels);

  void flipVertically();
  void rotateCCW();

  void copyRectFromImage(const Image& src, unsigned int sc, unsigned int sr, unsigned int tc, unsigned int tr,
                         unsigned int w, unsigned int h);

  inline unsigned int width() const { return m_width; }
  inline unsigned int height() const { return m_height; }
  inline ImageFormat format() const { return m_format; }
  inline unsigned char* pixels() const { return m_pixels; }

  unsigned char* getPixel(unsigned int c, unsigned int r) const;
  void setPixel(unsigned int c, unsigned int r, const unsigned int* pixel);

  private:
  ImageFormat m_format;
  unsigned int m_width, m_height;
  unsigned char* m_pixels;
};

} // namespace Dunjun

#endif
