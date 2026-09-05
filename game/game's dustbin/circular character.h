#pragma once
#include"../physics.h"
#include"Circle.h"

struct Character {
	Circle body;
public:
	int    health = 100; // bhemm ki health 
	float  velocityY = 0;  // kudne aur girne ki speed
	bool   isGrounded = false;  //check if bheem zameen par hai ya nai
	int    jumpCount = 0;      //0=ground , 1=1st jump , 2= high jump
	bool   wReleased = true;
	bool   isStunned = false;
	int    stunTimer = 0;      // Taki stun hamesha ke liye na rahe(time limit)
	float  walkSpeed = 400.0f;
	float  dashTimer = 0.5f;   // 0.2s ka ghost mode
	bool   canDash = true;
	float  currentCooldown = 2.0f;   //wait time for dash to be available again
	bool   isGhostMode = false;

	bool   isCrouching = false;
	bool   isDashing = false;
	bool   isDefending = false;
	bool   hasAttacked = false;


	float  normalRadius;

	// Constructor : bheem ko banane ke liye (x,y,radius)
	Character(float x, float y, float r);

	void Update();

	void death_circle();

	void ApplyPhysic(float deltaTime);
		
	void Jump();
};