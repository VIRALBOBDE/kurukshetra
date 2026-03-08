#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct vertex
{
	glm::vec2 coordinate;
	glm::vec4 rgba_value;
	glm::vec2 texturecoordinates;
	float texture_index;
};

void insert(float num, int size, vertex& v);