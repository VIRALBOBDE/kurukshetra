#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class camera
{
private:
	glm::vec3 camera_position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 projection;
	glm::mat4 view ;
	glm::mat4 view_projection;
public:
	camera(float width, float height);
	void viewmatrix(glm::vec3 changed_camera_pos);
	glm::mat4 view_projection_matrix() { return view_projection; }
};
