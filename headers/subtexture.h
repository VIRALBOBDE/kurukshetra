#pragma once
#include <glm/glm.hpp>  // GLM library ke saare core types (vec2, vec3, mat4) ke liye
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "texture.h"
class animation;
class subtexture 
{
private:
	glm::vec4 coordinates;

public:

	subtexture(glm::vec4 coordinate = { 0.0f,0.0f,0.0f,0.0f }) : coordinates(coordinate) {}
	void set_coordinates(glm::vec4 coordinates);
	glm::vec4 texturecoordinates(glm::vec2 indices, float tile_width, float tile_height, float sheetheight, float sheetwidth);
	glm::vec4 const get_coordinates() { return coordinates; }
};