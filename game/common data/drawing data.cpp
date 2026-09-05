#include "drawing data.h"

drawing_data::drawing_data()
{

}

drawing_data::drawing_data(glm::vec2 bottom_left_corner, glm::vec2 top_right_corner, glm::vec4 default_rgba_value, glm::vec4 texture_coordinates, float texture_ka_index) :
	left_bottom_corner(bottom_left_corner) ,
	right_top_corner ( top_right_corner ) ,
	rgba_value(default_rgba_value) , 
	texturecoordinates ( texture_coordinates ),
	texture_index(texture_ka_index)
{

}
