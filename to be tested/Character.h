#pragma once
#include"physics.h"
#include"Circle.h"
#include"Box.h"

class Character {
public:

	Box body;
	int    health = 100; // bhemm ki health 
	float  velocityY = 0;  // kudne aur girne ki speed
	bool   isGrounded = false;  //check if bheem zameen par hai ya nai
	int    jumpCount = 0;   //0=ground , 1=1st jump , 2= high jump
	bool   wReleased = true;
	bool   isStunned = false; 
	int    stunTimer = 0;      // Taki stun hamesha ke liye na rahe(time limit)

	bool   isCrouching = false;
	bool   isDashing = false;
	bool   isDefending = false;
	bool   hasAttacked = false;

	float  normalRadius;

	// Constructor : bheem ko banane ke liye (x,y,radius)
	Character() {};
	Character(float x, float y, float width , float height) : body("test character",x, y, width, height) {}

	void set_character_dimentions(float x, float y, float width, float height)
	{
		body.set_box_values({ x, y }, { width, height });
	}

	void Update() {
		if (isStunned) {
			stunTimer--;
			if (stunTimer <= 0) isStunned = false; // Stun khatam hoke player firse move karne lagega
		}
	}

	void ApplyPhysics() {
		if (isStunned) return; //freeze!! no movement

		if (!isGrounded) {
			velocityY -= 0.0008f; //gravity pull (zameen ke andar nai ghusega)
		}
		body.y += velocityY;
		body.width += velocityY;


		//20.0f -> floor level
		float floorlevel = 20.0f;
		if (body.y  <= floorlevel) {
			body.y = floorlevel ;
			body.height = floorlevel;
			velocityY = 0;
			isGrounded = true;
			jumpCount = 0;
		}
	}
		void Jump() {
			if (isStunned) return; // freezed !! no jump

			float normalJump = 0.015f;
			float highJump = 0.025f;

			if (isGrounded) {
				velocityY = normalJump;
				/*body.y += normalJump;
				body.height += normalJump;*/
				isGrounded = false;
				jumpCount = 1;
			}
			else if (jumpCount == 1) { //double jump
				velocityY = highJump;
				/*body.y += highJump;
				body.height += highJump;*/
				jumpCount = 2;
			}
		}
};