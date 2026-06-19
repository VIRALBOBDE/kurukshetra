#include "headers/animation.h"



void animation::update(float delta_timee)
{
	delta_time = delta_timee;
	if (frames.empty()) return;
	time_lapsed += delta_time;
	
	while (time_lapsed >= frame_duration)
	{
		time_lapsed -= frame_duration;
		//cout << current_frame << "\n";  // used for debugging
		current_frame++;
		if (current_frame >= frames.size() || backward_direction == true)
		{
			/*cout << "flag 1st if\n";*/
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
		else if (current_frame >= frames.size() && is_looping == false) current_frame = frames.size() - 1;
		if (current_frame < 0) current_frame = 0;

	}
}

void animation::push(glm::vec2 indices)
{
	//temporary.texturecoordinates(indices, tile_size.x, tile_size.y, texture_size.x, texture_size.y);
	if (no_of_frame_rows < indices.x)
	{
		cerr << "\nno. of frame rows is more than the number of frame rows provided in the object";
		__debugbreak();
	}
	else frames.push_back(subtexture2d.texturecoordinates({ indices.y ,(no_of_frame_rows - indices.x) - 1 }, tile_size.x, tile_size.y, texture_size.x, texture_size.y));
}

glm::vec4 const animation::get_current_frame()
{
	return frames[current_frame].get_coordinates();
}
