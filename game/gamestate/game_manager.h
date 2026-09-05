#pragma once
#include "base state.h"

class state_manager
{
	game_state* current_state;
	game_state* pending_state;

public:
	state_manager();

	~state_manager();

	void change_state(base_state * game_state);

	void update();

	void render();

};