#include "Box.h"

Box::Box(std::string n, float _x, float _y, float w, float h) : name(n), x(_x), y(_y), width(w), height(h) {}


void Box::set_box_values(glm::vec2 bottom_coordinates, glm::vec2 top_coordinates)
{
    x = bottom_coordinates.x;
    y = bottom_coordinates.y;
    width = top_coordinates.x;
    height = top_coordinates.y;
}