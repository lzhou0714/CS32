//
//  Map.cpp
//  Hw1
//
//  Created by Lily Zhou on 1/12/22.
//

#include "Map.h"
#include <string>
#include <iostream>
using namespace std;

//using KeyType = std::string;
 //Your implementation of the Map class must be such that the compiler-generated destructor, copy constructor, and assignment operator do the right things.

//private function
struct MapItem;
void Map::swapHelper(Map& n1,Map& n2) //n1 smaller, n2 larger
{
    int j;
    MapItem temp;
    for (j = 0; j<n1.size(); j++) //copies over smaller array to larger array
    {
        temp = n1.itemsList[j];
        n1.itemsList[j] = n2.itemsList[j];
        n2.itemsList[j] = temp;
    }
    for (j; j<n2.size(); j++ ) //copies rest of larger array to smaller array
    {
        n1.itemsList[j] = n2.itemsList[j];
    }
    j = n1.n_items;
    n1.n_items = n2.n_items;
    n2.n_items = j;
}
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



//public
Map::Map()
{
    n_items = 0;
};         // Create an empty map (i.e., one with no key/value pairs)

//private member function

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
    if (n_items >= DEFAULT_MAX_ITEMS)
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
    if (other.size()<=size())
    {
        swapHelper(*this, other);
    }
    else
        swapHelper(other, *this);
};

