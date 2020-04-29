#include "string.h"

//----------------------------------------------------------------
// String class implementations
//----------------------------------------------------------------

// Default constructor
String::String():length(0), string(NULL)
{

}

// Constructor with arg
String::String(char * to_copy)
{
    //Check if the param is NULL so strlen doesn't seg fault
    //You would think they could have done this themselves
    if (to_copy == NULL)
    {
        cout << "Char * is NULL" << endl;
        return;
    }
    
    length = strlen(to_copy);
    string = new char[length + 1];
    strcpy(string, to_copy);
}

// Copy Constructor
String::String(const String & to_copy)
{
    length = to_copy.length;
    string = new char[length + 1];
    strcpy(string, to_copy.string);
}

// Destructor
String::~String()
{
    delete [] string;
    string = NULL;
    length = 0;
}
        
//This will be used to "highlight" misspelled words by capitalizing the string
void String::highlight()
{
    char temp[100];
    int c;
    for(int i = 0; i <= length; i++)
    {
        c = toupper(string[i]);
        temp[i] = c;
    }
    strcpy(string, temp);
}

void String::set_string_null()
{
    if(string)
        delete [] string;
    string = NULL;
}

bool String::is_null()
{
    if(string == NULL)
        return true;
    else 
        return false;
};

// Insertion operator overload
istream & operator >> (istream &in, String & s)
{
    char temp[100];
    in >> temp;
    s.length = strlen(temp);
    s.string = new char[s.length + 1];
    strcpy(s.string, temp);
    return in;
}

// Extraction operator overload
ostream & operator << (ostream & out, const String & s)
{
    out << s.string;
    return out;
}

//Addition operator overload - String on left, literal on right
String operator + (const String & s, char * literal)
{
   char * temp = new char[s.length + strlen(literal) + 1];
   strcpy(temp, s.string);
   strcat(temp, literal);
   return String(temp);
}
    
//Addition operator overload - literal on left, String on right
String operator + (char * literal, const String &s)
{
   char * temp = new char[s.length + strlen(literal) + 1];
   strcpy(temp, s.string);
   strcat(temp, literal);
   return String(temp);
}

//Addition operator overload - String on left, String on right
String operator + (const String & s, const String & s2)
{
   char * temp = new char[s.length + s2.length + 1];
   strcpy(temp, s.string);
   strcat(temp, s2.string);
   return String(temp);
}

//Lesser than operator - String on left, literal on right
bool operator < (const String & s, char * literal)
{
    return (strcmp(s.string, literal) < 0);
}

//Lesser than operator -literal on left, String on right
bool operator < (char * literal, const String & s)
{
    return (strcmp(literal, s.string) < 0);
}

//Lesser than operater - String as both operands
bool operator < (const String & s, const String & s2) 
{
    return (strcmp(s.string, s2.string) < 0);
}
    
//Greater than operator - String on left, lit on right
bool operator > (const String & s, char * literal)
{
    return (strcmp(s.string, literal) > 0);
}

//Greater than operator - lit on left, String on right
bool operator > (char * literal, const String & s)
{
    return (strcmp(literal, s.string) > 0);
}

//Greater than operator - String as both operands 
bool operator > (const String  & s, const String & s2)
{   
    return (strcmp(s.string, s2.string) > 0);
}

//Lesser than or equal operator - String on left, literal on right
bool operator <= (const String & s, char * literal)
{
    return (strcmp(s.string, literal) <= 0);
}

//Lesser than or equal operator -literal on left, String on right
bool operator <= (char * literal, const String & s)
{
    return (strcmp(literal, s.string) <= 0);
}

//Lesser than or equal operater - String as both operands
bool operator <= (const String & s, const String & s2) 
{
    return (strcmp(s.string, s2.string) <= 0);
}

//Greater than or equal operator - String on left, lit on right
bool operator >= (const String & s, char * literal)
{
    return (strcmp(s.string, literal) >= 0);
}

//Greater than or equal operator - lit on left, String on right
bool operator >= (char * literal, const String & s)
{
    return (strcmp(literal, s.string) >= 0);
}

//Greater than or equal operator - String as both operands 
bool operator >= (const String  & s, const String & s2)
{   
    return (strcmp(s.string, s2.string) >= 0);
}

//Equal to operator - String on left, lit on right
bool operator == (const String & s, char * literal)
{
    return (strcmp(s.string, literal) == 0);
}

//Equal to operator - Lit on left, String on right
bool operator == (char * literal, const String & s)
{
    return (strcmp(literal, s.string) == 0);
}

//Equal to operator - String as both operands
bool operator == (const String & s, const String & s2)
{
    if(s.string == NULL || s2.string == NULL)
        return false;

    return (strcmp(s.string, s2.string) == 0);
}

//Not equal to operator - String on left, lit on right
bool operator != (const String & s, char * literal)
{
    return (strcmp(s.string, literal) != 0);
}

//Not equal to operator - Lit on left, String on right
bool operator != (char * literal, const String & s)
{
    return (strcmp(literal, s.string) != 0);
}

//Not equal to operator - String as both operands
bool operator != (const String & s, const String & s2)
{
    return (strcmp(s.string, s2.string) != 0);
}

//Assignment operator - assigning a String to a String
String & String::operator = (const String & s)
{
    //Self assignment check
    if(this == &s)
        return *this;

    //Checks if string already has a value
    //and deletes it if it does
    if(string)
        delete [] string;

    string = new char[s.length + 1];
    strcpy(string, s.string);
    length = s.length;
    return *this;
} 

//Assignment operator - assigning a Char* to a String
String & String::operator = (const char * literal)
{
    //Check if string is occupied
    if(string)
        delete [] string;

    length = strlen(literal);
    string = new char[length + 1];
    strcpy(string, literal);
    return *this;
}

//"Plus equals" operator - concat and assign String to String
String & String::operator += (const String & s)
{
    length += s.length;
    char * temp = new char[length + 1];
    strcpy(temp, string);
    strcat(temp, s.string);
    string = temp;
    return *this;
}

//"Plus equal" operator -concat and assign literal to String
String & String::operator += (const char * literal)
{
    length += strlen(literal);
    char * temp = new char[length + 1];
    strcpy(temp, string);
    strcat(temp, literal);
    string = temp;
    return *this;
}













    
