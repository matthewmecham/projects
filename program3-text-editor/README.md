# Text Editor

## Overview
For this challenge, I was prompted to make a very basic text editor in a little over two weeks. The main purpose of this program was to learn and practice operator overloading and to further increase my skills with recursion and data structures. In my studies, I have been forbidden to use the string library, forcing me to work with and understand dynamic memory and arrays of chars. For this program, I was allowed to create my own string class for use with full operator functionality. I wrote this program in Vim on a Linux server. I compiled it using g++ with the command `g++ *.cpp .h -g -Wall`. All debugging was done using Gnu Debugger's CLI (and boy was there a lot of it). The program assumes that the common_mispelled_words.txt file is in the same directory as the program.

### New C++ Tools
- Operator Overloading

### Requirements
- Create a string class with fully implemented operator overloading
- Implement some form of text highlighting to indicate mispelled words
- Implement a balanced 2-3 Tree recursively - no iteration allowed.

## Summary
Operator overloading for a string class was simple enough but it gave me practice with the syntax. More importantly, I learned how operator overloading can be very useful for client side use and it is one of the things that makes C++ unique and powerful; allowing for the complete deep copy of an object and all of its members with a simple assignment operator is just one example of its use. By far the hardest part of this, and my proudest accomplishment, was the implementation of a balanced 2-3 tree. I spent the vast majority of the two weeks on this. In doing so, my skill with the Gnu Debugger increased immensely. In order to support "highlighting" of a user's string, I created a file of the one-thousand most common mispelled words and populated my 2-3 tree with these words. The idea was that when the user input a word, I would check my data base for a match and, if there was a match, I would capitalize the string to indicate a mispelling. Due to the complexity of a fully recursive insertion, retrieval, and displaying of a 2-3 tree, I did not get to fully flush out my vision for this challenge but gained valuable practice and skills nonetheless. I recieved high marks regardless.
