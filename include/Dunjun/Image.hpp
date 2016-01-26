#ifndef DUNJUN_IMAGE_HPP
#define DUNJUN_IMAGE_HPP

#include <Dunjun/types.hpp>

namespace Dunjun {

class Image {
  public:
  Image();
  Image(const char* fileName);
  Image(uint32 width, uint32 height, uint32 format,
        const uint8* pixels = nullptr);
  Image(const Image& other);
  Image& operator=(const Image& other);
  virtual ~Image();

  void loadFromFile(const char* fileName);
  void loadFromMemory(uint32 width, uint32 height, uint32 format,
                      const uint8* pixels);

  void flipVertically();
  void rotateCCW();

  void copyRectFromImage(const Image& src, uint32 sc, uint32 sr, uint32 tc,
                         uint32 tr, uint32 w, uint32 h);

  inline uint32 width() const { return m_width; }
  inline uint32 height() const { return m_height; }
  inline uint32 format() const { return m_format; }
  inline uint8* pixels() const { return m_pixels; }

  uint8* getPixel(uint32 c, uint32 r) const;
  void setPixel(uint32 c, uint32 r, const uint32* pixel);

  private:
  uint32 m_format, m_width, m_height;
  uint8* m_pixels;
};

} // namespace Dunjun

#endif
