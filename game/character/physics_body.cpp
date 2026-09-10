#include "physics_body.h"
#include <algorithm>

PhysicsBody::PhysicsBody() :
    velocity(0.0f),
    mass(1.0f),
    gravity(-2900.0f),
    acceleration(0.0f),
    grounded(false),
    drag(0.0f)
{
}

float PhysicsBody::get_velocity() const
{
    return velocity;
}

void PhysicsBody::set_velocity(float value)
{
    velocity = value;
}

float PhysicsBody::get_mass() const
{
    return mass;
}

void PhysicsBody::set_mass(float value)
{
    mass = value;
}

float PhysicsBody::get_gravity() const
{
    return gravity;
}

void PhysicsBody::set_gravity(float value)
{
    gravity = value;
}

bool PhysicsBody::get_grounded() const
{
    return grounded;
}

void PhysicsBody::set_grounded(bool value)
{
    grounded = value;

    if (grounded)
    {
        jumpCount = 0;
    }
}

float PhysicsBody::get_drag() const
{
    return drag;
}

void PhysicsBody::set_drag(float value)
{
    drag = value;
}

void PhysicsBody::apply_force(float force)
{
    acceleration += force / mass;
}

void PhysicsBody::update(float deltaTime)
{
    if (!grounded)
    {
        acceleration += gravity;
    }

    velocity += acceleration * deltaTime;

    if (drag > 0.0f)
    {
        velocity *= std::max(0.0f, 1.0f - drag * deltaTime);
    }

    acceleration = 0.0f;
}

void PhysicsBody::jump(float force)
{
    if (jumpCount < maxJumps)
    {
        velocity = force;
        grounded = false;
        jumpCount++;
    }
}
