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

  void attachShaderFromFile(GLuint type, const std::string& fileName);
  void attachShaderFromMemory(GLuint type, const std::string& fileName);

  void use() const;
  void stopUsing() const;
  void link();

  void bindAttribLocation(GLuint location, const GLchar* name);
  GLint getAttribLocation(const GLchar* name);
  GLint getUniformLocation(const GLchar* name);

  void setUniform(const GLchar* name, float x);
  void setUniform(const GLchar* name, float x, float y);
  void setUniform(const GLchar* name, float x, float y, float z);
  void setUniform(const GLchar* name, float x, float y, float z, float w);
  void setUniform(const GLchar* name, int x);
  void setUniform(const GLchar* name, unsigned int x);
  void setUniform(const GLchar* name, bool x);
  void setUniform(const GLchar* name, Vector2f& v);
  void setUniform(const GLchar* name, Vector3f& v);
  void setUniform(const GLchar* name, Vector4f& v);
  void setUniform(const GLchar* name, Matrix4f& m);

  inline GLuint program() const { return m_program; }
  inline const std::string& errorLog() const { return m_errorLog; }

  private:
  GLuint m_program = glCreateProgram();
  std::string m_errorLog;

  std::map< std::string, GLint > m_uniformLocations;
  std::map< std::string, GLint > m_attribLocations;
};

} // namespace Dunjun

#endif
