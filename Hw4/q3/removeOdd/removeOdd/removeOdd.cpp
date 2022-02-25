//
//  main.cpp
//  removeOdd
//
//  Created by Lily Zhou on 2/22/22.
//
#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>
using namespace std;

  // Remove the odd integers from v.
  // It is acceptable if the order of the remaining even integers is not
  // the same as in the original vector.
void removeOdd(vector<int>& v)
{
    vector <int>:: iterator it;
    it = v.begin();
    while (it!=v.end())
    {
        if (*it%2 ==1)
            it = v.erase(it);
        else
            it++;
        
    }
    
}

void test()
{
    int a[8] = { 2, 8, 5, 6, 7, 3, 4, 1 };
    vector<int> x(a, a+8);  // construct x from the array
    assert(x.size() == 8 && x.front() == 2 && x.back() == 1);
    removeOdd(x);
    assert(x.size() == 4);
    sort(x.begin(), x.end());
    int expect[4] = { 2, 4, 6, 8 };
    for (int k = 0; k < 4; k++)
        assert(x[k] == expect[k]);
    
    int b[9] = {1,2,3,4,5,6,7,8,9};
    vector <int> y(b,b+9);
    removeOdd(y);
    for (int i = 0; i <4;i++)
    {
        cerr << b[i] << " ";
    }
    cout<< endl;
}

int main()
{
    test();
    cout << "Passed" << endl;
}
