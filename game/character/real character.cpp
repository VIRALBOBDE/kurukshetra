#include "real character.h"

void character::update_character_positions(glm::vec2 positions)
{
	character_transform_data.translate(positions);
}

void character::update_character_scale(glm::vec2 scale)
{
	character_transform_data.resize(scale);
}

void character::update_rotation(float rotation)
{
	character_transform_data.rotate(rotation);
}
