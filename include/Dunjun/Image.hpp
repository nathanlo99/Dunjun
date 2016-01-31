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
  Image(u32 width, u32 height, ImageFormat format, const u8* pixels = nullptr);
  Image(const Image& other);
  Image& operator=(const Image& other);
  virtual ~Image();

  void loadFromFile(const char* fileName);
  void loadFromMemory(u32 width, u32 height, ImageFormat format,
                      const u8* pixels);

  void flipVertically();
  void rotateCCW();

  void copyRectFromImage(const Image& src, u32 sc, u32 sr, u32 tc, u32 tr,
                         u32 w, u32 h);

  inline u32 width() const { return m_width; }
  inline u32 height() const { return m_height; }
  inline ImageFormat format() const { return m_format; }
  inline u8* pixels() const { return m_pixels; }

  u8* getPixel(u32 c, u32 r) const;
  void setPixel(u32 c, u32 r, const u32* pixel);

  private:
  ImageFormat m_format;
  u32 m_width, m_height;
  u8* m_pixels;
};

} // namespace Dunjun

#endif
