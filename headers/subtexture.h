#pragma once
#include "texture.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class subtexture
{
private:
	texture& l_texture;
	glm::vec2 tilesize;
	float sheetheight, sheetwidth, spriteheight, spritewidth;
	int tileheight;
public:
	subtexture(texture& tex, glm::vec2 tiledim);
	void texturecoordinates(glm::vec2 indices, glm::vec2* coordinates);
};