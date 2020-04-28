#include "battle.h"
//Matthew Mecham -- 10/22/2019 -- Program 1

//------------------------------------------------------------------
// Random Class Implementations
// -----------------------------------------------------------------

//Battle will check if attack hits, then check if attack crits
//then the damage will be calculated
bool Random::critical_strike() const
{
    if((rand()%4) == 0)
        return true;
    else 
        return false;
}

//Gives attack a chance to miss
bool Random::miss() const
{
    if((rand()%11) == 0)
        return true;
    else
        return false;
}

//------------------------------------------------------------------
//Battle Class Implementation
//------------------------------------------------------------------

Battle::Battle():round(0)
{
}

Battle::Battle(const int round_num):round(round_num)
{
}

//Function needed to make a fun little circle
int Battle::make_circle(int x, int y)
{
    return sqrt (pow(x,2) + pow(y,2));
}

//When the user decides it is time to fight, this will welcome them
//instead of clogging up main.cpp with couts
// the nested loop draws a circle based on r - fun little trick
// I spent way too long on it - many tabs open
void Battle::welcome() 
{
   int r = 10;
   int width = r;
   int length = r * 1.5;

   cout << "Welcome to the Battle Colosseum!!" << endl << endl;

   for(int y = width; y >= -width; y-=2)
   {
        for(int x = -length; x <= length; x++)
        {
            if(make_circle(x,y) == r) 
                cout << "*";
            else
                cout << " ";
        }
        cout << endl;
   }
   cout << "   Where dreams are made of!" << endl << endl;
}

// This functoin will handle the combat.
// It will take in a Barbarian object, generate a random
// opponent, and do battle. 
// Warning: There are three of these functions, Barbarian parameter, Knight parameter,
// and Rogue parameter. They all do relatively the same thing - the exception is each character's
// special ability. 
// Warning 2: These are VERY long. I had to account for when the player went first or when the enemy went first AND 
// had to account for if they used attack or their special ability. In addition, I had to repeat these fights
// for each potential enemy - if you read one case then you have pretty much read them all.
// I really should have figured out a sleeker way to do this but I had the design in my head and implemented it.
// It works just fine but it is gross to read - I guess this is what learning feels like.
// Returns true if victory, false if death
// I sure wish that I knew about upcasting when I wrote this class.
bool Battle::barb_battle(Character *& barbarian)
{
    int     choice = 0; // Stores what attack option players chooses
    int     result = 0; // Stores result of rand() to create a random opponent.
    bool    ability = false; // Boolean to keep track if an ability is activated or not
    
    result = (rand() % 3);
    ++round;

    //Generates a random opponent
    switch (result)
    {
        case 0:
        {

            Barbarian opponent;

            //Levels up the opponent to match the User
            while (opponent.check_level() < barbarian->check_level())
            {
                opponent.level_up();
                opponent.full_heal();
            }

            //Begin the fight!
            cout << "()xxx[:::::::::::> FIGHT <:::::::::::]xxx()" << endl << endl;
            barbarian->display_name(); 
            cout << "  VS Generic "; 
            opponent.display_name();
            cout << endl << endl;
            barbarian->display_all();

            //Time to duke it out
            while (barbarian->health() >= 0 || opponent.health() >= 0)
            {
                bool    hero_miss = random.miss(); //use for hero miss chance
                bool    hero_crit = random.critical_strike(); //used for player crit chance
                bool    enemy_miss = random.miss(); // used for enemy miss
                bool    enemy_crit = random.critical_strike(); //used for enemy crit
                int     hero_hp = barbarian->health(); //updates health every iteration
                int     enemy_hp = opponent.health(); //updates enemy health every iteration

                cout << "What would you like to do? Press corresponding number:\n";
                cout << "1. Attack\n2. Toggle Barbarian Rage\n";
                cin >> choice; cin.ignore(100, '\n');

                if(choice == 1)
                {
                    //if the barbarian is faster, then it attacks first based on hit
                    //and crit chance, then the opponent.attacks by default
                    if (barbarian->check_speed() >= opponent.check_speed())
                    {
                        if(hero_miss == false && hero_crit == true)
                        {
                            battle_banner();
                            opponent.take_damage(barbarian->attack() * 2);
                            cout << "Critical Strike! Your opponent receives "
                                << enemy_hp - opponent.health() << "points of damage!" << endl;
                            cout << "Your opponent has ";
                            opponent.display_health();
                            cout << " life left!" << endl;
                            if(opponent.is_dead())
                            {
                                return true;
                            }
                        }
                        else if (hero_miss == false && hero_crit == false)
                        {
                            battle_banner();
                            opponent.take_damage(barbarian->attack());
                            cout << "You hit the opponent for " << enemy_hp - opponent.health()
                            << " points of damage!" << endl;
                            cout << "Your opponent has ";
                            opponent.display_health();
                            cout << " life left!" << endl;
                            if(opponent.is_dead())
                            {
                                return true;
                            }
                        }
                        else
                        {
                            battle_banner();
                            cout << "haha! You missed!" << endl;
                            cout << "Your opponent has ";
                            opponent.display_health();
                            cout << " life left!" << endl;
                        }
                        
                        //Time for opponent's turn
                        if(enemy_miss == false && enemy_crit == true)
                        {
                            battle_banner();
                            barbarian->take_damage(opponent.attack() * 2);
                            cout << "Critical Strike! Your opponent hits you for "
                                << hero_hp - barbarian->health() << "points of damage!" << endl;
                            cout << "You have ";
                            opponent.display_health();
                            cout << " life left!" << endl;
                            if(barbarian->is_dead())
                            {
                                return false;
                            }
                        }
                        else if (enemy_miss == false && enemy_crit == false)
                        {
                            battle_banner();
                            barbarian->take_damage(opponent.attack());
                            cout << "The opponent hits you for " << hero_hp - barbarian->health()
                            << " points of damage!" << endl;
                            cout << "You have ";
                            barbarian->display_health();
                            cout << " life left!" << endl;
                            if(barbarian->is_dead())
                            {
                                return false;
                            }
                        }
                        else
                        {
                            battle_banner();
                            cout << "Phew! Your opponent missed!" << endl;
                            cout << "You have ";
                            opponent.display_health();
                            cout << " life left!" << endl;
                        }
                    }
                    //Now I have to do it backwards for if the opponent is faster... yikes
                    else
                    {
                        if(enemy_miss == false && enemy_crit == true)
                        {
                            battle_banner();
                            barbarian->take_damage(opponent.attack() * 2);
                            cout << "Critical Strike! Your opponent hits you for "
                                << hero_hp - barbarian->health() << "points of damage!" << endl;
                            cout << "You have ";
                            opponent.display_health();
                            cout << " life left!" << endl;
                            if(barbarian->is_dead())
                            {
                                return false;
                            }
                        }
                        else if (enemy_miss == false && enemy_crit == false)
                        {
                            battle_banner();
                            barbarian->take_damage(opponent.attack());
                            cout << "The opponent hits you for " << hero_hp - barbarian->health()
                            << " points of damage!" << endl;
                            cout << "You have ";
                            barbarian->display_health();
                            cout << " life left!" << endl;
                            if(barbarian->is_dead())
                            {
                                return false;
                            }
                        }
                        else
                        {
                            battle_banner();
                            cout << "Phew! Your opponent missed!" << endl;
                            cout << "You have ";
                            barbarian->display_health();
                            cout << " life left!" << endl;
                        }

                        // Now the slower barbarians turn
                        if(hero_miss == false && hero_crit == true)
                        {
                            battle_banner();
                            opponent.take_damage(barbarian->attack() * 2);
                            cout << "Critical Strike! Your opponent receives "
                                << enemy_hp - opponent.health() << "points of damage!" << endl;
                            cout << "Your opponent has ";
                            opponent.display_health();
                            cout << " life left!" << endl;
                            if(opponent.is_dead())
                            {
                                return true;
                            }
                        }
                        else if (hero_miss == false && hero_crit == false)
                        {
                            battle_banner();
                            opponent.take_damage(barbarian->attack());
                            cout << "You hit the opponent for " << enemy_hp - opponent.health()
                            << " points of damage!" << endl;
                            cout << "Your opponent has ";
                            opponent.display_health();
                            cout << " life left!" << endl;
                            if(opponent.is_dead())
                            {
                                return true;
                            }
                        }
                        else
                        {
                            battle_banner();
                            cout << "haha! You missed!" << endl;
                            cout << "Your opponent has ";
                            opponent.display_health();
                            cout << " life left!" << endl;
                        }
                    }
                    
                }
                // If the user didn't use attack then they used their ability and the opponent
                // will get attack in. Will will assume abilities have priority for 
                // the sake of brevity. 
                else
                {
                    if(!ability)
                    {
                        battle_banner();
                        cout << "You use Barbarian Rage!" << endl;
                        cout << "Your strength has increased at the cost of your defense!" <<endl;
                        cout << "Use again to turn it off." << endl;
                        ability = barbarian->start_rage();
                    }
                    else
                    {
                        battle_banner();
                        cout << "You return to normal." << endl;
                        ability = barbarian->end_rage();
                    }

                    // Now the enemy attacks by default
                    if(enemy_miss == false && enemy_crit == true)
                    {
                        battle_banner();
                        barbarian->take_damage(opponent.attack() * 2);
                        cout << "Critical Strike! Your opponent hits you for "
                            << hero_hp - barbarian->health() << "points of damage!" << endl;
                        cout << "You have ";
                        opponent.display_health();
                        cout << " life left!" << endl;
                        if(barbarian->is_dead())
                        {
                            return false;
                        }
                    }
                    else if (enemy_miss == false && enemy_crit == false)
                    {
                        battle_banner();
                        barbarian->take_damage(opponent.attack());
                        cout << "The opponent hits you for " << hero_hp - barbarian->health()
                        << " points of damage!" << endl;
                        cout << "You have ";
                        barbarian->display_health();
                        cout << " life left!" << endl;
                        if(barbarian->is_dead())
                        {
                            return false;
                        }
                    }
                    else
                    {
                        battle_banner();
                        cout << "Phew! Your opponent missed!" << endl;
                        cout << "You have ";
                        opponent.display_health();
                        cout << " life left!" << endl;
                    }
                }
            }


        break;
        }
        // Creates a knight to fight and does the same as case 0
        case 1:
        {
            Knight opponent;

            //Levels up the opponent to match the User
            while (opponent.check_level() < barbarian->check_level())
            {
                opponent.level_up();
                opponent.full_heal();
            }

            //Begin the fight!
            cout << "()xxx[:::::::::::>FIGHT<:::::::::::]xxx()" << endl << endl;
            barbarian->display_name(); 
            cout << " VS Generic "; 
            opponent.display_name();
            cout << endl << endl;
            barbarian->display_all();

            //Time to duke it out
            while (barbarian->health() >= 0 || opponent.health() >= 0)
            {
                bool    hero_miss = random.miss();
                bool    hero_crit = random.critical_strike();
                bool    enemy_miss = random.miss();
                bool    enemy_crit = random.critical_strike();
                int     hero_hp = barbarian->health();
                int     enemy_hp = opponent.health();
                
                cout << "What would you like to do? Press corresponding number:\n";
                cout << "1 Attack\n2. Toggle Barbarian Rage\n";
                cin >> choice; cin.ignore(100, '\n');

                if(choice == 1)
                {
                    //if the barbarian is faster, then it attacks first based on hit
                    //and crit chance, then the opponent.attacks by default
                    if (barbarian->check_speed() >= opponent.check_speed())
                    {
                        if(hero_miss == false && hero_crit == true)
                        {
                            battle_banner();
                            opponent.take_damage(barbarian->attack() * 2);
                            cout << "Critical Strike! Your opponent receives "
                                << enemy_hp - opponent.health() << "points of damage!" << endl;
                            cout << "Your opponent has ";
                            opponent.display_health();
                            cout << " life left!" << endl;
                            if(opponent.is_dead())
                            {
                                return true;
                            }
                        }
                        else if (hero_miss == false && hero_crit == false)
                        {
                            battle_banner();
                            opponent.take_damage(barbarian->attack());
                            cout << "You hit the opponent for " << enemy_hp - opponent.health()
                            << " points of damage!" << endl;
                            cout << "Your opponent has ";
                            opponent.display_health();
                            cout << " life left!" << endl;
                            if(opponent.is_dead())
                            {
                                return true;
                            }
                        }
                        else
                        {
                            battle_banner();
                            cout << "haha! You missed!" << endl;
                            cout << "Your opponent has ";
                            opponent.display_health();
                            cout << " life left!" << endl;
                        }
                        
                        //Time for opponent's turn
                        if(enemy_miss == false && enemy_crit == true)
                        {
                            battle_banner();
                            barbarian->take_damage(opponent.attack() * 2);
                            cout << "Critical Strike! Your opponent hits you for "
                                << hero_hp - barbarian->health() << "points of damage!" << endl;
                            cout << "You have ";
                            opponent.display_health();
                            cout << " life left!" << endl;
                            if(barbarian->is_dead())
                            {
                                return false;
                            }
                        }
                        else if (enemy_miss == false && enemy_crit == false)
                        {
                            battle_banner();
                            barbarian->take_damage(opponent.attack());
                            cout << "The opponent hits you for " << hero_hp - barbarian->health()
                            << " points of damage!" << endl;
                            cout << "You have ";
                            barbarian->display_health();
                            cout << " life left!" << endl;
                            if(barbarian->is_dead())
                            {
                                return false;
                            }
                        }
                        else
                        {
                            battle_banner();
                            cout << "Phew! Your opponent missed!" << endl;
                            cout << "You have ";
                            opponent.display_health();
                            cout << " life left!" << endl;
                        }
                    }
                    //Now I have to do it backwards for if the opponent is faster... yikes
                    else
                    {
                        if(enemy_miss == false && enemy_crit == true)
                        {
                            battle_banner();
                            barbarian->take_damage(opponent.attack() * 2);
                            cout << "Critical Strike! Your opponent hits you for "
                                << hero_hp - barbarian->health() << "points of damage!" << endl;
                            cout << "You have ";
                            opponent.display_health();
                            cout << " life left!" << endl;
                            if(barbarian->is_dead())
                            {
                                return false;
                            }
                        }
                        else if (enemy_miss == false && enemy_crit == false)
                        {
                            battle_banner();
                            barbarian->take_damage(opponent.attack());
                            cout << "The opponent hits you for " << hero_hp - barbarian->health()
                            << " points of damage!" << endl;
                            cout << "You have ";
                            barbarian->display_health();
                            cout << " life left!" << endl;
                            if(barbarian->is_dead())
                            {
                                return false;
                            }
                        }
                        else
                        {
                            battle_banner();
                            cout << "Phew! Your opponent missed!" << endl;
                            cout << "You have ";
                            opponent.display_health();
                            cout << " life left!" << endl;
                        }

                        // Now the slower barbarians turn
                        if(hero_miss == false && hero_crit == true)
                        {
                            battle_banner();
                            opponent.take_damage(barbarian->attack() * 2);
                            cout << "Critical Strike! Your opponent receives "
                                << enemy_hp - opponent.health() << "points of damage!" << endl;
                            cout << "Your opponent has ";
                            opponent.display_health();
                            cout << " life left!" << endl;
                            if(opponent.is_dead())
                            {
                                return true;
                            }
                        }
                        else if (hero_miss == false && hero_crit == false)
                        {
                            battle_banner();
                            opponent.take_damage(barbarian->attack());
                            cout << "You hit the opponent for " << enemy_hp - opponent.health()
                            << " points of damage!" << endl;
                            cout << "Your opponent has ";
                            opponent.display_health();
                            cout << " life left!" << endl;
                            if(opponent.is_dead())
                            {
                                return true;
                            }
                        }
                        else
                        {
                            battle_banner();
                            cout << "haha! You missed!" << endl;
                            cout << "Your opponent has ";
                            opponent.display_health();
                            cout << " life left!" << endl;
                        }
                    }
                    
                }
                // If the user didn't use attack then they used their ability and the opponent
                // will get attack in. Will will assume abilities have priority for 
                // the sake of brevity. 
                else
                {
                    if(!ability)
                    {
                        battle_banner();
                        cout << "You use Barbarian Rage!" << endl;
                        cout << "Your strength has increased at the cost of your defense!" <<endl;
                        cout << "Use again to turn it off." << endl;
                        ability = barbarian->start_rage();
                    }
                    else
                    {
                        battle_banner();
                        cout << "You return to normal." << endl;
                        ability = barbarian->end_rage();
                    }

                    // Now the enemy attacks by default
                    if(enemy_miss == false && enemy_crit == true)
                    {
                        battle_banner();
                        barbarian->take_damage(opponent.attack() * 2);
                        cout << "Critical Strike! Your opponent hits you for "
                            << hero_hp - barbarian->health() << "points of damage!" << endl;
                        cout << "You have ";
                        opponent.display_health();
                        cout << " life left!" << endl;
                        if(barbarian->is_dead())
                        {
                            return false;
                        }
                    }
                    else if (enemy_miss == false && enemy_crit == false)
                    {
                        battle_banner();
                        barbarian->take_damage(opponent.attack());
                        cout << "The opponent hits you for " << hero_hp - barbarian->health()
                        << " points of damage!" << endl;
                        cout << "You have ";
                        barbarian->display_health();
                        cout << " life left!" << endl;
                        if(barbarian->is_dead())
                        {
                            return false;
                        }
                    }
                    else
                    {
                        battle_banner();
                        cout << "Phew! Your opponent missed!" << endl;
                        cout << "You have ";
                        opponent.display_health();
                        cout << " life left!" << endl;
                    }
                }
            }

        break;
        }
        case 2:
        {
            Rogue opponent;

            //Levels up the opponent to match the User
            while (opponent.check_level() < barbarian->check_level())
            {
                opponent.level_up();
                opponent.full_heal();
            }

            //Begin the fight!
            cout << "()xxx[:::::::::::>FIGHT<:::::::::::]xxx()" << endl << endl;
            barbarian->display_name(); 
            cout << " VS Generic "; 
            opponent.display_name();
            cout << endl << endl;
            barbarian->display_all();

            //Time to duke it out
            while (barbarian->health() >= 0 || opponent.health() >= 0)
            {
                bool    hero_miss = random.miss();
                bool    hero_crit = random.critical_strike();
                bool    enemy_miss = random.miss();
                bool    enemy_crit = random.critical_strike();
                int     hero_hp = barbarian->health();
                int     enemy_hp = opponent.health();

                cout << "What would you like to do? Press corresponding number:\n";
                cout << "1. Attack\n2. Toggle Barbarian Rage\n";
                cin >> choice; cin.ignore(100, '\n');

                if(choice == 1)
                {

                    //if the barbarian is faster, then it attacks first based on hit
                    //and crit chance, then the opponent.attacks by default
                    if (barbarian->check_speed() >= opponent.check_speed())
                    {
                        if(hero_miss == false && hero_crit == true)
                        {
                            battle_banner();
                            opponent.take_damage(barbarian->attack() * 2);
                            cout << "Critical Strike! Your opponent receives "
                                << enemy_hp - opponent.health() << "points of damage!" << endl;
                            cout << "Your opponent has ";
                            opponent.display_health();
                            cout << " life left!" << endl;
                            if(opponent.is_dead())
                            {
                                return true;
                            }
                        }
                        else if (hero_miss == false && hero_crit == false)
                        {
                            battle_banner();
                            opponent.take_damage(barbarian->attack());
                            cout << "You hit the opponent for " << enemy_hp - opponent.health()
                            << " points of damage!" << endl;
                            cout << "Your opponent has ";
                            opponent.display_health();
                            cout << " life left!" << endl;
                            if(opponent.is_dead())
                            {
                                return true;
                            }
                        }
                        else
                        {
                            battle_banner();
                            cout << "haha! You missed!" << endl;
                            cout << "Your opponent has ";
                            opponent.display_health();
                            cout << " life left!" << endl;
                        }
                        
                        //Time for opponent's turn
                        if(enemy_miss == false && enemy_crit == true)
                        {
                            battle_banner();
                            barbarian->take_damage(opponent.attack() * 2);
                            cout << "Critical Strike! Your opponent hits you for "
                                << hero_hp - barbarian->health() << "points of damage!" << endl;
                            cout << "You have ";
                            opponent.display_health();
                            cout << " life left!" << endl;
                            if(barbarian->is_dead())
                            {
                                return false;
                            }
                        }
                        else if (enemy_miss == false && enemy_crit == false)
                        {
                            battle_banner();
                            barbarian->take_damage(opponent.attack());
                            cout << "The opponent hits you for " << hero_hp - barbarian->health()
                            << " points of damage!" << endl;
                            cout << "You have ";
                            barbarian->display_health();
                            cout << " life left!" << endl;
                            if(barbarian->is_dead())
                            {
                                return false;
                            }
                        }
                        else
                        {
                            battle_banner();
                            cout << "Phew! Your opponent missed!" << endl;
                            cout << "You have ";
                            opponent.display_health();
                            cout << " life left!" << endl;
                        }
                    }
                    //Now I have to do it backwards for if the opponent is faster... yikes
                    else
                    {
                        if(enemy_miss == false && enemy_crit == true)
                        {
                            battle_banner();
                            barbarian->take_damage(opponent.attack() * 2);
                            cout << "Critical Strike! Your opponent hits you for "
                                << hero_hp - barbarian->health() << "points of damage!" << endl;
                            cout << "You have ";
                            opponent.display_health();
                            cout << " life left!" << endl;
                            if(barbarian->is_dead())
                            {
                                return false;
                            }
                        }
                        else if (enemy_miss == false && enemy_crit == false)
                        {
                            battle_banner();
                            barbarian->take_damage(opponent.attack());
                            cout << "The opponent hits you for " << hero_hp - barbarian->health()
                            << " points of damage!" << endl;
                            cout << "You have ";
                            barbarian->display_health();
                            cout << " life left!" << endl;
                            if(barbarian->is_dead())
                            {
                                return false;
                            }
                        }
                        else
                        {
                            battle_banner();
                            cout << "Phew! Your opponent missed!" << endl;
                            cout << "You have ";
                            opponent.display_health();
                            cout << " life left!" << endl;
                        }

                        // Now the slower barbarians turn
                        if(hero_miss == false && hero_crit == true)
                        {
                            battle_banner();
                            opponent.take_damage(barbarian->attack() * 2);
                            cout << "Critical Strike! Your opponent receives "
                                << enemy_hp - opponent.health() << "points of damage!" << endl;
                            cout << "Your opponent has ";
                            opponent.display_health();
                            cout << " life left!" << endl;
                            if(opponent.is_dead())
                            {
                                return true;
                            }
                        }
                        else if (hero_miss == false && hero_crit == false)
                        {
                            battle_banner();
                            opponent.take_damage(barbarian->attack());
                            cout << "You hit the opponent for " << enemy_hp - opponent.health()
                            << " points of damage!" << endl;
                            cout << "Your opponent has ";
                            opponent.display_health();
                            cout << " life left!" << endl;
                            if(opponent.is_dead())
                            {
                                return true;
                            }
                        }
                        else
                        {
                            battle_banner();
                            cout << "haha! You missed!" << endl;
                            cout << "Your opponent has ";
                            opponent.display_health();
                            cout << " life left!" << endl;
                        }
                    }
                    
                }
                // If the user didn't use attack then they used their ability and the opponent
                // will get attack in. Will will assume abilities have priority for 
                // the sake of brevity. 
                else
                {
                    if(!ability)
                    {
                        battle_banner();
                        cout << "You use Barbarian Rage!" << endl;
                        cout << "Your strength has increased at the cost of your defense!" <<endl;
                        cout << "Use again to turn it off." << endl;
                        ability = barbarian->start_rage();
                    }
                    else
                    {
                        battle_banner();
                        cout << "You return to normal." << endl;
                        ability = barbarian->end_rage();
                    }

                    // Now the enemy attacks by default
                    if(enemy_miss == false && enemy_crit == true)
                    {
                        battle_banner();
                        barbarian->take_damage(opponent.attack() * 2);
                        cout << "Critical Strike! Your opponent hits you for "
                            << hero_hp - barbarian->health() << "points of damage!" << endl;
                        cout << "You have ";
                        opponent.display_health();
                        cout << " life left!" << endl;
                        if(barbarian->is_dead())
                        {
                            return false;
                        }
                    }
                    else if (enemy_miss == false && enemy_crit == false)
                    {
                        battle_banner();
                        barbarian->take_damage(opponent.attack());
                        cout << "The opponent hits you for " << hero_hp - barbarian->health()
                        << " points of damage!" << endl;
                        cout << "You have ";
                        barbarian->display_health();
                        cout << " life left!" << endl;
                        if(barbarian->is_dead())
                        {
                            return false;
                        }
                    }
                    else
                    {
                        battle_banner();
                        cout << "Phew! Your opponent missed!" << endl;
                        cout << "You have ";
                        opponent.display_health();
                        cout << " life left!" << endl;
                    }
                }
            }

        break;
        }
    }
    return false;
}
// Function will act very similarly to the barbarian_battle but it will take a knight object
// and use the knights special ability - thank god for search and replace
bool Battle::knight_battle(Character *& knight)
{
    int     choice = 0;
    int     result = 0;
    
    result = rand() % 3;
    ++round;

    //Generates a random opponent
    switch (result)
    {
        case 0:
        {

            Barbarian opponent;

            //Levels up the opponent to match the User
            while (opponent.check_level() < knight->check_level())
            {
                opponent.level_up();
                opponent.full_heal();
            }

            //Begin the fight!
            cout << "()xxx[:::::::::::>FIGHT<:::::::::::]xxx()" << endl << endl;
            knight->display_name(); 
            cout << "  VS Generic "; 
            opponent.display_name();
            cout << endl << endl;
            knight->display_all();

            //Time to duke it out
            while (knight->health() >= 0 || opponent.health() >= 0)
            {
                bool    hero_miss = random.miss();
                bool    hero_crit = random.critical_strike();
                bool    enemy_miss = random.miss();
                bool    enemy_crit = random.critical_strike();
                int     hero_hp = knight->health();
                int     enemy_hp = opponent.health();

                cout << "What would you like to do? Press corresponding number:\n";
                cout << "1. Attack\n2. Heal\n";
                cin >> choice; cin.ignore(100, '\n');

                if(choice == 1)
                {
                    //if the knight is faster, then it attacks first based on hit
                    //and crit chance, then the opponent.attacks by default
                    if (knight->check_speed() >= opponent.check_speed())
                    {
                        if(hero_miss == false && hero_crit == true)
                        {
                            battle_banner();
                            opponent.take_damage(knight->attack() * 2);
                            cout << "Critical Strike! Your opponent receives "
                                << enemy_hp - opponent.health() << "points of damage!" << endl;
                            cout << "Your opponent has ";
                            opponent.display_health();
                            cout << " life left!" << endl;
                            if(opponent.is_dead())
                            {
                                return true;
                            }
                        }
                        else if (hero_miss == false && hero_crit == false)
                        {
                            battle_banner();
                            opponent.take_damage(knight->attack());
                            cout << "You hit the opponent for " << enemy_hp - opponent.health()
                            << " points of damage!" << endl;
                            cout << "Your opponent has ";
                            opponent.display_health();
                            cout << " life left!" << endl;
                            if(opponent.is_dead())
                            {
                                return true;
                            }
                        }
                        else
                        {
                            battle_banner();
                            cout << "haha! You missed!" << endl;
                            cout << "Your opponent has ";
                            opponent.display_health();
                            cout << " life left!" << endl;
                        }
                        
                        //Time for opponent's turn
                        if(enemy_miss == false && enemy_crit == true)
                        {
                            battle_banner();
                            knight->take_damage(opponent.attack() * 2);
                            cout << "Critical Strike! Your opponent hits you for "
                                << hero_hp - knight->health() << "points of damage!" << endl;
                            cout << "You have ";
                            opponent.display_health();
                            cout << " life left!" << endl;
                            if(knight->is_dead())
                            {
                                return false;
                            }
                        }
                        else if (enemy_miss == false && enemy_crit == false)
                        {
                            battle_banner();
                            knight->take_damage(opponent.attack());
                            cout << "The opponent hits you for " << hero_hp - knight->health()
                            << " points of damage!" << endl;
                            cout << "You have ";
                            knight->display_health();
                            cout << " life left!" << endl;
                            if(knight->is_dead())
                            {
                                return false;
                            }
                        }
                        else
                        {
                            battle_banner();
                            cout << "Phew! Your opponent missed!" << endl;
                            cout << "You have ";
                            opponent.display_health();
                            cout << " life left!" << endl;
                        }
                    }
                    //Now I have to do it backwards for if the opponent is faster... yikes
                    else
                    {
                        if(enemy_miss == false && enemy_crit == true)
                        {
                            battle_banner();
                            knight->take_damage(opponent.attack() * 2);
                            cout << "Critical Strike! Your opponent hits you for "
                                << hero_hp - knight->health() << "points of damage!" << endl;
                            cout << "You have ";
                            opponent.display_health();
                            cout << " life left!" << endl;
                            if(knight->is_dead())
                            {
                                return false;
                            }
                        }
                        else if (enemy_miss == false && enemy_crit == false)
                        {
                            battle_banner();
                            knight->take_damage(opponent.attack());
                            cout << "The opponent hits you for " << hero_hp - knight->health()
                            << " points of damage!" << endl;
                            cout << "You have ";
                            knight->display_health();
                            cout << " life left!" << endl;
                            if(knight->is_dead())
                            {
                                return false;
                            }
                        }
                        else
                        {
                            battle_banner();
                            cout << "Phew! Your opponent missed!" << endl;
                            cout << "You have ";
                            opponent.display_health();
                            cout << " life left!" << endl;
                        }

                        // Now the slower knights turn
                        if(hero_miss == false && hero_crit == true)
                        {
                            battle_banner();
                            opponent.take_damage(knight->attack() * 2);
                            cout << "Critical Strike! Your opponent receives "
                                << enemy_hp - opponent.health() << "points of damage!" << endl;
                            cout << "Your opponent has ";
                            opponent.display_health();
                            cout << " life left!" << endl;
                            if(opponent.is_dead())
                            {
                                return true;
                            }
                        }
                        else if (hero_miss == false && hero_crit == false)
                        {
                            battle_banner();
                            opponent.take_damage(knight->attack());
                            cout << "You hit the opponent for " << enemy_hp - opponent.health()
                            << " points of damage!" << endl;
                            cout << "Your opponent has ";
                            opponent.display_health();
                            cout << " life left!" << endl;
                            if(opponent.is_dead())
                            {
                                return true;
                            }
                        }
                        else
                        {
                            battle_banner();
                            cout << "haha! You missed!" << endl;
                            cout << "Your opponent has ";
                            opponent.display_health();
                            cout << " life left!" << endl;
                        }
                    }
                    
                }
                // If the user didn't use attack then they used their ability and the opponent
                // will get attack in. Will will assume abilities have priority for 
                // the sake of brevity. 
                else
                {
                    int heal_amount;
                    cout << "You use heal!" << endl;
                    heal_amount = knight->super_heal();
                    cout << "You healed for " << heal_amount << endl;
                    cout << "You have ";
                    knight->display_health();
                    hero_hp = knight->health();
                    cout << "health!" << endl;

                    // Now the enemy attacks by default
                    if(enemy_miss == false && enemy_crit == true)
                    {
                        battle_banner();
                        knight->take_damage(opponent.attack() * 2);
                        cout << "Critical Strike! Your opponent hits you for "
                            << hero_hp - knight->health() << "points of damage!" << endl;
                        cout << "You have ";
                        opponent.display_health();
                        cout << " life left!" << endl;
                        if(knight->is_dead())
                        {
                            return false;
                        }
                    }
                    else if (enemy_miss == false && enemy_crit == false)
                    {
                        battle_banner();
                        knight->take_damage(opponent.attack());
                        cout << "The opponent hits you for " << hero_hp - knight->health()
                        << " points of damage!" << endl;
                        cout << "You have ";
                        knight->display_health();
                        cout << " life left!" << endl;
                        if(knight->is_dead())
                        {
                            return false;
                        }
                    }
                    else
                    {
                        battle_banner();
                        cout << "Phew! Your opponent missed!" << endl;
                        cout << "You have ";
                        opponent.display_health();
                        cout << " life left!" << endl;
                    }
                }
            }
        break;
        }
        // Creates a knight to fight and does the same as case 0
        case 1:
        {
            Knight opponent;

            //Levels up the opponent to match the User
            while (opponent.check_level() < knight->check_level())
            {
                opponent.level_up();
                opponent.full_heal();
            }

            //Begin the fight!
            cout << "()xxx[:::::::::::>FIGHT<:::::::::::]xxx()" << endl << endl;
            knight->display_name(); 
            cout << " VS Generic "; 
            opponent.display_name();
            cout << endl << endl;
            knight->display_all();

            //Time to duke it out
            while (knight->health() >= 0 || opponent.health() >= 0)
            {
                bool    hero_miss = random.miss();
                bool    hero_crit = random.critical_strike();
                bool    enemy_miss = random.miss();
                bool    enemy_crit = random.critical_strike();
                int     hero_hp = knight->health();
                int     enemy_hp = opponent.health();
                
                cout << "What would you like to do? Press corresponding number:\n";
                cout << "1. Attack\n2. Heal\n";
                cin >> choice; cin.ignore(100, '\n');

                if(choice == 1)
                {
                    //if the knight is faster, then it attacks first based on hit
                    //and crit chance, then the opponent.attacks by default
                    if (knight->check_speed() >= opponent.check_speed())
                    {
                        if(hero_miss == false && hero_crit == true)
                        {
                            battle_banner();
                            opponent.take_damage(knight->attack() * 2);
                            cout << "Critical Strike! Your opponent receives "
                                << enemy_hp - opponent.health() << "points of damage!" << endl;
                            cout << "Your opponent has ";
                            opponent.display_health();
                            cout << " life left!" << endl;
                            if(opponent.is_dead())
                            {
                                return true;
                            }
                        }
                        else if (hero_miss == false && hero_crit == false)
                        {
                            battle_banner();
                            opponent.take_damage(knight->attack());
                            cout << "You hit the opponent for " << enemy_hp - opponent.health()
                            << " points of damage!" << endl;
                            cout << "Your opponent has ";
                            opponent.display_health();
                            cout << " life left!" << endl;
                            if(opponent.is_dead())
                            {
                                return true;
                            }
                        }
                        else
                        {
                            battle_banner();
                            cout << "haha! You missed!" << endl;
                            cout << "Your opponent has ";
                            opponent.display_health();
                            cout << " life left!" << endl;
                        }
                        
                        //Time for opponent's turn
                        if(enemy_miss == false && enemy_crit == true)
                        {
                            battle_banner();
                            knight->take_damage(opponent.attack() * 2);
                            cout << "Critical Strike! Your opponent hits you for "
                                << hero_hp - knight->health() << "points of damage!" << endl;
                            cout << "You have ";
                            opponent.display_health();
                            cout << " life left!" << endl;
                            if(knight->is_dead())
                            {
                                return false;
                            }
                        }
                        else if (enemy_miss == false && enemy_crit == false)
                        {
                            battle_banner();
                            knight->take_damage(opponent.attack());
                            cout << "The opponent hits you for " << hero_hp - knight->health()
                            << " points of damage!" << endl;
                            cout << "You have ";
                            knight->display_health();
                            cout << " life left!" << endl;
                            if(knight->is_dead())
                            {
                                return false;
                            }
                        }
                        else
                        {
                            battle_banner();
                            cout << "Phew! Your opponent missed!" << endl;
                            cout << "You have ";
                            opponent.display_health();
                            cout << " life left!" << endl;
                        }
                    }
                    //Now I have to do it backwards for if the opponent is faster... yikes
                    else
                    {
                        if(enemy_miss == false && enemy_crit == true)
                        {
                            battle_banner();
                            knight->take_damage(opponent.attack() * 2);
                            cout << "Critical Strike! Your opponent hits you for "
                                << hero_hp - knight->health() << "points of damage!" << endl;
                            cout << "You have ";
                            opponent.display_health();
                            cout << " life left!" << endl;
                            if(knight->is_dead())
                            {
                                return false;    
                            }
                        }
                        else if (enemy_miss == false && enemy_crit == false)
                        {
                            battle_banner();
                            knight->take_damage(opponent.attack());
                            cout << "The opponent hits you for " << hero_hp - knight->health()
                            << " points of damage!" << endl;
                            cout << "You have ";
                            knight->display_health();
                            cout << " life left!" << endl;
                            if(knight->is_dead())
                            {
                                return false;
                            }
                        }
                        else
                        {
                            battle_banner();
                            cout << "Phew! Your opponent missed!" << endl;
                            cout << "You have ";
                            opponent.display_health();
                            cout << " life left!" << endl;
                        }

                        // Now the slower knights turn
                        if(hero_miss == false && hero_crit == true)
                        {
                            battle_banner();
                            opponent.take_damage(knight->attack() * 2);
                            cout << "Critical Strike! Your opponent receives "
                                << enemy_hp - opponent.health() << "points of damage!" << endl;
                            cout << "Your opponent has ";
                            opponent.display_health();
                            cout << " life left!" << endl;
                            if(opponent.is_dead())
                            {
                                return true;
                            }
                        }
                        else if (hero_miss == false && hero_crit == false)
                        {
                            battle_banner();
                            opponent.take_damage(knight->attack());
                            cout << "You hit the opponent for " << enemy_hp - opponent.health()
                            << " points of damage!" << endl;
                            cout << "Your opponent has ";
                            opponent.display_health();
                            cout << " life left!" << endl;
                            if(opponent.is_dead())
                            {
                                return true;
                            }
                        }
                        else
                        {
                            battle_banner();
                            cout << "haha! You missed!" << endl;
                            cout << "Your opponent has ";
                            opponent.display_health();
                            cout << " life left!" << endl;
                        }
                    }
                    
                }
                // If the user didn't use attack then they used their ability and the opponent
                // will get attack in. Will will assume abilities have priority for 
                // the sake of brevity. 
                else
                {
                    int heal_amount;
                    cout << "You use heal!" << endl;
                    heal_amount = knight->super_heal();
                    cout << "You healed for " << heal_amount << endl;
                    cout << "You have ";
                    knight->display_health();
                    hero_hp = knight->health();
                    cout << "health!" << endl;

                    // Now the enemy attacks by default
                    if(enemy_miss == false && enemy_crit == true)
                    {
                        battle_banner();
                        knight->take_damage(opponent.attack() * 2);
                        cout << "Critical Strike! Your opponent hits you for "
                            << hero_hp - knight->health() << "points of damage!" << endl;
                        cout << "You have ";
                        opponent.display_health();
                        cout << " life left!" << endl;
                        if(knight->is_dead())
                        {
                            return false;
                        }
                    }
                    else if (enemy_miss == false && enemy_crit == false)
                    {
                        battle_banner();
                        knight->take_damage(opponent.attack());
                        cout << "The opponent hits you for " << hero_hp - knight->health()
                        << " points of damage!" << endl;
                        cout << "You have ";
                        knight->display_health();
                        cout << " life left!" << endl;
                        if(knight->is_dead())
                        {
                            return false;
                        }
                    }
                    else
                    {
                        battle_banner();
                        cout << "Phew! Your opponent missed!" << endl;
                        cout << "You have ";
                        opponent.display_health();
                        cout << " life left!" << endl;
                    }
                }
            }

        break;
        }
        case 2:
        {
            Rogue opponent;

            //Levels up the opponent to match the User
            while (opponent.check_level() < knight->check_level())
            {
                opponent.level_up();
                opponent.full_heal();
            }

            //Begin the fight!
            cout << "()xxx[:::::::::::>FIGHT<:::::::::::]xxx()" << endl << endl;
            knight->display_name(); 
            cout << " VS Generic "; 
            opponent.display_name();
            cout << endl << endl;
            knight->display_all();

            //Time to duke it out
            while (knight->health() >= 0 || opponent.health() >= 0)
            {
                bool    hero_miss = random.miss();
                bool    hero_crit = random.critical_strike();
                bool    enemy_miss = random.miss();
                bool    enemy_crit = random.critical_strike();
                int     hero_hp = knight->health();
                int     enemy_hp = opponent.health();

                cout << "What would you like to do? Press corresponding number:\n";
                cout << "1. Attack\n2. Heal\n";
                cin >> choice; cin.ignore(100, '\n');

                if(choice == 1)
                {
                    //if the knight is faster, then it attacks first based on hit
                    //and crit chance, then the opponent.attacks by default
                    if (knight->check_speed() >= opponent.check_speed())
                    {
                        if(hero_miss == false && hero_crit == true)
                        {
                            battle_banner();
                            opponent.take_damage(knight->attack() * 2);
                            cout << "Critical Strike! Your opponent receives "
                                << enemy_hp - opponent.health() << "points of damage!" << endl;
                            cout << "Your opponent has ";
                            opponent.display_health();
                            cout << " life left!" << endl;
                            if(opponent.is_dead())
                            {
                                return true;
                            }
                        }
                        else if (hero_miss == false && hero_crit == false)
                        {
                            battle_banner();
                            opponent.take_damage(knight->attack());
                            cout << "You hit the opponent for " << enemy_hp - opponent.health()
                            << " points of damage!" << endl;
                            cout << "Your opponent has ";
                            opponent.display_health();
                            cout << " life left!" << endl;
                            if(opponent.is_dead())
                            {
                                return true;
                            }
                        }
                        else
                        {
                            battle_banner();
                            cout << "haha! You missed!" << endl;
                            cout << "Your opponent has ";
                            opponent.display_health();
                            cout << " life left!" << endl;
                        }
                        
                        //Time for opponent's turn
                        if(enemy_miss == false && enemy_crit == true)
                        {
                            battle_banner();
                            knight->take_damage(opponent.attack() * 2);
                            cout << "Critical Strike! Your opponent hits you for "
                                << hero_hp - knight->health() << "points of damage!" << endl;
                            cout << "You have ";
                            opponent.display_health();
                            cout << " life left!" << endl;
                            if(knight->is_dead())
                            {
                                return false;
                            }
                        }
                        else if (enemy_miss == false && enemy_crit == false)
                        {
                            battle_banner();
                            knight->take_damage(opponent.attack());
                            cout << "The opponent hits you for " << hero_hp - knight->health()
                            << " points of damage!" << endl;
                            cout << "You have ";
                            knight->display_health();
                            cout << " life left!" << endl;
                            if(knight->is_dead())
                            {
                                return false;
                            }
                        }
                        else
                        {
                            battle_banner();
                            cout << "Phew! Your opponent missed!" << endl;
                            cout << "You have ";
                            opponent.display_health();
                            cout << " life left!" << endl;
                        }
                    }
                    //Now I have to do it backwards for if the opponent is faster... yikes
                    else
                    {
                        if(enemy_miss == false && enemy_crit == true)
                        {
                            battle_banner();
                            knight->take_damage(opponent.attack() * 2);
                            cout << "Critical Strike! Your opponent hits you for "
                                << hero_hp - knight->health() << "points of damage!" << endl;
                            cout << "You have ";
                            opponent.display_health();
                            cout << " life left!" << endl;
                            if(knight->is_dead())
                            {
                                return false;
                            }
                        }
                        else if (enemy_miss == false && enemy_crit == false)
                        {
                            battle_banner();
                            knight->take_damage(opponent.attack());
                            cout << "The opponent hits you for " << hero_hp - knight->health()
                            << " points of damage!" << endl;
                            cout << "You have ";
                            knight->display_health();
                            cout << " life left!" << endl;
                            if(knight->is_dead())
                            {
                                return false;
                            }
                        }
                        else
                        {
                            battle_banner();
                            cout << "Phew! Your opponent missed!" << endl;
                            cout << "You have ";
                            opponent.display_health();
                            cout << " life left!" << endl;
                        }

                        // Now the slower knights turn
                        if(hero_miss == false && hero_crit == true)
                        {
                            battle_banner();
                            opponent.take_damage(knight->attack() * 2);
                            cout << "Critical Strike! Your opponent receives "
                                << enemy_hp - opponent.health() << "points of damage!" << endl;
                            cout << "Your opponent has ";
                            opponent.display_health();
                            cout << " life left!" << endl;
                            if(opponent.is_dead())
                            {
                                return true;
                            }
                        }
                        else if (hero_miss == false && hero_crit == false)
                        {
                            battle_banner();
                            opponent.take_damage(knight->attack());
                            cout << "You hit the opponent for " << enemy_hp - opponent.health()
                            << " points of damage!" << endl;
                            cout << "Your opponent has ";
                            opponent.display_health();
                            cout << " life left!" << endl;
                            if(opponent.is_dead())
                            {
                                return true;
                            }
                        }
                        else
                        {
                            battle_banner();
                            cout << "haha! You missed!" << endl;
                            cout << "Your opponent has ";
                            opponent.display_health();
                            cout << " life left!" << endl;
                        }
                    }
                    
                }
                // If the user didn't use attack then they used their ability and the opponent
                // will get attack in. Will will assume abilities have priority for 
                // the sake of brevity. 
                else
                {
                    int heal_amount;
                    cout << "You use heal!" << endl;
                    heal_amount = knight->super_heal();
                    cout << "You healed for " << heal_amount << endl;
                    cout << "You have ";
                    knight->display_health();
                    hero_hp = knight->health();
                    cout << "health!" << endl;

                    // Now the enemy attacks by default
                    if(enemy_miss == false && enemy_crit == true)
                    {
                        battle_banner();
                        knight->take_damage(opponent.attack() * 2);
                        cout << "Critical Strike! Your opponent hits you for "
                            << hero_hp - knight->health() << "points of damage!" << endl;
                        cout << "You have ";
                        opponent.display_health();
                        cout << " life left!" << endl;
                        if(knight->is_dead())
                        {
                            return false;
                        }
                    }
                    else if (enemy_miss == false && enemy_crit == false)
                    {
                        battle_banner();
                        knight->take_damage(opponent.attack() * 2);
                        knight->take_damage(opponent.attack());
                        cout << "The opponent hits you for " << hero_hp - knight->health()
                        << " points of damage!" << endl;
                        cout << "You have ";
                        knight->display_health();
                        cout << " life left!" << endl;
                        if(knight->is_dead())
                        {
                            return false;
                        }
                    }
                    else
                    {
                        battle_banner();
                        knight->take_damage(opponent.attack() * 2);
                        cout << "Phew! Your opponent missed!" << endl;
                        cout << "You have ";
                        opponent.display_health();
                        cout << " life left!" << endl;
                    }
                }
            }

        break;
        }
    }
    return false;
}

//Simlar to the others but takes a rogue argument. 
bool Battle::rogue_battle(Character *& rogue)
{
    int     choice = 0;
    int     result = 0;
    bool    ability = false;
    
    result = rand() % 3;
    ++round;

    //Generates a random opponent
    switch (result)
    {
        case 0:
        {
            Barbarian opponent;

            //Levels up the opponent to match the User
            while (opponent.check_level() < rogue->check_level())
            {
                opponent.level_up();
                opponent.full_heal();
            }

            //Begin the fight!
            cout << "()xxx[:::::::::::>FIGHT<:::::::::::]xxx()" << endl << endl;
            rogue->display_name(); 
            cout << "  VS Generic "; 
            opponent.display_name();
            cout << endl << endl;
            rogue->display_all();

            //Time to duke it out
            while (rogue->health() >= 0 || opponent.health() >= 0)
            {
                bool    hero_miss = random.miss();
                bool    hero_crit = random.critical_strike();
                bool    enemy_miss = random.miss();
                bool    enemy_crit = random.critical_strike();
                int     hero_hp = rogue->health();
                int     enemy_hp = opponent.health();

                cout << "What would you like to do? Press corresponding number:\n";
                cout << "1. Attack\n2. Heal\n";
                cin >> choice; cin.ignore(100, '\n');

                if(choice == 1)
                {
                    //if the rogue is faster, then attacks first based on hit
                    //and crit chance, then the opponent.attacks by default
                    if (rogue->check_speed() >= opponent.check_speed())
                    {
                        if(hero_miss == false && hero_crit == true)
                        {
                            battle_banner();
                            opponent.take_damage(rogue->attack() * 2);
                            
                            //turns off rogue ability if it is activated
                            if(ability)
                                ability = rogue->end_vanish();
                            
                            cout << "Critical Strike! Your opponent receives "
                                << enemy_hp - opponent.health() << "points of damage!" << endl;
                            cout << "Your opponent has ";
                            opponent.display_health();
                            cout << " life left!" << endl;
                            if(opponent.is_dead())
                            {
                                return true;
                            }
                        }
                        else if (hero_miss == false && hero_crit == false)
                        {
                            battle_banner();
                            opponent.take_damage(rogue->attack());
                            
                            //turns off rogue ability if it is activated
                            if(ability)
                                ability = rogue->end_vanish();
                            
                            cout << "You hit the opponent for " << enemy_hp - opponent.health()
                            << " points of damage!" << endl;
                            cout << "Your opponent has ";
                            opponent.display_health();
                            cout << " life left!" << endl;
                            if(opponent.is_dead())
                            {
                                return true;
                            }
                        }
                        else
                        {
                            //turns off rogue ability if it is activated
                            if(ability)
                                ability = rogue->end_vanish();
                            
                            battle_banner();
                            cout << "haha! You missed!" << endl;
                            cout << "Your opponent has ";
                            opponent.display_health();
                            cout << " life left!" << endl;
                        }
                        
                        //Time for opponent's turn
                        if(ability)
                        {
                            battle_banner();
                            cout << "The enemy swings at thin air!" << endl;
                            break;
                        }
                        if(enemy_miss == false && enemy_crit == true)
                        {
                            battle_banner();
                            rogue->take_damage(opponent.attack() * 2);
                            cout << "Critical Strike! Your opponent hits you for "
                                << hero_hp - rogue->health() << "points of damage!" << endl;
                            cout << "You have ";
                            opponent.display_health();
                            cout << " life left!" << endl;
                            if(rogue->is_dead())
                            {
                                return false;
                            }
                        }
                        else if (enemy_miss == false && enemy_crit == false)
                        {
                            battle_banner();
                            rogue->take_damage(opponent.attack());
                            cout << "The opponent hits you for " << hero_hp - rogue->health()
                            << " points of damage!" << endl;
                            cout << "You have ";
                            rogue->display_health();
                            cout << " life left!" << endl;
                            if(rogue->is_dead())
                            {
                                return false;
                            }
                        }
                        else
                        {
                            battle_banner();
                            cout << "Phew! Your opponent missed!" << endl;
                            cout << "You have ";
                            opponent.display_health();
                            cout << " life left!" << endl;
                        }
                    }
                    //Now I have to do it backwards for if the opponent is faster... yikes
                    else
                    {
                        if(ability)
                        {
                            battle_banner();
                            cout << "Your opponent swings at thin air!" << endl;
                            break;
                        }
                        if(enemy_miss == false && enemy_crit == true)
                        {
                            battle_banner();
                            rogue->take_damage(opponent.attack() * 2);
                            cout << "Critical Strike! Your opponent hits you for "
                                << hero_hp - rogue->health() << "points of damage!" << endl;
                            cout << "You have ";
                            opponent.display_health();
                            cout << " life left!" << endl;
                            if(rogue->is_dead())
                            {
                                return false;
                            }
                        }
                        else if (enemy_miss == false && enemy_crit == false)
                        {
                            battle_banner();
                            rogue->take_damage(opponent.attack());
                            cout << "The opponent hits you for " << hero_hp - rogue->health()
                            << " points of damage!" << endl;
                            cout << "You have ";
                            rogue->display_health();
                            cout << " life left!" << endl;
                            if(rogue->is_dead())
                            {
                                return false;
                            }
                        }
                        else
                        {
                            battle_banner();
                            cout << "Phew! Your opponent missed!" << endl;
                            cout << "You have ";
                            opponent.display_health();
                            cout << " life left!" << endl;
                        }

                        // Now the slower rogues turn
                        if(hero_miss == false && hero_crit == true)
                        {
                            battle_banner();
                            opponent.take_damage(rogue->attack() * 2);
                            
                            //turns off rogue ability if it is activated
                            if(ability)
                                ability = rogue->end_vanish();
                            
                            cout << "Critical Strike! Your opponent receives "
                                << enemy_hp - opponent.health() << "points of damage!" << endl;
                            cout << "Your opponent has ";
                            opponent.display_health();
                            cout << " life left!" << endl;
                            if(opponent.is_dead())
                            {
                                return true;
                            }
                        }
                        else if (hero_miss == false && hero_crit == false)
                        {
                            battle_banner();
                            opponent.take_damage(rogue->attack());
                            
                            //turns off rogue ability if it is activated
                            if(ability)
                                ability = rogue->end_vanish();
                            
                            cout << "You hit the opponent for " << enemy_hp - opponent.health()
                            << " points of damage!" << endl;
                            cout << "Your opponent has ";
                            opponent.display_health();
                            cout << " life left!" << endl;
                            if(opponent.is_dead())
                            {
                                return true;
                            }
                        }
                        else
                        {
                            //turns off rogue ability if it is activated
                            if(ability)
                                ability = rogue->end_vanish();
                            
                            battle_banner();
                            cout << "haha! You missed!" << endl;
                            cout << "Your opponent has ";
                            opponent.display_health();
                            cout << " life left!" << endl;
                        }
                    }
                    
                }
                // If the user didn't use attack then they used their ability and the opponent
                // will get attack in. Will will assume abilities have priority for 
                // the sake of brevity. 
                else
                {
                    battle_banner();
                    cout << "You used vanish! Your next attack will have bonus damage!" <<endl;
                    ability = rogue->start_vanish();
                    
                    // Now the enemy attacks by default
                    // but we are stealthed so they miss! yay! less code!
                    cout << "Your opponent swings at thin air!" << endl;
                }
            }
        
        break;
        }
        // Creates a rogue to fight and does the same as case 0
        case 1:
        {
            Knight opponent;

            //Levels up the opponent to match the User
            while (opponent.check_level() < rogue->check_level())
            {
                opponent.level_up();
                opponent.full_heal();
            }

            //Begin the fight!
            cout << "()xxx[:::::::::::>FIGHT<:::::::::::]xxx()" << endl << endl;
            rogue->display_name(); 
            cout << " VS Generic "; 
            opponent.display_name();
            cout << endl << endl;
            rogue->display_all();

            //Time to duke it out
            while (rogue->health() >= 0 || opponent.health() >= 0)
            {
                bool    hero_miss = random.miss();
                bool    hero_crit = random.critical_strike();
                bool    enemy_miss = random.miss();
                bool    enemy_crit = random.critical_strike();
                int     hero_hp = rogue->health();
                int     enemy_hp = opponent.health();
                
                cout << "What would you like to do? Press corresponding number:\n";
                cout << "1. Attack\n2. Vanish\n";
                cin >> choice; cin.ignore(100, '\n');

                if(choice == 1)
                {
                    //if the rogue is faster, then attacks first based on hit
                    //and crit chance, then the opponent.attacks by default
                    if (rogue->check_speed() >= opponent.check_speed())
                    {
                        if(hero_miss == false && hero_crit == true)
                        {
                            battle_banner();
                            opponent.take_damage(rogue->attack() * 2);
                            
                            //turns off rogue ability if it is activated
                            if(ability)
                                ability = rogue->end_vanish();
                            
                            cout << "Critical Strike! Your opponent receives "
                                << enemy_hp - opponent.health() << "points of damage!" << endl;
                            cout << "Your opponent has ";
                            opponent.display_health();
                            cout << " life left!" << endl;
                            if(opponent.is_dead())
                            {
                                return true;
                            }
                        }
                        else if (hero_miss == false && hero_crit == false)
                        {
                            battle_banner();
                            opponent.take_damage(rogue->attack());
                        
                            //turns off rogue ability if it is activated
                            if(ability)
                                ability = rogue->end_vanish();
                            
                            cout << "You hit the opponent for " << enemy_hp - opponent.health()
                            << " points of damage!" << endl;
                            cout << "Your opponent has ";
                            opponent.display_health();
                            cout << " life left!" << endl;
                            if(opponent.is_dead())
                            {
                                return true;
                            }
                        }
                        else
                        {
                            battle_banner();
                            //turns off rogue ability if it is activated
                            if(ability)
                                ability = rogue->end_vanish();
                            
                            cout << "haha! You missed!" << endl;
                            cout << "Your opponent has ";
                            opponent.display_health();
                            cout << " life left!" << endl;
                        }
                        
                        //Time for opponent's turn
                        if(ability)
                        {
                            battle_banner();
                            cout << "Your opponent swings at thin air!" << endl;
                            break;
                        }
                        if(enemy_miss == false && enemy_crit == true)
                        {
                            battle_banner();
                            rogue->take_damage(opponent.attack() * 2);
                            cout << "Critical Strike! Your opponent hits you for "
                                << hero_hp - rogue->health() << "points of damage!" << endl;
                            cout << "You have ";
                            opponent.display_health();
                            cout << " life left!" << endl;
                            if(rogue->is_dead())
                            {
                                return false;
                            }
                        }
                        else if (enemy_miss == false && enemy_crit == false)
                        {
                            battle_banner();
                            rogue->take_damage(opponent.attack());
                            cout << "The opponent hits you for " << hero_hp - rogue->health()
                            << " points of damage!" << endl;
                            cout << "You have ";
                            rogue->display_health();
                            cout << " life left!" << endl;
                            if(rogue->is_dead())
                            {
                                return false;
                            }
                        }
                        else
                        {
                            battle_banner();
                            cout << "Phew! Your opponent missed!" << endl;
                            cout << "You have ";
                            opponent.display_health();
                            cout << " life left!" << endl;
                        }
                    }
                    //Now I have to do it backwards for if the opponent is faster... yikes
                    else
                    {
                        if(ability)
                        {
                            battle_banner();
                            cout << "Your opponent swings at thin air!" << endl;
                            break;
                        }
                        if(enemy_miss == false && enemy_crit == true)
                        {
                            battle_banner();
                            rogue->take_damage(opponent.attack() * 2);
                            cout << "Critical Strike! Your opponent hits you for "
                                << hero_hp - rogue->health() << "points of damage!" << endl;
                            cout << "You have ";
                            opponent.display_health();
                            cout << " life left!" << endl;
                            if(rogue->is_dead())
                            {
                                return false;
                            }
                        }
                        else if (enemy_miss == false && enemy_crit == false)
                        {
                            battle_banner();
                            rogue->take_damage(opponent.attack());
                            cout << "The opponent hits you for " << hero_hp - rogue->health()
                            << " points of damage!" << endl;
                            cout << "You have ";
                            rogue->display_health();
                            cout << " life left!" << endl;
                            if(rogue->is_dead())
                            {
                                return false;
                            }
                        }
                        else
                        {
                            battle_banner();
                            cout << "Phew! Your opponent missed!" << endl;
                            cout << "You have ";
                            opponent.display_health();
                            cout << " life left!" << endl;
                        }

                        // Now the slower rogues turn
                        if(hero_miss == false && hero_crit == true)
                        {
                            battle_banner();
                            opponent.take_damage(rogue->attack() * 2);
                            //turns off rogue ability if it is activated
                            if(ability)
                                ability = rogue->end_vanish();
                            
                            cout << "Critical Strike! Your opponent receives "
                                << enemy_hp - opponent.health() << "points of damage!" << endl;
                            cout << "Your opponent has ";
                            opponent.display_health();
                            cout << " life left!" << endl;
                            if(opponent.is_dead())
                            {
                                return true;
                            }
                        }
                        else if (hero_miss == false && hero_crit == false)
                        {
                            battle_banner();
                            opponent.take_damage(rogue->attack());
                            //turns off rogue ability if it is activated
                            if(ability)
                                ability = rogue->end_vanish();
                            
                            cout << "You hit the opponent for " << enemy_hp - opponent.health()
                            << " points of damage!" << endl;
                            cout << "Your opponent has ";
                            opponent.display_health();
                            cout << " life left!" << endl;
                            if(opponent.is_dead())
                            {
                                return true;
                            }
                        }
                        else
                        {
                            //turns off rogue ability if it is activated
                            if(ability)
                                ability = rogue->end_vanish();
                            
                            battle_banner();
                            cout << "haha! You missed!" << endl;
                            cout << "Your opponent has ";
                            opponent.display_health();
                            cout << " life left!" << endl;
                        }
                    }
                    
                }
                // If the user didn't use attack then they used their ability and the opponent
                // will get attack in. Will will assume abilities have priority for 
                // the sake of brevity. 
                else
                {
                            battle_banner();
                    cout << "You used vanish! Your next attack will have bonus damage!" <<endl;
                    ability = rogue->start_vanish();
                    
                    // Now the enemy attacks by default
                    // but we are stealthed so they miss! yay! less code!
                    cout << "Your opponent swings at thin air!" << endl;
                }            
            }
        break;
        }
        case 2:
        {
            Rogue opponent;

            //Levels up the opponent to match the User
            while (opponent.check_level() < rogue->check_level())
            {
                opponent.level_up();
                opponent.full_heal();
            }

            //Begin the fight!
            cout << "()xxx[:::::::::::>FIGHT<:::::::::::]xxx()" << endl << endl;
            rogue->display_name(); 
            cout << " VS Generic "; 
            opponent.display_name();
            cout << endl << endl;
            rogue->display_all();

            //Time to duke it out
            while (rogue->health() >= 0 || opponent.health() >= 0)
            {
                bool    hero_miss = random.miss();
                bool    hero_crit = random.critical_strike();
                bool    enemy_miss = random.miss();
                bool    enemy_crit = random.critical_strike();
                int     hero_hp = rogue->health();
                int     enemy_hp = opponent.health();

                cout << "What would you like to do? Press corresponding number:\n";
                cout << "1. Attack\n2. Vanish\n";
                cin >> choice; cin.ignore(100, '\n');

                if(choice == 1)
                {

                    //if the rogue is faster, then attacks first based on hit
                    //and crit chance, then the opponent.attacks by default
                    if (rogue->check_speed() >= opponent.check_speed())
                    {
                        if(hero_miss == false && hero_crit == true)
                        {
                            battle_banner();
                            opponent.take_damage(rogue->attack() * 2);
                            //turns off rogue ability if it is activated
                            if(ability)
                                ability = rogue->end_vanish();
                            
                            cout << "Critical Strike! Your opponent receives "
                                << enemy_hp - opponent.health() << "points of damage!" << endl;
                            cout << "Your opponent has ";
                            opponent.display_health();
                            cout << " life left!" << endl;
                            if(opponent.is_dead())
                            {
                                return true;
                            }
                        }
                        else if (hero_miss == false && hero_crit == false)
                        {
                            battle_banner();
                            opponent.take_damage(rogue->attack());
                            //turns off rogue ability if it is activated
                            if(ability)
                                ability = rogue->end_vanish();
                            
                            cout << "You hit the opponent for " << enemy_hp - opponent.health()
                            << " points of damage!" << endl;
                            cout << "Your opponent has ";
                            opponent.display_health();
                            cout << " life left!" << endl;
                            if(opponent.is_dead())
                            {
                                return true;
                            }
                        }
                        else
                        {
                            //turns off rogue ability if it is activated
                            if(ability)
                                ability = rogue->end_vanish();
                            
                            battle_banner();
                            cout << "haha! You missed!" << endl;
                            cout << "Your opponent has ";
                            opponent.display_health();
                            cout << " life left!" << endl;
                        }
                        
                        //Time for opponent's turn
                        if(ability)
                        {
                            battle_banner();
                            cout << "Your opponent swings at thin air!" << endl;
                            break;
                        }
                        if(enemy_miss == false && enemy_crit == true)
                        {
                            battle_banner();
                            rogue->take_damage(opponent.attack() * 2);
                            cout << "Critical Strike! Your opponent hits you for "
                                << hero_hp - rogue->health() << "points of damage!" << endl;
                            cout << "You have ";
                            opponent.display_health();
                            cout << " life left!" << endl;
                            if(rogue->is_dead())
                            {
                                return false;
                            }
                        }
                        else if (enemy_miss == false && enemy_crit == false)
                        {
                            battle_banner();
                            rogue->take_damage(opponent.attack());
                            cout << "The opponent hits you for " << hero_hp - rogue->health()
                            << " points of damage!" << endl;
                            cout << "You have ";
                            rogue->display_health();
                            cout << " life left!" << endl;
                            if(rogue->is_dead())
                            {
                                return false;
                            }
                        }
                        else
                        {
                            battle_banner();
                            cout << "Phew! Your opponent missed!" << endl;
                            cout << "You have ";
                            opponent.display_health();
                            cout << " life left!" << endl;
                        }
                    }
                    //Now I have to do it backwards for if the opponent is faster... yikes
                    else
                    {
                        if(ability)
                        {
                            battle_banner();
                            cout << "Your opponent swings at thin air!" << endl;
                            break;
                        }
                        if(enemy_miss == false && enemy_crit == true)
                        {
                            battle_banner();
                            rogue->take_damage(opponent.attack() * 2);
                            cout << "Critical Strike! Your opponent hits you for "
                                << hero_hp - rogue->health() << "points of damage!" << endl;
                            cout << "You have ";
                            opponent.display_health();
                            cout << " life left!" << endl;
                            if(rogue->is_dead())
                            {
                                return false;
                            }
                        }
                        else if (enemy_miss == false && enemy_crit == false)
                        {
                            battle_banner();
                            rogue->take_damage(opponent.attack());
                            cout << "The opponent hits you for " << hero_hp - rogue->health()
                            << " points of damage!" << endl;
                            cout << "You have ";
                            rogue->display_health();
                            cout << " life left!" << endl;
                            if(rogue->is_dead())
                            {
                                return false;
                            }
                        }
                        else
                        {
                            battle_banner();
                            cout << "Phew! Your opponent missed!" << endl;
                            cout << "You have ";
                            opponent.display_health();
                            cout << " life left!" << endl;
                        }

                        // Now the slower rogues turn
                        if(hero_miss == false && hero_crit == true)
                        {
                            battle_banner();
                            opponent.take_damage(rogue->attack() * 2);
                            //turns off rogue ability if it is activated
                            if(ability)
                                ability = rogue->end_vanish();
                            
                            cout << "Critical Strike! Your opponent receives "
                                << enemy_hp - opponent.health() << "points of damage!" << endl;
                            cout << "Your opponent has ";
                            opponent.display_health();
                            cout << " life left!" << endl;
                            if(opponent.is_dead())
                            {
                                return true;
                            }
                        }
                        else if (hero_miss == false && hero_crit == false)
                        {
                            battle_banner();
                            opponent.take_damage(rogue->attack());
                            //turns off rogue ability if it is activated
                            if(ability)
                                ability = rogue->end_vanish();
                            
                            cout << "You hit the opponent for " << enemy_hp - opponent.health()
                            << " points of damage!" << endl;
                            cout << "Your opponent has ";
                            opponent.display_health();
                            cout << " life left!" << endl;
                            if(opponent.is_dead())
                            {
                                return true;
                            }
                        }
                        else
                        {
                            //turns off rogue ability if it is activated
                            if(ability)
                                ability = rogue->end_vanish();
                            
                            battle_banner();
                            cout << "haha! You missed!" << endl;
                            cout << "Your opponent has ";
                            opponent.display_health();
                            cout << " life left!" << endl;
                        }
                    }
                    
                }
                // If the user didn't use attack then they used their ability and the opponent
                // will get attack in. Will will assume abilities have priority for 
                // the sake of brevity. 
                else
                {
                    battle_banner();
                    cout << "You used vanish! Your next attack will have bonus damage!" <<endl;
                    ability = rogue->start_vanish();
                    
                    // Now the enemy attacks by default
                    // but we are stealthed so they miss!
                    cout << "Your opponent swings at thin air!" << endl;
                }
            }
        break;
        }
    }
    return false;
}

// Takes Barbarian object and causes a random effect to it
void Battle::barb_between_rounds(Character *& barb)
{
    long result = 0;

    result = (rand()%3);
    switch (result)
    {
        case 0:
            barb->take_damage(100);
            cout << "Ouch! A spike trap? Who put that there?" << endl;
            cout << "You took 100 points of damage!" << endl;
            break;
        case 1:
            {
            barb->heal(100);
            cout << "Oh hey! A tasty sandwich!" << endl;
            cout << "You gained 100 life! Yum!" << endl;
            break;
            }
        case 2:
            {
            barb->heal(10000);
            cout << "You are treated to a 5-course meal. Excellent." << endl;
            cout << "You are fully healed!" << endl;
            break;
            }
    }
}

// Takes Knight object and causes a random effect to it
void Battle::knight_between_rounds(Character *& knight)
{
    long result = 0;

    result = (rand()%3);

    switch (result)
    {
        case 0:
            {
            knight->take_damage(100);
            cout << "Ouch! A spike trap? Who put that there?" << endl;
            cout << "You took 100 points of damage!" << endl;
            break;
            }
        case 1:
            {
            knight->heal(100);
            cout << "Oh hey! A tasty sandwich!" << endl;
            cout << "You gained 100 life! Yum!" << endl;
            break;
            }
        case 2:
            {
            knight->heal(10000);
            cout << "You are treated to a 5-course meal. Excellent." << endl;
            cout << "You are fully healed!" << endl;
            break;
            }
    }
}

// Takes Rogue object and causes a random effect to it
void Battle::rogue_between_rounds(Character *& rogue)
{
    int result = 0;

    result = (rand()%3);

    switch (result)
    {
        case 0:
            {
            rogue->take_damage(100);
            cout << "Ouch! A spike trap? Who put that there?" << endl;
            cout << "You took 100 points of damage!" << endl;
            break;
            }
        case 1:
            {
            rogue->heal(100);
            cout << "Oh hey! A tasty sandwich!" << endl;
            cout << "You gained 100 life! Yum!" << endl;
            break;
            }
        case 2:
            {
            rogue->heal(10000);
            cout << "You are treated to a 5-course meal. Excellent." << endl;
            cout << "You are fully healed!" << endl;
            break;
            }
    }
}

//used to make output of fight a little cleaner
void Battle::battle_banner() const
{
    cout << endl << "---------------------------------------------" << endl << endl;
}

// Keep track of round in main
int Battle::get_round() const
{
    return round;
}
