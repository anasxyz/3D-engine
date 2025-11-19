#pragma once
#include "glad/glad.h"
#include <glm/glm.hpp>
#include <vector>

using namespace glm;

struct Vertex {
  vec3 position;
  vec3 normal;
  vec2 uv;
	// default colour
  vec4 colour = vec4(0.7f, 0.7f, 0.75f, 1.0f); 

  Vertex(const vec3 &p, const vec3 &n = vec3(0), const vec2 &t = vec2(0))
      : position(p), normal(n), uv(t) {}
};
static_assert(sizeof(Vertex) == 48, "Vertex struct must be tightly packed");
