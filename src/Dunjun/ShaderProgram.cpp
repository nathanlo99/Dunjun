#include <fstream>
#include <iostream>
#include <vector>

#include <Dunjun/ShaderProgram.hpp>

namespace Dunjun {

// Reads an entire fire into a std::string
INTERNAL std::string readFile(const std::string& fileName) {
  std::ifstream file;
  file.open(fileName.c_str(), std::ios::in | std::ios::binary);
  std::string result, line;

  if (!file.is_open()) {
    std::cerr << "Failed to open file: " << fileName << std::endl;
    std::exit(1);
  } else {
    while (file.good()) {
      getline(file, line);
      result.append(line + "\n");
    }
  }

  file.close();
  return result;
}

ShaderProgram::ShaderProgram() : m_errorLog() { m_program = glCreateProgram(); }

ShaderProgram::~ShaderProgram() { glDeleteProgram(m_program); }

bool ShaderProgram::attachShaderFromFile(GLuint type,
                                         const std::string& fileName) {
  const std::string source = readFile(fileName);
  const char* text         = source.c_str();
  GLuint shader            = glCreateShader(type);
  glShaderSource(shader, 1, &text, nullptr);
  glCompileShader(shader);
  GLint success = 0;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (success == GL_FALSE) {
    GLint maxLength = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
    std::vector< GLchar > errorLog(maxLength);
    glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);
    std::cout << "VS ERROR: \n" << (char*)&errorLog[0] << std::endl;
    glDeleteShader(shader);
    std::cerr << "Could not compile Vertex Shader" << std::endl;
    std::exit(1);
  }
  glAttachShader(m_program, shader);
  return true;
}

bool ShaderProgram::attachShaderFromMemory(GLuint type,
                                           const std::string& source) {
  const char* text = source.c_str();
  GLuint shader    = glCreateShader(type);
  glShaderSource(shader, 1, &text, nullptr);
  glCompileShader(shader);
  GLint success = 0;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (success == GL_FALSE) {
    GLint maxLength = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
    std::vector< GLchar > errorLog(maxLength);
    glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);
    std::cout << "VS ERROR: \n" << (char*)&errorLog[0] << std::endl;
    glDeleteShader(shader);
    std::cerr << "Could not compile Fragment Shader" << std::endl;
    std::exit(1);
  }
  glAttachShader(m_program, shader);
  return true;
}

void ShaderProgram::use() const { glUseProgram(m_program); }
void ShaderProgram::stopUsing() const { glUseProgram(0); }

void ShaderProgram::link() {
  glLinkProgram(m_program);

  GLint success = 0;
  glGetProgramiv(m_program, GL_LINK_STATUS, &success);
  if (success == GL_FALSE) {
    GLint maxLength = 0;
    glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &maxLength);
    std::vector< GLchar > infoLog(maxLength);
    glGetProgramInfoLog(m_program, maxLength, &maxLength, &infoLog[0]);
    std::cout << "PROGRAM ERROR: \n" << (char*)&infoLog[0] << std::endl;
    glDeleteProgram(m_program);
    std::cerr << "Could not link Shader Program" << std::endl;
    std::exit(1);
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

void ShaderProgram::setUniform(
    const GLchar* name, float x, float y, float z, float w) {
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

} // namespace Dunjun
