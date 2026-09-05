#pragma once
#include <iostream>
#include "../physics.h"
#include "Box.h"
#include "moves.h"

#include "../../engine/renderer.h"
#include "../../engine/animation.h"
#include <vector>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class BoxCharacter
{

public:
	GLFWwindow* window = NULL ;
	renderer2D* renderer = NULL ;
	Box body;

	int    health = 1000; // bhemm ki health 
	int    jumpCount = 0;   //0=ground , 1=1st jump , 2= high jump
	int    current_attack = 0;
	int    texture_no = 0 ;

	float  hurtTimer = 0.0f;
	float  stunTimer = 0.0f;      // Taki stun hamesha ke liye na rahe(time limit)
	float  jumpForce = 1000.0f;
	float  velocityY = 0.0f;  // kudne aur girne ki speed
	float  gravity = -2900.0f;
	float  floorY = 100.0f;
	float  walkSpeed = 400.0f;
	float  dashTimer = 0.5f;
	float  currentCooldown = 2.0f;
	float  playerReach = 50.0f;
	float  getXvalue;
	float  velocityX = 0.0f;
	float  resistance = 200.0f; // air resistance for dash
	float  dashSpeed = 800.0f;
	float  normalRadius;
	float  normalHeight = 220.0f;
	float  attack_delta_time = 0.0f;
	float  bheemCenter;
	float  duryodhanCenter;

	bool   wReleased = true;
	bool   sReleased = true;
	bool   shiftpressed = false;
	bool   spacepressed = false;
	bool   isGrounded = false;  //check if bheem zameen par hai ya nai
	bool   isStunned = false;
	bool   isCrouching = false;
	bool   isDashing = false;
	bool   canDash = true;
	bool   isGhostMode = false;
	bool   isDefending = false;
	bool   hasAttacked = false;
	bool   isHitboxActive = false;
	bool   hasDealtDamage = false;
	bool   isFacingRight = true;


	Box    hurtbox;
	Box    hitbox;

	std::vector<std::vector<float>> attacks;

	enum State
	{
		IDLE = 0,
		WALKING = 1,
		JUMPING = 2,
		CROUCHING = 3,
		DASHING = 4,
		ATTACKING = 5,
		DEFENDING = 6,
		STUNNED = 7,
		HURT = 8,
		DEAD = 9
	};

	State current_state;

	glm::vec4 sprite_coordinates;
	//glm::vec4 hurtbox_coordinates;

	glm::mat4 modelMatrix;

	std::vector<animation*> character_animations;



	// Constructor : bheem ko banane ke liye 
	BoxCharacter() {};

	BoxCharacter(GLFWwindow* window, float x, float y, float width, float height);
	BoxCharacter(int texture_no , renderer2D* renderer_address, glm::vec4 character_coordinates_width_and_height , glm::vec4 hurt_box_values );

	//setting animations
	void set_animations(int index_i, int index_j);
	void set_animations(int animation_no , int row, int column, int total_no_of_rows_in_the_sprite_sheet, float delay_to_implement, glm::vec2 sprite_dimentions, bool to_loop, bool ping_pong_loping, bool no_looping);

	// draw character
	void draw(glm::vec4 rgb_values , float delta_time);
	void draw(glm::vec4 rgb_values , glm::vec4 current_animations);

	glm::vec4 get_current_animation();

	// KnockBack apply karne ke liye function
	void apply_knockback(float force, int direction);

	//character ki positions set karne ke liye funciton
	void set_character_dimentions(float x, float y, float width, float height);

	// character mara ya nahi wo dekhne ke liye function
	bool death();

	// character ki saari values ko upadate karne ke liye function
	void Update(float deltaTime, BoxCharacter& enemy);

	// character ke physics ko update karne ke liye function
	void UpdatedPhysics(float deltaTime);

	// character ko jump karane ke liye function
	bool Jump(float deltatime);











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