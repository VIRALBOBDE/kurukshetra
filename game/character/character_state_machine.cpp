#include "character_state_machine.h"

StateMachine::StateMachine() :
    current_state(IDLE),
    previous_state(IDLE)
{
}

bool StateMachine::can_transition_flow(flow_state new_flow) const
{
    {
        switch (current_flow)
        {
        case CHOOSING_ACTION_LAYER_0:
            // Layer 0 se bas Layer 1 mein ja sakte hain (Back nahi ja sakte)
            return new_flow == CHOOSING_ACTION_LAYER_1;

        case CHOOSING_ACTION_LAYER_1:
            // Layer 1 se wapas Layer 0 ja sakte hain (Back) YA Layer 2 (Confirm Action)
            return new_flow == CHOOSING_ACTION_LAYER_0 || new_flow == CHOOSING_ACTION_LAYER_2;

        case CHOOSING_ACTION_LAYER_2:
            // Layer 2 se sirf Enemy turn (GETTING_ATTACKED) par ja sakte hain
            return new_flow == GETTING_ATTACKED;

        case GETTING_ATTACKED:
            // Enemy turn khatam hone par wapas Player turn (Layer 0) shuru hoga
            return new_flow == CHOOSING_ACTION_LAYER_0;

        default:
            return false;
        }
    }
}

bool StateMachine::change_flow_state(flow_state new_flow)
{
    if (can_transition_flow(new_flow))
    {
        previous_flow = current_flow;
        current_flow = new_flow;
        return true;
    }
    return false; // Invalid movement attempt
}

bool StateMachine::go_back()
{
    if (current_flow == CHOOSING_ACTION_LAYER_1)
    {
        return change_flow_state(CHOOSING_ACTION_LAYER_0);
    }
    return false; // Baki kisi layer mein back dabana allowed nahi hai
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
bool StateMachine::can_transition(State new_state ) const
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