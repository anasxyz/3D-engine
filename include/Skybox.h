#pragma once

#include <glm/glm.hpp>
#include <string>
#include "Mesh.h"
#include "GLFW/WrapperGLFW.h"

class Skybox {
public:
    Skybox(GLWrapper* glw, const std::vector<std::string>& faces);
    void render(const glm::mat4& view, const glm::mat4& projection);

private:
    GLuint program;
    GLuint viewId, projectionId, samplerId;
    GLuint cubemapTexture;
    Mesh cubeMesh;
};

