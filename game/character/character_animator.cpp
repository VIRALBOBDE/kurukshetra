#include "character_animator.h"


void Animator::add_animation(const std::string& state, texture* texture_object,
	int		total_no_of_frame_rows,
	float	frame_delay,
	glm::vec2 tile_dimentions,
	bool	is_walking ,
	bool	ping_pong_motion,
	bool	full_texture 
)
{

	auto it = animations.find(state);
	
	if (it == animations.end())
	{
		animations.emplace(state , new animation (texture_object , total_no_of_frame_rows , frame_delay , tile_dimentions , is_walking , ping_pong_motion , full_texture));
	}
	else
	{
		delete it->second;
		it->second = new animation(texture_object, total_no_of_frame_rows, frame_delay, tile_dimentions, is_walking, ping_pong_motion, full_texture);
	}
}

void Animator::play(const std::string& state)
{
	auto it = animations.find(state);

	if (it != animations.end())
	{
		current = it->second;
	}
	else
	{
		cout << "couldn't find the animation you want \npotential suspect:- check the place where you added the animation";
		__debugbreak();
	}
}

void Animator::update(float delta_time)
{
	if (current != nullptr)
	{
		current->update(delta_time);
	}
}

glm::vec4 Animator::get_current_frame()
{
	if (current != nullptr)
	{
		return current->get_current_frame();
	}
	else
	{
		return glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
	}
}