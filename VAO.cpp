#include "headers/VAO.h"

vao::vao()
{
	 glGenVertexArrays(1, &id); 
	 glBindVertexArray(id);
}

vao::vao(int slot_no, int no_of_vertices, int stride, int first_elements_place , bool normalized)
{
	if (id==0) glGenVertexArrays(1, &id);
	glBindVertexArray(id);
	glVertexAttribPointer(slot_no, no_of_vertices, GL_FLOAT,(normalized==false)?GL_FALSE:GL_TRUE, sizeof(float) * stride, (void*)(first_elements_place * sizeof(float)));
	glEnableVertexAttribArray(slot_no);
}

void vao::bind()
{
	if (id == 0) glGenVertexArrays(1, &id);
	glBindVertexArray(id);
}

void vao::unbind()
{
	glBindVertexArray(0);
}

void vao::loaddata(int slot_no, int no_of_vertices, int stride, int first_elements_place, bool normalized)
{
	bind();
	glVertexAttribPointer(slot_no, no_of_vertices, GL_FLOAT, (normalized == false) ? GL_FALSE : GL_TRUE, sizeof(float) * stride, (void*)(first_elements_place * sizeof(float)));
	glEnableVertexAttribArray(slot_no);
}

vao::~vao()
{
	glDeleteVertexArrays(1, &id);
}


