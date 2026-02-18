#pragma once
#include <glad/glad.h>
#include <stb_image/stb_image.h>
#include <iostream>
#include <string>
#include <GLFW/glfw3.h>
class texture
{
private:
	unsigned int texture_id = 0;
	int height, width, channels;
public:
	texture(std::string file_name , int slot);
	void bind(unsigned int slot);
	void unbind() const;
	float getheight() { return height; }
	float getwidth() { return width; }
	~texture();

};