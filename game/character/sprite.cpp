#include "sprite.h"


Sprite::Sprite() {}


Sprite::Sprite(texture* tex, float w, float h) : s_texture(tex), width(w), height(h) {}


// Getters
texture* Sprite::getTexture() const {
	return s_texture;
}

float Sprite::getWidth() const {
	return width;
}

float Sprite::getHeight() const {
	return height;
}

glm::vec4 Sprite::getColor() const {
	return color;
}

bool Sprite::getFlipHorizontal() const {
	return flipHorizontal;
}

bool Sprite::getFlipVertical() const {
	return flipVertical;
}

int Sprite::getLayer() const {
	return layer;
}

// Setters
void Sprite::setTexture(texture* tex) {
	s_texture = tex;
}

void Sprite::setWidth(float w) {
	width = w;
}

void Sprite::setHeight(float h) {
	height = h;
}

void Sprite::setColor(const glm::vec4& col) {
	color = col;
}

void Sprite::setFlipHorizontal(bool flip) {
	flipHorizontal = flip;
}

void Sprite::setFlipVertical(bool flip) {
	flipVertical = flip;
}

void Sprite::setLayer(int lyr) {
	layer = lyr;
}