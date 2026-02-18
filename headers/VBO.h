#pragma once
#include <glad/glad.h>

class vbo
{
	unsigned int id=0;
public:
	vbo() {};
	vbo(float* array, int size);
	void bind();
	void unbind();
	void loaddata(float* array, int size);
	~vbo();
};