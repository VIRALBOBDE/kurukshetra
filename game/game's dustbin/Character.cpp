#include "Character.h"

void BoxCharacter::set_animations(int index_i, int index_j)
{
	for (int i{ 0 }; i < index_j; i++)
	{
		character_animations[i]->push({ index_i , i });
	}
}

void BoxCharacter::set_animations(int animation_no , int row, int column, int total_no_of_rows_in_the_sprite_sheet, float delay_to_implement, glm::vec2 sprite_dimentions, bool to_loop, bool ping_pong_loping, bool no_looping)
{
	
	character_animations[animation_no] = new animation;
	character_animations[animation_no]->set_vals
	(
		renderer->get_texture_address(texture_no),
		total_no_of_rows_in_the_sprite_sheet,
		delay_to_implement,
		sprite_dimentions,
		to_loop,
		ping_pong_loping,
		no_looping
	);

	for (int i{ 0 }; i < column; i++)
	{
		character_animations[animation_no]->push({ row , i });
	}

}

void BoxCharacter::draw(glm::vec4 rgb_values , glm::vec4 texture_coordinates)
{

	renderer->draw_quad
	(
		{ sprite_coordinates.x , sprite_coordinates.y },
		{ sprite_coordinates.z , sprite_coordinates.w },
		rgb_values,
		texture_coordinates,
		this->texture_no
	);
}

BoxCharacter::BoxCharacter(GLFWwindow* window, float x, float y, float width, float height) :
	body("test character", x, y, width, height),
	hurtbox("hurtbox", x, y, width, height),
	hitbox("hitbox", x, y, width, height),
	window(window)
{
	attacks.push_back({ 30.0f, 20.0f, 20.0f, 20.0f, 10.0f }); // Punch
	attacks.push_back({ 60.0f, 10.0f, 50.0f, 50.0f, 30.0f }); // Gada

	sprite_coordinates = glm::vec4(x, y, width, height);
	//hurtbox_coordinates = sprite_coordinates;

}

BoxCharacter::BoxCharacter(int texture_index , renderer2D* renderer_address, glm::vec4 character_coordinates_width_and_height, glm::vec4 hurt_box_values)
{
	texture_no = texture_index;
	renderer = renderer_address;
	sprite_coordinates = character_coordinates_width_and_height;
	hurtbox.x = hurt_box_values.x;
	hurtbox.y = hurt_box_values.y;
	hurtbox.width = hurt_box_values.z;
	hurtbox.height = hurt_box_values.w;
	character_animations.resize(20);
}




glm::vec4 BoxCharacter::get_current_animation()
{

	return character_animations[current_state]->get_current_frame();
}

void BoxCharacter::apply_knockback(float force, int direction)
{
	velocityX = force * (float)direction;
	isStunned = true;
	stunTimer = 0.5f;
}




void BoxCharacter::set_character_dimentions(float x, float y, float width, float height)
{
	body.set_box_values({ x, y }, { width, height });
}




bool BoxCharacter::death()
{
	if (health <= 0)
	{
		body.x = body.width = body.height = body.y = 0;
		return true;
	}
	return false;
}




void BoxCharacter::Update(float deltaTime, BoxCharacter& enemy)
{
	sprite_coordinates.x = body.x;
	sprite_coordinates.y = body.y;
	sprite_coordinates.z = body.width;
	sprite_coordinates.w = body.height;

	hurtbox.y = sprite_coordinates.y;
	hurtbox.x = sprite_coordinates.x + (body.width - hurtbox.width) / 2.0f;
	hurtbox.width = body.width * 0.8f;
	hurtbox.height = body.height * 0.9f;

	body.height = normalHeight;
	isCrouching = false;



	switch (current_state)
	{
	case IDLE:

		isCrouching = false;
		if (!isGrounded) current_state = JUMPING;
		break;

	case WALKING:

		if (!isGrounded) current_state = JUMPING;
		if (std::abs(velocityX) < 0.1f) current_state = IDLE;
		break;

	case JUMPING:

		std::cout << "State = JUMPING\n";
		if (isGrounded) current_state = IDLE;
		break;

	case CROUCHING:

		body.height = normalHeight * 0.5f;
		hurtbox.height = body.height * 0.9f;
		isCrouching = true;
		break;

	case DASHING:

		isGhostMode = true;
		dashTimer -= deltaTime;
		if (dashTimer <= 0.0f)
		{
			isGhostMode = false;
			velocityX = 0.0f;
			current_state = IDLE;
		}
		break;

	case ATTACKING:
	{
		// vector se attack data uthao
		float offX = attacks[current_attack][0];
		float offY = attacks[current_attack][1];
		float hWidth = attacks[current_attack][2];
		float hHeight = attacks[current_attack][3];

		// agar right dekh raha hai: Normal Offset
		if (isFacingRight)
		{
			hitbox.x = sprite_coordinates.x + offX;
		}
		// agar left dekh raha hai: Reverse Offset 
		else
		{
			// sprite ke start se peeche jao offset jitna, 
			// phir hitbox ki width bhi peeche karo taaki woh body ke bahar rahe
			hitbox.x = sprite_coordinates.x - offX - hWidth;
		}

		// y axis aur size set karo (Y axis flip nahi hota)
		hitbox.y = sprite_coordinates.y + offY;
		hitbox.width = hWidth;
		hitbox.height = hHeight;

		// timer aur window Logic 
		attack_delta_time -= deltaTime;

		if (attack_delta_time < 0.3f && attack_delta_time > 0.1f)
		{
			hitbox.isActive = true;
		}
		else hitbox.isActive = false;

		if (attack_delta_time <= 0.0f) current_state = IDLE;

		// Hit Check
		if (!hasDealtDamage && Physics::checkcollision(hitbox, enemy.hurtbox))
		{
			std::cout << "HIT" << std::endl;
			enemy.health -= 20;
			hasDealtDamage = true; // No spamming

			// Knockback ( 30% chance)
			if (rand() % 100 < 30)
			{
				int dir = (body.x + body.width * 0.5f < enemy.body.x + enemy.body.width * 0.5f) ? 1 : -1;
				apply_knockback(500.0f, dir);

				enemy.isStunned = true;
				enemy.stunTimer = 0.5f;
			}
		}
		break;
	}
	case DEFENDING:

		isDefending = true;
		velocityX = 0.0f;
		break;

	case STUNNED:

		stunTimer -= deltaTime;
		if (stunTimer <= 0.0f) {
			isStunned = false;
			current_state = IDLE;
		}

		break;

	case HURT:

		hurtTimer -= deltaTime;
		if (hurtTimer <= 0.0f) {
			current_state = IDLE;
		}
		break;

	case DEAD:

		health = 0;
		velocityX = 0.0f;
		break;
	}

	modelMatrix = glm::mat4(1.0f); // Reset
	modelMatrix = glm::translate(modelMatrix, glm::vec3(body.x, body.y, 0.0f));

	// Agar Bheem Left dekh raha hai, toh flip karo
	if (!isFacingRight) {
		modelMatrix = glm::scale(modelMatrix, glm::vec3(-1.0f, 1.0f, 1.0f));
	}

}






void BoxCharacter::UpdatedPhysics(float deltaTime)
{
	//y-axis
	if (!isGrounded)
	{
		velocityY += gravity * deltaTime;  //niche aayega
	}

	body.y += velocityY * deltaTime;     // velocity change hui to position bhi change hogi

	if (body.y <= floorY)
	{
		body.y = floorY;     // floor pe ayega
		velocityY = 0.0f;   // movement stop ho jayegi
		isGrounded = true; // grounded
		jumpCount = 0;    // jump resest ho jayega
	}

	//x-axis

	if (dashTimer > 0.0f)
	{
		dashTimer -= deltaTime;
		if (dashTimer <= 0.0f)
		{
			dashTimer = 0.0f;
			isGhostMode = false; // ghost mode khatam
			velocityX = 0.0f; // speed reset ho jayegi
		}
	}
	if (currentCooldown > 0.0f)
	{
		currentCooldown -= deltaTime;
		if (currentCooldown <= 0.0f)
		{
			currentCooldown = 0.0f;
			canDash = true;
		}
	}
	float direction = (velocityX > 0) ? 1.0f : -1.0f;

	if (std::abs(velocityX) > 0.1f)
	{
		body.x += velocityX * deltaTime; // x position change hogi
		velocityX *= 0.9f; // speed gradually kam hogi(friction)

		velocityX -= resistance * deltaTime * direction; // air resistance apply hoga
		if (std::abs(velocityX) < walkSpeed)
		{
			velocityX = walkSpeed * direction; // speed reset ho jayegi
		}
	}
	if (body.x < 0) body.x = 0.0f; // left wall
	if (body.x + body.width > 1280) body.x = 1280 - body.width; // right wall

}




bool BoxCharacter::Jump(float deltatime)
{
	if (isStunned) return false; // freezed !! no jump

	if (isGrounded || jumpCount < 2)   //double jump 
	{
		velocityY = jumpForce;    // upar ki taraf force
		isGrounded = false;
		jumpCount++;
		return true;
	}
	std::cout << "Jump Success\n";
	return false;
}

