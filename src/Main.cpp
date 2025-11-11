#ifdef _DEBUG
#pragma comment(lib, "glfw3D.lib")
#else
#pragma comment(lib, "glfw3.lib")
#endif
#pragma comment(lib, "opengl32.lib")

#include "../include/GLFW/wrapper_glfw.h"
#include "../include/Mesh.h"
#include "../include/MeshFactory.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace glm;

GLFWwindow *g_window = nullptr;

// Shader program
GLuint program;
GLuint modelID, viewID, projectionID;

// Window size
int width_g = 1024, height_g = 768;
float aspect;

// Camera variables
vec3 cameraPosition(0.0f, 0.0f, 3.0f);
vec3 cameraFront(0.0f, 0.0f, -1.0f);
vec3 cameraUp(0.0f, 1.0f, 0.0f);
float camYaw = -90.0f;
float camPitch = 0.0f;

// Scene
vector<Mesh> sceneObjects;

// Rotation speed
float angle_x_inc = 0.01f;
float angle_y_inc = 0.01f;

// ----------- Functions -----------

void updateCamera() {
  float moveSpeed = 0.02f;
  float rotSpeed = 1.0f;

  // Rotation
  if (glfwGetKey(g_window, GLFW_KEY_LEFT) == GLFW_PRESS)
    camYaw -= rotSpeed;
  if (glfwGetKey(g_window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    camYaw += rotSpeed;
  if (glfwGetKey(g_window, GLFW_KEY_UP) == GLFW_PRESS)
    camPitch += rotSpeed;
  if (glfwGetKey(g_window, GLFW_KEY_DOWN) == GLFW_PRESS)
    camPitch -= rotSpeed;

  if (camPitch > 89.0f)
    camPitch = 89.0f;
  if (camPitch < -89.0f)
    camPitch = -89.0f;

  vec3 front;
  front.x = cos(radians(camYaw)) * cos(radians(camPitch));
  front.y = sin(radians(camPitch));
  front.z = sin(radians(camYaw)) * cos(radians(camPitch));
  cameraFront = normalize(front);

  // Movement
  if (glfwGetKey(g_window, GLFW_KEY_W) == GLFW_PRESS)
    cameraPosition += moveSpeed * cameraFront;
  if (glfwGetKey(g_window, GLFW_KEY_S) == GLFW_PRESS)
    cameraPosition -= moveSpeed * cameraFront;
  if (glfwGetKey(g_window, GLFW_KEY_A) == GLFW_PRESS)
    cameraPosition -= normalize(cross(cameraFront, cameraUp)) * moveSpeed;
  if (glfwGetKey(g_window, GLFW_KEY_D) == GLFW_PRESS)
    cameraPosition += normalize(cross(cameraFront, cameraUp)) * moveSpeed;
}

void initScene() {
  Mesh cube1 = createCube();
  cube1.transform.position = vec3(0, 0, -2);

  Mesh cube2 = createCube();
  cube2.transform.position = vec3(2, 0, -3);
  cube2.transform.scale = vec3(0.5f);

  sceneObjects.push_back(cube1);
  sceneObjects.push_back(cube2);
}

void init(GLWrapper *glw) {
  glEnable(GL_DEPTH_TEST);

  try {
    program = glw->LoadShader("shaders/lab2.vert", "shaders/lab2.frag");
  } catch (exception &e) {
    cout << "Shader load failed: " << e.what() << endl;
    exit(0);
  }

  modelID = glGetUniformLocation(program, "model");
  viewID = glGetUniformLocation(program, "view");
  projectionID = glGetUniformLocation(program, "projection");

  initScene();
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glfwGetFramebufferSize(g_window, &width_g, &height_g);
  aspect = (float)width_g / (float)height_g;
  glViewport(0, 0, width_g, height_g);

  glUseProgram(program);

  updateCamera();
  mat4 view = lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);
  mat4 projection = perspective(radians(45.0f), aspect, 0.1f, 100.0f);

  glUniformMatrix4fv(viewID, 1, GL_FALSE, &view[0][0]);
  glUniformMatrix4fv(projectionID, 1, GL_FALSE, &projection[0][0]);

  for (auto &obj : sceneObjects) {
    obj.transform.rotation.x += angle_x_inc;
    obj.transform.rotation.y += angle_y_inc;

    mat4 model = obj.transform.getMatrix();
    glUniformMatrix4fv(modelID, 1, GL_FALSE, &model[0][0]);
    obj.draw();
  }

  glUseProgram(0);
}

static void reshape(GLFWwindow *window, int w, int h) {
  glfwGetFramebufferSize(window, &width_g, &height_g);
  glViewport(0, 0, width_g, height_g);
}

static void keyCallback(GLFWwindow *window, int k, int s, int action,
                        int mods) {
  if (action == GLFW_PRESS && k == GLFW_KEY_ESCAPE)
    glfwSetWindowShouldClose(window, GL_TRUE);
}

static void error_callback(int error, const char *description) {
  fputs(description, stderr);
}

int main() {
  GLWrapper *glw = new GLWrapper(width_g, height_g, "Project");
  g_window = glw->getWindow();

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    cout << "Failed to initialize GLAD." << endl;
    return -1;
  }

  glw->setErrorCallback(error_callback);
  glw->setRenderer(display);
  glw->setKeyCallback(keyCallback);
  glw->setReshapeCallback(reshape);
  glw->DisplayVersion();

  init(glw);

  glw->eventLoop();

  delete glw;
  return 0;
}
