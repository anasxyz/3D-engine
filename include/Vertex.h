#pragma once
#include "glad/glad.h"
#include <glm/glm.hpp>
#include <vector>

using namespace glm;

struct Vertex {
    vec3 position;
    vec3 normal;
    vec2 uv;

    Vertex(const vec3& p,
           const vec3& n = vec3(0),
           const vec2& t = vec2(0))
        : position(p), normal(n), uv(t) {}
};
