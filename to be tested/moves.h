#pragma once

inline float apply_dash(float currentX, int direction)
{
	float dashDistance = 0.5f;
	return currentX + (direction * dashDistance);
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