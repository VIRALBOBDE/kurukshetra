#include "Character.h"

BoxCharacter::BoxCharacter(GLFWwindow* window, float x, float y, float width, float height) :
	body("test character", x, y, width, height),
	hurtbox("hurtbox", x, y, width, height),
	hitbox("hitbox", x, y, width, height),
	window(window)
{
	attacks.push_back({ 30.0f, 20.0f, 20.0f, 20.0f, 10.0f }); // Punch
	attacks.push_back({ 60.0f, 10.0f, 50.0f, 50.0f, 30.0f }); // Gada

	sprite_coordinates = glm::vec4(x, y, width, height);
	hurtbox_coordinates = sprite_coordinates;

}

BoxCharacter::BoxCharacter(renderer2D* renderer , GLFWwindow* window, glm::vec4 sprite_coordinates, glm::vec4 hurtbox_coordinates)
{
	this->renderer = renderer;
	this->sprite_coordinates = sprite_coordinates;
	this->hurtbox_coordinates = hurtbox_coordinates;
}

void BoxCharacter::draw(glm::vec4 rgb_values)
{
	renderer->draw_quad({sprite_coordinates.x,sprite_coordinates.y} , { sprite_coordinates.z,sprite_coordinates.w } , rgb_values , /*animation[current_state]*/ , )
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




void BoxCharacter::Update(float deltaTime)
{
	sprite_coordinates.x = body.x;
	sprite_coordinates.y = body.y;
	sprite_coordinates.z = body.width;
	sprite_coordinates.w = body.height;

	hurtbox_coordinates.y = sprite_coordinates.y;
	hurtbox_coordinates.x = sprite_coordinates.x + (body.width - hurtbox.width) / 2.0f;
	hurtbox.width = body.width * 0.8f;
	hurtbox.height = body.height * 0.9f;

	body.height = normalHeight;

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

		if (isGrounded) current_state = IDLE;
		break;

	case CROUCHING:

		body.height = normalHeight * 0.5f;
		velocityX = 0.0f;

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
		// Vector se Attack Data uthao
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




void BoxCharacter::Jump(float deltatime)
{
	if (isStunned) return; // freezed !! no jump

	if (isGrounded || jumpCount < 2)   //double jump 
	{
		velocityY = jumpForce;    // upar ki taraf force
		isGrounded = false;
		jumpCount++;
	}
}