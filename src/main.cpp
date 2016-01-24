#define GLEW_STATIC

#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <Dunjun/common.hpp>

#include <Dunjun/ShaderProgram.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <OpenGL/gl.h>

GLOBAL const int g_windowWidth   = 854;
GLOBAL const int g_windowHeight  = 480;
GLOBAL const char* g_windowTitle = "Dunjun";

// Uncomment when fullscreen is re-implemented
// global int g_fullWidth, g_fullHeight;

int main(int argc, char** argv) {

  // Initialize GLFW
  if (!glfwInit()) return -1;

  // Create a window and its OpenGL context, set to OpenGL 2.1
  glfwWindowHint(GLFW_VERSION_MAJOR, 2);
  glfwWindowHint(GLFW_VERSION_MINOR, 1);

  GLFWwindow* window = glfwCreateWindow(g_windowWidth, g_windowHeight,
                                        g_windowTitle, nullptr, nullptr);
  if (!window) {
    std::cout << "GLFWwindow could not be created!" << std::endl;
    glfwTerminate();
    return -1;
  }

  // Make the window's current context
  glfwMakeContextCurrent(window);

  // Initializes GLEW. This *must* be done after the OpenGL context creation
  // and GLFW initialization.
  if (glewInit() != GLEW_OK) {
    std::cerr << "Could not initialize GLEW" << std::endl;
    return glGetError();
  }

  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);

  // Detects the primary monitor's screen width and height (Disabled until
  // fullscreen is fixed)
  // const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
  // g_fullWidth = mode->width;
  // g_fullHeight = mode->height;
  // std::cout << "Monitor size detected: " << g_fullWidth << " by "
  // << g_fullHeight << " pixels." << std::endl;
  // bool fullscreen = false;

  // Initialize VBO and shader program
  // Vertices in CCW Order
  float vertices[] = {
      +0.5f, +0.5f, +1.0f, +1.0f, +1.0f, // Vertex 0
      -0.5f, +0.5f, +0.0f, +0.0f, +1.0f, // Vertex 1
      +0.5f, -0.5f, +0.0f, +1.0f, +0.0f, // Vertex 2
      -0.5f, -0.5f, +1.0f, +0.0f, +0.0f, // Vertex 3
  };

  GLuint vbo; // Vertex Buffer Object
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  Dunjun::ShaderProgram shader;
  shader.attachShaderFromFile(GL_VERTEX_SHADER,
                              "res/shaders/default.vert.glsl");
  shader.attachShaderFromFile(GL_FRAGMENT_SHADER,
                              "res/shaders/default.frag.glsl");
  shader.bindAttribLocation(0, "v_position");
  shader.bindAttribLocation(1, "v_color");
  shader.link();
  shader.use();

  // Loop until the user closes the window
  while (!glfwWindowShouldClose(window)) {
    // Clears the buffer
    glClearColor(0.5f, 0.69f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Render here
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                          (const GLvoid*)(2 * sizeof(float)));
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    // Swap buffers
    glfwSwapBuffers(window);

    // Poll for and process events
    glfwPollEvents();

    // Exit if ESCAPE is pressed
    if (glfwGetKey(window, GLFW_KEY_ESCAPE)) break;

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
