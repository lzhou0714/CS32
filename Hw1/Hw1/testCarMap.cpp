//
//  testCarMap.cpp
//  Hw1
//
//  Created by Lily Zhou on 1/14/22.
//

#include "CarMap.h"
#include <cassert>
#include <iostream>
#include <string>
using namespace std;



int main()
{
    CarMap testcm;
    assert(testcm.fleetSize()==0);

    //test add Car

    //    //initialize size to default max and then run the following
    //    assert(testcm.fleetSize()==260);
    //    assert(testcm.addCar("hfgjhkjl") ==0);

    testcm.addCar("fhggkl");
    testcm.addCar("cmhb");
    testcm.addCar("oweryhouwf");
    assert(testcm.addCar("fhggkl")==0);
    assert(testcm.fleetSize()==3);

    testcm.print();
    cerr << endl;

    //test drive
    assert(testcm.drive("fhggkl", -1)==0);
    assert(testcm.drive("gdxcfhgvjhk", 8)==0);
    assert(testcm.drive("oweryhouwf", 5)==1);

    testcm.print();
    cerr << endl;
    //test miles
    assert(testcm.miles("oweryhouwf") == 5);
    assert(testcm.miles("fhggkl") == 0);
    assert(testcm.miles("fcyguhi")==-1);

}
