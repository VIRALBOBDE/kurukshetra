#pragma once
#include "base_state.h"
#include "game_manager.h"
#include "../common data/drawing data.h"



class main_menu:public game_state
{
	int currently_chosen = 1;
	bool up_released = true;
	bool down_released = true;
	drawing_data play;
	drawing_data quit;

public:
	main_menu() {}
	
	void init(state_manager* manager) override;

	void pre_loop_function(state_manager* manager) override;

	void update(state_manager* manager, float del_time) override;

	void draw(drawing_system*  renderer) override;

	void transition() override {};

	void poll_events(GLFWwindow* window) override;

	void cleanup() override {};

	~main_menu() {};
};