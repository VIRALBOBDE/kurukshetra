#pragma once
#include<unordered_map>
#include"../../engine/animation.h"
#include<string>

class Animator
{
private:
	std::unordered_map<std::string, animation*> animations;
	animation* current = nullptr;

public:
	// animation ko state ke naam ke sath add karna hoga
	void add_animation
	(
		const std::string& state,
		texture* texture_object,
		int		total_no_of_frame_rows,
		float	frame_delay,
		glm::vec2 tile_dimentions,
		bool	is_walking = true,
		bool	ping_pong_motion = false,
		bool	full_texture = false
	);

	//to get current frame
	glm::vec4 get_current_frame();

	// active animation karne ke liye state ka naam pass karna hoga
	void play(const std::string& state);

	// Update active animation
	void update(float delta_time);

};