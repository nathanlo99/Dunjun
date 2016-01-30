#include <cmath>

#include <Dunjun/common.hpp>
#include <Dunjun/Color.hpp>
#include <Dunjun/Clock.hpp>
#include <Dunjun/TickCounter.hpp>
#include <Dunjun/ShaderProgram.hpp>
#include <Dunjun/Image.hpp>
#include <Dunjun/Texture.hpp>

#include <Dunjun/Math.hpp>

GLOBAL const int g_fpsCap = 1200; // Basically unreachable
GLOBAL int g_windowWidth  = 800;
GLOBAL int g_windowHeight = 600;

GLOBAL const char* g_windowTitle = "Dunjun";

// Uncomment when fullscreen is re-implemented
// GLOBAL int g_fullWidth, g_fullHeight;

struct Vertex {
  Dunjun::Vector2f pos;
  Dunjun::Color color;
  Dunjun::Vector2f texCoords;
};

INTERNAL void render() {
  glClearColor(0.5f, 0.69f, 1.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  glEnableVertexAttribArray(0); // v_pos
  glEnableVertexAttribArray(1); // v_color
  glEnableVertexAttribArray(2); // v_texCoord

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        (const GLvoid*)(0 * sizeof(float)));
  glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex),
                        (const GLvoid*)(sizeof(Dunjun::Vector2f)));
  glVertexAttribPointer(
      2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
      (const GLvoid*)(sizeof(Dunjun::Vector2f) + sizeof(Dunjun::Color)));

  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(2);
}

INTERNAL void handleInput(GLFWwindow* window, bool& running, bool& fullscreen) {
  glfwPollEvents();

  // Exit if ESCAPE is pressed
  if (glfwGetKey(window, GLFW_KEY_ESCAPE)) running = false;

  fullscreen = fullscreen; // To stop 'unused' warnings until fullscreen fixed

  // Toggle fullscreen if F11 is pressed (Disabled until later fix)
  // if (glfwGetKey(window, GLFW_KEY_F11)) {
  //   fullscreen = !fullscreen;
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
  // glEnable(GL_CULL_FACE);
  // glCullFace(GL_BACK);

  // Detects the primary monitor's screen width and height (Disabled until
  // fullscreen is fixed)
  // const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
  // g_fullWidth = mode->width;
  // g_fullHeight = mode->height;
  // std::cout << "Monitor size detected: " << g_fullWidth << " by "
  // << g_fullHeight << " pixels." << std::endl;
  // bool fullscreen = false;

  // Vertices in CCW Order
  Vertex vertices[] = {
      //    x      y      r    g    b    a       u     v
      {{+0.5f, +0.5f}, {255, 255, 255, 255}, {1.0f, 1.0f}}, // Vertex 0
      {{-0.5f, +0.5f}, {000, 000, 255, 255}, {0.0f, 1.0f}}, // Vertex 1
      {{+0.5f, -0.5f}, {000, 255, 000, 255}, {1.0f, 0.0f}}, // Vertex 2
      {{-0.5f, -0.5f}, {255, 000, 000, 255}, {0.0f, 0.0f}}, // Vertex 3
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
  Dunjun::TickCounter tc;
  Dunjun::Clock frameClock;

  // Main loop
  while (!glfwWindowShouldClose(window) && running) {
    // Updates the viewport in case the user resizes the window
    glfwGetWindowSize(window, &g_windowWidth, &g_windowHeight);
    glViewport(0, 0, g_windowWidth, g_windowHeight);
    if (tc.update(1.0)) {
      std::size_t tps   = tc.tickRate();
      std::string title = std::string(g_windowTitle) + " | " +
                          std::to_string(tps) + " FPS | " +
                          std::to_string(1000. / tps) + " MS/F";
      std::cout << title << std::endl;
      glfwSetWindowTitle(window, title.c_str());
    }

    Dunjun::Matrix4f model =
        Dunjun::rotate(glfwGetTime() * 60, true, {0, 1, 0});
    Dunjun::Matrix4f view = Dunjun::lookAt({1, 1, 1}, {0, 0, 0}, {0, 1, 0});

    const float aspect = (float)g_windowWidth / (float)g_windowHeight;

    Dunjun::Matrix4f projection = Dunjun::perspective(70, true, aspect, 0.1f);

    Dunjun::Matrix4f camera = projection * view;
    shader.setUniform("u_model", model);
    shader.setUniform("u_camera", camera);
    shader.use();
    render();
    glfwSwapBuffers(window);
    handleInput(window, running, fullscreen);

    while (frameClock.getElapsedTime() < 1 / (double)g_fpsCap)
      ;
    frameClock.reset();
  }

  // Clean up and terminate
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
