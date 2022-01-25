
#include "Map.h"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    Map emptyMap;
    //given test cases
    Map msd;  // KeyType is std::string, ValueType is double
        msd.insert("ccc", 80);
        msd.insert("aaa", 40);
        msd.insert("ddd", 60);
        msd.insert("bbb", 20);
        KeyType k = "xxx";
        ValueType v;

            assert(!msd.get(4, k, v)  &&  k == "xxx");  // x is unchanged
            assert(msd.get(1, k, v)  &&  k == "bbb");   // "bbb" is greater than
                                                        // exactly 1 item

//////////////////own test cases////////////////////////////
    //check that map constructs
    Map gpas;
//    //initialize size to max size to test that the function returns false when the array is full
//    assert(gpas.insert("jhkl", 1234) ==0);
//    assert(gpas.insertOrUpdate("jhkl", 1234) ==0);
//
    assert(gpas.empty());
    gpas.insert("Fred", 2.956);
    assert(!gpas.empty());
    assert(gpas.contains("Fred"));
    assert(!gpas.contains(""));

    //inserts at front
    assert(!gpas.update("Ethel", 1.222));
    gpas.insert("Ethel", 3.538);
    assert(gpas.update("Ethel", 1.222));
    gpas.insert("", 4.000);

    //inserts at end
    gpas.insert("Lucy", 2.956);
    gpas.insert("Zayne", 506.2);

    //inserts in the middle
    gpas.insert("George", 2.29);
    gpas.insert("Ash", 506.2);
    gpas.dump();

    assert(gpas.contains(""));
    assert(gpas.size() == 7);
    assert(gpas.size() == 7  && gpas.contains("George") && gpas.contains("Ash") && gpas.contains("Fred") &&  gpas.contains("Lucy")  &&  gpas.contains("Ethel")  &&
gpas.contains("") && gpas.contains("Zayne"));

    //test assignment operator
    gpas = gpas; //reassigning an object to itslef
    assert(gpas.size() == 7  && gpas.contains("George") && gpas.contains("Ash") && gpas.contains("Fred") &&  gpas.contains("Lucy")  &&  gpas.contains("Ethel")  &&
gpas.contains("") && gpas.contains("Zayne"));
    cerr << "////////////copyGpa////////////" << endl;
    Map copyGpa;
    copyGpa.insert("Bob", 301.2);
    copyGpa.insert("giyl", 12.5);
    assert(copyGpa.size() == 2  &&  copyGpa.contains("Bob") &&  copyGpa.contains("giyl"));
    copyGpa.dump();

    //reconstrcuted to an empty map
    cerr << "////////////emptyGpa1 : reconstructed to an empty map////////////" << endl;
    Map emptyGpa(copyGpa);
//    cerr << "////////////pre reconstruction////////////" << endl;
    assert(emptyGpa.size() == 2  &&  emptyGpa.contains("Bob") &&  emptyGpa.contains("giyl"));
//    cerr << "////////////post reconstruction////////////" << endl;
    emptyGpa = emptyMap;
    assert(emptyGpa.size()==0 && !emptyGpa.contains(""));


    cerr << "////////////gpas2////////////" << endl;
    Map gpas2;
    gpas2.insert("Bob", 301.2);
    gpas2 = gpas;
    gpas2.dump();
    copyGpa = gpas2;
    cerr << "////////////deconstructed gpas2////////////" << endl;
    gpas2.~Map(); //check that the reassigned object still holds it values when the original object is deconstructed
    gpas2.dump();
    cerr << "/////////////copyGpa reassigned///////////" << endl;

    copyGpa.dump();
    assert(gpas.size() == 7  && gpas.contains("George") && gpas.contains("Ash") && gpas.contains("Fred") &&  gpas.contains("Lucy")  &&  gpas.contains("Ethel")  &&
gpas.contains("") && gpas.contains("Zayne"));
    assert(copyGpa.size()==7  && copyGpa.contains("George") && copyGpa.contains("Ash") && copyGpa.contains("Zayne") && copyGpa.contains("Fred") &&  copyGpa.contains("Lucy")  &&  copyGpa.contains("Ethel")  && copyGpa.contains(""));

    //test copy constructor

    Map copyConstructedGpa = copyGpa;
    cerr << "///////////copyConstructedGpa/////////////" << endl;
    copyConstructedGpa.dump();
    copyGpa.~Map(); //check that if copyGpa is deleted copy constructed Gpa is still there
    cerr << "///////////copy Gpa dump: /////////////" << endl;
    copyGpa.dump();
    assert(copyConstructedGpa.size()==7  && copyConstructedGpa.contains("George") && copyConstructedGpa.contains("Ash") && copyConstructedGpa.contains("Zayne") && copyConstructedGpa.contains("Fred") &&  copyConstructedGpa.contains("Lucy")  &&  copyConstructedGpa.contains("Ethel")  && copyConstructedGpa.contains(""));
    cerr << "////////////emptyGpa2 : copy constructed to an empty map////////////" << endl;
    Map emptyGpa1(emptyMap); //copy constructed to empty map
    assert(emptyGpa1.size()==0 && !emptyGpa1.contains(""));
    //test erase function

    //delete from middle of linked list
    assert(gpas.erase("Fred"));
    assert(!gpas.erase("akagkcakc"));
    cerr << "/////////////Fred erased///////////" << endl;
    gpas.dump();
    assert(gpas.size() == 6  && gpas.contains("George") && gpas.contains("Ash")  &&  gpas.contains("Lucy")  &&  gpas.contains("Ethel")  &&
gpas.contains("") && gpas.contains("Zayne"));


//    //delete from top
    cerr << "/////////////////top object deleted///////////"<< endl;
    assert(gpas.erase(""));
    gpas.dump();
    assert(gpas.size() == 5  && gpas.contains("George") && gpas.contains("Ash")  &&  gpas.contains("Lucy")  &&  gpas.contains("Ethel") && gpas.contains("Zayne"));


//    delete from end of linked list
    cerr << "/////////////////last object deleted///////////"<< endl;

    assert(gpas.erase("Zayne"));
    gpas.dump();
    assert(gpas.size() == 4  && gpas.contains("George") && gpas.contains("Ash")  &&  gpas.contains("Lucy")  &&  gpas.contains("Ethel"));

//   try erasing empty map
    assert(!emptyMap.erase("") && emptyMap.size() == 0);
//erase all member of a map
    cerr << "/////////////////erase entire map one by one///////////"<< endl;

    assert(copyConstructedGpa.size()==7  && copyConstructedGpa.contains("George") && copyConstructedGpa.contains("Ash") && copyConstructedGpa.contains("Zayne") && copyConstructedGpa.contains("Fred") &&  copyConstructedGpa.contains("Lucy")  &&  copyConstructedGpa.contains("Ethel")  && copyConstructedGpa.contains(""));
    assert(copyConstructedGpa.erase("George") && copyConstructedGpa.size()==6 && !copyConstructedGpa.contains("George") && copyConstructedGpa.contains("Ash") && copyConstructedGpa.contains("Zayne") && copyConstructedGpa.contains("Fred") &&  copyConstructedGpa.contains("Lucy")  &&  copyConstructedGpa.contains("Ethel")  && copyConstructedGpa.contains("")); //erase from middle
    assert(copyConstructedGpa.erase("Ash")&& copyConstructedGpa.size()==5 && !copyConstructedGpa.contains("George") && !copyConstructedGpa.contains("Ash") && copyConstructedGpa.contains("Zayne") && copyConstructedGpa.contains("Fred") &&  copyConstructedGpa.contains("Lucy")  &&  copyConstructedGpa.contains("Ethel")  && copyConstructedGpa.contains("")); //erase from top
    assert(copyConstructedGpa.erase("Zayne")&& copyConstructedGpa.size()==4 && !copyConstructedGpa.contains("George") && !copyConstructedGpa.contains("Ash") && !copyConstructedGpa.contains("Zayne") && copyConstructedGpa.contains("Fred") &&  copyConstructedGpa.contains("Lucy")  &&  copyConstructedGpa.contains("Ethel")  && copyConstructedGpa.contains("")); // erase from bottom
    assert(copyConstructedGpa.erase("Fred") && copyConstructedGpa.size()==3  &&!copyConstructedGpa.contains("George") && !copyConstructedGpa.contains("Ash") && !copyConstructedGpa.contains("Zayne") && !copyConstructedGpa.contains("Fred") &&  copyConstructedGpa.contains("Lucy")  &&  copyConstructedGpa.contains("Ethel")  && copyConstructedGpa.contains(""));
    assert(copyConstructedGpa.erase("Lucy")&& copyConstructedGpa.size()==2 && !copyConstructedGpa.contains("George") && !copyConstructedGpa.contains("Ash") && !copyConstructedGpa.contains("Zayne") && !copyConstructedGpa.contains("Fred") &&  !copyConstructedGpa.contains("Lucy")  &&  copyConstructedGpa.contains("Ethel")  && copyConstructedGpa.contains(""));
    assert(copyConstructedGpa.erase("")&& copyConstructedGpa.size()==1 && !copyConstructedGpa.contains("George") && !copyConstructedGpa.contains("Ash") && !copyConstructedGpa.contains("Zayne") && !copyConstructedGpa.contains("Fred") &&  !copyConstructedGpa.contains("Lucy")  &&  copyConstructedGpa.contains("Ethel")  && !copyConstructedGpa.contains(""));
    cerr << "/////////////////erase from map of length one///////////"<< endl;

    assert(copyConstructedGpa.erase("Ethel")&& copyConstructedGpa.size()==0 && !copyConstructedGpa.contains("George") && !copyConstructedGpa.contains("Ash") && !copyConstructedGpa.contains("Zayne") && !copyConstructedGpa.contains("Fred") &&  !copyConstructedGpa.contains("Lucy")  &&  !copyConstructedGpa.contains("Ethel")  && !copyConstructedGpa.contains("")); //erasinng from array of length one

    copyConstructedGpa.dump();
    assert(!copyConstructedGpa.erase("Ethel") && copyConstructedGpa.size()==0); //attempt to erase from empty map should return false




//    test the get function ver 1
    double value = 0;
    assert(!gpas.get("Fred", value)); //returns false since Fred is not in map
    assert(value == 0); //test that value is not changed
    assert( gpas.get("Ash", value));
    assert(value == 506.2);
    assert( gpas.get("George", value));
    assert(value == 2.29 );
    assert( gpas.get("Lucy", value));
    assert(value == 2.956 );

//    test the get function ver2

    string key = "";
    value = 0;
    assert(!gpas.get(-1,key, value)); //returns false since Fred is not in map
    assert(!gpas.get(7,key, value)); //returns false since Fred is not in map
    assert(key == "" && value == 0); //test that value is not changed
    assert( gpas.get(0,key, value));
    assert(key == "Ash" && value == 506.2);
    assert( gpas.get(1,key, value));
    assert(key == "Ethel" && value == 1.222);
    assert( gpas.get(2,key, value));
    assert(key == "George" && value == 2.29 );
    assert( gpas.get(3,key, value));
    assert(key == "Lucy" && value == 2.956);
    assert(!gpas.get(4,key, value));
    assert(key == "Lucy" && value == 2.956);

//test swap
    Map m1;
    m1.insert("Fred", 2.956);
    Map m2;
    m2.insert("Ethel", 3.538);
    m2.insert("Lucy", 2.956);
    m2.insert("dfhgjkj", 3.242);
    m1.swap(m2);
    assert(m1.size() == 3  &&  m1.contains("Ethel")  &&  m1.contains("Lucy")  && m1.contains("dfhgjkj") &&
           m2.size() == 1  &&  m2.contains("Fred"));
    cerr << "////////////swapped m1 ///////" << endl;
    m1.dump();
    cerr << "////////////swapped m2 ///////" << endl;
    m2.dump();

//test merge
//possible cases
//    result is an empty map
//    m1 and m2 have no overlapping keys
//    result is the same as m1
//    result is not the same as m1 or m1 but has preexisting values

    //m1, m2, m1 and m2 have overlapping keys that have the same value
    cerr << "/////////////////result1///////////"<< endl;

    Map sub1;
    assert(sub1.insert("Fred", 123));
    assert(sub1.insert("Ethel", 456));
    assert(sub1.insert("Lucy", 789));
    Map sub2;
    assert(sub2.insert("Lucy", 789));
    assert(sub2.insert("Ricky", 321));
    Map result;
    assert(merge(sub1,sub2,result) && result.contains("Fred")&& result.contains("Ethel")&& result.contains("Lucy") && result.contains("Ricky") );
    result.dump();
//    result.~Map();

    //    result is the same as m2
    cerr << "/////////////////m2 = result///////////"<< endl;
    cerr << "/////////////////m2 premerge///////////"<< endl;
    sub2.dump();
    assert(sub2.size()==2);
    assert(merge(sub1,sub2,sub2)  && sub2.size() == 4 && sub2.contains("Fred")&& sub2.contains("Ethel")&& sub2.contains("Lucy") && sub2.contains("Ricky") );
    cerr << "/////////////////m2 postmerge///////////"<< endl;
    sub2.dump();

    //    m1 and m2 have overlapping keys that have different values
    cerr << "/////////////////result1///////////"<< endl;
    Map result2;
    result2.insert("jfgvkhhk", 1);
    result2.insert("dfvsv", 1);


    sub2.update("Lucy", 654);
    assert(sub2.get("Lucy", value) && value == 654);
    assert(!merge(sub1,sub2,result2) && result2.size()==3 && result2.contains("Fred")&& result2.contains("Ethel")&& result2.contains("Ricky") && !result2.contains("jfgvkhhk") && !result2.contains("dfvsv") && !result2.contains("Lucy"));
    result2.dump();

    //    result is the same as m2
    cerr << "/////////////////m2 = result (overlapping keys different values)///////////"<< endl;
    cerr << "/////////////////m2 premerge///////////"<< endl;
    sub2.dump();
    cerr << "/////////////////m2 postmerge///////////"<< endl;
    assert(!merge(sub1,sub2,sub2) && sub2.size()==3 && sub2.contains("Fred")&& sub2.contains("Ethel")&& sub2.contains("Ricky"));
    sub2.dump();


    //m1 and m2 are the same
    cerr << "/////////////////m1 and m2 are the same///////////"<< endl;
    sub1.~Map();
    sub2.~Map();
    result.~Map();
    assert(sub1.insert("Fred", 123));
    assert(sub1.insert("Ethel", 456));
    assert(sub1.insert("Lucy", 789));
    sub2 = sub1;
    assert(merge(sub1,sub2,result) && result.size() ==3 &&result.contains("Fred") && result.contains("Ethel")&& result.contains("Lucy"));
    result.dump();

    cerr << "/////////////////m1 same keys as m2 but different values, result = m1///////////"<< endl;

    sub1.~Map();
    sub2.~Map();
    result.~Map();
    assert(sub1.insert("c", 3));
    assert(sub1.insert("d", 4));
    assert(sub1.insert("a", 1));
    assert(sub1.insert("b", 2));
    assert(sub2.insert("c", 1883));
    assert(sub2.insert("d", 456));
    assert(sub2.insert("a", 425));
    assert(sub2.insert("b", 123));
    assert(!merge(sub1,sub2,sub1) && sub1.size()==0);
    sub1.dump();
//    cerr << "sub1 size" << sub1.size() << endl;
//    sub2.dump();
//    cerr << "sub2 size" << sub2.size() << endl;


    //    result is a non empty map and contains keys that should and should not be included
    cerr << "/////////////////result originally non empty unique map///////////"<< endl;

    sub1.~Map();
    sub2.~Map();
    result.~Map();
    assert(sub1.insert("c", 3));
    assert(sub1.insert("d", 4));
    assert(sub1.insert("a", 1));
    assert(sub1.insert("b", 2));
    assert(sub2.insert("a", 1));
    assert(sub2.insert("b", 4));
    assert(sub2.insert("j", 5));
    assert(sub2.insert("c", 3));
    assert(result.insert("a", 7));
    assert(result.insert("b", 2));
    assert(result.insert("t", 87));
    assert(result.insert("z", 321));


    assert(!merge(sub1,sub2,result));
    result.dump();
    assert(result.size() == 4 && result.contains("a") && result.contains("c") && result.contains("d") && result.contains("j"));
    cerr << "/////////////////result originally non empty unique map///////////"<< endl;

    assert(!merge(sub1,sub2,sub1));
    assert(sub1.contains("a") && sub1.contains("c") && sub1.contains("d") && sub1.contains("j"));



//m1 or m2 is empty
//    result = emptyMap;
    cerr << "/////////////////m1 is an empty map///////////"<< endl;

    sub1 = emptyMap;
    assert(merge(sub1,sub2,result));
    result.dump();
    assert(result.contains("a") && result.contains("b") && result.contains("j") && result.contains("c"));


//    test reassign
    cerr <<"/////////////reassign r1 non empty result//////" << endl;
    cerr <<"/////////////prereassigning r1//////" << endl;
    Map r1 = gpas;
    r1.dump();
    cerr <<"/////////////post reassign result//////" << endl;
    reassign(r1, result);
    result.dump();
    cerr <<"/////////////r1 = result//////" << endl;
    cerr <<"/////////////pre//////" << endl;

    r1.dump();
    reassign(r1, r1);
    cerr <<"/////////////post//////" << endl;
    r1.dump();

    cerr <<"/////////////reassign map of length one//////" << endl;
    Map singleNode;
    singleNode.insert("igkh", 5);
    reassign(singleNode, result);
    result.dump();
    cerr <<"/////////////reassign empty map//////" << endl;
    reassign(emptyMap, result);
    assert(emptyMap.size() ==0 && result.size()==0);
    result.dump();
    cerr <<"/////////////reassign empty map + result = empty map//////" << endl;
    reassign(emptyMap, emptyMap);
    emptyMap.dump();

}
/*
 void Map::LinkedList::addItem(KeyType k, ValueType v)
{
    if key is in map return false
    iterate through the list
        if key is larger than the key at the current node
            move on to the next node
        if key is smaller
            insert new node before current node
    return true


}
 bool merge(const Map& m1, const Map& m2, Map& result);
 {
     check if result is the same as m1 or m2
         if it isnt the deconstruct it
     if it is keep as is
     iterate through the m1
         find the key and value at each node
             check if the key is in m2
                 if the key is in the otehr map check if corresponding the values are
                 the same add to/update result if different do nothing and prepare to
                 return false
             if the key is only in the m1 add to result
     iterate through m2
         find keys unique to m2 since overlapping keys would have
         been updated through m1 and add it to restult

     void reassign(const Map& m, Map& result)
 }

{
 check if result is the same as m, if not destruct to clear
 iterate through m,
    get the value at the next node and chaneg the value at the current node to that value
}
*/
