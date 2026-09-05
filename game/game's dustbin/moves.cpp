#include "moves.h"

 float apply_dash(float currentX, int direction)
{
		float dashDistance = 300.0f;
		//return currentX + (direction * dashDistance);
		return 3000.0f * direction; // dash speed
}


inline float get_crouch_height(float normalHeight)
{
	return normalHeight * 0.5f;
}


inline int is_attack_successful(float dist, float reach)
{
	if (dist <= reach)   return 1;
	else   return 0;
}

 void apply_knockback(float& velX, float force, int direction)
{
	velX = force * (float)direction;
}





