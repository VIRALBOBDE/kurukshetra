#pragma once

class StateMachine
{
public:

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

private:

    State current_state;
    State previous_state;

public:

    StateMachine();

    void change_states(State new_state);
    bool can_transition(State new_state) const;
    void update();

    State get_current_state() const;
    State get_previous_state() const;
}; 
