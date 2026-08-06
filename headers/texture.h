#pragma once
#include <glad/glad.h>
#include <stb_image/stb_image.h>
#include <iostream>
#include <string>
#include <GLFW/glfw3.h>
#include "error.h"
class texture
{
private:
	unsigned int texture_id = 0;
	int height, width, channels , slot = -1;
public:
	texture(std::string file_name , int slot);
	texture(int width_of_image, int height_of_image , int channels_in_image , int slot);
	void update_texture(const unsigned char* data , int slot);
	void add_texture(std::string file_name, int slot);
	void bind();
	void unbind() const;
	float getheight() const  { return height; }
	float getwidth()  const  { return width; }
	unsigned int get_texture_id() const { return texture_id;  }
	~texture();

};