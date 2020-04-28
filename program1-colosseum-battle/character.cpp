#include "character.h"

//-----------------------------------------------------------------------------------
//Character Class constructors, destructor, and methods
//-----------------------------------------------------------------------------------

//Default Constructor sets everything to zero equiv
Character::Character():name(NULL),max_health(300),current_health(300),defense(10),speed(10),
    strength(10),weapon_damage(10),level(0), attack_margin(2)
{
}

//Constructor with params - the subclasses will use this to set unique starting stats
Character::Character(char * name, int hp,int current_hp, int def, int spd, int str,int wep_dmg, int lvl, int attack_mar):name{new char[strlen(name) + 1]},
    max_health(hp),
    current_health(current_hp),
    defense(def),
    speed(spd),
    strength(str),
    weapon_damage(wep_dmg),
    level(lvl),
    attack_margin(attack_mar)
{
    strcpy(this->name, name);
}

//Copy constructor - don't want them shallow copies, now do we?
Character::Character(const Character & to_copy)
{
    name = new char[strlen(to_copy.name) + 1];
    strcpy(name,to_copy.name);
    max_health = to_copy.max_health;
    current_health = to_copy.current_health;
    defense = to_copy.defense;
    speed = to_copy.speed;
    strength = to_copy.strength;
    weapon_damage = to_copy.weapon_damage;
    level = to_copy.level;
}

//Desctructor - frees name
Character::~Character()
{
    delete [] name;
    name = NULL;
}

//Changes the name...
void Character::change_name(const char * newName)
{
    if(name)
        delete [] name;

    name = new char[strlen(newName)+1];
    strcpy(name,newName);
}

//Displays Name
void Character::display_name() const
{
    int length = 0;
    length = strlen(name);
    for(int i = 0; i < length; i++)
        cout << name[i];
}

//Displays Health
void Character::display_health() const
{
    cout << current_health << "/" << max_health;
}

//Displays Character's Member - like that guy in the park....
void Character::display_all() const
{
    cout << "Name:       ";
    display_name();
    cout << endl;
    cout << "Health:     ";
    display_health();
    cout << endl;
    cout << "Defense:    " << defense << endl;
    cout << "Speed:      " << speed << endl;
    cout << "Strength:   " << strength << endl;
    cout << "Damage:     " << weapon_damage << endl;
    cout << "Level:      " << level << endl << endl;
}

//I will be passing in the attack() as the argument and it will subtract whatever attack() calculates from health
//Pretty dang simply function
void Character::take_damage(int damage)
{
    current_health = current_health - (damage / (defense * 0.25));
}

//Pretty Similar to the last one. Battle Class will have a random heal amount between rounds that I will pass into this puppy.
void Character::heal(int heal)
{
    current_health = current_health + heal;
    if (current_health >= max_health)
        current_health = max_health;
}

void Character::full_heal()
{
    current_health = max_health;
}

int Character::health() const
{
    return current_health;
}

//Returns level to insure that the user can fight an appropriatey leveled opponent.
int Character::check_level() const
{
    return level;
}

//This cutie will return your base weapon damage plus a random number like a dice roll
int Character::attack() const
{
    srand(time(NULL)); //makes it actually random
    return weapon_damage + (rand()%attack_margin + 1) + (strength * 0.25);
}

// Getter for speed
int Character::check_speed() const
{
    return speed;
}
// Simple function to check if my character is dead
bool Character::is_dead() const
{
    if(current_health <= 0)
        return true;
    else 
        return false;
}

//----------------------------------------------------------------------------------
// Virtual Func Declarations - they will be blank for base class -- Allows for dynamic binding
// --------------------------------------------------------------------------------

bool Character::start_vanish()
{
    return true;
}

bool Character::end_vanish()
{
    return true;
}

bool Character::start_rage()
{
    return true;
}

bool Character::end_rage()
{
    return true;
}

void Character::level_up()
{
    return;
}

int Character::super_heal()
{
    return 0;
}

//-----------------------------------------------------------------------------------
//Barbarian Class constructors and methods
//-----------------------------------------------------------------------------------

Barbarian::Barbarian():Character(),healthMod(1.4),defenseMod(1.1),strengthMod(1.4),speedMod(1.1),
    weaponMod(1.2),attackBonus(2)
{
    char temp[] = "Barbarian";
    change_name(temp);
}

Barbarian::Barbarian(float hpMod, float defMod, float strMod, float spdMod, float wepMod, int attackMod):Character(), healthMod(hpMod), defenseMod(defMod), strengthMod(strMod), speedMod(spdMod), weaponMod(wepMod), attackBonus(attackMod)
{
}

Barbarian::Barbarian(const Barbarian & to_copy):Character(to_copy)
{
    healthMod = to_copy.healthMod;
    defenseMod = to_copy.defenseMod;
    strengthMod = to_copy.strengthMod;
    speedMod = to_copy.speedMod;
    weaponMod = to_copy.weaponMod;
    attackBonus = to_copy.attackBonus;
}

//A function to significantly increase Barbarian damage while sacrificing defense
bool Barbarian::start_rage()
{
    strength = strength * 3;
    defense = defense / 2;
    return true;
}

//This function resets barbarian rage
bool Barbarian::end_rage()
{
    strength = strength / 3;
    defense = defense * 2;
    return false;
}

// Specifically levels up the barbarian
void Barbarian::level_up()
{
    max_health *= healthMod;
    defense *= defenseMod;
    strength *= strengthMod;
    speed *= speedMod;
    weapon_damage *= weaponMod;
    attack_margin += attackBonus;
    level++;
}

//This function will let me know what class my object is
int Barbarian::class_id()
{
    return 1;
}

//------------------------------------------------------------------
//Knight Class constructors and methods
//------------------------------------------------------------------

Knight::Knight():Character(),healthMod(1.2),defenseMod(1.4),strengthMod(1.2),speedMod(1.2),weaponMod(1.4),attackBonus(3)
{
    char temp[] = "Knight";
    change_name(temp);
}

Knight::Knight(float hpMod, float defMod, float strMod, float spdMod, float wepMod, int attackMod):Character(), healthMod(hpMod), defenseMod(defMod), strengthMod(strMod), speedMod(spdMod), weaponMod(wepMod), attackBonus(attackMod)
{
}

// Provides a means for the knight to heal during combat.
int Knight::super_heal()
{
    current_health = current_health + (50 * (defense / 10));
    if(current_health >= max_health)
        current_health = max_health;
    return (50 * (defense/2));
}

Knight::Knight(const Knight & to_copy):Character(to_copy)
{
    healthMod = to_copy.healthMod;
    defenseMod = to_copy.defenseMod;
    strengthMod = to_copy.strengthMod;
    speedMod = to_copy.speedMod;
    weaponMod = to_copy.weaponMod;
    attackBonus = to_copy.attackBonus;
}

void Knight::level_up()
{
    max_health *= healthMod;
    defense *= defenseMod;
    strength *= strengthMod;
    speed *= speedMod;
    weapon_damage *= weaponMod;
    attack_margin += attackBonus;
    level++;
}

// A way to know what class my object is if needed - Now I know about RTTI, though it isn't always ideal
int Knight::class_id()
{
    return 2;
}

//------------------------------------------------------------------
//Rogue Class constructors and methods
//------------------------------------------------------------------

Rogue::Rogue():Character(),healthMod(1.2),defenseMod(1.1),strengthMod(1.2),speedMod(1.4),weaponMod(1.3),attackBonus(7),is_stealth(false) 
{
    char temp[] = "Rogue";
    change_name(temp);
}

Rogue::Rogue(float hpMod, float defMod, float strMod, float spdMod, float wepMod, int attackMod, bool stealth):Character(), healthMod(hpMod), defenseMod(defMod), strengthMod(strMod), speedMod(spdMod), weaponMod(wepMod), attackBonus(attackMod), is_stealth(stealth)
{
}

Rogue::Rogue(const Rogue & to_copy):Character(to_copy)
{
    healthMod = to_copy.healthMod;
    defenseMod = to_copy.defenseMod;
    strengthMod = to_copy.strengthMod;
    speedMod = to_copy.speedMod;
    weaponMod = to_copy.weaponMod;
    attackBonus = to_copy.attackBonus;
    is_stealth = to_copy.is_stealth;
}

// This begins the rogues special move where he vanishes and can't be struck. Their attack margin is greatly increase too
bool Rogue::start_vanish()
{
    is_stealth = true;
    attack_margin = attack_margin * 2;
    return true;
}

// Resets the rogue back to normal after vanish.
bool Rogue::end_vanish()
{
    is_stealth = false;
    attack_margin = attack_margin / 2;
    return false;
}

void Rogue::level_up()
{
    max_health *= healthMod;
    defense *= defenseMod;
    strength *= strengthMod;
    speed *= speedMod;
    weapon_damage *= weaponMod;
    attack_margin += attackBonus;
    level++;
}
// Lets me know what class I am playing with
int Rogue::class_id() const
{
    return 3;
}
