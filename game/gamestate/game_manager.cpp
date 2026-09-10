#include "game_manager.h"

state_manager::state_manager()
{
	current_state = nullptr;
	pending_state = nullptr;
	video = new video_player;
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

void state_manager::initialize(game_state* game_state)
{
	current_state = game_state;
	video->initialize();
	renderer->set_shader("resources/shaders/default.shader");
	current_state->init(this);
}

void state_manager::pre_loop_functions()
{
	if (current_state) current_state->pre_loop_function(this);
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
		current_state->init(this);
		pending_state = nullptr;
	}
	if (current_state) current_state->update(this , delta_time);
}

void state_manager::draw()
{
	if (current_state )current_state->draw(renderer);
}

void state_manager::poll_event()
{
	if (current_state) current_state->poll_events(window, this);
}


