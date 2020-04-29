#include "tree.h"
//Matthew Mecham - Program 3 - 11/15/2019

//This 2-3 tree took me hours of research and drawing each step out on a whiteboard
//Good luck

//--------------------------------------------------------------
// Tree_Node Implementations
//--------------------------------------------------------------

//Constructor
Tree_Node::Tree_Node():left(NULL), middle(NULL), right(NULL), parent(NULL)
{

}

//Constructor with args that is very nice when splitting nodes.
//When needing to split a leaf node you can just Tree_Node temp = new Tree_Node(obj->word1, obj)
Tree_Node::Tree_Node(const String &s, Tree_Node * ptr):left(NULL), middle(NULL), right(NULL)
{
    word1 = s;
    parent = ptr;
}

//Destructor
Tree_Node::~Tree_Node()
{
    left = NULL;
    middle = NULL;
    right = NULL;
    parent = NULL;
}

//Wrapper for private left pointer
Tree_Node *& Tree_Node::go_left()
{
    return left;
}

//Wrapper for private middle pointer
Tree_Node *& Tree_Node::go_middle()
{
    return middle;
}

//Wrapper for private right pointer
Tree_Node *& Tree_Node::go_right()
{
    return right;
}

//Wrapper for parent
Tree_Node *& Tree_Node::go_parent()
{
    return parent;
}

//Returns word1 object in order to utilize the operator overloading
String & Tree_Node::get_word1()
{
    return word1;
}

//Returns word2 for the same reason
String & Tree_Node::get_word2()
{
    return word2;
}

//At times during the splitting and pushing, word1 and 2 need to be set to null
void Tree_Node::set_word1_null()
{
    word1.set_string_null();
}

//Same as above
void Tree_Node::set_word2_null()
{
    word2.set_string_null();
}

//Checks if node is a leaf - helpful for inserting
bool Tree_Node::is_leaf() const
{
    if(left == NULL && middle == NULL && right == NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//Checks if node is full
bool Tree_Node::is_two_node()
{
    if(!word1.is_null() && word2.is_null())
        return true;
    else
        return false;
}

//By nature of the algorithm, a node with 2 values can only be either a leaf, or a full 3node
//where both data members are full and has 3 children.
bool Tree_Node::is_three_node()
{
    if(!word1.is_null() && !word2.is_null())
        return true;
    else
        return false;
}

//Checks if parent is null - needed for knowing when you are at the root during recursive calls
//Additionally if !NULL you know you can attempt to insert a pushed up node
bool Tree_Node::null_parent() const
{
    if(parent == NULL)
        return true;
    else
        return false;
}

//------------------------------------------------------------------
// Two_Three_Tree implementations
//------------------------------------------------------------------

// Constructor
Two_Three_Tree::Two_Three_Tree()
{
    char temp[2];
    strcpy(temp, "i");
    String s(temp);
    root = new Tree_Node(s, NULL);
}

// Destructor
Two_Three_Tree::~Two_Three_Tree()
{
    delete root;
    root = NULL;
}

//wrapper
void Two_Three_Tree::insert(const String &s)
{
    return insert(s, root);
}

//recursive insert
//Treverses using overloaded conditionals to find the correct leaf
void Two_Three_Tree::insert(const String &s, Tree_Node *& root)
{
    //Root is a leaf, yay!
    if(root->is_leaf())
    {
        if(root->is_two_node()) //only one data item in leaf
        {
            if(root->get_word1() < s) // is is bigger than word1 and can go in word2
            {
                root->get_word2() = s;
            }
            else //s is smaller than word 1 and needs to be swapped
            {
                root->get_word2() = root->get_word1();
                root->get_word1() = s;
            }
        }
        else //leaf has two items and must be split
        {
            split_leaf(s, root);
            if(!root->null_parent()) //if parent != NULL
            {
                push_up(root->go_parent(), root);
            }
        }
        return;
    }
    else //root is not a leaf and must keep traversing
    {
        if (root->is_three_node())
        {
            if(s < root->get_word1())
            {
                return insert(s, root->go_left());
            }
            else if(s < root->get_word2())
            {
                return insert(s, root->go_middle());
            }
            else
            {
                return insert(s, root->go_right());
            }
        }
        else // root is a two node
        {
            if(s < root->get_word1())
            {
                return insert(s, root->go_left());
            }
            else
            {
                return insert(s, root->go_right());
            }
        }
    }
}
            
//Wrapper::search tree and return true if found
bool Two_Three_Tree::search(const String &s)
{
   return search(s, root); 
}

//Private search to check for misspelled words
bool Two_Three_Tree::search(const String &s, Tree_Node *& root)
{
    //base case
    if(root->get_word1() == s || root->get_word2() == s)
        return true;
    else if(root->is_leaf())
        return false;

    if(root->is_three_node())
    {
        if(s < root->get_word1())
        {
            return search(s, root->go_left());
        }
        else if(s < root->get_word2())
        {
            return search(s, root->go_middle());
        }
        else
        {
            return search(s, root->go_right());  
        }
    }
    else
    {
        if(s < root->get_word1())
        {
            return search(s, root->go_left());
        }
        else
        {
            return search(s, root->go_right());
        }
    }
}

//Wrapper to capatalize a word if it is found in the tree
void Two_Three_Tree::highlight(String &s)
{
    s.highlight();
}

//splits a full leaf
void Two_Three_Tree::split_leaf(const String &s, Tree_Node *& root)
{
   if(s < root->get_word1()) //S is smaller than word1
   {
       root->go_left() = new Tree_Node(s, root);
       root->go_right() = new Tree_Node(root->get_word2(), root);
       root->set_word2_null();
   }
   else if(s < root->get_word2()) //s is bigger than word1 but smaller than word 2
   {
       root->go_left() = new Tree_Node(root->get_word1(), root);
       root->go_right() = new Tree_Node(root->get_word2(), root);
       root->get_word1() = s;
       root->set_word2_null();
   }
   else //s is largest item
   {
       root->go_right() = new Tree_Node(s, root);
       root->go_left() = new Tree_Node(root->get_word1(), root);
       root->get_word1() = root->get_word2();
       root->set_word2_null();
   }
}

//  Params:Parent and Child pointer references
//  Child was just split and is guaranteed to be a two-node so we know it only has one data item
//  If parent is a two node as well, push the middle value from the child split into parent.
//  If parent is a three node, it will have to call a 3-node split function 
//  and split the parent and push it up again
void Two_Three_Tree::push_up(Tree_Node *& parent,  Tree_Node * child)
{
    if(parent->is_two_node())//node has a free space for the pushed up obect 
    {
        // Unprofessional comment but... god damn, this took much white-boarding!
        if(child->get_word1() < parent->get_word1()) 
        {
            parent->get_word2() = parent->get_word1(); //bigger number into parent word2
            parent->get_word1() = child->get_word1(); //Now child middle value is pushed to parent
            parent->go_left() = child->go_left(); //connecting pointers do make a 3 node
            parent->go_left()->go_parent() = parent;
            parent->go_middle() = child->go_right();
            parent->go_middle()->go_parent() = parent;
            child->go_left() = child->go_right() = child->go_middle() = child->go_parent() = NULL;
        }
        else //The value being pushed up is greater than parent's word1
        {
            parent->get_word2() = child->get_word1(); // bigger child# gets its proper spot
            parent->go_middle() = child->go_left();
            parent->go_middle()->go_parent() = parent;
            parent->go_right() = child->go_right();
            parent->go_right()->go_parent() = parent;
        }
    }
    else //parent is a three node and must be split again....... yay (sad trumpet)
    {
        split_three_node(parent, child); //No room in current parent and must be split

        if(!parent->null_parent()) //if parent of current parent is null 
            push_up(parent->go_parent(), parent); //pushes up current parent's parent and tries again
        //with the new child being current parent
    }
}

void Two_Three_Tree::split_three_node(Tree_Node *& to_split, Tree_Node *& to_add)
{
    Tree_Node * temp;

    if(to_add->get_word1() < to_split->get_word1())// to_add->word1() is the middle value from the 2-node being passed up - we need to figure out where it goes
    {
        to_split->go_left() = to_add; 
        to_add->go_left()->go_parent() = to_split;
        temp = new Tree_Node(to_split->get_word2(), to_split);
        to_split->set_word2_null();
        temp->go_left() = to_split->go_middle();
        temp->go_left()->go_parent() = temp;
        temp->go_right() = to_split->go_right();
        temp->go_right()->go_parent() = temp;
        to_split->go_right() = temp;
        to_split->go_middle() = NULL;
    }
    else if(to_add->get_word1() < to_split->get_word2()) //push up item in between three-node items
    {
        temp = new Tree_Node(to_split->get_word1(), to_split);
        temp->go_left() = to_split->go_left();
        temp->go_left()->go_parent() = temp;
        temp->go_right() = to_add->go_left();
        temp->go_right()->go_parent() = temp;
        to_split->go_left() = temp;
        temp = new Tree_Node(to_split->get_word2(), to_split);
        temp->go_left() = to_add->go_right();
        temp->go_left()->go_parent() = temp;
        temp->go_right() = to_split->go_right();
        temp->go_right()->go_parent() = temp;
        to_split->go_right() = temp;
        to_split->get_word1() = to_add->get_word1();
        to_split->set_word2_null();
        to_split->go_middle() = NULL;
    }
    else //item being pushed up is larger than word2 of to_split
    {
        to_split->go_right() = to_add;
        to_add->go_parent() = to_split;
        temp = new Tree_Node(to_split->get_word1(), to_split);
        temp->go_left() = to_split->go_left();
        temp->go_left()->go_parent() = temp;
        temp->go_right() = to_split->go_middle();
        temp->go_right()->go_parent() = temp;
        to_split->go_left() = temp;
        to_split->get_word1() = to_split->get_word2();
        to_split->set_word2_null();
        to_split->go_middle() = NULL;
    }
}

//Reads a local file full of misspelled words and places in the 23Tree.
void Two_Three_Tree::build()
{
    ifstream in_file;
    in_file.open("common_misspelled_words.txt");
    String temp;
    in_file >> temp;

    while(!in_file.eof())
    {
        insert(temp);    
        in_file >> temp;
    }
    in_file.close();
}


