#ifndef DUNJUN_SHADERPROGRAM_HPP
#define DUNJUN_SHADERPROGRAM_HPP

#include <string>

#include <Dunjun/common.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Dunjun {
class ShaderProgram { // Wrapper class for an OpenGL shader
  public:
  ShaderProgram();
  virtual ~ShaderProgram();

  bool attachShaderFromFile(GLuint type, const std::string& fileName);
  bool attachShaderFromMemory(GLuint type, const std::string& fileName);

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

  inline GLuint getObject() const { return m_program; }
  inline const std::string& getErrorLog() const { return m_errorLog; }

  private:
  GLuint m_program;
  std::string m_errorLog;
};

} // namespace Dunjun

#endif
