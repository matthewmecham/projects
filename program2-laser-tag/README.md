# Laser Tag

## Overview
For this challenge I was instructed to create a laser tag obstacle course in a little over two weeks. The main theme of this challenge was to familiarize myself with c++'s ability to utilize polymorphism to build the course. To experience polymorphism, we were to build a hierachy in which objects on the laser tag course were derived from an abstract base class - the derived classes being a player, obstacle (an obstruction of some sort), pathway, and a home base. I was also prompted to create an array of doubly linked lists to form the laster tag course. Then, utilize upcasting to have a pointer of type abstract base class traverse the data structure and output different things based on what object it was pointing to, which demonstrates the power of polymorphism. All data structure functions were to be implemented recursively and nodes must be classes. This was created in Vim on a Linux server using g++ for compilation with the command `g++ *.cpp *.h -g -Wall`. All debugging was done with GDB CLI. 

### New C++ Tools
- Polymorphism
- Upcasting
- RTTI (Run-Time Type Identification)
- Virtual keyword and Abstract Base Classes
- Proper use of initialization lists in derived classes to kickstart the base class's
copy constructor

## Summary
This challenge pushed me with new syntax more than anything. When this challenge came around, I welcomed the design phase and got right to creating a UMl Diagram that helped immensely with identifying what sort of functions the abstract base class needed and how to give unique functionality to my derived classes. Additionally, I was challenged by the concept of using a data structure to create something slightly visual; this was new to me. In previous exercises, data structures were very clever ways of using arrays and linked lists to store large amounts of data. I eventually wrapped my head around the idea of using a data structure to represent objects on a grid-like board. By having a pointer of type base class as a private data member in my Node class, I was able to easily and quickly traverse my data structure and ouput various things based on what the pointer was pointing to - upcasting is awesome. I really enjoyed learning about polymorphism and am very excited to have it as a tool in my kit.
