
#include "Map.h"
#include <iostream>
using namespace std;


bool merge(const Map& m1, const Map& m2, Map& result)
{
    const Map* ptrm1 = &m1;
    const Map* ptrm2 = &m2;
    Map* ptrR = &result;
    if (ptrm1 != ptrR && ptrm2!=ptrR) //if result is not the same as map 1 or two
    {
        result.~Map(); //empty result

    }
    bool returnValue = true;
    int i;
    KeyType k;
    ValueType v1;
    ValueType v2;
    for (i = 0; i<m2.size();i++) //find all keys unique to m2 and add it
    {
        m2.get(i,k,v2);
        if (!m1.contains(k)) //check that the key is unique to m2
        {
            result.insert(k, v2);
        }
    }
    for (i = m1.size()-1;i>=0;i--) //iterate through first map
    {
        m1.get(i, k,v2); //get the key value pairs of m1
        if (m2.get(k, v1)) //check if key in both maps
        {
            if (v1 == v2) //value that key corresponds to in both maps are equal
                result.insert(k, v2); //add to result
            else if  (v1 !=v2) //if not equal dont add the key and remove the key from result if it already contains it
            {
                if (result.contains(k))
                    result.erase(k);
                returnValue = false;
            }
        }
        else
        {
            result.insert(k, v2);
        }
    }

    return returnValue;
};
void reassign(const Map& m, Map& result)
{

    const Map* ptrm = &m;
    Map* ptrR = &result;
    if (ptrm!=ptrR) //if result is not the same as m
    {
        result.~Map(); //empty result
    }
    if (m.size()==0) //if map is empty nothing to rearrange
        return;
    int i;
    ValueType valueContainer;
    KeyType k;
    KeyType k2;
    ValueType v;
    ValueType v2;
    
    m.get(0,k, valueContainer);
    for (i = 0; i+1<m.size();i++)
    {
        m.get(i,k,v);
        m.get(i+1,k2,v2);
        result.insertOrUpdate(k, v2);
    }
    m.get(m.size()-1,k,v);
    result.insertOrUpdate(k, valueContainer);
};


void Map::addToFront(KeyType k, ValueType v)
{
    Node* p = new Node; //make new node and  make pointer point to it
    p->key = k;
    p->value = v;
    p->next = head; //links p to head
    if (head!=nullptr) //incase the linked list is empty
    {
        head->prev = p; //link from head to p
    }
    p->prev = nullptr;
    head = p; //update head to equal to the addressa at p

};
void Map::addToRear(KeyType k, ValueType v)
{
    Node* p = new Node;
    p->key = k;
    p->value = v;
    p->next = nullptr; //since this is the last item in the list
    p->prev = tail; //links new node to previous tail
    tail->next = p; //links previous tail to new node;
    tail = p; //moves tail pointer to point to new tail node;

};

Map::Map()
{
    n_items = 0;

    
};         // Create an empty map (i.e., one with no key/value pairs)
Map::~Map()
{
    while (head!=nullptr)
    {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    n_items = 0;
    head = nullptr;
    tail = nullptr;
}
Map::Map(const Map& other)
{

    n_items = 0;

    Node*p = other.head;
    while (p!=nullptr)
    {
        insert(p->key, p->value);
        p = p->next;
    }
}

Map& Map::operator=(const Map &other)
{
    if (head==other.head) //check if self = other
        return *this;
    
    this->~Map();
    n_items = 0;
    Node*p = other.head;
    while (p!=nullptr)
    {
        insert(p->key, p->value);
        p = p->next;
    }
    return *this;
};

void Map::dump() const
{
    Node* p  = head;
    while (p!= nullptr)
    {
        cerr <<"key: "<< p->key << endl;
        cerr <<"value: "<< p->value << endl;
        p = p->next;
    }
}

bool Map::empty() const
{
    return n_items ==0;
};

int Map::size() const
{
    return n_items;
};


bool Map::insert(const KeyType& key, const ValueType& value)
{
    if (contains(key))
        return false;
    else if (head == nullptr)
    {
        addToFront(key, value);
        tail = head; //since if the list only has one item then tail and head point to the same thing
    }
    else if (key< (head->key))
        addToFront(key, value);
    else if (key>(tail->key))
        addToRear(key, value);
    else
    {
        Node* p = new Node; //make new node and  make pointer point to it
        p->key = key;
        p->value = value;

        Node* track = head;
        while (track!=nullptr) //while the pointer has not reached the last item
        {
            if ((track->key) > (p->key))
            {
                p->prev = track->prev; //link to item before track
                p->next = track; //links item to item at track
                track->prev->next = p; //links item before track to p

                track->prev = p; //links item at track to p
                //track->next does not change
                break;

            }
            track = track->next;
        }
        
    }
    n_items++;
    return true;
};


bool Map::update(const KeyType& key, const ValueType& value)
{
    if (!contains(key))
        return false;
    
    Node* p = head;
    while (p!= nullptr)
    {
        if (p->key == key)
        {
            p->value = value;
            break;
        }
        p= p->next;
    }
    return true;

};

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value)
{
    if (!update(key, value)) //update returns false if the key is not already in the map, try inserting
        insert(key, value);//insert returns false if the key can't be added to the map
    return true;
};


bool Map::erase(const KeyType& key)
{
    Node* p = head;
    while (p!= nullptr)
    {
        if (p->key == key)
        {
            if (p->prev!=nullptr) //check if object is at the front of list, if not, runs
                p->prev->next = p->next;
            else
            {
                head = p->next; //set new head pointer if first obejct is destructred
            }
            if (p->next!=nullptr) //check if object is at the end of list, if not, runs
                p->next->prev = p->prev;
            else if (p->next == nullptr)
            {
                tail = p->prev; //move tail up when deleting from end of list


            }
            delete p;
            n_items--;
            return true;;
        }
        p= p->next;
    }


    return false;

};

bool Map::contains(const KeyType& key) const
{
    
    Node* p = head;
    while (p!= nullptr)
    {
        if (p->key == key)
            return true;
        p = p->next;
    }
    return false;
};

bool Map::get(const KeyType& key, ValueType& value) const
{
    Node* p = head;
    if (!contains(key))
        return false;
    else
    {
        while (p!= nullptr)
        {
            if (p->key == key)
            {
                value = p->value;
                return true;

            }
            p = p->next;
        }
        return true;
    }

};

bool Map::get(int i, KeyType& key, ValueType& value) const
{
    if (i<0 or i >=size())
        return false;
    Node* p = head;
    for (int j = 0; j<i;j++)
    {
        p = p->next;
    }
    key = p->key;
    value = p->value;
    return true;

};


void Map::swap(Map& other)
{
    int tempInt;
    Node* tempptr;
    
    tempInt = other.n_items;
    other.n_items = n_items;
    n_items = tempInt;
    
    tempptr = other.head;
    other.head = head;
    head = tempptr;
    
    tempptr = other.tail;
    other.tail = tail;
    tail = tempptr;
    
};

