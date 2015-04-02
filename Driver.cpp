#include <iostream>
#include <iomanip>
#include <cassert>
#include <fstream>
#include <string>
#include <vector>
#include <time.h>
#include <unistd.h>
#include <map>
#include <cstdlib>
#include <cmath>
#include <iterator>
#include "SeparateChaining.h"

using namespace std;

int TABLE_SIZE; //Make TABLE_SIZE global to allow the Table Size to be taken in within main() and used in hash()

size_t hasher(const string & key); //declaration of hash function


int main()
{
	Symbol temp;
	vector<Symbol> symbols;
	string s;
    
    int t;
    int hash_key_array[TABLE_SIZE]; //array to hold hash key values
	
	ifstream file;
    file.open("symbols.txt");
    cout << "Opening file..." << endl;
    if(!file)
    {
    	cout << "System failed to open file.";
    }
    else
    {
    	cout << "File successfully opened" << endl;
    }

    int numSymbols;
    //for loop to read in the string name and the integer that follows the string name from symbols.txt
    while(file >> s)
    {
        numSymbols++;
        temp.setData(s);
        file >> t;
        temp.setType(t);
        symbols.push_back(temp);
    }


    cout << "What size would you like the hash table to be?" << endl;
    cin >> TABLE_SIZE;

    HashTable<Symbol> hashtable(TABLE_SIZE); //makes a hash table using TABLE_SIZE
    cout << endl;

    //loop to populate the hash table delcared above
    for(int j = 0; j < numSymbols; j++)
    {
    	temp.setData(symbols[j].getData());
        cout << temp.getData() << endl;

        temp.setType(symbols[j].getType());
        cout << temp.getType() << endl;

        cout << endl;

        hashtable.insert(temp);
    }
  hashtable.print();
}


//function to get the correct hash value
size_t hasher(const string & key)
{
	size_t hashVal = 0;

	for(char ch : key)
	{
		hashVal = 37 * hashVal + ch;
	}
	return labs(hashVal % TABLE_SIZE);
}








