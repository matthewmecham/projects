#include "string.h"
//Matthew Mecham - Program 3 - 11/22/2019

//These two class work together to build a balanced, doubly-linked 2-3 Tree.
//It was a freaking nightmare but I am proud now.
//Using the overloaded Sring class operators, I was able read a file of common misspelled words and
//build the balanced 2-3 tree. Now, my editor can check the tree and will put the word in all capitals
//if it is found in the tree. For example "mispelled" would write "MISPELLED" into the file so the user
//can fix it later. That is the idea, anyways.
class Tree_Node
{
    public:
        Tree_Node();
        Tree_Node(const String &s, Tree_Node * ptr);
        ~Tree_Node();
        
        Tree_Node   *& go_left();
        Tree_Node   *& go_middle();
        Tree_Node   *& go_right();
        Tree_Node   *& go_parent();
        String      & get_word1();
        String      & get_word2();
           
        void        set_word1_null();
        void        set_word2_null();
        bool        is_leaf() const;
        bool        is_two_node();
        bool        is_three_node();
        bool        null_parent() const; // returns true if null


    protected:
        String      word1;
        String      word2;
        Tree_Node   * left;
        Tree_Node   * middle;
        Tree_Node   * right;
        Tree_Node   * parent;

};

// The tree is made up of Tree_Nodes that can each hold up to 2 string objects and can have
// up to 3 children and one parent. The algorithm goes a little something like this:
// 1. Traverse alphabetically with overloaded conditional operators until you arive at a leaf.
// 2. If the leaf only has one member, insert the word and call it good.
// 3. If the leaf is full, however, you must split the node.
// The smallest value is moved to a new node and kept track with the left pointer of the old leaf.
// The largest value goes to the right and the middle value now takes up the first member of the old leaf
// But, now maybe the tree is unbalanced since you just added another row. So...
// 4. Check if the parent of the middle value node is NULL - if it is then you are at the root and life is groovy.
// if the parent is !NULL, then you need to push_up() the middle node of the leaf you just split up until there is room for it,
// which balances the leaf and makes sure that it doesn't unnecessarily grow too large down one side. 
// This is where the most tedious sequence of pointer management I have ever experienced commenced. 
// Now that it is working and I understand, though, I am pretty proud of it! Good luck! 

class Two_Three_Tree
{
    public:
        Two_Three_Tree();
        ~Two_Three_Tree();

        void    insert(const String &s);
        bool    search(const String &s);
        void    highlight(String &s); //will highlight a few common misspelled words (like mispelled)
        void    build(); //will build from file
        


    protected:
        Tree_Node * root;
        bool    search(const String &s, Tree_Node *& root);
        void    insert(const String &s, Tree_Node *& root);
        void    split_leaf(const String &s, Tree_Node *& root);
        void    push_up(Tree_Node *& parent, Tree_Node * child);
        void    split_three_node(Tree_Node *& to_split, Tree_Node *& to_add);
};

// Alright, I am going to be straight with you. I did not implement these next two classes.
// As it turns out, figuring out a balanced, doubly linked 23Tree took an insane amount of time.
// I had to step through that monster in gdb for hours upon hours. I will explain what my idea was
// for this class before I lose my will and sleep for 20 straight hours.
class Node
{
    public:
        Node();
        Node(String &s);
        ~Node();

        Node    *& go_next();
        void    display();

    private:
        String  word;
        Node    * next;
};

// My idea for this class was to have each array index act like a line in an editor - length and max_length keeps track of this
// The max_size would then be the size of the page.
// The linked lists would be string objects and when their total lenghts became >= max_length, it would start inserting the string objects
// on the next line until the page was filled. During all this, I would check the string objects with the 23Tree which is full of
// common misspelled words. If there was a match, the string would be capatalized. Badda boom badda bing. Good night. Be nice. Love you. 
class Page
{
    public:
        Page();
        ~Page();
        void    insert(String &s);
        void    remove(String &s);
        void    write_string(String &s);
        void    read_string(String &s);
        void    display_all(); 

    protected:
        Node    * head;
        Node    * tail;
        void    insert(String &s, Node *& head, Node *& tail);
        void    remove(String &s, Node *& head, Node *& tail);
        int     size; // Keeps track of current size so we know when the end of the page is reached
        int     max_size; //this will be how many lines are allowed on one page
        int     length; //keeps track of current length - this will be used to know when the end of a line is released
        int     max_length; //this will be the end of the line
};
