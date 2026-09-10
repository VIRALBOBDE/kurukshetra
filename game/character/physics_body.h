#pragma once

class PhysicsBody
{
private:
    float velocity;
    float mass;
    float gravity;
    bool grounded;
    float drag;
    float acceleration;
    int jumpCount = 0;
    int maxJumps = 2;

public:
    PhysicsBody();

    float get_velocity() const;
    void set_velocity(float value);

    float get_mass() const;
    void set_mass(float value);

    float get_gravity() const;
    void set_gravity(float value);

    bool get_grounded() const;
    void set_grounded(bool value);

    float get_drag() const;
    void set_drag(float value);

    void apply_force(float force);
    void update(float deltaTime);
    void jump(float force);
};