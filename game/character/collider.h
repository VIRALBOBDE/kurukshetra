#pragma once

#include "../game's dustbin/Box.h"
#include <glm/glm.hpp>
#include "../physics.h"

class Collider
{
private:
    Box hurtbox;
    Box hitbox;

    glm::vec2 previous_position;
    bool initialized = false;

    bool isActive = true;

public:
    Collider();

    Box& get_hurtbox();
    Box& get_hitbox();

    void set_hurtbox(const Box& box);
    void set_hitbox(const Box& box);

    void update(float x, float y);

    bool intersects(const Collider& other) const;
}; 
