#include "array.h"

// Matthew Mecham -- Program 2 - 10/31/2019


//----------------------------------------------------------------------
// Node Class Implementations
//----------------------------------------------------------------------

Node::Node():base_ptr(NULL), next(NULL), previous(NULL)
{

}

// This constructor with args will help keep track of where this node is in the data structure
// This will allow me to implement the move and shoot functionality of Player
Node::Node(int index, int link):base_ptr(NULL), next(NULL), previous(NULL)
                                , index_location(index), link_location(link)
{

}

Node::~Node()
{
    delete base_ptr;
    base_ptr = NULL;
} 

// Wrapper for protected next pointer
Node *& Node::go_next()
{
    return next;
}

// Wrapper for protected prev pointer
Node *& Node::go_prev()
{
    return previous;
}

// A dynamically bound display for the base class pointer within the node
void Node::display()
{
    base_ptr->display();
}

// Makes an obstacle object made by ABC pointer
void Node::make_obstacle()
{
    base_ptr = new Obstacle;
}

// Makes a player object made by ABC pointer
void Node::make_player()
{
    base_ptr = new Player;
}

// Makes a pathway object made by ABC pointer
void Node::make_pathway()
{
    base_ptr = new Pathway;
}

// Makes a home object made by ABC pointer
void Node::make_home()
{
    base_ptr = new Home_Base;
}

//------------------------------------------------------------------------
// Array Class Implementaions
//------------------------------------------------------------------------

Array::Array():head(NULL), tail(NULL), size(0), index_count(0), links(0), link_count(0), arena(NULL)
{

}

Array::Array(int max_size, int max_links):head(NULL), tail(NULL), size(max_size), index_count(0), links(max_links)
                                          , link_count(0), arena(NULL)
{

}

Array::~Array()
{
    head = NULL;
    tail = NULL;
}

//Wrapper
void Array::insert_obstacle(int index, int link)
{
    return insert_obstacle(head, tail, index, link);
}

// Insert an obstacle at tail of DLL
void Array::insert_obstacle(Node *& head, Node *& tail, int index, int link)
{
    //If head is NULL
    if(!head)
    {
        head = new Node(index, link);
        head->make_obstacle();
        tail = head;
    }
    else
    {
        Node * temp = new Node(index, link);
        temp->make_obstacle();
        temp->go_prev() = tail;
        tail->go_next() = temp;
        tail = temp;
    }
}

// Wrapper
void Array::insert_player(int index, int link)
{
    return insert_player(head, tail, index, link);
}

// Insert a player at tail
void Array::insert_player(Node *& head, Node *& tail, int index, int link)
{
    //If head is NULL
    if(!head)
    {
        head = new Node(index, link);
        head->make_player();
        tail = head;
    }
    else
    {
        Node * temp = new Node(index, link);
        temp->make_player();
        temp->go_prev() = tail;
        tail->go_next() = temp;
        tail = temp;
    }
}

// Wrapper
void Array::insert_pathway(int index, int link)
{
    return insert_pathway(head, tail, index, link);
}

// Insert pathway at tail
void Array::insert_pathway(Node *& head, Node *& tail, int index, int link)
{
    if(!head)
    {
        head = new Node(index, link);
        head->make_pathway();
        tail = head;
    }
    else
    {
        Node * temp = new Node(index, link);
        temp->make_pathway();
        temp->go_prev() = tail;
        tail->go_next() = temp;
        tail = temp;
    }
}

// Wrapper
void Array::insert_home(int index, int link)
{
    return insert_home(head, tail, index, link);
}

// Inserts a home object at the end of the list
void Array::insert_home(Node *& head, Node *& tail, int index, int link)
{
    if(!head)
    {
        head = new Node(index, link);
        head->make_home();
        tail = head;
    }
    else
    {
        Node * temp = new Node(index, link);
        temp->make_home();
        temp->go_prev() = tail;
        tail->go_next() = temp;
        tail = temp;
    }
}

// Builds a little arena demonstration, one row at a time.
void Array::build_demo()
{
    //Make arena member an array for demonstration
    arena = new Array[5];
     
    // First row
    inc_link_count(); //first link
    arena[0].insert_home(index_count, link_count);
    inc_link_count(); //second link
    arena[0].insert_player(index_count, link_count);
    inc_link_count(); //third link
    arena[0].insert_pathway(index_count, link_count);
    inc_link_count(); //forth link
    arena[0].insert_obstacle(index_count, link_count);
    inc_link_count(); //fifth link
    arena[0].insert_pathway(index_count, link_count);

    // Second Row
    inc_index_count();
    link_count = 1; //first link again
    arena[1].insert_player(index_count, link_count);
    inc_link_count(); // second link
    arena[1].insert_pathway(index_count, link_count);
    inc_link_count(); // third link
    arena[1].insert_pathway(index_count, link_count);
    inc_link_count(); // forth link
    arena[1].insert_pathway(index_count, link_count);
    inc_link_count(); // fifth link
    arena[1].insert_pathway(index_count, link_count);
    
    // Third row
    inc_index_count();
    link_count = 1; //first link again
    arena[2].insert_pathway(index_count, link_count);
    inc_link_count(); //second link
    arena[2].insert_obstacle(index_count, link_count);
    inc_link_count(); //third link
    arena[2].insert_pathway(index_count, link_count);
    inc_link_count(); //forth link
    arena[2].insert_obstacle(index_count, link_count);
    inc_link_count(); //fifth link
    arena[2].insert_pathway(index_count, link_count);

    // Forth Row
    inc_index_count();
    link_count = 1; //first link again
    arena[3].insert_pathway(index_count, link_count);
    inc_link_count(); //second link
    arena[3].insert_obstacle(index_count, link_count);
    inc_link_count(); //third link
    arena[3].insert_pathway(index_count, link_count);
    inc_link_count(); //forth link
    arena[3].insert_obstacle(index_count, link_count);
    inc_link_count(); //fifth link
    arena[3].insert_player(index_count, link_count);

    // Fifth row
    inc_index_count();
    link_count = 1; //first link again
    arena[4].insert_pathway(index_count, link_count);
    inc_link_count(); //second link
    arena[4].insert_pathway(index_count, link_count);
    inc_link_count(); //third link
    arena[4].insert_pathway(index_count, link_count);
    inc_link_count(); //forth link
    arena[4].insert_player(index_count, link_count);
    inc_link_count(); //fifth link
    arena[4].insert_home(index_count, link_count);

    //reset index_count
    index_count = 0;
}

// Wrapper
void Array::remove_row()
{
    return remove_row(head, tail);
}   

//Recursive removal of every node in a doubly linked list
void Array::remove_row(Node *& head, Node *& tail)
{
    // Checking if list is empty
    if(!head)
    {
        cout << "List is empty on this row." << endl;
        return;
    }
    //Base Case
    if(head == tail)
    {
        delete head;
        head = NULL;
        tail = NULL;
        return;
    }
    
    //Otherwise, keep passing in head->next and delete what is there until base is reached
    delete head;
    return remove_row(head->go_next(), tail);

}

// Wrapper
void Array::display_row()
{
    return display_row(head, tail);
}

// This will recursively display all nodes in a list
void Array::display_row(Node *& head, Node *& tail)
{
    // If list is empty
    if(!head)
    {
        cout << "Row is empty." << endl;
        return;
    }
    
    // Base case
    if(head == tail)
    {
        head->display();
        return;
    }
    else
        head->display();

    return display_row(head->go_next(), tail);
}

// Public wrapper
void Array::display_arena()
{
    return display_arena(size);
}

// Recursive display of indices making use of the the display_row() function
void Array::display_arena(int array_size)
{
   if(index_count == (size - 1))
   {
       arena[index_count].display_row();
       cout << endl;
       return;
   }
   else
   {
       arena[index_count].display_row();
       cout << endl;
   }

   return display_arena(++index_count);
}

// Increments link count if there is room left in grid
int Array::inc_link_count()
{
    if(link_count < links)
        link_count++;

    return link_count;
}

// Increments index count if there is room
int Array::inc_index_count()
{
    //this will prevent user from incrementing index_count past the maximum array index
    if(index_count < (size - 1))
        ++index_count;

    return index_count;
}
