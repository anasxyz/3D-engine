#include "../include/Mesh.h"

Mesh::~Mesh() {
  if (vbo)
    glDeleteBuffers(1, &vbo);
  if (ebo)
    glDeleteBuffers(1, &ebo);
  if (vao)
    glDeleteVertexArrays(1, &vao);
}

void Mesh::setup(const std::vector<Vertex> &vertices,
                 const std::vector<GLuint> &indices) {
  indexCount = static_cast<GLuint>(indices.size());

  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  // vbo
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex),
               vertices.data(), GL_STATIC_DRAW);

  // ebo
  glGenBuffers(1, &ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint),
               indices.data(), GL_STATIC_DRAW);

  // layout
  // position: location 0
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        (void *)offsetof(Vertex, position));

  // normal: location 1
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        (void *)offsetof(Vertex, normal));

  // uv: location 2
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        (void *)offsetof(Vertex, uv));

  glBindVertexArray(0);
}

void Mesh::draw() const {
  glBindVertexArray(vao);
  glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}
