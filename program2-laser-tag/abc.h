#include <iostream>
#include <cstring>
using namespace std; 

// Matthew Mecham - Program 2 - 10/31/2019

// In this file you will find my abstract base class.
// Derived from this base class are 4 things:
// a player, obstacle, home base, and pathway (an object the player can move through).
// These objects will make up the grid of the arena.   

class ABC
{
    public:
        ABC();
        ABC(bool travers);
        virtual ~ABC();

        virtual void display() const = 0; 
        virtual void display_name() const = 0;
        virtual void output_message() const = 0;

    protected:
        bool    traversable; 
};

class Player : public ABC
{
    public:
        Player();
        ~Player();

        void    display() const;
        void    display_name() const;
        void    output_message() const;
        void    reload();
        void    move();
        void    shoot();

    protected:
        int     ammo;
        int     life;
        int     is_stunned;
};

class Obstacle : public ABC
{
    public:
        Obstacle();
        ~Obstacle();

        void    display() const;
        void    display_name() const;
        void    output_message() const;

    protected:

};

class Home_Base : public ABC
{
    public:
        Home_Base();
        ~Home_Base();

        void    display() const;
        void    display_name() const;
        void    output_message() const;
        void    reload_ammo(ABC * ptr);

    protected:

};

class Pathway : public ABC
{
    public:
        Pathway();
        ~Pathway();

        void    display() const;
        void    display_name() const;
        void    output_message() const;

    protected:

};
