#include "myString.h"

#include <iostream>
#include <cassert>
#include <cstring>


using namespace std;

// Copy costructor using reference
myString::myString(const myString& s)
{
    try
    {
        buffer = new char[s.size];
    }
    catch (std::bad_alloc& ba)
    {
        std::cerr << "bad_alloc caught: " << ba.what() << '\n';
    }
//   strcpy(buffer, s);
    size = s.size;

    for(int i = 0; i < size; i++)
    {
        buffer[i] = s.buffer[i];
    }
    buffer[size] = '\n';
    bufferLength = size + 1;
}
// Copy constructor using pointer
myString::myString(const char *p)
{
    int i = 0;
    const char * t = p;

    while(*p++)
    {
        i++;
    }
    try
    {
        buffer = new char[i+1];
    }
    catch (std::bad_alloc& ba)
    {
        std::cerr << "bad_alloc caught: " << ba.what() << '\n';
    }

    int j = 0;
    for(j; *t; t++,j++)
    {
        buffer[j] = *t;
    }

    buffer[j] = '\0';
    size = j;
    bufferLength = j+1;
}

myString::~myString()
{
    delete[] buffer;
}

void myString::clear ()
{
    if ( bufferLength )
        free( buffer );
    init();
}

inline void myString::init()
{
    buffer = NULL;
    bufferLength = size = 0;
}

int myString::length() const
{
    if(buffer == nullptr)
    {
        return 0;
    }
    else
    {
        return size;
    }
}

void myString::resize(size_t newSize )
{
    newSize = newSize > 0 ? newSize : 0;
    buffer = ( char* )realloc( buffer, newSize );
    if ( buffer )
    {
        if ( size > newSize )
        {
            size = newSize > 0 ? newSize - 1 : 0;
        }

        buffer[ size ] = '\0';
        bufferLength = newSize;
    }
    else
    {
        init();
    }
}

char & myString::operator[] (unsigned int x)
{

    return buffer[x];
}

// Copy assignment
const myString & myString::operator=( const myString & copy )
{
    // Prevent copy to self! if copy itself, do nothing.
    if ( &copy != this )
    {
        size = copy.size;
        if ( !bufferLength )
        {
            bufferLength = size + 1;
            buffer = ( char * ) malloc( bufferLength );

        }
        else if ( bufferLength <= size )
        {
            bufferLength = size + 1;
            buffer = ( char * ) realloc( buffer, bufferLength );
        }
        memcpy ( buffer, copy.buffer, size + 1 );
    }
    return *this;
}

myString & myString::append( const myString& str, size_t len )
{
    char * new_string;
    size_t new_alloc, new_size, size_suffix=0;

    // don't use strlen - it can overrun the len passed in!
    // following codes get the char* length
    const char* p = str.getBuffer( ); //buffer;

    while ( *p && size_suffix < (unsigned)len )
    {
        ++p;
        ++size_suffix;
    }
    if ( !size_suffix)
        return *this;

    new_size = length () + size_suffix + 1;
    // check if we need to expand
    if ( new_size > bufferLength )
    {
        // compute new size
        new_alloc = assign_new_size ( new_size );

        // allocate new buffer
        new_string = (char*) malloc( new_alloc );
        new_string [ 0 ] = 0;

        // copy the previous allocated buffer into this one
        if ( bufferLength && buffer )
            memcpy ( new_string, buffer, length () );

        // append the suffix. It does exist, otherwize we wouldn't be expanding
        memcpy ( new_string + length (), str.buffer, size_suffix );

        // return previsously allocated buffer if any
        if ( bufferLength && buffer )
            free ( buffer );

        // update member variables
        buffer = new_string;
        bufferLength = new_alloc;
    }
    else
    {
        // we know we can safely append the new string
        memcpy ( buffer + length (), str.buffer, size_suffix );
    }
    size = new_size - 1;
    buffer [ size ] = '\0';
    return *this;

}

void myString::insert( size_t start, const myString & str, size_t len )
{
    if(len<=0 || start < 0 || start > str.length()  )
        return;

    char* tmp = buffer;
    if( size + len +1 >= bufferLength )
    {
        //resize( size + len + 1);
        char* tmp = new char [ size + len + 1];
    }

    memmove( buffer + start + len, buffer + start, size - start );
    memmove( buffer + start, str.buffer, len );
    size += len;
    bufferLength = size;
    buffer[size] = '\0';
    return;
}

int myString::compare(const myString& right) const
{
    const char* left= buffer;
    return strcmp( left, right.getBuffer() );
}

myString& myString::swap( myString& strB)
{
    myString tmp(strB);
    strB = *this;
    *this = tmp;
    return *this;
}

int myString::substr(myString& sub_str)
{
    int index =-1;
    int step=0;
    for(int i=0; i< size; i++)
    {
        if(buffer[i] == sub_str[step])
        {
            if(step==0)
            {
                index =i;
            }
            step++;
            if(step == sub_str.length())
            {
                return index;
            }
        }
        else
        {
            step=0;
        }
    }
    return -1;
}

ostream & operator<<(ostream &os, const myString &s)
{
    for(int i = 0; i < s.size; i++)
    {
        os << s.buffer[i];
    }
    return os;

}

bool operator==(const myString & s, const myString & t)
{
    if(s.length() != t.length())
    {
        return false;
    }
    else
    {
        for(int i = 0; i < s.length(); i++)
        {
            if(s.buffer[i] != t.buffer[i])
            {
                return false;
            }
        }
    }
    return true;

}





