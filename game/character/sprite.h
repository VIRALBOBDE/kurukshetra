#pragma once
#include"../../engine/texture.h"
#include<glm/glm.hpp>
class Sprite
{
private:
	float width = 0.0f;
	float height = 0.0f;
	texture* s_texture = nullptr;
	bool flipHorizontal = false;
	bool flipVertical = false;
	int layer = 0;
	glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

public:
	Sprite();

	Sprite(texture* tex, float w, float h);

	// Getters
	texture* getTexture() const;
	float getWidth() const;
	float getHeight() const;
	glm::vec4 getColor() const;
	bool getFlipHorizontal() const;
	bool getFlipVertical() const;
	int getLayer() const;

	// Setters
	void setTexture(texture* tex);
	void setWidth(float w);
	void setHeight(float h);
	void setColor(const glm::vec4& col);
	void setFlipHorizontal(bool flip);
	void setFlipVertical(bool flip);
	void setLayer(int lyr);
};