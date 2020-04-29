#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

//This class will be in charge of making cstrings 
//For this course, I am not allowed to use the string library so I made my own


class String
{
    public:
        String();
        String(char * to_copy);
        String(const String & to_copy);
        ~String();

        //String  *& get_object();
        void    highlight();  
        void    set_string_null();
        bool    is_null(); 
        //char*   get_word();

        //-----------------------------------------------
        // Friend Operators
        //-----------------------------------------------

        //Insertion and extraction operators
        friend istream & operator >> (istream &, String &); //Input string into string member
        friend ostream & operator << (ostream &, const String &); //Output string to out
        
        //Addition operator
        friend String operator + (const String &, char *); //When String object on left and literal string on right
        friend String operator + (char *, const String &); //When literal string on left and String object on right
        friend String operator + (const String &, const String &); //When both sides are String objects; <-- Lol at ';'

        //Lesser than relational operator
        friend bool operator < (const String &, char *); //When String on left and literal on right
        friend bool operator < (char *, const String &); //Literal on left, String on right
        friend bool operator < (const String &, const String &); //Both operands are of type String
        
        //Greater than relations operator
        friend bool operator > (const String &, char *); //When String on left and literal on right
        friend bool operator > (char *, const String &); //Literal on left, String on right
        friend bool operator > (const String &, const String &); //Both operands are of type String
        
        //Lesser than or equal to
        friend bool operator <= (const String &, char *); //When String on left and literal on right
        friend bool operator <= (char *, const String &); //Literal on left, String on right
        friend bool operator <= (const String &, const String &); //Both operands are of type String

        //Greater than or equal to
        friend bool operator >= (const String &, char *); //When String on left and literal on right
        friend bool operator >= (char *, const String &); //Literal on left, String on right
        friend bool operator >= (const String &, const String &); //Both operands are of type String
        
        //Equal to operator
        friend bool operator == (const String &, char *); //When String on left and literal on right
        friend bool operator == (char *, const String &); //Literal on left, String on right
        friend bool operator == (const String &, const String &); //Both operands are of type String

        //Not equal operator
        friend bool operator != (const String &, char *); //When String on left and literal on right
        friend bool operator != (char *, const String &); //Literal on left, String on right
        friend bool operator != (const String &, const String &); //Both operands are of type String
        
        //----------------------------------------------------
        // Member Operators - a much smaller list
        //----------------------------------------------------

        //Assignment operator
        String & operator = (const String &); //If you want to assign one String to another
        String & operator = (const char *); //If you want to assign a literal to String object
        
        //"Plus equals" assignment operator - a combo of concatenation and assignment
        String & operator += (const String &); //Concatenate and assign String to String
        String & operator += (const char *); //Concatenate and assign literal to String

        

    protected:
        int     length;
        char    * string;
        

};

class Syntax
{
    public:

    protected:
        bool    corrected;

};
