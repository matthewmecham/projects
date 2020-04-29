# Colosseum Battle


## Overview

The overall idea behind this challenge was to create a colosseum battle game where the user could choose a character and engage in some sort of combat. This first program was designed to introduce us to using Object Oriented Programming (OOP). A minimum of five classes was required as well as utilizing single inheritance. I had a little over two weeks to work on this program - no errors or warnings allowed by the deadline. It was created in Vim on a Linux server and compiled with g++ using the command `g++ *.cpp *.h -g -Wall`. All debugging was done using Gnu Debugger's CLI. All .cpp files and .h files are required for the program. 

### New C++ and OOP tools
- UML diagrams that help create a heirarchy and identify common function that can be pushed to the base class
- Using single inheritance to create a safe hierarchy with properly protected data members
- Constructors, Copy Constructors, Destructors, Constructors with Args

### Game Requirements:
- At least three unique characters to choose from with various stengths and weaknesses
- Characters get stronger in some way throughout the game
- Random events occur throughout gameplay
- While battle is commencing, update the user on the status of combat
- Provide various choices based on character during combat

### Data Structure Requirements
- Keep track of a specific user's different characters using a circular linked list of arrays
- Keep track of the character's wins and losses with a array of linked lists with seperated wins and losses
- Implementation of data structures should have full support of insert, display, remove, retrieve, and remove all functions
- All data structure implementation must be recrusive - no iteration! 

## Summary

This exercise was by far the largest and most robust programming endeavor to be put before me at this point in time. Truly, it was never intended for us to have fully implemented all requirements by the deadline. It really forced me to embrace the design phase and utilize UML diagrams. Being my first ever UML diagram, it was a little uncomfortable but, by the end, having a visual representation of my hierarchy and control flow became utterly invaluable. Proper time spent designing my UML diagram allowed me to stop being intimidated and start creating. The practice with new c++ syntax and techniques was, of course, challenging and rewarding but time spent designing was my biggest take-away. By the end of the deadline, the only requirement I was missing was the array of linked lists to keep track of win/losses. I recieved high marks. 
