# Pizza/Burger Order

## Overview
This challenge was remeniscent of past learning exercises I have done; however, this one came with a twist: program it in Java. This is the very first time I have programmed in Java and, I have to say, I like it. For this challenge, I was to further practice designing an OOP hierarchy with an abstract base class (now called a superclass) to enable upcasting and dynamic binding. The premise of this program was to create an interface where a user could put together an order of two different food items. The two food items would allow the user to customize their food options with various ingredients and toppings. I had a little over two weeks to work on this project. It was written, compiled, and debugged in IntelliJ. All files are necessary and the program assumes the .txt files are in the source folder.

### Requirements
- Create a hierachy utilizing a superclass and dynamic binding
- Create an interface where a user can choose place an order
- Provide two options of food items with multiple choices for toppings/ingredients
- Read ingredients and toppings from an external file and populate an array of linked lists with the data
- Store orders as an object within a Binary Search Tree
- Implement data structures recursively, from scratch, with no iteration

### Java at a glance
Overall the design for this program was fairly simple but my C++ brain needed to learn some of the nuances of Java. I was surprised how much I could figure out in Java just from having experience with C++. "Thinking in Java" by Bruce Eckel helped too. Syntax is syntax but one of the core differences I learned between Java and C++ is that Java treats everything as an object and, while it doesn't give you direct access to pointers, it still utilizes pointer functionality constantly - it just doesn't let the user mess with them. Additionally, there is no pass by reference, which causes copy constructors to be invoked every time an object is passed as a parameter. 

## Summary
I decided the user's options would be between pizza and hamburgers as both have a variety of topping options and are similar enough to be derived from a superclass. When the program starts, two arrays of linked lists are created: one for pizza and one for burgers. When the user chose an option, an Order object was created, dynamic binding would be initiated with a superclass object assignemnt, and ingredients would be listed based on the user's choice (dynamic binding is great). Once the order was placed, it would act as a Node in the BST. I ran out of time and did not get the BST functional, however, it was only three functions away from operation. I recieved high marks and am excited for more Java in the future.
