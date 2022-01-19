
#include "iostream"
using namespace std;
#include "newMap.h"
#include <string>
#include <cassert>
//#include <typeinfo>
//
//
//int main()
//{
//    Map m;  // maps ints to strings
//    assert(m.empty());
//    ValueType v = "Ouch";
//    assert( !m.get(42, v)  &&  v == "Ouch"); // v unchanged by get failure
//    m.insert(123456789, "Wow!");
//    assert(m.size() == 1);
//    KeyType k = 9876543;
//    assert(m.get(0, k, v)  &&  k == 123456789  &&  v == "Wow!");
//    cerr << "Passed all tests" << endl;
//}
//

//int main()
//{
//    Map m;  // maps strings to doubles
//    assert(m.empty());
//    ValueType v = -1234.5;
//    assert( !m.get("abc", v)  &&  v == -1234.5); // v unchanged by get failure
//    m.insert("xyz", 9876.5);
//    assert(m.size() == 1);
//    KeyType k = "hello";
//    assert(m.get(0, k, v)  &&  k == "xyz"  &&  v == 9876.5);
//    cerr << "Passed all tests" << endl;
////}
//
int main(){
    Map a(1000);   // a can hold at most 1000 key/value pairs
    Map b(5);      // b can hold at most 5 key/value pairs
    Map c;         // c can hold at most DEFAULT_MAX_ITEMS key/value pairs
    KeyType k[6] = { "vfcds","vefcsda","thnbgrvefc","htnbgrvfe","yjnhtbgrvfd","yutre"};
    ValueType v  = 1.0;

      // No failures inserting pairs with 5 distinct keys into b
    for (int n = 0; n < 5; n++)
        assert(b.insert(k[n], v));

      // Failure if we try to insert a pair with a sixth distinct key into b
    assert(!b.insert(k[5], v));

      // When two Maps' contents are swapped, their capacities are swapped
      // as well:
    a.swap(b);
    assert(!a.insert(k[5], v)  &&  b.insert(k[5], v));


//

        Map gpas;
//    //initialize size to max size to test that the function returns false when the array is full
//    assert(gpas.insert("jhkl", 1234) ==0);
//    assert(gpas.insertOrUpdate("jhkl", 1234) ==0);
//

    gpas.insert("Fred", 2.956);
    assert(!gpas.contains(""));
    gpas.insert("Ethel", 3.538);
    gpas.insert("", 4.000);
    gpas.insert("Lucy", 2.956);
    assert(gpas.contains(""));
    gpas.erase("Fred");
    assert(gpas.size() == 3  &&  gpas.contains("Lucy")  &&  gpas.contains("Ethel")  &&
                gpas.contains(""));
    string z;
    double v1;
    assert(gpas.get(1, z, v1)  &&  z == "Ethel");
    assert(gpas.get(0, z, v1)  &&  z == "");

    Map mm;
        mm.insert("Little Ricky", 3.206);
        mm.insert("Ethel", 3.538);
        mm.insert("Ricky", 3.350);
        mm.insert("Lucy", 2.956);
        mm.insert("Ethel", 3.538);
        mm.insert("Lucy", 2.956);
//        assert(mm.size() == 5);  // duplicate "Ethel" and "Lucy" were not added
        string x;
        double y;
        mm.get(0, x, y);
        cerr << "x = " << x<< endl;
        assert(x == "Ethel");  // "Ethel" is greater than exactly 0 items in mm
    mm.insert("Fred", 2.956);

        mm.get(4, x, y);
    cerr << "x = " << x<< endl;

        assert(x == "Ricky");  // "Ricky" is greater than exactly 4 items in mm
        mm.get(2, x, y);
    cerr << "x = " << x<< endl;

        assert(x == "Little Ricky");  // "Little Ricky" is greater than exactly 2 items in mm
        assert(y == 3.206);  // the value corresponding to the key "Little Ricky"



    Map m1;
    m1.insert("Fred", 2.956);
    Map m2;
    m2.insert("Ethel", 3.538);
    m2.insert("Lucy", 2.956);
    m2.insert("dfhgjkj", 3.242);
    m1.swap(m2);
    assert(m1.size() == 3  &&  m1.contains("Ethel")  &&  m1.contains("Lucy")  && m1.contains("dfhgjkj") &&
           m2.size() == 1  &&  m2.contains("Fred"));



    Map testMap = Map();
    cerr << "testMap size:" << testMap.size() << endl;
    cerr << "testMap empty: " << testMap.empty()<< endl;
    testMap.insert("cfhvgjbk", 1.568);
    testMap.insert("sdgfh", 2.321);

    cerr << "testMap size:" << testMap.size() << endl;
    cerr << "testMap empty:" << testMap.empty()<< endl;
    assert(testMap.contains("cfhvgjbk") == 1);
    assert(testMap.insert("cfhvgjbk", 1.568) == 0);
    assert(testMap.update("cfhvgjbk", 9.23) ==1);
    cerr << "testMap size:" << testMap.size() << endl;
    cerr << "testMap empty:" << testMap.empty()<< endl;
    assert(testMap.insertOrUpdate("cfhvgjbk", 1.568) == 1);
    cerr << "testMap size:" << testMap.size() << endl;
    cerr << "testMap empty:" << testMap.empty()<< endl;
    assert(testMap.erase("cfhvgjbk")==1);
    cerr << "testMap size:" << testMap.size() << endl;
    cerr << "testMap empty:" << testMap.empty()<< endl;



    return 0;
//    int test[10];
//    cerr << test.si;
};
