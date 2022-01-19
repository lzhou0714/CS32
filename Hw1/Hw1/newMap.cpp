//
//  newMap.cpp
//  Hw1
//
//  Created by Lily Zhou on 1/15/22.
//

#include "newMap.h"
#include <string>
#include <iostream>
using namespace std;

//using KeyType = std::string;
 //Your implementation of the Map class must be such that the compiler-generated destructor, copy constructor, and assignment operator do the right things.

//private function
struct MapItem;

int Map::keyLocation(KeyType key) const
{
    
    int i;
    for (i = 0; i<size();i++)
    {
        if (key == itemsList[i].key )
        {
            return i;
        }
    }
    return -1;
};

void Map::sortMap()
{
    int n = size();
    int i, j;
//    insertion sort
    for (i = 1; i<n; i++) //starts off at second element
    {
        MapItem temp = itemsList[i]; //stores current element in temp
        j = i-1;
        while (j>=0 && temp.key < itemsList[j].key) //checks if the previous item is larger, if it is, switch positions
        {
            itemsList[j+1] = itemsList[j];
            j--;
        }
        itemsList[j+1] = temp;
    }
}



//public///////////////////////////////////////////
Map::Map()
{
    n_items = 0;
    maxSize =DEFAULT_MAX_ITEMS;
    itemsList = new MapItem[maxSize];
};         // Create an empty map (i.e., one with no key/value pairs)


Map::Map(int n)
{
    n_items = 0;
    maxSize = n;
    itemsList = new MapItem[maxSize];
    
}

Map::~Map()
{
    delete [] itemsList;
    
};

//copy constructor
Map::Map(const Map& other )
{
    n_items = other.n_items;
    maxSize = other.maxSize;
    itemsList = new MapItem[maxSize];
    for (int i = 0;i<n_items;i++)
    {
        itemsList[i] = other.itemsList[i];
    }
};

//assignment operator
Map& Map::operator=(const Map& other)
{
    delete [] itemsList;
    n_items = other.n_items;
    maxSize = other.maxSize;
    itemsList = new MapItem[maxSize];
    
    for (int i = 0;i<n_items;i++)
    {
        itemsList[i] = other.itemsList[i];
    }
    return *this;
};
bool Map::empty() const
{
    return n_items ==0;
};  // Return true if the map is empty, otherwise false.
//const
int Map::size() const
{
    return n_items;
};    // Return the number of key/value pairs in the map.
// const

bool Map::insert(const KeyType& key, const ValueType& value)
{
    if (n_items >= maxSize)
        return false;
    if (contains(key)) //
        return false;
    itemsList[n_items].key = key;
    itemsList[n_items].value = value;
    //adds key value pair to last index postion
    n_items++; //update n_items

    sortMap();
    return true;

};


bool Map::update(const KeyType& key, const ValueType& value)
{
    if (!contains(key))
        return false;
    itemsList[keyLocation(key)].value = value;
    
        
    return true;

};

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value)
{
    if (!update(key, value)) //update returns false if the key is not already in the map, try inserting
        if (!insert(key, value))//insert returns false if the key can't be added to the map
            return false; //if both are false then it means that the key is not already in the map but can;t be added
    {
            
    }
    
    return true;
};


bool Map::erase(const KeyType& key)
{
    if (contains(key))
    {
        int n = keyLocation(key);
        //shift everything left
        while (n+1<n_items)
        {
            itemsList[n] = itemsList[n+1];
            n++;
        }
        n_items--;

        return true;
    }
    
    return false;

};

bool Map::contains(const KeyType& key) const
{
    int i;
    for (i = 0; i<size();i++)
    {
        if (key == itemsList[i].key )
        {
            return true; //key already exists, returns index position of key
        }
            
    }
    return false;

};

bool Map::get(const KeyType& key, ValueType& value) const
{
    if (contains(key))
    {
        
        value = itemsList[keyLocation(key)].value;
        return true;
    }
    return false;

};

bool Map::get(int i, KeyType& key, ValueType& value) const
{
    if (i<0 or i >=size())
        return false;
    key = itemsList[i].key;
    value = itemsList[i].value;
    return true;

};


void Map::swap(Map& other)
{
    int i  = other.n_items;
    other.n_items = n_items;
    n_items = i;
    
    i = maxSize;
    maxSize = other.maxSize;
    other.maxSize = i;
    
    MapItem* temp = itemsList;
    itemsList = other.itemsList;
    other.itemsList = temp;
};

