#include "headers/IBO.h"

ibo::ibo(unsigned int* array, int size)
{
	glGenBuffers(1, &ibo_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER , ibo_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER , size, array, GL_DYNAMIC_DRAW);
}

void ibo::bind()
{
	if (ibo_id == 0)      glGenBuffers(1 , &ibo_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER , ibo_id);
}

void ibo::unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER , 0);
}

void ibo::loaddata(unsigned int* array, int size)
{
	bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, array, GL_DYNAMIC_DRAW);
}

ibo::~ibo()
{
	glDeleteBuffers(1, &ibo_id);
}