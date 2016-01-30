#pragma once
#ifndef DUNJUN_SHADERPROGRAM_HPP
#define DUNJUN_SHADERPROGRAM_HPP

#include <string>
#include <map>

#include <Dunjun/common.hpp>
#include <Dunjun/Math/Vector2f.hpp>
#include <Dunjun/Math/Vector3f.hpp>
#include <Dunjun/Math/Vector4f.hpp>
#include <Dunjun/Math/Matrix4f.hpp>
#include <Dunjun/NonCopyable.hpp>

namespace Dunjun {
class ShaderProgram : public NonCopyable { // Wrapper class for an OpenGL shader
  public:
  ShaderProgram();
  virtual ~ShaderProgram();

  void attachShaderFromFile(const GLuint type, const std::string& fileName);
  void attachShaderFromMemory(const GLuint type, const std::string& fileName);

  void use() const;
  void stopUsing() const;
  void link() const;

  void bindAttribLocation(const GLuint location, const GLchar* name);
  GLint getAttribLocation(const GLchar* name);
  GLint getUniformLocation(const GLchar* name);

  void setUniform(const GLchar* name, const float x);
  void setUniform(const GLchar* name, const float x, const float y);
  void setUniform(const GLchar* name, const float x, const float y,
                  const float z);
  void setUniform(const GLchar* name, const float x, const float y,
                  const float z, const float w);
  void setUniform(const GLchar* name, const int x);
  void setUniform(const GLchar* name, const unsigned int x);
  void setUniform(const GLchar* name, const bool x);
  void setUniform(const GLchar* name, const Vector2f& v);
  void setUniform(const GLchar* name, const Vector3f& v);
  void setUniform(const GLchar* name, const Vector4f& v);
  void setUniform(const GLchar* name, const Matrix4f& m);

  inline GLuint program() const { return m_program; }

  private:
  GLuint m_program = glCreateProgram();

  std::map<std::string, GLint> m_uniformLocations;
  std::map<std::string, GLint> m_attribLocations;
};

} // namespace Dunjun

#endif
