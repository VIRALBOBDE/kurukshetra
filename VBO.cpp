#include "headers/VBO.h"

vbo::vbo(float* array , int size)
{
	glGenBuffers(1, &id);
	glBindBuffer(GL_ARRAY_BUFFER, id);
	glBufferData(GL_ARRAY_BUFFER, size, array, GL_DYNAMIC_DRAW);
}

void vbo::bind()
{
	if (id == 0) glGenBuffers(1, &id);
	glBindBuffer(GL_ARRAY_BUFFER, id);
}

void vbo::unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void vbo::loaddata(float* array , int size)
{
	bind();
	glBufferData(GL_ARRAY_BUFFER, size, array, GL_DYNAMIC_DRAW);
}

vbo::~vbo()
{
	glDeleteBuffers(1, &id);
}
