#include "physics.h"

bool Physics::checkcollision(const Box& player, const Box& target)
{
	bool leftoverlap = player.x <= (target.x + target.width);
	bool rightoverlap = (player.x + player.width) >= target.x;
	bool bottomoverlap = player.y <= (target.y + target.height);
	bool topoverlap = (player.y + player.height) >= target.y;

	return leftoverlap && rightoverlap && bottomoverlap && topoverlap;
}


bool Physics::isColliding(const Circle& a, const Circle& b)
{

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

bool Physics::CheckCircleBox(const Circle& c, const Box& b)
{
	float closestX = std::max(b.x, std::min(c.x, b.x + b.width));
	float closestY = std::max(b.y, std::min(c.y, b.y + b.height));

	float dx = c.x - closestX;
	float dy = c.y - closestY;

	return (dx * dx + dy * dy) < (c.radius * c.radius);
}

bool Physics::isHit(Box hitbox, Box defenderhurtbox)
{
	return false;
}





