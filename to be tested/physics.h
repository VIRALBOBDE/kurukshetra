#pragma once
#include "Box.h"
#include "circle.h"
#include<algorithm> // max aur min ke liye



    //-----------AABB vs AABB (box to box)---------
static bool checkcollision(const Box& bheem, const Box& target) {
	bool leftoverlap = bheem.x <= (target.x + target.width);
	bool rightoverlap = (bheem.x + bheem.width) >= target.x+1 ;
	bool bottomoverlap = bheem.y-1 <= (target.y + target.height);
	bool topoverlap = (bheem.y + bheem.height) >= target.y+1;

	return leftoverlap && rightoverlap && bottomoverlap && topoverlap;
    }

    //--------------circle vs circle---------------------
	static bool isColliding(const Circle& a , const Circle& b) {

		//1. center ke bich ka difference
		float dx = a.x - b.x;
		float dy = a.y - b.y;

		//2. pythagoras use karke distance ka square
		float distanceSquared = (dx * dx) + (dy * dy);

		//3. dono radius ke sum ka square 
		float radiusSum = a.radius + b.radius;
		float radiusSumSquared = radiusSum * radiusSum;

		//4. comparison : if distance,radius ke sum se kam hai toh,collision hua hai..
		if (distanceSquared < radiusSumSquared) {
			return true;
		}
		return false;
	}

	//------------circle to box(clamping logic)-----------
	static bool CheckCircleBox(const Circle& c, const Box& b) {
		float closestX = std::max(b.x, std::min(c.x, b.x + b.width));
		float closestY = std::max(b.y, std::min(c.y, b.y + b.height));

		float dx = c.x - closestX;
		float dy = c.y - closestY;

		return (dx * dx + dy * dy) < (c.radius * c.radius);
	}
