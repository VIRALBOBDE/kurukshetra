#pragma once
#include "base_state.h"
#include "../../engine/drawing system.h"
#include "../../engine/video.h"
#include "../../engine/window.h"

class state_manager
{
	game_state* current_state;
	game_state* pending_state;
	renderer2D* drawer = new renderer2D(1280, 720, "kurukshetra");

public:

	drawing_system* renderer = new drawing_system(*drawer);
	video_player* video;
	GLFWwindow* window = renderer->get_window_address();

	state_manager();
	~state_manager();

	void initialize(game_state* game_state);

	void pre_loop_functions();

	void change_state(game_state* game_state);

	void update(float delta_time);

	void draw();

	void poll_event();

};