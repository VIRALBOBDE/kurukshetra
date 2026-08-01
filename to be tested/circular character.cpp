#include "circular character.h"

Character::Character(float x, float y, float r) : body(x, y, r), normalRadius(r) {}

void Character::Update()
{
	if (isStunned) {
		stunTimer--;
		if (stunTimer <= 0) isStunned = false; // Stun khatam hoke player firse move karne lagega
	}
}



void Character::death_circle()
{
	if (health <= 0)
	{
		body.radius = 0;
	}
}



void Character::ApplyPhysic(float deltaTime)
{
	if (isStunned) return; //freeze!! no movement

	if (!isGrounded) {
		velocityY -= 0.0008f; //gravity pull (zameen ke andar nai ghusega)
	}
	body.y += velocityY;


	//-0.9f -> floor level
	float floorlevel = -0.9f;
	if (body.y - body.radius <= floorlevel) {
		body.y = floorlevel + body.radius;
		velocityY = 0;
		isGrounded = true;
		jumpCount = 0;
	}

	//x-axis
	if (dashTimer > 0.0f)
	{
		dashTimer -= deltaTime;
		if (dashTimer <= 0.0f)
		{
			dashTimer = 0.0f;
			isGhostMode = false; // ghost mode khatam
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
}



void Character::Jump()
{
	if (isStunned) return; // freezed !! no jump

	float normalJump = 0.015f;
	float highJump = 0.025f;

	if (isGrounded) {
		velocityY = normalJump;
		isGrounded = false;
		jumpCount = 1;
	}
	else if (jumpCount == 1) { //double jump
		velocityY = highJump;
		jumpCount = 2;
	}
}



