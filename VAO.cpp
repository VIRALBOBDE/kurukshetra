#include "headers/VAO.h"

vao::vao()
{
	 GLcall(glGenVertexArrays(1, &id));
	 GLcall(glBindVertexArray(id));
}

vao::vao(int slot_no, int no_of_vertices, int stride, int first_elements_place , bool normalized)
{
	if (id==0) glGenVertexArrays(1, &id);
	GLcall(glBindVertexArray(id));
	GLcall(glVertexAttribPointer(slot_no, no_of_vertices, GL_FLOAT,(normalized==false)?GL_FALSE:GL_TRUE, stride , (void*)first_elements_place));
	GLcall(glEnableVertexAttribArray(slot_no));
}

void vao::bind()
{
	if (id == 0) glGenVertexArrays(1, &id);
	GLcall(glBindVertexArray(id));
}

void vao::unbind()
{
	GLcall(glBindVertexArray(0));
}

void vao::loaddata(int slot_no, int no_of_vertices, int stride, int first_elements_place, bool normalized)
{
	bind();
	GLcall(glVertexAttribPointer(slot_no, no_of_vertices, GL_FLOAT, (normalized == false) ? GL_FALSE : GL_TRUE, sizeof(float) * stride, (void*)(first_elements_place * sizeof(float))));
	GLcall(glEnableVertexAttribArray(slot_no));
}

vao::~vao()
{
	GLcall(glDeleteVertexArrays(1, &id));
}


