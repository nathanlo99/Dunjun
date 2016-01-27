#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#include <Dunjun/ShaderProgram.hpp>

namespace Dunjun {

// Reads an entire fire into a std::string
INTERNAL std::string readFile(const std::string& fileName) {
  std::ifstream t(fileName);
  if (!t.good())
    throw std::runtime_error(std::string("Failed to open file: ") + fileName);
  std::stringstream buffer;
  buffer << t.rdbuf();
  return buffer.str();
}

ShaderProgram::ShaderProgram() { m_program = glCreateProgram(); }

ShaderProgram::~ShaderProgram() {
  if (m_program) glDeleteProgram(m_program);
}

void ShaderProgram::attachShaderFromFile(GLuint type,
                                         const std::string& fileName) {
  attachShaderFromMemory(type, readFile(fileName));
}

void ShaderProgram::attachShaderFromMemory(GLuint type,
                                           const std::string& source) {
  const char* text = source.c_str();
  GLuint shader = glCreateShader(type);
  glShaderSource(shader, 1, &text, nullptr);
  glCompileShader(shader);
  GLint success;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (success == GL_FALSE) {
    GLint maxLength;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
    char* log = new char[maxLength];
    glGetShaderInfoLog(shader, maxLength, &maxLength, log);
    throw std::runtime_error(std::string("COMPILE ") + log);
    delete[] log;
    glDeleteShader(shader);
  }
  glAttachShader(m_program, shader);
}

void ShaderProgram::use() const { glUseProgram(m_program); }
void ShaderProgram::stopUsing() const { glUseProgram(0); }

void ShaderProgram::link() {
  if (!m_program) m_program = glCreateProgram();
  glLinkProgram(m_program);
  GLint success;
  glGetProgramiv(m_program, GL_LINK_STATUS, &success);
  if (success == GL_FALSE) {
    GLint maxLength;
    glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &maxLength);
    char* log = new char[maxLength];
    glGetProgramInfoLog(m_program, maxLength, &maxLength, log);
    throw std::runtime_error(std::string("LINK ") + log);
    delete[] log;
    glDeleteProgram(m_program);
    m_program = 0;
  }
}

void ShaderProgram::bindAttribLocation(GLuint location, const GLchar* name) {
  glBindAttribLocation(m_program, location, name);
}

GLint ShaderProgram::getAttribLocation(const GLchar* name) {
  return glGetAttribLocation(m_program, name);
}

GLint ShaderProgram::getUniformLocation(const GLchar* name) {
  return glGetUniformLocation(m_program, name);
}

void ShaderProgram::setUniform(const GLchar* name, float x) {
  glUniform1f(getUniformLocation(name), x);
}

void ShaderProgram::setUniform(const GLchar* name, float x, float y) {
  glUniform2f(getUniformLocation(name), x, y);
}

void ShaderProgram::setUniform(const GLchar* name, float x, float y, float z) {
  glUniform3f(getUniformLocation(name), x, y, z);
}

void ShaderProgram::setUniform(const GLchar* name, float x, float y, float z,
                               float w) {
  glUniform4f(getUniformLocation(name), x, y, z, w);
}

void ShaderProgram::setUniform(const GLchar* name, unsigned int x) {
  glUniform1i(getUniformLocation(name), x);
}

void ShaderProgram::setUniform(const GLchar* name, int x) {
  glUniform1i(getUniformLocation(name), x);
}

void ShaderProgram::setUniform(const GLchar* name, bool x) {
  glUniform1i(getUniformLocation(name), x);
}

} // namespace Dunjun
