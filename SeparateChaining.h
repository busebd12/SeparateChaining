#ifndef SEPARATE_CHAINING_H
#define SEPARATE_CHAINING_H

#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <functional>
#include "Symbol.h"
#include <iterator>

using namespace std;

int nextPrime( int n );
bool isPrime( int n );


// SeparateChaining Hash table class
//
// CONSTRUCTION: an approximate initial size or default of 101
//
// ******************PUBLIC OPERATIONS*********************
// bool insert( x )       --> Insert x
// bool remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// void makeEmpty( )      --> Remove all items

template<typename string>
class thehash2
{
public:
    size_t operator()(const string & key)
    {
        size_t hashVal = 0;
        for(char ch : key)

            //takes the key and combines all of the ASCI II
            //characters together and makes a single number
            //these numbers are generated from the ASCII value of each character
            hashVal = 37 * hashVal + ch;
        return hashVal;
    }
};


//defining a template for the hash
//specifically used for symbols
template<typename Symbol>
class thehash
{
public:

    //overloading the () operator
    size_t operator()(const Symbol & item)
    {
        static thehash2<string> hf;
        return hf(item.getData());
    }
};


//declaring a template for the HashTable 
//specifically for Hashed Objects
template <typename HashedObj>
class HashTable
{
  public:

    //Uses the whatever value table_size has
    //Otherwise, it will make a hash table of size 101
    explicit HashTable( int size = 101 )
    { 
        currentSize = 0;
        theLists.resize(size); 
    }

    bool contains( const HashedObj & x ) const
    {
        //represents the correct list in the hash table vector to start looking through
        auto & whichList = theLists[ myhash( x ) ];

        //returns whatever you wanted to search for in the table provided it is there
        return find( begin( whichList ), end( whichList ), x ) != end( whichList );
    }

    void makeEmpty( )
    {
        for( auto & thisList : theLists )
        {
            thisList.clear( );
        }
    }

    bool insert( const HashedObj & x )
    {
         //represents the correct list in the hash table vector to start looking through
        auto & whichList = theLists[myhash( x )];

        //goes through the beginning and end of the list, and if it
        //doesn't get to the end, then it found the object you wanted to insert in the hash table already
        //prevents duplicate insertions
        if( find( begin( whichList ), end( whichList ), x ) != end( whichList) )
        {
            return false;
        }
        if(whichList.size() > 0)
        {
            cout << "Collision Occured. " << endl;
        }
        //otherwise, it has gotten to the end of the list without finding a duplicate
        //and puts what you want to insert in the list
        whichList.push_back( x );

        /*
        // Rehash; see Section 5.5
        if( ++currentSize > theLists.size( ) )
        {
            rehash( );
            cout << "New Table Created" << endl;
        }
        */


        return true;
    }
    
    
    bool insert( HashedObj && x )
    {
        //represents the correct list in the hash table vector to start looking through
        auto & whichList = theLists[ myhash( x ) ]; 

        //goes through the beginning and end of the list, and if it
        //doesn't get to the end, then it found the object you wanted to insert in the hash table already
        //prevents duplicate insertions
        if( find( begin( whichList ), end( whichList ), x ) != end( whichList ) )
        {
            return false;
        }

        //checks for collisions
        if(whichList.size() > 0)
        {
            cout << "Collision Occured. " << endl;
        }
        whichList.push_back( std::move( x ) );

        //see the rehash function
        if( ++currentSize > theLists.size( ) )
        {
            rehash( );
            cout << "New Table Created" << endl;
        }


        return true;
    }
    

    bool remove( const HashedObj & x )
    {
        //represents the correct list in the hash table vector to start looking through
        auto & whichList = theLists[ myhash( x ) ];

        //trying to find x within the list
        //the iterator points to the slot in the list that contains x
        auto itr = find( begin( whichList ), end( whichList ), x );

        //if it gets to the end of the list without finding what you want to remove, then it returns false
        if( itr == end( whichList ) )
        {
            return false;
        }
            

        //if it finds x, it removes it from the list
        whichList.erase( itr );
        --currentSize;
        return true;
    }

    //function to print out the hash table
    void print()
    {
        
        //loop using iterators to iterate through the vector "theLists"
        //and print out its contents
        for(int i = 0; i < theLists.size(); ++i)
        {
            typename list<HashedObj>::iterator li;
            for(li = theLists[i].begin(); li != theLists[i].end(); ++li)
            {
                cout << *li << endl;
            }       
        }
    }

  private: 
     vector<list<HashedObj>> theLists; // The array of Lists
     int currentSize;

     //function to rehash the table
     void rehash( )
     {
         vector<list<HashedObj>> oldLists = theLists;

         // Creates new double-sized, empty table
         theLists.resize( nextPrime( 2 * theLists.size( ) ) );
         for( auto & thisList : theLists )
         {
             thisList.clear( );
         }

         // Copies the old table into the new table
         currentSize = 0;
         for( auto & thisList : oldLists )
         {
             for( auto & x : thisList )
             {
                insert( std::move( x ) );
             }
         }
                 
     }

    //this takes in an object, puts this object through the hash templates defined above and creates a hashed object named hf
    size_t myhash( const HashedObj & x ) const
    {
         static thehash<HashedObj> hf;

         //mods it by the table size to get appropriate hash
         return hf( x ) % theLists.size( );
    }

};


//function to simply search for the next prime number
int nextPrime( int n )
{
    if( n % 2 == 0 )
    {
        ++n;
    }
        

    for( ; !isPrime( n ); n += 2 )
    {

    }
        

    return n;
}


//function to simply see if a number is prime
bool isPrime( int n )
{
    if( n == 2 || n == 3 )
        return true;

    if( n == 1 || n % 2 == 0 )
        return false;

    for( int i = 3; i * i <= n; i += 2 )
        if( n % i == 0 )
            return false;

    return true;
}


#endif