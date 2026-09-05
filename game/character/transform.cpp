#include"transform.h"

//Constructors:

// This function takes no value and assigns some predefined values
Transform::Transform()
{
	position = glm::vec2(0.0f, 0.0f);
	scale = glm::vec2(1.0f, 1.0f);
	rotation = 0.0f;

};

// This function takes values for assignment
Transform::Transform(glm::vec2 pos, glm::vec2 scl, float rot) :position(pos), scale(scl), rotation(rot) 
{

}

//getters
// positions ko fund karne ke liye function
glm::vec2 Transform::getPosition()
{
	return position;
}
// scale ya size pata karne ke liye function
glm::vec2 Transform::getScale()
{
	return scale;
}
//rotation find karne ke liye function
float Transform::getRotation()
{
	return rotation;
}


//setters
void Transform::setPosition(glm::vec2 pos)
{
	position = pos;
}
void Transform::setScale(glm::vec2 scl)
{
	scale = scl;
}
void Transform::setRotation(float rot)
{
	rotation = rot;
}


void Transform::translate(glm::vec2 offset)
{
	// Current position mein offset add kar rahe hain
	position += offset;
}

void Transform::rotate(float angle)
{
	// Current rotation mein angle add kar rahe hain
	rotation += angle;
}