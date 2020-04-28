#include "array.h"

// Matthew Mecham Program 2 - 10/31/2019

// This is a simple demonstration of my class' ability to use dynamic binding
// and an abstract base class to correctly call overridden function.
// I ran out of time and could not implement the player functions that would make this playable.
int main ()
{
    Array laser_tag(5,5); // Make the array object with a max link/array size

    laser_tag.build_demo(); // Builds arena mock-up

    cout << "Hello Wor... *cough* I mean... hello grader!" << endl;
    cout << "In this small demonstration of dynamic binding, " << endl
        << "each object in the arena is represented by certain characters." << endl
        << "The symbols are inspired by one of my favorite games, NetHack.\n" << endl
        << "Home Base: H\nPlayer: @\nObstacle: O\nPathway: .\n" << endl;
    cout << "Below is a small representation of what type of arena could be built.\n\n";

    laser_tag.display_arena();

    return 0;
}
