#pragma once
#include <glad/glad.h>
#include "error.h"

class vbo
{
	unsigned int id=0;
public:

	//  NORMAL FUNCTIONS

	vbo() {};
	vbo(int size);
	void bind();
	void unbind();
	float* get_data_from_vram(float* array, int size);
	


	//   TEMPLATE FUNCTIONS

	template<typename T>
	vbo(T* array, int size)
	{
		glGenBuffers(1, &id);
		GLcall(glBindBuffer(GL_ARRAY_BUFFER, id));
		GLcall(glBufferData(GL_ARRAY_BUFFER, sizeof(T) * size, array, GL_DYNAMIC_DRAW));
	}
	
	template<typename T>
	void loaddata(T* array, int size)
	{
		bind();
		GLcall(glBufferData(GL_ARRAY_BUFFER, sizeof(T) * size, array, GL_DYNAMIC_DRAW));
	}

	
	void subdata(void* array, int size)
	{
		bind();
		GLcall(glBufferSubData(GL_ARRAY_BUFFER, 0, size, array));
	}

	//   DESTRUCTOR

	~vbo();

};