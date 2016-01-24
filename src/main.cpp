#include <iostream>
#include <string>

#include <Dunjun/common.hpp>

#include <GLFW/glfw3.h>

global const int g_windowWidth = 854;
global const int g_windowHeight = 480;
global const char *g_windowTitle = "Dunjun";

global int g_fullWidth, g_fullHeight;

int main(int argc, char **argv) {
  GLFWwindow *window;

  // Initialize the library
  if (!glfwInit()) {
    return -1;
  }

  // Create a window and its OpenGL context
  window = glfwCreateWindow(g_windowWidth, g_windowHeight, g_windowTitle,
                            nullptr, nullptr);
  if (!window) {
    glfwTerminate();
    return -1;
  }

  // Make the window's current context
  glfwMakeContextCurrent(window);

  const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
  g_fullWidth = mode->width;
  g_fullHeight = mode->height;

  std::cout << g_fullWidth << ", " << g_fullHeight << std::endl;

  bool fullscreen = false;

  // Loop until the user closes the window
  while (!glfwWindowShouldClose(window)) {
    // Clears the buffer
    glClearColor(0.5f, 0.69f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Render here

    // Swap buffers
    glfwSwapBuffers(window);

    // Poll for and process events
    glfwPollEvents();

    if (glfwGetKey(window, GLFW_KEY_ESCAPE))
      break;

    if (glfwGetKey(window, GLFW_KEY_F11)) {
      fullscreen = !fullscreen;
      GLFWwindow *newWindow;
      if (fullscreen) {
        newWindow = glfwCreateWindow(g_fullWidth, g_fullHeight, g_windowTitle,
                                     glfwGetPrimaryMonitor(), window);
      } else {
        newWindow = glfwCreateWindow(g_windowWidth, g_windowHeight,
                                     g_windowTitle, nullptr, window);
      }
      glfwDestroyWindow(window);
      window = newWindow;
      glfwMakeContextCurrent(window);
    }
  }
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
