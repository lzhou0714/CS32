//
//  Map.hpp
//  Hw1
//
//  Created by Lily Zhou on 1/12/22.
//

#ifndef Map_hpp
#define Map_hpp
#include <string>
using KeyType = std::string;
using ValueType = double;
//using KeyType = int;
//using ValueType = std::string;
const int DEFAULT_MAX_ITEMS = 260;

struct MapItem
{
    public:
        KeyType key;
        ValueType value;
};
class Map
{
  public:
    Map();         // Create an empty map (i.e., one with no key/value pairs)

    bool empty() const;  // Return true if the map is empty, otherwise false.
//const
    int size() const;    // Return the number of key/value pairs in the map.
// const
    bool insert(const KeyType& key, const ValueType& value);

    bool update(const KeyType& key, const ValueType& value);
    bool insertOrUpdate(const KeyType& key, const ValueType& value);

    bool erase(const KeyType& key);

    bool contains(const KeyType& key) const;

    bool get(const KeyType& key, ValueType& value) const;

    bool get(int i, KeyType& key, ValueType& value) const;

    void swap(Map& other);

private:
//    const int DEFAULT_MAX_ITEMS = 260;
    //important for spec
    MapItem itemsList[DEFAULT_MAX_ITEMS];
    int n_items;

    //self added help functions
    int keyLocation(KeyType key) const;
    void sortMap();
    void swapHelper(Map& n1,Map& n2);

    
};

#endif

