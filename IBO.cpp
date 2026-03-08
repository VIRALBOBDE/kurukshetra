#include "headers/IBO.h"

ibo::ibo(unsigned int* array, int size)
{
	GLcall(glGenBuffers(1, &ibo_id));
	GLcall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER , ibo_id));
	GLcall(glBufferData(GL_ELEMENT_ARRAY_BUFFER , size, array, GL_DYNAMIC_DRAW));
}

void ibo::bind()
{
	if (ibo_id == 0)      GLcall(glGenBuffers(1 , &ibo_id));
	GLcall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER , ibo_id));
}

void ibo::unbind()
{
	GLcall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER , 0));
}

void ibo::loaddata(unsigned int* array, int size)
{
	bind();
	GLcall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, array, GL_DYNAMIC_DRAW));
}

ibo::~ibo()
{
	GLcall(glDeleteBuffers(1, &ibo_id));
}