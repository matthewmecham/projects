#include "battle.h"

// This file handles the generation of Nodes and the CLL in which the nodes
// will be placed. Each Node should be made with a unique username in mind. 
// When the CLL wants to save a Character object, it will check for the correct 
// username and store that object in an array of Character pointers. The array
// and the linked list can both grow to accommodate as many user and characters
// as the client wants. 
// Unfortuneately, I ran out of time and was unable to implement writing and reading 
// from a file.

class Node
{
    public:
        Node();
        Node(const Node & to_copy);
        ~Node();

        bool    insert_barb(Character *& barb);
        bool    insert_knight(Character *& knight);
        bool    insert_rogue(Character *& rogue);
        bool    remove_barb(Character *& user_barb);
        bool    remove_knight(Character *& user_knight);
        bool    remove_rogue(Character *& user_rogue);
        void    set_username(const char * name);
        char    * get_username() const;
        void    display_username() const;
        void    display() const;
        void    write();
        void    read();
        Node    *& go_next(); 
    protected:
        Node    * next;
        Character **characters;
        int     capacity;
        int     size;
        void    grow();
        char    * username;
};

class CLL
{
    public:
        CLL();
        ~CLL();
        void    insert_node(Node * p);
        int     remove(Node * p);
        int     display_nodes();
        int     add_barb(Character *& barb, char *owner);
        int     add_knight(Character *& knight, char *owner);
        int     add_rogue(Character *& rogue, char *owner);
        int     delete_barb(Character *& barb, char *owner);
        int     delete_knight(Character *& knight, char *owner);
        int     delete_rogue(Character *& rogue, char *owner);
        void    set_owner(const char * owner);

    protected:
        Node    * rear;
        int     display_nodes(Node * rear);
        int     add_barb(Character *& barb, char *owner, Node * rear);
        int     add_knight(Character *& knight, char *owner, Node * rear);
        int     add_rogue(Character *& rogue, char *owner, Node * rear);
        int     delete_barb(Character *& barb, char *owner, Node * rear);
        int     delete_knight(Character *& knight, char *owner, Node * rear);
        int     delete_rogue(Character *& rogue, char *owner, Node * rear);

        void    set_owner(const char * owner, Node * rear);
};
