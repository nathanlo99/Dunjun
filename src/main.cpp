#include <Dunjun/common.hpp>
#include <Dunjun/Color.hpp>
#include <Dunjun/Clock.hpp>
#include <Dunjun/TickCounter.hpp>
#include <Dunjun/ShaderProgram.hpp>
#include <Dunjun/Image.hpp>
#include <Dunjun/Texture.hpp>
#include <Dunjun/Vertex.hpp>
#include <Dunjun/Math.hpp>

GLOBAL const int g_fpsCap      = 90;
GLOBAL const float g_timeStep  = 1.0f / 60.f;
GLOBAL int g_windowWidth       = 800;
GLOBAL int g_windowHeight      = 600;
GLOBAL bool g_resizedLastFrame = false;

GLOBAL const char* g_windowTitle = "Dunjun";

GLOBAL int g_fullWidth, g_fullHeight;

struct ModelAsset {
  Dunjun::ShaderProgram* shaders;
  Dunjun::Texture* texture;

  GLuint vbo, ibo;
  GLenum drawType;
  GLint drawStart, drawCount;
};

struct ModelInstance {
  ModelAsset* asset;
  Dunjun::Transform transform;
};

GLOBAL Dunjun::ShaderProgram* g_defaultShader;
GLOBAL ModelAsset g_sprite;
GLOBAL std::vector<ModelInstance> g_instances;
GLOBAL Dunjun::Matrix4f g_cameraTransform;

INTERNAL void onResize(GLFWwindow* window, int width, int height) {
  if (g_resizedLastFrame) return;
  g_resizedLastFrame = true;

  g_windowWidth  = width;
  g_windowHeight = height;
  glViewport(0, 0, g_windowWidth, g_windowHeight);

  Dunjun::Matrix4f view = Dunjun::lookAt({1, 2, 4}, {0, 0, 0}, {0, 1, 0});

  Dunjun::Matrix4f projection = Dunjun::perspective(
      70, true, (float)g_windowWidth / (float)g_windowHeight, 0.1f);

  g_cameraTransform = projection * view;

  std::cout << "RESIZED" << std::endl;
}

INTERNAL void handleInput(GLFWwindow* window, bool& running, bool& fullscreen) {
  glfwPollEvents();

  // Exit if ESCAPE is pressed
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) running = false;

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

INTERNAL void loadShaders() {
  g_defaultShader = new Dunjun::ShaderProgram();
  g_defaultShader->attachShaderFromFile(GL_VERTEX_SHADER,
                                        "res/shaders/default.vert.glsl");
  g_defaultShader->attachShaderFromFile(GL_FRAGMENT_SHADER,
                                        "res/shaders/default.frag.glsl");
  g_defaultShader->bindAttribLocation(0, "v_position");
  g_defaultShader->bindAttribLocation(1, "v_color");
  g_defaultShader->bindAttribLocation(2, "v_texCoords");
  g_defaultShader->link();
}

INTERNAL void loadSpriteAsset() {

  Dunjun::Vertex vertices[] = {
      //    x      y     z       r     g     b     a       u     v
      {{-0.5f, -0.5f, 0.0f}, {0x00, 0x00, 0xFF, 0xFF}, {0.0f, 0.0f}}, // V0
      {{+0.5f, -0.5f, 0.0f}, {0x00, 0xFF, 0x00, 0xFF}, {1.0f, 0.0f}}, // V1
      {{+0.5f, +0.5f, 0.0f}, {0xFF, 0xFF, 0xFF, 0xFF}, {1.0f, 1.0f}}, // V2
      {{-0.5f, +0.5f, 0.0f}, {0xFF, 0x00, 0x00, 0xFF}, {0.0f, 1.0f}}, // V3
  };

  glGenBuffers(1, &g_sprite.vbo);
  glBindBuffer(GL_ARRAY_BUFFER, g_sprite.vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  unsigned int indices[] = {0, 1, 2, 2, 3, 0};

  glGenBuffers(1, &g_sprite.ibo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_sprite.ibo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
               GL_STATIC_DRAW);

  g_sprite.shaders = g_defaultShader;
  g_sprite.texture = new Dunjun::Texture("res/textures/kitten.jpg");

  g_sprite.drawType  = GL_TRIANGLES;
  g_sprite.drawCount = 6;
}

INTERNAL void loadInstances() {

  ModelInstance a;
  a.asset              = &g_sprite;
  a.transform.position = {0, 0, 0};
  a.transform.scale    = {3, 3, 3};
  a.transform.rotation = Dunjun::Quaternion(45, true, {0, 0, 1});
  g_instances.push_back(a);

  ModelInstance b;
  b.asset              = &g_sprite;
  b.transform.position = {2, 0, 0};
  g_instances.push_back(b);

  ModelInstance c;
  c.asset              = &g_sprite;
  c.transform.position = {0, 0, 1};
  c.transform.rotation = Dunjun::Quaternion(45, true, {0, 1, 0});
  g_instances.push_back(c);
}

INTERNAL void update(float dt) {
  const Dunjun::Matrix4f view = Dunjun::lookAt({1, 2, 4}, {0, 0, 0}, {0, 1, 0});

  const Dunjun::Matrix4f projection = Dunjun::perspective(
      70, true, (float)g_windowWidth / (float)g_windowHeight, 0.1f);

  g_cameraTransform = projection * view;

  g_instances[0].transform.rotation =
      Dunjun::Quaternion(120 * dt, true, {0, 1, 0}) *
      g_instances[0].transform.rotation;
}

INTERNAL void renderInstance(const ModelInstance& instance) {
  ModelAsset* asset = instance.asset;

  asset->shaders->setUniform("u_transform", instance.transform);
  asset->shaders->setUniform("u_camera", g_cameraTransform);

  asset->shaders->setUniform("u_tex", 0);
  asset->texture->bind(0);

  asset->shaders->use();

  glBindBuffer(GL_ARRAY_BUFFER, g_sprite.vbo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_sprite.ibo);

  glEnableVertexAttribArray(0); // v_pos
  glEnableVertexAttribArray(1); // v_color
  glEnableVertexAttribArray(2); // v_texCoords

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Dunjun::Vertex),
                        (const GLvoid*)offsetof(Dunjun::Vertex, pos));
  glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Dunjun::Vertex),
                        (const GLvoid*)offsetof(Dunjun::Vertex, color));
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Dunjun::Vertex),
                        (const GLvoid*)offsetof(Dunjun::Vertex, texCoords));

  glDrawElements(asset->drawType, asset->drawCount, GL_UNSIGNED_INT, nullptr);

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(2);

  asset->shaders->stopUsing();
}

INTERNAL void render(GLFWwindow* window) {

  glClearColor(0.5f, 0.69f, 1.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  for (const ModelInstance& instance : g_instances) {
    instance.asset->shaders->use();
    renderInstance(instance);
  }
  glUseProgram(0);

  glfwSwapBuffers(window);
}

int main() {

  GLFWwindow* window;
  bool running = true, fullscreen = false;
  Dunjun::TickCounter tc;
  Dunjun::Clock frameClock;

  // Initialize GLFW
  if (!glfwInit()) return -1;

  // Create a window and its OpenGL context, set to OpenGL 2.1
  glfwDefaultWindowHints();
  glfwWindowHint(GLFW_VERSION_MAJOR, 2);
  glfwWindowHint(GLFW_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

  window = glfwCreateWindow(g_windowWidth, g_windowHeight, g_windowTitle,
                            nullptr, nullptr);
  if (!window) {
    std::cout << "GLFWwindow could not be created!" << std::endl;
    glfwTerminate();
    return -1;
  }

  // Make the window's context current
  glfwMakeContextCurrent(window);

  // Pass in > 0 to enable v-syncing
  glfwSwapInterval(0);

  glfwSetWindowSizeCallback(window, onResize);

  // Initializes GLEW. This *must* be done after the OpenGL context creation
  // and GLFW initialization.
  if (glewInit() != GLEW_OK)
    throw std::runtime_error("Could not initialize GLEW");

  // Enables face-culling
  // glEnable(GL_CULL_FACE);
  // glCullFace(GL_BACK);
  glEnable(GL_DEPTH_TEST);

  // Detects the primary monitor's screen width and height (Disabled until
  // fullscreen is fixed)
  const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
  g_fullWidth             = mode->width;
  g_fullHeight            = mode->height;
  std::cout << "Monitor size detected: " << g_fullWidth << " by "
            << g_fullHeight << " pixels." << std::endl;

  loadShaders();
  loadSpriteAsset();
  loadInstances();

  double lastFrame = glfwGetTime();
  float dt;
  float accumulator = 0.0f;

  // Main loop
  while (!glfwWindowShouldClose(window) && running) {
    double now = glfwGetTime();
    dt         = now - lastFrame;
    lastFrame  = now;
    accumulator += dt;

    handleInput(window, running, fullscreen);

    while (accumulator >= g_timeStep) {
      update(g_timeStep);
      accumulator -= g_timeStep;
    }

    if (tc.update(1.0)) {
      std::size_t tps = tc.tickRate();
      std::stringstream title;
      title << g_windowTitle << " | " << tps << " FPS | " << 1000. / tps
            << " MS/F";
      std::cout << "| " << tps << " FPS | [" << 1000. / tps << " MS/F]"
                << std::endl;
      glfwSetWindowTitle(window, title.str().c_str());
    }

    render(window);

    while (frameClock.getElapsedTime() < 1 / (double)g_fpsCap)
      ;
    frameClock.reset();

    g_resizedLastFrame = false;
  }

  // Clean up and terminate
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
