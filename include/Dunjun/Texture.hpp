#pragma once
#ifndef DUNJUN_TEXTURE_HPP
#define DUNJUN_TEXTURE_HPP

#include <Dunjun/common.hpp>
#include <Dunjun/NonCopyable.hpp>
#include <Dunjun/Image.hpp>

namespace Dunjun {

class Texture : public NonCopyable {
  public:
  Texture(const Image& image, GLint minMagFilter = GL_LINEAR,
          GLint wrapMode = GL_CLAMP_TO_EDGE);
  Texture(const char* fileName, GLint minMagFilter = GL_LINEAR,
          GLint wrapMode = GL_CLAMP_TO_EDGE);
  virtual ~Texture();

  void loadFromImage(const Image& image, GLint minMagFilter = GL_LINEAR,
                     GLint wrapMode = GL_CLAMP_TO_EDGE);

  void bind(GLuint position) const;

  inline GLuint texture() const { return m_texture; }
  inline GLsizei width() const { return m_width; }
  inline GLsizei height() const { return m_height; }

  private:
  GLuint m_texture;
  GLsizei m_width, m_height;
};

} // namespace Dunjun

#endif
