#pragma once

class Combat
{
public:

    enum Attack
    {
        NONE = 0,
        LIGHT,
        HEAVY,
        ULTIMATE,
        SPECIAL
    };

private:

    Attack current_attack;
    Attack attack_list[4];

    float stamina_consumption;
    Attack combo[5];

    float damage;

public:

    Combat();

    Attack get_current_attack() const;
    float get_stamina_consumption() const;
    float get_damage() const;

    void set_current_attack(Attack attack);
    void set_stamina_consumption(float value);
    void set_damage(float value);
};