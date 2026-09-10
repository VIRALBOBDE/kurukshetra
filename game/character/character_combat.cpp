#include "character_combat.h"

Combat::Combat()
    : current_attack(NONE),
    stamina_consumption(0.0f),
    damage(0.0f)
{
    for (int i = 0; i < 4; i++)
    {
        attack_list[i] = NONE;
    }

    for (int i = 0; i < 5; i++)
    {
        combo[i] = NONE;
    }
}



Combat::Attack Combat::get_current_attack() const
{
    return current_attack;
}

float Combat::get_stamina_consumption() const
{
    return stamina_consumption;
}

float Combat::get_damage() const
{
    return damage;
}



void Combat::set_current_attack(Attack attack)
{
    current_attack = attack;
}

void Combat::set_stamina_consumption(float value)
{
    stamina_consumption = value;
}

void Combat::set_damage(float value)
{
    damage = value;
}