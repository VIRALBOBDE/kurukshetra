#include "transform.h"
#include "character_animator.h"
#include "character_combat.h"
#include "character_sprite.h"
#include "character_state_machine.h"
#include "character_stats.h"
#include "collider.h"
#include "physics_body.h"
#include "sprite.h"
#include "../common data/drawing data.h"

class character
{
	drawing_data character_drawing_data;
	Transform character_transform_data;
	Animator animations;
	Combat fight;
	Sprite appearence;
	StateMachine states;
	CharacterStats stats;
	Collider collision;
	PhysicsBody physics;

public:
	character() {};
	
	void update_character_positions(glm::vec2 positions);
	void update_character_scale(glm::vec2 scale);
	void update_rotation(float rotation);



};