#pragma once
#include "glad/glad.h"
#include "iostream"
#include "fstream"
#include "string"
#include "sstream"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "error.h"
class shader
{
private:
	unsigned int ids[2];
	unsigned int program_id = 0;
public:
	shader(std::string filename);
	void use();
	void setsampler(std::string name, int data);
	void setsamplermatrix(std::string name_of_matrix , glm::mat4& matrix);
	unsigned int getid() const { return program_id; }
	~shader();
};