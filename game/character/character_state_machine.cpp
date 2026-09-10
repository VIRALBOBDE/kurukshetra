#include "character_state_machine.h"

StateMachine::StateMachine() :
    current_state(IDLE),
    previous_state(IDLE)
{
}

void StateMachine::change_states(State new_state)
{
    if (!can_transition(new_state))
    {
        return;
    }

    previous_state = current_state;
    current_state = new_state;

}
bool StateMachine::can_transition(State new_state) const
{
    switch (current_state)
    {
    case IDLE:
        return new_state == WALKING ||
            new_state == JUMPING ||
            new_state == CROUCHING ||
            new_state == ATTACKING ||
            new_state == DEFENDING ||
            new_state == DASHING;

    case WALKING:
        return new_state == IDLE ||
            new_state == JUMPING ||
            new_state == CROUCHING ||
            new_state == ATTACKING ||
            new_state == DEFENDING ||
            new_state == DASHING;

    case JUMPING:
        return new_state == IDLE ||
            new_state == ATTACKING ||
            new_state == HURT ||
            new_state == STUNNED;

    case CROUCHING:
        return new_state == IDLE ||
            new_state == WALKING ||
            new_state == ATTACKING;

    case DASHING:
        return new_state == IDLE ||
            new_state == HURT ||
            new_state == STUNNED;

    case ATTACKING:
        return new_state == IDLE ||
            new_state == HURT ||
            new_state == STUNNED;

    case DEFENDING:
        return new_state == IDLE ||
            new_state == WALKING ||
            new_state == HURT ||
            new_state == STUNNED;

    case STUNNED:
        return new_state == IDLE ||
            new_state == HURT ||
            new_state == DEAD;

    case HURT:
        return new_state == IDLE ||
            new_state == STUNNED ||
            new_state == DEAD;

    case DEAD:
        return false;
    }

    return false;
}

void StateMachine::update()
{
    switch (current_state)
    {
    case IDLE:
        break;

    case WALKING:
        break;

    case JUMPING:
        break;

    case CROUCHING:
        break;

    case DASHING:
        break;

    case ATTACKING:
        break;

    case DEFENDING:
        break;

    case STUNNED:
        break;

    case HURT:
        break;

    case DEAD:
        break;
    }
}
StateMachine::State StateMachine::get_current_state() const
{
    return current_state;
}

StateMachine::State StateMachine::get_previous_state() const
{
    return previous_state;
}