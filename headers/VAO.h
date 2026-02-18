#pragma once
#include <glad/glad.h>
class vao
{
private:
	unsigned int id = 0;
public:
	vao();
	vao(int slot_no, int no_of_vertices , int stride , int first_elements_place , bool normalized);
	void bind();
	void unbind();
	void loaddata(int slot_no, int no_of_vertices, int stride, int first_elements_place , bool normalized);
	~vao();
};