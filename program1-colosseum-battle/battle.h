#include "character.h"

// Matthew Mecham -- 10/22/2019 -- Program 1
//This little hierarchy will handle the battle sequence as well as 
//give character's prompts and updates on the battle. This hierarchy will also take care
//of the random events that will occur while fighting. Random will be the base class
//and contain a few functions to control various random events. I decided to make Battle the derived
//class since it makes more sense for the client to create a battle object than it does to make a Random
//object to control a fight. This way the battle object will be random "plus more" - much more, really.
//Additionally, battle will "have an" array of linear linked lists that keeps track
//of wins and losses. I don't think it necessarily needs to be a containing relationship
//but I want the practice and I think it fits the instructions.

// I would have loved to implement this, but sadly, I ran out of time
// This was supposed to store wins and losses
// Now that I have figured out how to work with classes it would be doable, however
// I am out of time.
class Linked_list
{
    public:

    protected:

};

//Not a big class but I thought I could always expand it to other types of characters
//that need random calculations - I used to have it be a derived class but turned it into something
//that can be contained by other classes when needed.
class Random
{
    public:
        bool    critical_strike() const;
        bool    miss() const;
    protected:

};


class Battle:public Linked_list
{
    public:
        Battle();
        Battle(const int round_num);

        int     make_circle(int x, int y); 
        void    welcome();
        bool    barb_battle(Character *& barbarian);
        bool    knight_battle(Character *& knight);
        bool    rogue_battle(Character *& rogue);
        void    barb_between_rounds(Character *& barb);
        void    knight_between_rounds(Character *& knight);
        void    rogue_between_rounds(Character *& rogue);
        void    battle_banner() const;
        int     get_round() const;
    protected:
        int     round;
        Random random;
};


