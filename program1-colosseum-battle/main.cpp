// Matthew Mecham -- 10/22/2019 -- Program 1

// This program lets you pick one of three different characters
// and allows you to fight a randomly generated opponent of a similar
// level. Once your character has achieved 10 wins then that character
// has won. If they die, then you have to start over.

#include "cll.h"

int main()
{
    srand(time(NULL)); // set random seed
    int     max = 100; // Max characters in temp 
    int     choice = 0; // Holds user choice 
    char    response = 0; //
    char    temp[max]; // Used to name things
    char    owner[max]; // Keeps track of who is playing
    bool    stop = false; // Flag to release player from playing the game
    bool    continue_fight = true; // Let's player break out of battle early
    bool    victory = true; // checks if the player one their fight or not

    CLL list; // This CLL object - Nodes are delimited by username - each node has a dynamic array of Character objects
    Character * hero; // A base class pointer so I don't have to write a gross amount of code like my battle class
    Battle fight; // The class object that will handle fighting between Character objects
    
    cout << "Welcome to Matt Mecham's Battle Colosseum!" << endl
        << "Who will be playing today? (please enter unique name): ";
    cin.get(owner, max, '\n');
    list.set_owner(owner);

    // Will keep user playing until they want to be done
    while (!stop)
    {
        cout << "What would you like to send into the colosseum today?" << endl;
        cout << "1. Barbarian - Barbarian Rage increases strength at the cost of defense." << endl;
        cout << "2. Knight - Heavy Armor and the ability to heal in combat." << endl;
        cout << "3. Rogue - Can vanish into the shadows and strike with extra damage." << endl;
        cin >> choice; cin.ignore(100,'\n');
        cout << endl;

        // This switch will begin the battle sequence based on what character they chose.
        switch(choice)
        {
            // Starts Barbarian Specific Battle
            case 1:
            {
                Barbarian barb; //Generates Barb object based on user choice
                cout << "What is this Barbarian's name?: ";
                cin.get(temp, max, '\n');
                barb.change_name(temp);
                barb.level_up(); //It starts at level 0 so this makes it level 1
                barb.full_heal(); // Based on how it levels up, I need to fully heal the character
                hero = &barb; 
                fight.welcome();
                cout << "You are experiencing history! Win 10 times for glory!" << endl;
                cout << "After every round you will have the option of quitting and saving your character!" << endl;
                cout << "Let us begin!" << endl;
                // If they have less than 10 wins, want to keep fighting, and win their fight
                // they will be able to play with their current character
                while(fight.get_round() < 10 && continue_fight && victory)
                {
                    victory = fight.barb_battle(hero);
                    if (victory)
                    {
                        cout << "You win!!" << endl;
                        cout << "Your hero levels up! You completed round: " << fight.get_round();
                        if (fight.get_round() == 10)
                        {
                            cout << "10 wins! You are a god damned legend! *air horn*" << endl;
                            break;
                        }
                        hero->level_up();
                        cout << "Would you like to send your character back in for more? [Y/N]: ";
                        cin >> response; cin.ignore(100,'\n');
                        if(toupper(response) == 'Y')
                        {
                            continue_fight = true;
                            fight.barb_between_rounds(hero);
                        }
                        else
                        {
                            continue_fight = false;
                            cout << "Saving your character..." << endl;
                            list.add_barb(hero, owner);
                        }
                    }
                    else
                    {
                        cout << "You lose - This is not a very balanced game. Better luck next time!" << endl;
                    }
                }
                break;
            }
            // Starts Knight Specific Battle
            case 2:
            {
                Knight knight;
                cout << "What is this Knight's name?: ";
                cin.get(temp, max, '\n');
                knight.change_name(temp);
                knight.level_up();
                knight.full_heal();
                hero = &knight;
                fight.welcome();
                cout << "You are experiencing history! Win 10 times for glory!" << endl;
                cout << "After every round you will have the option of quitting and saving your character!" << endl;
                cout << "Let us begin!" << endl;
                // If they have less than 10 wins, want to keep fighting, and win their fight
                // they will be able to play with their current character
                while(fight.get_round() < 10 && continue_fight && victory)
                {
                    victory = fight.knight_battle(hero);
                    if (victory)
                    {
                        cout << "You win!!" << endl;
                        cout << "Your hero levels up! You completed round: " << fight.get_round();
                        if (fight.get_round() == 10)
                        {
                            cout << "10 wins! You are a god damned legend! *air horn*" << endl;
                            break;
                        }
                        hero->level_up();
                        cout << "Would you like to send your character back in for more? [Y/N]: ";
                        cin >> response; cin.ignore(100,'\n');
                        if(toupper(response) == 'Y')
                        {
                            continue_fight = true;
                            fight.knight_between_rounds(hero);
                        }
                        else
                        {
                            continue_fight = false;
                            cout << "Saving your character..." << endl;
                            list.add_knight(hero, owner);
                        }
                    }
                    else
                    {
                        cout << "You lose - this is not a very balanced game. Better luck next time!" << endl;
                    }
                }
                break;
            }
            // Rogue Specific Battle
            case 3:
            {
                Rogue rogue;
                cout << "What is this Rogue's name?: ";
                cin.get(temp, max, '\n');
                rogue.change_name(temp);
                rogue.level_up();
                rogue.full_heal();
                hero = &rogue;
                fight.welcome();
                cout << "You are experiencing history! Win 10 times for glory!" << endl;
                cout << "After every round you will have the option of quitting and saving your character!" << endl;
                cout << "Let us begin!" << endl;
                // If they have less than 10 wins, want to keep fighting, and win their fight
                // they will be able to play with their current character
                while(fight.get_round() < 10 && continue_fight && victory)
                {
                    victory = fight.rogue_battle(hero);
                    if (victory)
                    {
                        cout << "You win!!" << endl;
                        cout << "Your hero levels up! You completed round: " << fight.get_round();
                        if (fight.get_round() == 10)
                        {
                            cout << "10 wins! You are a god damned legend! *air horn*" << endl;
                            break;
                        }
                        hero->level_up();
                        cout << "Would you like to send your character back in for more? [Y/N]: ";
                        cin >> response; cin.ignore(100,'\n');
                        if(toupper(response) == 'Y')
                        {
                            continue_fight = true;
                            fight.rogue_between_rounds(hero);
                        }
                        else
                        {
                            continue_fight = false;
                            cout << "Saving your character..." << endl;
                            list.add_rogue(hero, owner);
                        }
                    }
                    else
                    {
                        cout << "You lose - this is not a very balanced game. Better luck next time!" << endl;
                    }
                }
                break;
            }
        } 
        // At this point, they have either won, lost or quit their current character.
        // I will now give them the option of exiting the program or playing again.
        cout << endl << "What a rush! Would you like to send another soul in for the chance of glory? [Y/N]: ";
        cin >> response; cin.ignore(100, '\n');
        if(toupper(response) == 'Y')
            stop = false;
        else
            stop = true;
    }
        
    cout << "El fin" << endl; 

    return 0;
}

