/* Create your own string class (don't use the standard one).
Overload next operators (and more if needed) : "=", "+", "+=", "<<", ">>", "==", "!="
Among the standard function-members also add copy constructor and next functions:
append
compare
length
resize
clear
swap
substr //should search for a specified substring into existing one and return position of the 1st character
insert //means inserting one character or another string into a specified position
*/
#ifndef MYSTRING_H

#define MYSTRING_H


#include <iostream>
#include <cassert>

using namespace std;

class myString
{
private:
    size_t size;
    size_t bufferLength;
    char * buffer;

// methods
    void init();
    size_t assign_new_size (size_t minimum_to_allocate)
    {
        return minimum_to_allocate * 2;
    }

public:

//  constructors
    //myString();
    myString():buffer(nullptr), size(0), bufferLength(0){};
    myString(const myString &);
    myString(const char *);

    //  destructor
    ~myString();

//  mutators
    void clear ();
    void resize(size_t newSize );
    myString& append(  const myString & str, size_t len );
    void insert( size_t start, const myString & str, size_t len );
    myString& swap( myString& strB);

//  operators (accessors)
    char& operator[] (unsigned int);

    const myString & operator=( const myString & copy );
    void operator+(const myString&);
    void operator += (const myString&);
    // Return string allocated size
    size_t getBufferLength( ) const
    {
        return ( bufferLength ) ? bufferLength : 0;
    }
    const char *  getBuffer( ) const
    {
        return buffer;
    }
//;
    int substr(myString& sub_str);

//  accessors
    int length() const;
    int compare(const myString& right) const;

//  friend functions
    friend bool operator+=(const myString &, const myString &);
    friend bool operator<=(const myString &, const myString &);	//?
    friend bool operator<(const myString &, const myString &);	//?
    friend ostream & operator<<(ostream &, const myString &);
    friend istream & operator>>(istream &, const myString &);
    friend bool operator==(const myString &, const myString &);
    friend bool operator!=(const myString &, const myString &);
};

#endif
