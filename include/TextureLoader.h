#pragma once
#include <iostream>
#include <string>
#include "glad/glad.h"

class TextureLoader {
public:
	static GLuint loadTexture(const std::string &path);
};
