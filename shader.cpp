#include "headers/shader.h"
#include <filesystem>

shader::shader(std::string filename)
{
	enum class shadertype
	{
		none = -1 , vertex = 0 , fragment = 1
	};
	
	std::cout << "\nTrying to open: " << filename << std::endl;

	std::ifstream     readdata(filename, std::ios::binary);
	std::ifstream test("resources/shaders/default.shader");
	std::string       readingline;
	std::stringstream strings[2];
	shadertype        khatka = shadertype::none;

	//working directory ka location
	/*std::cout << std::filesystem::current_path() << std::endl;   TELLS WORKING DIRECTORY */


	//checking if file opened or not

	/*if (!readdata.is_open())									   FILE CHECKER
	{
		throw std::runtime_error("Failed to open shader file");
	}*/

	/*if (test)                                                     FILE CHECKER
		std::cout << "FOUND\n";
	else
		std::cout << "NOT FOUND\n";


	if (readdata.is_open())                                         FILE CHECKER
		std::cout << "FILE OPENED SUCCESSFULLY\n";
	else
		std::cout << "FILE FAILED TO OPEN\n";*/

	while (std::getline(readdata, readingline))
	{
		if (readingline.find("#shader") != std::string::npos)
		{
			if (readingline.find("vertex") != std::string::npos)
				khatka = shadertype::vertex;
			else if (readingline.find("fragment") != std::string::npos)
				khatka = shadertype::fragment;
		}
		else if (khatka != shadertype::none)
			strings[(int)khatka] << readingline << "\n";
	}
	std::string svertex = strings[0].str();
	const char*  vertex = svertex.c_str();

	std::string sfragment = strings[1].str();
	const char*  fragment = sfragment.c_str();

	ids[0]     = glCreateShader(GL_VERTEX_SHADER);
	ids[1]     = glCreateShader(GL_FRAGMENT_SHADER);
	program_id = glCreateProgram();
	GLcall(glShaderSource(ids[0], 1, &vertex , NULL));
	GLcall(glShaderSource(ids[1], 1, &fragment, NULL));
	GLcall(glCompileShader(ids[0]));
	GLcall(glCompileShader(ids[1]));
	GLcall(glAttachShader(program_id, ids[0]));
	GLcall(glAttachShader(program_id, ids[1]));
	GLcall(glLinkProgram(program_id));
	GLcall(glDeleteShader(ids[0]));
	GLcall(glDeleteShader(ids[1]));

	//checking if shader compiled properly
	/*int success;
	char infoLog[512];

	glGetShaderiv(ids[0], GL_COMPILE_STATUS, &success);                SHADER CHECKER
	if (!success)
	{
		glGetShaderInfoLog(ids[0], 512, NULL, infoLog);
		std::cout << "Vertex Shader Error:\n" << infoLog << std::endl;
	}*/

	/*glGetShaderiv(ids[1], GL_COMPILE_STATUS, &success);               SHADER CHECKER
	if (!success)
	{
		glGetShaderInfoLog(ids[1], 512, NULL, infoLog);
		std::cout << "Fragment Shader Error:\n" << infoLog << std::endl;
	}*/



	//checking if program linked properly                        LINKER CHECKER
	/*glGetProgramiv(program_id, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(program_id, 512, NULL, infoLog);
		std::cout << "Program Link Error:\n" << infoLog << std::endl;
	}*/

}

void shader::use()
{
	GLcall(glUseProgram(program_id));
}

void shader::setsampler(std::string name , int data)
{
	const char* sampler  = name.c_str();
	unsigned int address = glGetUniformLocation(program_id, sampler);
	GLcall(glUniform1i(address, data));
}

void shader::setsamplermatrix(std::string name_of_matrix , glm::mat4& matrix)
{
	unsigned int address = glGetUniformLocation(program_id, name_of_matrix.c_str());
	GLcall(glUniformMatrix4fv(address, 1, GL_FALSE, &matrix[0][0]));
}

shader::~shader()
{
	GLcall(glDeleteProgram(program_id));
}