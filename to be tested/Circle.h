#pragma once
class Circle {
public:
	float x, y, radius;
	Circle() {}
	Circle(float _x, float _y, float _r);
	void set_values(float _x, float _y, float _r);
};