//
//  Map.h
//  proj2
//
//  Created by Lily Zhou on 1/19/22.
//

#ifndef Map_h
#define Map_h
#include <string>
using KeyType = std::string;
using ValueType = double;



class Map
{
  public:
    Map();         // Create an empty map (i.e., one with no key/value pairs)
    ~Map();
    Map(const Map& other);
    Map &operator=(const Map &other);
    bool empty() const;  // Return true if the map is empty, otherwise false.
    int size() const;    // Return the number of key/value pairs in the map.
    bool insert(const KeyType& key, const ValueType& value);
    bool update(const KeyType& key, const ValueType& value);
    bool insertOrUpdate(const KeyType& key, const ValueType& value);
    bool erase(const KeyType& key);
    bool contains(const KeyType& key) const;
    bool get(const KeyType& key, ValueType& value) const;
    bool get(int i, KeyType& key, ValueType& value) const;
    void swap(Map& other);
    void dump() const;

private:
    struct Node
    {
        KeyType key;
        ValueType value;
        Node* next;
        Node* prev;
        
    };
    Node* head = nullptr;
    Node* tail = nullptr;
    int n_items;
    void addToFront(KeyType k, ValueType v);
    void addToRear(KeyType k, ValueType v);
    
};
bool merge(const Map& m1, const Map& m2, Map& result);
void reassign(const Map& m, Map& result);
#endif /* Map_h */
