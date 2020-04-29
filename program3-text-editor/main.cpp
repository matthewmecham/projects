#include "tree.h"

//Matthew Mecham - Program 3 - 11/15/2019
//
//
//
//

int main()
{

    char temp[100];
    Two_Three_Tree tree;
    tree.build();

    strcpy(temp, "thier");
    String string(temp);
    cout << string << endl;

    //I do not have time to implement the array of linked lists but here
    //is an example of how my array class would have checked for misspelled words
    //assuming I had another week to work on this. 
    if(tree.search(temp))
    {
        tree.highlight(string);
    }
    cout << string << endl;



    


    return 0;
}
