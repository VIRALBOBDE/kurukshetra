#include "headers/common.h"

void insert(float num, int size, vertex& v)
{
		int limit = size / sizeof(vertex);
		for (int i = 0; i < limit; i++)
		{
			v.coordinate = glm::vec2(num);
			v.rgba_value = glm::vec4(num);
			v.texturecoordinates = glm::vec2(num);
			v.texture_index = 0.0f;
		}
}
