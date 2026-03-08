#pragma once
#include <glad/glad.h>
#include <iostream>
#include "error.h"

class ibo
{
private:
	unsigned int ibo_id = 0;
public:
	ibo() {}
	ibo(unsigned int* array, int size);
	void loaddata(unsigned int* array, int size);
	void bind();
	void unbind();
	~ibo();
};