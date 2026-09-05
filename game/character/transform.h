#pragma once
#include <glm/glm.hpp>

class Transform
{
private:
	glm::vec2 position;
	glm::vec2 scale;  //size
	float rotation;

public:
	Transform();

	Transform(glm::vec2 pos, glm::vec2 scl, float rot);

	//getters
	glm::vec2 getPosition();
	glm::vec2 getScale();
	float getRotation();

	//setters
	void setPosition(glm::vec2 pos);
	void setScale(glm::vec2 scl);
	void setRotation(float rot);

	void translate(glm::vec2 offset);
	void rotate(float angle);
};