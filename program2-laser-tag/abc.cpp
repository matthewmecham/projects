#include "abc.h"
// Matthew Mecham - Program 2 - 10/31/2019

//---------------------------------------------------------------------------
// Abstract Base Class to allow dynamic binding
//---------------------------------------------------------------------------

ABC::ABC():traversable(false)
{

}

ABC::~ABC()
{

}

ABC::ABC(bool travers):traversable(travers)
{

}

void ABC::display() const
{

}

void ABC::display_name() const
{

}

void ABC::output_message() const
{

}

//---------------------------------------------------------------------------
// Player Class Implementations
//---------------------------------------------------------------------------

Player::Player():ABC(false), ammo(5), life(5), is_stunned(false)
{

}

Player::~Player()
{

}

// Will output an '@' when I traverse my data structure
void Player::display() const
{
    cout << "@";
}

// Gives something for dynamic biding to mess with
void Player::display_name() const
{
    cout << "Generic Player" << endl;
}

// Another way of telling if dynamic binding is in effect
void Player::output_message() const
{
    cout << "Player gonna zap you!" << endl;
}

// Public Wrapper for home base
void Player::reload()
{
    ammo = 5;
}

// I would like to use RTTI here and get this to be playable but I am running out of time
void Player::move()
{

}

// I would like to use RTTI here and get this to be playable but I am running out of time
void Player::shoot()
{

}

//-------------------------------------------------------------------------
// Obstacle Class Implementations
//-------------------------------------------------------------------------

Obstacle::Obstacle():ABC(false)
{

}

Obstacle::~Obstacle()
{

}

// Obastacles will be represented by an 'O' on the map
void Obstacle::display() const
{
    cout << "O"; 
}

// Overridden display_name for obastacles
void Obstacle::display_name() const
{
    cout << "Obstacle" << endl;
}

// Oberridden output message for obstacles
void Obstacle::output_message() const
{
    cout << "You shall not... PASS!" << endl;
}

//------------------------------------------------------------------------
// Home_Base Class Implementations
//------------------------------------------------------------------------

Home_Base::Home_Base():ABC(true)
{

}

Home_Base::~Home_Base()
{

}

// Home bases will be represented by 'H' on screen
void Home_Base::display() const
{
    cout << "H";
}

// Overridden display name functions
void Home_Base::display_name() const
{
    cout << "Home Base" << endl;
}

// Oberridden output message for home base
void Home_Base::output_message() const
{
    cout << "Get your ammo! Get your free ammo!" << endl;
}

// Reloads a players ammo -- this is where my RTTI demonstration is located. 
void Home_Base::reload_ammo(ABC * ptr)
{
    Player *test;

    test = dynamic_cast<Player *>(ptr);
    if(test)
        test->reload();
        
}

//----------------------------------------------------------------------
// Pathway Class Implementations
//----------------------------------------------------------------------

Pathway::Pathway():ABC(true)
{

}

Pathway::~Pathway()
{

}

// Pathways will be represented by a '.' on the map
void Pathway::display() const
{
    cout << ".";
}

// Overridden pathway name display
void Pathway::display_name() const
{
    cout << "Pathway" << endl;
}

// Overridden output message for pathway
void Pathway::output_message() const
{
    cout << "The coase is clear! Maybe." << endl;
}

