#include <unistd.h>

#include <sstream>

#include <Dunjun/common.hpp>
#include <Dunjun/ShaderProgram.hpp>
#include <Dunjun/Image.hpp>
#include <Dunjun/Texture.hpp>

#define STB_IMAGE_IMPLEMENTATION
#define STBI_FAILURE_USERMSG
#include <STB/stb_image.h>

GLOBAL const int g_windowWidth   = 854;
GLOBAL const int g_windowHeight  = 480;
GLOBAL const char* g_windowTitle = "Dunjun";

// Uncomment when fullscreen is re-implemented
// GLOBAL int g_fullWidth, g_fullHeight;

class Clock {
  public:
  inline double getElapsedTime() const { return glfwGetTime() - m_startTime; }
  inline double restart() {
    double now     = glfwGetTime();
    double elapsed = now - m_startTime;
    m_startTime    = now;
    return elapsed;
  }

  private:
  double m_startTime = glfwGetTime();
};

class TickCounter {
  public:
  bool update(double frequency) {
    bool reset = false;
    if (m_clock.getElapsedTime() >= frequency) {
      m_tickRate = m_ticks / frequency;
      m_ticks    = 0;
      reset = true;
      m_clock.restart();
    }
    m_ticks++;
    return reset;
  }

  inline std::size_t tickRate() const { return m_tickRate; }

  private:
  std::size_t m_ticks = 0, m_tickRate = 0;
  Clock m_clock;
};

INTERNAL void render() {
  glClearColor(0.5f, 0.69f, 1.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  glEnableVertexAttribArray(0); // v_pos
  glEnableVertexAttribArray(1); // v_color
  glEnableVertexAttribArray(2); // v_texCoord

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float),
                        (const GLvoid*)(0 * sizeof(float)));
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float),
                        (const GLvoid*)(2 * sizeof(float)));
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float),
                        (const GLvoid*)(5 * sizeof(float)));

  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(2);
}

INTERNAL void handleInput(GLFWwindow* window, bool* running, bool* fullscreen) {
  glfwPollEvents();

  // Exit if ESCAPE is pressed
  if (glfwGetKey(window, GLFW_KEY_ESCAPE)) *running = false;

  // Toggle fullscreen if F11 is pressed (Disabled until later fix)
  // if (glfwGetKey(window, GLFW_KEY_F11)) {
  //   *fullscreen = !*fullscreen;
  //   GLFWwindow *newWindow;
  //   if (*fullscreen) {
  //     newWindow = glfwCreateWindow(g_fullWidth, g_fullHeight,
  //     g_windowTitle, glfwGetPrimaryMonitor(), window);
  //   } else {
  //     newWindow = glfwCreateWindow(g_windowWidth, g_windowHeight,
  //                                  g_windowTitle, nullptr, window);
  //   }
  //   glfwDestroyWindow(window);
  //   window = newWindow;
  //   glfwMakeContextCurrent(window);
  // }
}

int main() {

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

  // Make the window's context current
  glfwMakeContextCurrent(window);

  // Pass in > 0 to enable v-syncing
  glfwSwapInterval(0);

  // Initializes GLEW. This *must* be done after the OpenGL context creation
  // and GLFW initialization.
  if (glewInit() != GLEW_OK)
    throw std::runtime_error("Could not initialize GLEW");

  // Enables face-culling
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

  // Vertices in CCW Order
  float vertices[] = {
      //  x      y     r     g     b     u     v
      +0.5f, +0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, // Vertex 0
      -0.5f, +0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, // Vertex 1
      +0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // Vertex 2
      -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // Vertex 3
  };

  // Initialize Vertex Buffer Object and shader program
  GLuint vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // Initializes the shaders
  Dunjun::ShaderProgram shader;
  shader.attachShaderFromFile(GL_VERTEX_SHADER,
                              "res/shaders/default.vert.glsl");
  shader.attachShaderFromFile(GL_FRAGMENT_SHADER,
                              "res/shaders/default.frag.glsl");
  shader.bindAttribLocation(0, "v_position");
  shader.bindAttribLocation(1, "v_color");
  shader.link();
  shader.use();

  // Loads the kitten texture into texture slot 0
  Dunjun::Texture texture("res/textures/kitten.jpg");
  texture.bind(0);
  shader.setUniform("u_tex", 0);

  bool running = true, fullscreen = false;
  TickCounter tc;
  Clock frameClock;

  // Main loop
  while (!glfwWindowShouldClose(window) && running) {
    // Updates the viewport in case the user resizes the window
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    glViewport(0, 0, width, height);
    if (tc.update(1.0)) {
      std::size_t tps   = tc.tickRate();
      std::string title = std::string(g_windowTitle) + " | " +
                          std::to_string(tps) + " TPS | " +
                          std::to_string(1000. / tps) + " MS/F";
      std::cout << title << std::endl;
      glfwSetWindowTitle(window, title.c_str());
    }
    render();
    glfwSwapBuffers(window);
    handleInput(window, &running, &fullscreen);

    while (frameClock.getElapsedTime() < 1.0 / 240.0)
      ;
    frameClock.restart();
  }

  // Clean up and terminate
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
