#include<iostream>
#include<glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class drawing_data
{
public:
	glm::vec2 left_bottom_corner;
	glm::vec2 right_top_corner;
	glm::vec4 rgba_value;
	glm::vec4 texturecoordinates;
	float texture_index;


	// Constructors
	drawing_data();
	drawing_data(glm::vec2 bottom_left_corner, glm::vec2 top_right_corner, glm::vec4 default_rgba_value, glm::vec4 texture_coordinates, float texture_ka_index);

};