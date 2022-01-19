//
//  CarMap.cpp
//  Hw1
//
//  Created by Lily Zhou on 1/14/22.
//
#include <iostream>
#include "CarMap.h"
using namespace std;
CarMap:: CarMap()
{
//    std::cerr <<( m_map.empty());
    
};       // Create an empty car map.

bool CarMap::addCar(std::string license)
{
    if(!m_map.contains(license))
    {
        if (m_map.insert(license, 0))
            return true;
    }
        
    return false;
};
  // If a car with the given license plate is not currently in the map,  there is room in the map, add an entry for that car recording that it has been driven 0 miles, and return true.
  // Otherwise, make no change to the map and return false.

double CarMap::miles(std::string license) const
{
    double value = -1;
    m_map.get(license, value);
    return value;
};
  // If a car with the given license plate is in the map, return how
  // many miles it has been driven; otherwise, return -1.

bool CarMap::drive(std::string license, double distance)
{
    if (distance <0 || !m_map.contains(license))
        return false;
    m_map.update(license, distance + miles(license));
    return true;
};
  // If no car with the given license plate is in the map or if
  // distance is negative, make no change to the map and return
  // false.  Otherwise, increase by the distance parameter the number
  // of miles the indicated car has been driven and return true.

int CarMap::fleetSize() const
{
    return m_map.size();
};// Return the number of cars in the CarMap.

void CarMap::print() const
{
    int i;
    string license;
    double value;
    for (i = 0; i<fleetSize();i++)
    {
        m_map.get(i, license, value);
        cout << license<< " " << value << endl;
    }
};
  // Write to cout one line for every car in the map.  Each line
  // consists of the car's license plate, followed by one space,
  // followed by the number of miles that car has been driven.  Write
  // no other text.  The lines need not be in any particular order.

