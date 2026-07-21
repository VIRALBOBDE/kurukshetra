#pragma once
#include"physics.h"
#include"Circle.h"
#include"Box.h"
#include"moves.h"
#include"map.h"
#include <GLFW/glfw3.h>
//#include "headers/renderer.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class BoxCharacter {
public:
	GLFWwindow* window;
	Box body;
	int    health = 100; // bhemm ki health 
	float  velocityY = 0.0f;  // kudne aur girne ki speed
	bool   isGrounded = false;  //check if bheem zameen par hai ya nai
	int    jumpCount = 0;   //0=ground , 1=1st jump , 2= high jump
	bool   isStunned = false;
	int    stunTimer = 0;      // Taki stun hamesha ke liye na rahe(time limit)
	float  jumpForce = 1000.0f;
	float  gravity = -2900.0f;
	float  floorY = 100.0f;
	float  walkSpeed = 400.0f;
	bool   canDash = true;
	float  dashTimer = 0.5f;
	float  currentCooldown = 2.0f;
	bool   isGhostMode = false;
	float  playerReach = 50.0f;


	float  getXvalue;
	float  velocityX = 0.0f;
	float  resistance = 200.0f; // air resistance for dash
	float  dashSpeed = 800.0f;


	bool   wReleased = true;
	bool   sReleased = true;
	bool   shiftpressed = false;
	bool   spacepressed = false;
	bool   isCrouching = false;
	bool   isDashing = false;
	bool   isDefending = false;
	bool   hasAttacked = false;


	float  bheemCenter;
	float  duryodhanCenter;

	Box  hurtbox;
	Box  hitbox;


	float  normalRadius;
	float  normalHeight = 220.0f;

	// Constructor : bheem ko banane ke liye (x,y,radius)
	BoxCharacter() {};
	BoxCharacter(GLFWwindow* window, float x, float y, float width, float height) : body("test character", x, y, width, height), hurtbox("hurtbox", x, y, width, height), hitbox("hitbox", x, y, width, height), window(window) {}

	void set_character_dimentions(float x, float y, float width, float height)
	{
		body.set_box_values({ x, y }, { width, height });
	}
	bool death()
	{
		if (health <= 0)
		{
			body.x = body.width = body.height = body.y = 0;
			return true;
		}
		else return false;
	}

	void Update()
	{
		hurtbox.x = body.x;
		hurtbox.y = body.y;
		hurtbox.width = body.width;
		hurtbox.height = body.height;

		if (isStunned)
		{
			stunTimer--;
			if (stunTimer <= 0) isStunned = false; // Stun khatam hoke player firse move karne lagega
		}
	}

	void UpdatedPhysics(float deltaTime)
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

		if (std::abs(velocityX) >= walkSpeed)
		{
			body.x += velocityX * deltaTime; // x position change hogi

			velocityX -= resistance * deltaTime * direction; // air resistance apply hoga
			if (std::abs(velocityX) < walkSpeed)
			{
				velocityX = walkSpeed * direction; // speed reset ho jayegi
			}
		}
		if (body.x < 0) body.x = 0.0f; // left wall
		if (body.x + body.width > 1280) body.x = 1280 - body.width; // right wall

	}
	void Jump(float deltatime)
	{
		if (isStunned) return; // freezed !! no jump

		if (isGrounded || jumpCount < 2)   //double jump 
		{
			velocityY = jumpForce;    // upar ki taraf force
			isGrounded = false;
			jumpCount++;
		}
	}















	/*void draw(glm::vec4 r_g_b_values, glm::vec2 texture_indices, int texture_slot , renderer2D& renderer)
{
	renderer.draw_quad({ body.x,body.y }, { body.x + body.width + 10.0f , body.y + body.height + 10.0f }, r_g_b_values, texture_indices, texture_slot);
}*/

/*void ApplyPhysics(BoxCharacter& target) {
	if (isStunned) return; //freeze!! no movement
	float oldpos = body.y;

	if (!isGrounded)
	{
		if (!checkcollision(body, target.body))
		{
			velocityY -= 0.09f;
			body.y += velocityY;
		}
		else
		{
			isGrounded = true;
			velocityY = 0;
			body.y = oldpos;
		}
		//gravity pull (zameen ke andar nai ghusega)
	}
	//body.width += velocityY;


	//20.0f -> floor level
	float floorlevel = 20.0f;
	if (body.y  <= floorlevel) {
		body.y = floorlevel ;
		//body.height = floorlevel;
		velocityY = 0;
		isGrounded = true;
		jumpCount = 0;
	}
}*/
};