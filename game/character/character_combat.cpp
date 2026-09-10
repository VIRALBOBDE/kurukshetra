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
    switch (attack)
    {
    case LIGHT:
        stamina_consumption = 25.0f;
        damage = 30.0f;
        break;

    case HEAVY:
        stamina_consumption = 40.0f;
        damage = 50.0f;
        break;

    case ULTIMATE:
    case SPECIAL:  // Dono ki values same hain toh hum inko combine kar sakte hain
        stamina_consumption = 50.0f;
        damage = 70.0f;
        break;

    case NONE:
    default:
        stamina_consumption = 0.0f;
        damage = 0.0f;
        break;
    }

}

void Combat::set_stamina_consumption(float value)
{
    stamina_consumption = value;
}

void Combat::set_damage(float value)
{
    damage = value;
}