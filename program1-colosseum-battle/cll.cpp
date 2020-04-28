// Matthew Mecham - Program 1

#include "cll.h"

Node::Node():next(NULL),capacity(5),size(0),username(NULL)
{
}

Node::Node(const Node & to_copy)
{
    username = new char[strlen(to_copy.username) + 1];
    strcpy(username, to_copy.username);
    capacity = to_copy.capacity;
    size = to_copy.size;

    if (to_copy.next == NULL)
    {
        next = NULL;
    }
    else 
    {
        next = to_copy.next;
    }

    characters = new Character*[to_copy.capacity];
    for(int i = 0; i < to_copy.capacity; ++i)
        characters[i] = to_copy.characters[i];
}

Node::~Node()
{
    delete [] characters;
    characters = NULL;
}

// 1. Checks if there is room in the array and grows if needed
// 2. Checks the arrays for a NULL then points to the Barbarian object
// 3. Returns true if successful, false if not
bool Node::insert_barb(Character *& barb)
{
    if (size >= capacity)
        grow();

    for(int i = 0; i < capacity; ++i)
    {
        if(characters[i] == NULL)
        {
            characters[i] = barb;
            ++size;
            return true;
        }
    }
    return false;
}

// 1. Checks if there is room in the array and grows if needed
// 2. Checks the arrays for a NULL then points to the knight object
// 3. Returns true if successful, false if not
bool Node::insert_knight(Character *& knight)
{
    if (size >= capacity)
        grow();

    for(int i = 0; i < capacity; ++i)
    {
        if(characters[i] == NULL)
        {
            characters[i] = knight;
            ++size;
            return true;
        }
    }
    return false;
}

// 1. Checks if there is room in the array and grows if needed
// 2. Checks the arrays for a NULL then points to the rogue object
// 3. Returns true if successful, false if not
bool Node::insert_rogue(Character *& rogue)
{
    if (size >= capacity)
        grow();

    for(int i = 0; i < capacity; ++i)
    {
        if(characters[i] == NULL)
        {
            characters[i] = rogue;
            ++size;
            return true;
        }
    }
    return false;
}

// 1. Goes through array and looks for the reference param
// 2. If it finds one, then it will change characters[i] pointer to NULL
// 3. Returns true is successful, false if not
bool Node::remove_barb(Character *& user_barb)
{
    for(int i = 0; i < capacity; ++i)
    {
        if(characters[i] == user_barb)
        {
            characters[i] = NULL;
            --size;
            return true;
        }
    }
    return false;
}

// 1. Goes through array and looks for the reference param
// 2. If it finds one, then it will change characters[i] pointer to NULL
// 3. Returns true is successful, false if not
bool Node::remove_knight(Character *& user_knight)
{
    for(int i = 0; i < capacity; ++i)
    {
        if(characters[i] == user_knight)
        {
            characters[i] = NULL;
            --size;
            return true;
        }
    }
    return false;
}

// 1. Goes through array and looks for the reference param
// 2. If it finds one, then it will change characters[i] pointer to NULL
// 3. Returns true is successful, false if not
bool Node::remove_rogue(Character *& user_rogue)
{
    for(int i = 0; i < capacity; ++i)
    {
        if(characters[i] == user_rogue)
        {
            characters[i] = NULL;
            --size;
            return true;
        }
    }
    return false;
}

// Sets name
void Node::set_username(const char* name)
{
    if (username)
        delete username;
    username = new char[strlen(name) + 1];
    strcpy(username, name);
}

// Gets the name - Needed to check where to place within CLL
char * Node::get_username() const
{
    return username;
}

// Displays username
void Node::display_username() const
{
    int length = 0;
    length = strlen(username);
    for(int i = 0; i < length; i++)
        cout << username[i];
}

//Shows all user and all the characters associated with that user
void Node::display() const
{
    display_username();
    cout << endl;

    for(int i = 0; i < capacity; i++)
    {
       if(characters[i])
       characters[i]->display_all();
    }
}

// Wrapper to use next pointer
Node *& Node::go_next()
{
    return next;
}

// A function to help me grow the array if needed, instead of tossing this in 
// every insert function. 
void Node::grow()
{
    int newSize = (capacity + 5);
    Character **newArray;

    newArray = new Character*[newSize];

    for(int i = 0; i < newSize; ++i)
        newArray[i] = NULL;

    for (int i = 0; i < capacity; ++i)
        newArray[i] = characters[i];

    delete [] characters;
    characters = newArray;
    capacity = newSize;
}

//--------------------------------------------------------------------------------------
// CLL Methods
// -------------------------------------------------------------------------------------

//CLL is generated with a fully allocated rear node
CLL::CLL()
{
    rear = new Node;
    rear->go_next() = rear;
}

CLL::~CLL()
{
    delete rear;
    rear = NULL;
} 

// Inserts at the beginning of the CLL
// This way I don't have to recursively traverse to insert
// *shifty eyes*
void CLL::insert_node(Node *p)
{
    Node * temp;
    temp = new Node;
    p = temp;

    p->go_next() = rear->go_next();
    rear = p;
}

// Removes the node that is passed in
int CLL::remove(Node * p)
{
    // base case
    if(this->rear->go_next() == this->rear)
        return 0;

    if(this->rear == p)
    {
        delete p;
        p = NULL;
    }

    return remove(this->rear->go_next()) + 1;
}

// Public Wrapper
int CLL::display_nodes()
{
    return display_nodes(rear);
}

// Recursively displays all nodes and the array of Characters
int CLL::display_nodes(Node *rear)
{
    // base case
    if (rear->go_next() == rear)
        return 0;

    rear->display();

    return display_nodes(rear->go_next()) + 1;
}
 
// Public wrapper to add Barb
int CLL::add_barb(Character *& barb, char *owner)
{
    return add_barb(barb, owner, rear);
}

// Recursively adds barb. It will check the name of the owner, if it is a match
// then it will add to that array, if not it will keep searching for correct owner
int CLL::add_barb(Character *& barb, char *owner, Node * rear)
{
    // Base case
    if(rear->go_next() == rear)
        return 0;

    if (!strcmp(owner, rear->get_username()))
    {
        rear->insert_barb(barb);
    }
    return add_barb(barb, owner, rear->go_next()) + 1;
}

// Public Wrapper to add Knight
int CLL::add_knight(Character *& knight, char *owner)
{
    return add_knight(knight, owner, rear);
}

// Functions same as Barb
int CLL::add_knight(Character *& knight, char *owner, Node * rear)
{
    // Base case
    if(rear->go_next() == rear)
        return 0;

    if (!strcmp(owner, rear->get_username()))
    {
        rear->insert_knight(knight);
    }

    return add_knight(knight, owner, rear->go_next()) + 1;

}

// Public Wrapper to add Rogue
int CLL::add_rogue(Character *& rogue, char *owner)
{
    return add_rogue(rogue, owner, rear);
}

// Functions same as barb
int CLL::add_rogue(Character *& rogue, char *owner, Node * rear)
{
    // Base case
    if(rear->go_next() == rear)
        return 0;

    if (!strcmp(owner, rear->get_username()))
    {
        rear->insert_rogue(rogue);
    }
    return add_rogue(rogue, owner, rear->go_next()) + 1;
}

// Wrapper for recursive removal of Barbarian object
int CLL::delete_barb(Character *& barb, char *owner)
{
    return delete_barb(barb, owner, rear);
}

// Recursively removes barb from Node array - checks vs the owner name
int CLL::delete_barb(Character *& barb, char *owner, Node * rear)
{
    // Base case
    if(rear->go_next() == rear)
        return 0;

    if(!strcmp(owner, rear->get_username()))
    {
        rear->remove_barb(barb);
    }
    return delete_barb(barb, owner, rear->go_next()) + 1;
}

// Wrapper for recursive removal of Knight object
int CLL::delete_knight(Character *& knight, char *owner)
{
    return delete_knight(knight, owner, rear);
}

// Functions similar to barb
int CLL::delete_knight(Character *& knight, char *owner, Node * rear)
{
    // Base case
    if(rear->go_next() == rear)
        return 0;

    if(!strcmp(owner, rear->get_username()))
    {
        rear->remove_knight(knight);
    }
    return delete_knight(knight, owner, rear->go_next()) + 1;
}

// Wrapper for recursive removal of Rogue object
int CLL::delete_rogue(Character *& rogue, char *owner)
{
    return delete_rogue(rogue, owner, rear);   
}

// Functions similar to barb
int CLL::delete_rogue(Character *& rogue, char *owner, Node * rear)
{
    // Base case
    if(rear->go_next() == rear)
        return 0;

    if(!strcmp(owner, rear->get_username()))
    {
        rear->remove_rogue(rogue);
    }
    return delete_rogue(rogue, owner, rear->go_next()) + 1;

}

// Public Wrapper
void CLL::set_owner(const char * owner)
{
    return set_owner(owner, rear);
}

// Checks if username is null and names username, otherwise it recursively searches for another 
// node with a NULL username
void CLL::set_owner(const char * owner, Node * rear)
{
    if(rear->go_next() == rear)
        return;

    if(!rear->get_username())
    {
        rear->set_username(owner);
    }
    
    return set_owner(owner, rear->go_next());
}
