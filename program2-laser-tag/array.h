#include "abc.h"
// Matthew Mecham - CS202 - Program 2 - 10/31/2019

// - This file is all about making an array of doubly linked lists
// - You will have the option of inserting either a path, obstacle, home base, or player
// - Each node will have an ABC base pointer which will be used to create
// the object within the node. 
// - The array class will have a node head and tail pointer and I will create an array of class
// pointers with which I will generate the lists at each index.
// - Using these, I will create a crude map of a laser tag arena

class Node
{
    public:
        Node();
        Node(int index, int link);
        ~Node();
        
        Node    *& go_next();
        Node    *& go_prev();
        void    display();
        void    make_obstacle();
        void    make_player();
        void    make_pathway();
        void    make_home();

    protected:
        ABC     * base_ptr;
        Node    * next;
        Node    * previous;
        int     index_location;
        int     link_location;
};

class Array
{
    public:
        Array();
        Array(int max_size, int max_links);
        ~Array();

        void    insert_obstacle(int index, int link);
        void    insert_player(int index, int link);
        void    insert_pathway(int index, int link);
        void    insert_home(int index, int link);
        void    build_demo();
        void    remove(int index, int link);
        void    remove_row();
        void    display_row();
        void    display_arena();
        int     inc_link_count();
        int     inc_index_count();

    protected:
        Node    * head;
        Node    * tail;
        int     size;
        int     index_count;
        int     links;
        int     link_count;
        void    insert_obstacle(Node *& head, Node *& tail, int index, int link);
        void    insert_player(Node *& head, Node *& tail, int index, int link);
        void    insert_pathway(Node *& head, Node *& tail, int index, int link);
        void    insert_home(Node *& head, Node *& tail, int index, int link);
        void    remove_row(Node *& head, Node *& tail);
        void    display_row(Node *& head, Node *& tail);
        void    display_arena(int array_size);
        Array   *arena;
};
