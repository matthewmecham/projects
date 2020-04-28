#include <iostream>
#include <math.h>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <fstream>
#include <time.h>
using namespace std;

//This Class is everything to do with generating a Character object. 
//This is the oject that the User will create and battle with
//Derived from this base Character Class will be 3 individuals: Barbarian, Rogue, Knight
//The purpose of this hierachy is to define a unique character object that can be then
//be sent to a battle class in order to fight other character objects.

class Character
{
    public:
        Character(); //default constructor
        //Constructor with arguments
        Character(char * name, int hp,int current_hp, int def, int str, int spd, int wep_dmg, int lvl, int attack_marg);
        Character(const Character & to_copy); //Copy Constructor
        virtual ~Character(); //destructor

        void    change_name(const char * newName);
        void    display_name() const;
        void    display_health() const;
        void    display_all() const;
        void    take_damage(int damage);
        void    heal(int heal);
        void    full_heal();
        int     health() const;
        int     check_level() const;
        int     attack() const;
        int     check_speed() const;
        bool    is_dead() const;

        // Virtual function declarations
        virtual bool    start_vanish();
        virtual bool    end_vanish();
        virtual bool    start_rage();
        virtual bool    end_rage();
        virtual void    level_up();
        virtual int     super_heal();
    protected:
        char    * name;
        int     max_health;
        int     current_health;
        int     defense;
        int     speed;
        int     strength;
        int     weapon_damage;
        int     level;
        int     attack_margin;
};

// This class is a Barbarian. As such, it will have higher base HP and Attack than the other classes
// It's special ability is Barbarian Rage, which increases attack power at the cost of defense for a short period
// of time. 
class Barbarian: public Character
{
    public:
        Barbarian();
        Barbarian(float hpMod, float defMod, float strMod, float spdMod, float wepMod, int attackMod);
        Barbarian(const Barbarian & to_copy);

        bool    start_rage();
        bool    end_rage();
        void    level_up();
        int     class_id();
    private:
        float   healthMod;
        float   defenseMod;
        float   strengthMod;
        float   speedMod;
        float   weaponMod;
        int     attackBonus;
};

// The knight will have high defense values.
// Special Ability: Heal
class Knight: public Character
{
    public:
        Knight();
        Knight(float hpMod, float defMod, float strMod, float spdMod, float wepMod, int attackMod);
        Knight(const Knight & to_copy);

        int     super_heal();
        void    level_up();
        int     class_id();
    private:
        float   healthMod;
        float   defenseMod;
        float   strengthMod;
        float   speedMod;
        float   weaponMod;
        int     attackBonus;
};

// The rogue has middling stats but has high speed and a high variance in weapon damage - essentially an RNG heavy character
// Special Ability: Stealth - while stealthed the rogue cannot be hit. After emerging from stealth,
// the rogue will do bonus damage.
class Rogue: public Character
{
    public:
        Rogue();
        Rogue(float hpMod, float defMod, float strMod, float spdMod, float wepMod, int attackMod, bool stealth);
        Rogue(const Rogue & to_copy);

        bool    start_vanish();
        bool    end_vanish();
        void    level_up();
        int     class_id() const;
    private:
        float   healthMod;
        float   defenseMod;
        float   strengthMod;
        float   speedMod;
        float   weaponMod;
        int     attackBonus;
        bool    is_stealth;
};
