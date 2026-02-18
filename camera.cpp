#include "headers/camera.h"

camera::camera(float width, float height)
{
	projection = glm::ortho(0.0f, width, 0.0f, height, -1.0f, 1.0f);
	view = glm::mat4(1.0f); 
	view = glm::translate(glm::mat4(1.0f), -camera_position);
	view_projection = projection * view;
}

void camera::viewmatrix(glm::vec3 changed_camera_pos)
{
	camera_position = changed_camera_pos;
	view            = glm::translate(glm::mat4(1.0f), -changed_camera_pos);
	view_projection = projection * view;
}
