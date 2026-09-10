#pragma once
#include "base_state.h"
#include "game_manager.h"
#include "../common data/drawing data.h"


enum Input
{
	NONE,
	UP,
	DOWN,
	LEFT,
	RIGHT,
	SHIFT,
	ENTER
};


class fight_scene : public game_state
{


	//drawing data for the engine
	drawing_data bheem;
	drawing_data duryodhan;



	Input current_selection = NONE;
	Input previous_selection = NONE;

	void execute_selection();

	

public:
	//constructors
	fight_scene() {};

	// mandatory functions
	void init(state_manager* manager) override {};
	void pre_loop_function(state_manager* manager) override {};
	void update(state_manager* manager, float delta_time) override {};
	void draw(drawing_system* renderer) override {};
	void transition() override {};
	void cleanup() override {};
	void poll_events(GLFWwindow* window, state_manager* manager) override ;
	
	//destructros
	~fight_scene() {};
};