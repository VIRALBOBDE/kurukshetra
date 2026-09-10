#pragma once
#include "../common data/drawing data.h"
#include "../../engine/drawing system.h"


class state_manager;
struct GLFWwindow;

class game_state
{
public:      
	game_state() { }

	virtual void init(state_manager* manager) = 0;
	virtual void pre_loop_function(state_manager* manager) = 0;
	virtual void update(state_manager* manager , float delta_time) = 0;
	virtual void draw(drawing_system* renderer) = 0;
	virtual void transition() = 0;
	virtual void cleanup() = 0;
	virtual void poll_events(GLFWwindow* window, state_manager* manager) = 0;

	virtual ~game_state() = default;	

};