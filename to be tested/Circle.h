#pragma once
class Circle {
public:
	float x, y, radius;
	Circle() {}
	Circle(float _x,float _y,float _r) : x(_x),y(_y),radius(_r){}
	void set_values(float _x, float _y, float _r)
	{
		x = -x     ;
		y = _y     ;
		radius = _r;
	}
};