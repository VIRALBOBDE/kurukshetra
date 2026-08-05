#pragma once

float apply_dash(float currentX, int direction)
{
	float dashDistance = 300.0f;
	//return currentX + (direction * dashDistance);
	return 3000.0f * direction; // dash speed
}

//crouch
inline float get_crouch_height(float normalHeight);

//attack
inline int is_attack_successful(float dist, float reach);

//knockbackk
 void apply_knockback(float& velX, float force, int direction);