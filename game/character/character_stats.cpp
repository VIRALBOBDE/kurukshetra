#include "Character_stats.h"

float CharacterStats::get_health()
{
	return health;
}

float CharacterStats::get_max_health()
{
	return max_health;
}

float CharacterStats::get_walk_speed()
{
	return walk_speed;
}

float CharacterStats::get_jump_force()
{
	return jump_force;
}

float CharacterStats::get_dash_speed()
{
	return dash_speed;
}

float CharacterStats::get_defence()
{
	return defence;
}

float CharacterStats::get_weight()
{
	return weight;
}

float CharacterStats::get_stamina()
{
	return stamina;
}

void CharacterStats::set_health(float h)
{
	health = h;
}

void CharacterStats::set_max_health(float max_h)
{
	max_health = max_h;
}

void CharacterStats::set_walk_speed(float w_sp)
{
	walk_speed = w_sp;
}

void CharacterStats::set_jump_force(float j_fc)
{
	jump_force = j_fc;
}

void CharacterStats::set_dash_speed(float d_sp)
{
	dash_speed = d_sp;
}

void CharacterStats::set_defence(float def)
{
	defence = def;
}

void CharacterStats::set_weight(float wt)
{
	weight = wt;
}

void CharacterStats::set_stamina(float st)
{
	stamina = st;
}
