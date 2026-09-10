#pragma once

struct CharacterStats
{
	float health = 1000.0f;
	float max_health = 1000.f;
	float walk_speed = 400.0f;
	float dash_speed = 800.0f;
	float jump_force = 1000.0f;
	float defence;
	float weight;
	float stamina;

	//getter
	float get_health();
	float get_max_health();
	float get_walk_speed();
	float get_jump_force();
	float get_dash_speed();
	float get_defence();
	float get_weight();
	float get_stamina();

	//setter
	void set_health(float h);
	void set_max_health(float max_h);
	void set_walk_speed(float w_sp);
	void set_jump_force(float j_fc);
	void set_dash_speed(float d_sp);
	void set_defence(float def);
	void set_weight(float wt);
	void set_stamina(float st);
};