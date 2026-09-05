#include "game manager.h"

state_manager::state_manager()
{
	current_state = nullptr;
	pending_state = nullptr;
}

state_manager::~state_manager()
{
	if (current_state)
	{
		current_state->cleanup();
	}
	if (pending_state)
	{
		pending_state->cleanup();
	}

	delete current_state;
	delete pending_state;
}

void state_manager::change_state(game_state* game_state)
{
	pending_state = game_state;
}

void state_manager::update(float delta_time)
{
	if (pending_state)
	{
		current_state->cleanup();
		delete current_state;
		current_state = pending_state;
		current_state->init();
		pending_state = nullptr;
	}
	if (current_state) current_state->update(_placeholder_);

}
