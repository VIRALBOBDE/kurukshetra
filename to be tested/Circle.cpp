#include "Circle.h"

Circle::Circle(float _x, float _y, float _r)
	: x(_x), y(_y), radius(_r){}


void Circle::set_values(float _x, float _y, float _r)
{
	x = -x;
	y = _y;
	radius = _r;
}
