#include "headers/VBO.h"




vbo::vbo(int size)
{
	glGenBuffers(1, &id);
	GLcall(glBindBuffer(GL_ARRAY_BUFFER, id));
	GLcall(glBufferData(GL_ARRAY_BUFFER, size, NULL , GL_DYNAMIC_DRAW));
}

void vbo::bind()
{
	if (id == 0)
	{
		cout << "NO VBO!!!\n";
		GLcall(glGenBuffers(1, &id));
	}
	GLcall(glBindBuffer(GL_ARRAY_BUFFER, id));
}

void vbo::unbind()
{
	GLcall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

float* vbo::get_data_from_vram(float* array, int size)
{
	bind();
	glBindBuffer(GL_ARRAY_BUFFER, id);
	glGetBufferSubData(GL_ARRAY_BUFFER, 0, size , array);
	return array;
}

vbo::~vbo()
{
	GLcall(glDeleteBuffers(1, &id));
}
