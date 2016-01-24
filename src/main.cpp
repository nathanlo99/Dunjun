#define GLEW_STATIC

#include <iostream>
#include <string>
#include <vector>

#include <Dunjun/common.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <OpenGL/gl.h>

global const int g_windowWidth = 854;
global const int g_windowHeight = 480;
global const char *g_windowTitle = "Dunjun";

// Uncomment when fullscreen is re-implemented
// global int g_fullWidth, g_fullHeight;

// Tell GLFW to use OpenGL 2.1 whenever creating a window
inline void glfwHints() {
  glfwWindowHint(GLFW_VERSION_MAJOR, 2);
  glfwWindowHint(GLFW_VERSION_MINOR, 1);
}

int main(int argc, char **argv) {

  GLFWwindow *window;

  // Initialize the library
  if (!glfwInit()) {
    return -1;
  }

  // Create a window and its OpenGL context
  glfwHints();
  window = glfwCreateWindow(g_windowWidth, g_windowHeight, g_windowTitle,
                            nullptr, nullptr);
  if (!window) {
    glfwTerminate();
    return -1;
  }

  // Make the window's current context
  glfwMakeContextCurrent(window);

  // Initializes GLEW. This *must* be done after the OpenGL context creation and
  // GLFW initialization.
  if (glewInit() != GLEW_OK)
    return glGetError();

  // Detects the primary monitor's screen width and height (Disabled until
  // fullscreen is fixed)
  // const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
  // g_fullWidth = mode->width;
  // g_fullHeight = mode->height;
  // std::cout << "Monitor size detected: " << g_fullWidth << " by "
  // << g_fullHeight << " pixels." << std::endl;
  // bool fullscreen = false;

  { // Initialize VBO and shader program
    // Vertices in CCW Order
    float vertices[] = {0.0f, 0.5f, -0.5f, -0.5f, 0.5f, -0.5f};

    GLuint vbo; // Vertex Buffer Object
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    const char *vertexShaderText = {
        "#version 120\n"
        "attribute vec2 position; "
        "void main(){ gl_Position = vec4(position, 0.0, 1.0); }"};
    const char *fragmentShaderText = {
        "#version 120\n"
        "void main() { gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0); }"};

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderText, nullptr);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderText, nullptr);
    glCompileShader(fragmentShader);

    GLint success = 0;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) {
      GLint maxLength = 0;
      glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);
      std::vector<GLchar> errorLog(maxLength);
      glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &errorLog[0]);
      std::cout << (char *)&errorLog[0] << std::endl;
      glDeleteShader(vertexShader);
    }

    success = 0;
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) {
      GLint maxLength = 0;
      glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);
      std::vector<GLchar> errorLog(maxLength);
      glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &errorLog[0]);
      std::cout << (char *)&errorLog[0] << std::endl;
      glDeleteShader(fragmentShader);
    }

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glBindAttribLocation(shaderProgram, 0, "position");
    glLinkProgram(shaderProgram);

    success = 0;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (success == GL_FALSE) {
      GLint maxLength = 0;
      glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &maxLength);

      std::vector<GLchar> infoLog(maxLength);
      glGetProgramInfoLog(shaderProgram, maxLength, &maxLength, &infoLog[0]);
      std::cout << (char *)&infoLog[0] << std::endl;
      glDeleteProgram(shaderProgram);
    }

    glUseProgram(shaderProgram);
  }

  // Loop until the user closes the window
  while (!glfwWindowShouldClose(window)) {
    // Clears the buffer
    glClearColor(0.5f, 0.69f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    { // Render here
      glEnableVertexAttribArray(0);
      glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
      glDrawArrays(GL_TRIANGLES, 0, 3);
      glDisableVertexAttribArray(0);
    }

    // Swap buffers
    glfwSwapBuffers(window);

    // Poll for and process events
    glfwPollEvents();

    // Exit if ESCAPE is pressed
    if (glfwGetKey(window, GLFW_KEY_ESCAPE))
      break;

    // Toggle fullscreen if F11 is pressed (Disabled until later fix)
    // if (glfwGetKey(window, GLFW_KEY_F11)) {
    //   fullscreen = !fullscreen;
    //   GLFWwindow *newWindow;
    //   glfwHints();
    //   if (fullscreen) {
    //     newWindow = glfwCreateWindow(g_fullWidth, g_fullHeight,
    //     g_windowTitle,
    //                                  glfwGetPrimaryMonitor(), window);
    //   } else {
    //     newWindow = glfwCreateWindow(g_windowWidth, g_windowHeight,
    //                                  g_windowTitle, nullptr, window);
    //   }
    //   glfwDestroyWindow(window);
    //   window = newWindow;
    //   glfwMakeContextCurrent(window);
    // }
  }

  // Clean up and terminate
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
