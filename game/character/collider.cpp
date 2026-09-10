#include "collider.h"

Collider::Collider()
{
}

Box& Collider::get_hurtbox()
{
    return hurtbox;
}

Box& Collider::get_hitbox()
{
    return hitbox;
}

void Collider::set_hurtbox(const Box& box)
{
    hurtbox = box;
}

void Collider::set_hitbox(const Box& box)
{
    hitbox = box;
}

void Collider::update(float x, float y)
{
    if (!initialized)
    {
        previous_position = glm::vec2(x, y);
        initialized = true;
        return;
    }

    float dx = x - previous_position.x;
    float dy = y - previous_position.y;

    hurtbox.x += dx;
    hurtbox.y += dy;

    hitbox.x += dx;
    hitbox.y += dy;

    previous_position = glm::vec2(x, y);
}

bool Collider::intersects(const Collider& other) const
{
    if (!hitbox.isActive || !other.hurtbox.isActive)
        return false;

    return Physics::checkcollision(hitbox, other.hurtbox);
}