#pragma once

float apply_dash(float currentX, int direction);

//crouch
inline float get_crouch_height(float normalHeight);

//attack
inline int is_attack_successful(float dist, float reach);

//knockbackk
 void apply_knockback(float& velX, float force, int direction);