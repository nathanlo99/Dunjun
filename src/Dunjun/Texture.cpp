#include <Dunjun/Texture.hpp>

namespace Dunjun {

INTERNAL GLenum getFormat(u32 format, bool srgb) {
  switch (format) {
  case 1:
    return GL_LUMINANCE;
  case 2:
    return GL_LUMINANCE_ALPHA;
  case 3:
    return srgb ? GL_SRGB : GL_RGB;
  case 4:
    return srgb ? GL_SRGB_ALPHA : GL_RGBA;
  default:
    throw std::runtime_error("Invalid format");
  }
}

Texture::Texture(const Image& image, GLint minMagFilter, GLint wrapMode) {
  loadFromImage(image, minMagFilter, wrapMode);
}

Texture::Texture(const char* fileName, GLint minMagFilter, GLint wrapMode) {
  Image image(fileName);
  image.flipVertically();
  loadFromImage(image, minMagFilter, wrapMode);
}

void Texture::loadFromImage(const Image& image, GLint minMagFilter,
                            GLint wrapMode) {
  m_width  = (GLsizei)image.width();
  m_height = (GLsizei)image.height();

  glGenTextures(1, &m_texture);
  glBindTexture(GL_TEXTURE_2D, m_texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minMagFilter);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, minMagFilter);

  glTexImage2D(GL_TEXTURE_2D, 0, getFormat(image.format(), true), m_width,
               m_height, 0, getFormat(image.format(), false), GL_UNSIGNED_BYTE,
               image.pixels());
  glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture() { glDeleteTextures(1, &m_texture); }

void Texture::bind(GLuint position) {
  if (position > 31) {
    std::cerr << "Texture position too high: " << position << std::endl;
    std::cerr << "Binding to position [31] instead" << std::endl;
  }

  glActiveTexture(GL_TEXTURE0 + position);
  glClientActiveTexture(GL_TEXTURE0 + position);

  glBindTexture(GL_TEXTURE_2D, m_texture);

  glEnable(GL_TEXTURE_2D);
  glDisable(GL_TEXTURE_2D);
}

} // namespace Dunjun
