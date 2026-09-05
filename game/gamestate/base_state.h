#pragma once

class state_manager;

class game_state
{
private:
	state_manager* manager;

public:      
	game_state(state_manager* state_manager):
		manager(state_manager) { }

	virtual void init() = 0;
	virtual void update(float delta_time) = 0;
	virtual void draw() = 0;
	virtual void transition() = 0;
	virtual void cleanup() = 0;

	virtual ~game_state() = default;	

};