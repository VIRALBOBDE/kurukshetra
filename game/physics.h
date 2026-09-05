#pragma once
#include "game's dustbin/Box.h"
#include "game's dustbin/circle.h"
#include<algorithm> // max aur min ke liye


class Physics {
public:
	//-----------AABB vs AABB (box to box)---------
	static bool checkcollision(const Box& player, const Box& target);

	//--------------circle vs circle---------------------
	static bool isColliding(const Circle& a, const Circle& b);

	//------------circle to box(clamping logic)-----------
	static bool CheckCircleBox(const Circle& c, const Box& b);

	bool isHit(Box hitbox, Box defenderhurtbox);
};

