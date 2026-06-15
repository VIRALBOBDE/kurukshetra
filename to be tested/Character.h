#pragma once
#include"physics.h"
#include"Circle.h"
#include"Box.h"
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
	float  velocityY = 0;  // kudne aur girne ki speed
	bool   isGrounded = false;  //check if bheem zameen par hai ya nai
	int    jumpCount = 0;   //0=ground , 1=1st jump , 2= high jump
	bool   wReleased = true;
	bool   sReleased = true;
	bool   shiftpressed = false;
	bool   spacepressed = false;
	bool   isStunned = false; 
	int    stunTimer = 0;      // Taki stun hamesha ke liye na rahe(time limit)

	bool   isCrouching = false;
	bool   isDashing = false;
	bool   isDefending = false;
	bool   hasAttacked = false;

	float  normalRadius;

	// Constructor : bheem ko banane ke liye (x,y,radius)
	BoxCharacter() {};
	BoxCharacter(GLFWwindow* winodow ,float x, float y, float width , float height) : body("test character",x, y, width, height),window(winodow) {}

	void set_character_dimentions(float x, float y, float width, float height)
	{
		body.set_box_values({ x, y }, { width, height });
	}
	void death()
	{
		if (health <= 0)
		{
			body.x=body.width=body.height=body.y = 0;
		}
	}

	void Update() {
		if (isStunned) {
			stunTimer--;
			if (stunTimer <= 0) isStunned = false; // Stun khatam hoke player firse move karne lagega
		}
	}

	/*void draw(glm::vec4 r_g_b_values, glm::vec2 texture_indices, int texture_slot , renderer2D& renderer)
	{
		renderer.draw_quad({ body.x,body.y }, { body.x + body.width + 10.0f , body.y + body.height + 10.0f }, r_g_b_values, texture_indices, texture_slot);
	}*/

	void ApplyPhysics(BoxCharacter& target) {
		if (isStunned) return; //freeze!! no movement
		float oldpos = body.y;

		if (!isGrounded) 
		{
			if (!checkcollision(body, target.body))
			{
				velocityY -= 0.08f;
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
	}
		void Jump(float deltatime) {
			if (isStunned) return; // freezed !! no jump

			float normalJump = 300.0f*deltatime;
			float highJump   = 50.0f * deltatime;

			if (isGrounded) {
				velocityY += normalJump;
				//body.y += normalJump;
				isGrounded = false;
				jumpCount = 1;
			}
			else if (jumpCount == 1) { //double jump
				velocityY += highJump;
				//body.y += highJump;
				//body.height += highJump;
				jumpCount = 2;
			}
		}
};