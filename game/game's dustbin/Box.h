#pragma once // Isse file sirf ek baar include hogi
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Box {
public:
    float x, y, width, height;
	bool isActive = true;
    std::string name;

    Box() {}
    Box(std::string n, float _x, float _y, float w, float h);

    void set_box_values(glm::vec2 bottom_coordinates, glm::vec2 top_coordinates);
    
};