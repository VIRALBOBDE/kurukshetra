#include "headers/animation.h"



void animation::update(float delta_timee)
{
	delta_time = delta_timee;
	if (frames.empty()) return;
	time_lapsed += delta_time;
	
	while (time_lapsed >= frame_duration)
	{
		time_lapsed -= frame_duration;
		current_frame++;
		cout << current_frame << "\n";
		if (current_frame >= frames.size() || backward_direction == true )
		{
			if (current_frame < 2) backward_direction = false;
			else backward_direction = true;
			if (is_looping)
			{
				if (ping_pong_animation) 
				{
					if (backward_direction)
					{
						current_frame -= 2;
					}
					else  continue;
				}
				else current_frame = 0;

			}
			else current_frame = frames.size() - 1;
		}
		if (current_frame < 0) current_frame = 0;

	}
}

void animation::push(glm::vec2 indices)
{
	//temporary.texturecoordinates(indices, tile_size.x, tile_size.y, texture_size.x, texture_size.y);
	frames.push_back(subtexture2d.texturecoordinates(indices, tile_size.x, tile_size.y, texture_size.x, texture_size.y));
}

glm::vec4 const animation::get_current_frame()
{
	return frames[current_frame].get_coordinates();
}
