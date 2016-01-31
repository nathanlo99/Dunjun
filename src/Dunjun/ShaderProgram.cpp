#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#include <Dunjun/ShaderProgram.hpp>

namespace Dunjun {

// Reads an entire fire into a std::string
INTERNAL std::string readFile(const std::string& fileName) {
  std::ifstream in(fileName.c_str(), std::ios::in | std::ios::binary);
  if (in) {
    std::string contents;
    in.seekg(0, std::ios::end);
    contents.resize(in.tellg());
    in.seekg(0, std::ios::beg);
    in.read(&contents[0], contents.size());
    in.close();
    return contents;
  }
  throw std::runtime_error(std::string("Failed to open file: ") + fileName);
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

void ShaderProgram::link() const {
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
  }
}

void ShaderProgram::bindAttribLocation(GLuint location, const GLchar* name) {
  glBindAttribLocation(m_program, location, name);
  m_attribLocations[std::string(name)] = location;
}

GLint ShaderProgram::getAttribLocation(const GLchar* name) {
  std::string str_name = std::string(name);
  auto found = m_attribLocations.find(str_name);
  if (found != m_attribLocations.end()) return found->second;
  GLint loc = glGetAttribLocation(m_program, name);
  if (loc == -1)
    throw std::runtime_error(std::string("Could not find attribute: ") +
                             str_name);
  return m_attribLocations[str_name] = loc;
}

GLint ShaderProgram::getUniformLocation(const GLchar* name) {
  std::string str_name = std::string(name);
  auto found = m_uniformLocations.find(str_name);
  if (found != m_uniformLocations.end()) return found->second;
  GLint loc = glGetUniformLocation(m_program, name);
  if (loc == -1)
    throw std::runtime_error(std::string("Could not find uniform: ") +
                             str_name);
  return m_uniformLocations[str_name] = loc;
}

void ShaderProgram::setUniform(const GLchar* name, float x) {
  use();
  glUniform1f(getUniformLocation(name), x);
}

void ShaderProgram::setUniform(const GLchar* name, float x, float y) {
  use();
  glUniform2f(getUniformLocation(name), x, y);
}

void ShaderProgram::setUniform(const GLchar* name, float x, float y, float z) {
  use();
  glUniform3f(getUniformLocation(name), x, y, z);
}

void ShaderProgram::setUniform(const GLchar* name, float x, float y, float z,
                               float w) {
  use();
  glUniform4f(getUniformLocation(name), x, y, z, w);
}

void ShaderProgram::setUniform(const GLchar* name, unsigned int x) {
  use();
  glUniform1i(getUniformLocation(name), x);
}

void ShaderProgram::setUniform(const GLchar* name, int x) {
  use();
  glUniform1i(getUniformLocation(name), x);
}

void ShaderProgram::setUniform(const GLchar* name, bool x) {
  use();
  glUniform1i(getUniformLocation(name), x);
}

void ShaderProgram::setUniform(const GLchar* name, const Vector2f& v) {
  use();
  glUniform2fv(getUniformLocation(name), 1, v.data);
}

void ShaderProgram::setUniform(const GLchar* name, const Vector3f& v) {
  use();
  glUniform3fv(getUniformLocation(name), 1, v.data);
}

void ShaderProgram::setUniform(const GLchar* name, const Vector4f& v) {
  use();
  glUniform4fv(getUniformLocation(name), 1, v.data);
}

void ShaderProgram::setUniform(const GLchar* name, const Matrix4f& m) {
  use();
  glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, m[0].data);
}

void ShaderProgram::setUniform(const GLchar* name, const Quaternion& q) {
  use();
  glUniform4fv(getUniformLocation(name), 1, &q.x);
}

void ShaderProgram::setUniform(const GLchar* name, const Transform& t) {
  std::string n = name;
  setUniform((n + ".position").c_str(), t.position);
  setUniform((n + ".rotation").c_str(), t.rotation);
  setUniform((n + ".scale").c_str(), t.scale);
}

} // namespace Dunjun
