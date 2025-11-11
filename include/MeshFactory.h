#pragma once
#include "Mesh.h"

inline Mesh createCube(float size = 1.0f) {
  Mesh cube;
  float s = size / 2.0f;

  std::vector<GLfloat> positions = {
      // back face (red)
      -s, -s, -s, 1, s, -s, -s, 1, s, s, -s, 1, -s, s, -s, 1,
      // front face (green)
      -s, -s, s, 1, s, -s, s, 1, s, s, s, 1, -s, s, s, 1,
      // left face (blue)
      -s, -s, -s, 1, -s, s, -s, 1, -s, s, s, 1, -s, -s, s, 1,
      // right face (yellow)
      s, -s, -s, 1, s, s, -s, 1, s, s, s, 1, s, -s, s, 1,
      // top face (magenta)
      -s, s, -s, 1, s, s, -s, 1, s, s, s, 1, -s, s, s, 1,
      // bottom face (cyan)
      -s, -s, -s, 1, s, -s, -s, 1, s, -s, s, 1, -s, -s, s, 1};

  std::vector<GLfloat> colors = {// back - red
                                 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1,
                                 // front - green
                                 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
                                 // left - blue
                                 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1,
                                 // right - yellow
                                 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1,
                                 // top - magenta
                                 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1,
                                 // bottom - cyan
                                 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1,
                                 1};

  std::vector<GLuint> indices = {
      0,  1,  2,  2,  3,  0,  // back
      4,  5,  6,  6,  7,  4,  // front
      8,  9,  10, 10, 11, 8,  // left
      12, 13, 14, 14, 15, 12, // right
      16, 17, 18, 18, 19, 16, // top
      20, 21, 22, 22, 23, 20  // bottom
  };

  cube.setup(positions, colors, indices);
  return cube;
}

inline Mesh createSphere(float radius = 1.0f, int stacks = 16,
                         int slices = 32) {
  Mesh sphere;

  std::vector<GLfloat> positions;
  std::vector<GLfloat> colors;
  std::vector<GLuint> indices;

  for (int i = 0; i <= stacks; ++i) {
    float phi = glm::pi<float>() * (float)i / (float)stacks; // from 0 to π

    for (int j = 0; j < slices; ++j) {
      float theta =
          glm::two_pi<float>() * (float)j / (float)slices; // from 0 to 2π

      float x = radius * sin(phi) * cos(theta);
      float y = radius * cos(phi);
      float z = radius * sin(phi) * sin(theta);

      positions.push_back(x);
      positions.push_back(y);
      positions.push_back(z);
      positions.push_back(1.0f);

      // give each vertex a simple color gradient (optional)
      float u = (float)j / slices;
      if (j == slices)
        u = 0.0f; // wrap around to avoid color seam

      colors.push_back((float)i / stacks);
      colors.push_back(u);
      colors.push_back(1.0f - (float)i / stacks);
      colors.push_back(1.0f);
    }
  }

  // generate indices
  for (int i = 0; i < stacks; ++i) {
    for (int j = 0; j < slices; ++j) {
      int first = i * slices + j;
      int second = first + slices;

      int nextJ = (j + 1) % slices; // wrap around
      int firstNext = i * slices + nextJ;
      int secondNext = firstNext + slices;

      indices.push_back(first);
      indices.push_back(second);
      indices.push_back(firstNext);

      indices.push_back(second);
      indices.push_back(secondNext);
      indices.push_back(firstNext);
    }
  }

  sphere.setup(positions, colors, indices);
  return sphere;
}
