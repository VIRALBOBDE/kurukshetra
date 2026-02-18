#include "headers/texture.h"

texture::texture(std::string file_name , int slot)
{
	
	stbi_set_flip_vertically_on_load(1);
	const char* filename = file_name.c_str();
	unsigned char* data  = stbi_load(filename, &width, &height, &channels, 4);

	//CHECKER
	if (!data) {
		// YE LINE TUJHE ASLI SACH BATAYEGI:
		std::cout << "[STB ERROR]: " << stbi_failure_reason() << " | Path: " << file_name << std::endl;
		__debugbreak();
	}
	else
	{
		glGenTextures    (1, &texture_id);
		glActiveTexture  (GL_TEXTURE0 + slot);
		glBindTexture    (GL_TEXTURE_2D , texture_id);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER , GL_LINEAR         );
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER , GL_LINEAR         );
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S     , GL_CLAMP_TO_EDGE  );
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T     , GL_CLAMP_TO_EDGE  );
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(data);
		glBindTexture(GL_TEXTURE_2D, 0);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

}

void texture::bind(unsigned int slot)
{
	if (texture_id == 0) glGenTextures(1, &texture_id);
	glActiveTexture  (GL_TEXTURE0 + slot);
	glBindTexture    (GL_TEXTURE_2D, texture_id);
}

void texture::unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

texture::~texture()
{
	glDeleteTextures  ( 1 , &texture_id );
}