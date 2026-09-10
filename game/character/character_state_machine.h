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

    enum flow_state
    {
        CHOOSING_ACTION_LAYER_0 = 0, // Skills / Items / High-Risk
        CHOOSING_ACTION_LAYER_1,     // Light / Heavy / Ult (Sub-menu)
        CHOOSING_ACTION_LAYER_2,     // Action executing (Locked in)
        GETTING_ATTACKED
    };

private:

    State current_state;
    State previous_state;

    flow_state current_flow;
    flow_state previous_flow;

public:

    StateMachine();

    // Action Flow Methods
    bool can_transition_flow(flow_state new_flow) const;
    bool change_flow_state(flow_state new_flow);
    bool go_back(); // Back button handle karne ke liye

    flow_state get_current_flow() const;

    void change_states(State new_state);
    bool can_transition(State new_state) const;
    void update();

    State get_current_state() const;
    State get_previous_state() const;
}; 
