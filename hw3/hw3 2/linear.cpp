//
//  linear.cpp
//  hw3
//
//  Created by Lily Zhou on 2/5/22.
//
//#include <iostream>
//#include <cassert>
//using namespace std;

//bool somePredicate(double x)
//{
//    return x > 0;
//}

// Return true if the somePredicate function returns false for at
// least one of the array elements, false otherwise.
bool anyFalse(const double a[], int n)
{
    if (n<=0)
    {
        return false;
    }
    if (!somePredicate(a[n-1]))
        return true;
    return anyFalse(a, n-1);
}

int countFalse(const double a[], int n)
{
    int count  = 0;
    if (n<=0)
        return 0;
    if (!somePredicate(a[n-1]))
        count = 1;
    return count + countFalse(a, n-1);
}

int firstTrue(const double a[], int n)
{
    if (somePredicate(a[0]))
        return 0;
    if (n<=0)
        return -1; //what appens if thess no such element sidgskchsdlcd
    int count = 1+firstTrue(a+1, n-1);
    if (count ==0)
    {
        return -1;
    }
    return count;
}

int locateMax(const double a[], int n)
{
    if (n<=0)
        return -1;
    if (n ==1)
        return 0;
    int index = 1+ locateMax(a+1, n-1); //position of previous max will be moved down one as we recurse back up -->ie from n=2 to n=3
    if (a[0] >= a[index])
    {
//        cerr << "returning 0" << endl;
        return 0;
    }
    else
    {
//        cerr << "returning index" << endl;
        return index;
    }
}

bool contains(const double a1[], int n1, const double a2[], int n2)
{
    if (n2 ==0)
        return true;
    if (n2>n1)
        return false;
    if (a1[0] == a2[0])
    {
//        cerr << "contains" << endl;

        return contains(a1+1, n1-1, a2+1, n2-1);
    }
    else
    {
//        cerr << "contains" << endl;
        return contains(a1+1, n1-1, a2, n2);  // This is not always correct.
    }
}


//
//int main()
//{
//    double a[5] = {1,1,5, 7,4};
//    double b[5] = {-1,-1,-3,-4,-5};
//    double c[0] ={};
//    double d[5] = {1,1,3,4,-5};
//    double e[5] = {-1,-1,3,4,5};
//
//    assert(!anyFalse(c, 0));
//    assert(anyFalse(b, 5));
//    assert(!anyFalse(a, 5));
//    assert(anyFalse(d, 5));
//    assert(!anyFalse(d, 1));
//    assert(countFalse(a, 5) == 0);
//    assert(countFalse(b,5) ==5);
//    assert(countFalse(c, 0) == 0);
//    assert(countFalse(d, 5)==1);
//    assert(countFalse(e, 5)==2);
//    cerr << firstTrue(e, 5) << endl;
//    cerr <<  "5" << endl;
//    assert(locateMax(b, 5) ==0);
//    cerr <<  "5" << endl;
//    assert(locateMax(a, 5) == 3 );
//    cerr <<  "0" << endl;
//    assert(locateMax(c, 0) == -1);
//    cerr << "-1" << endl;
//    assert(locateMax(c, -1) ==-1);
//    cerr << "4" << endl;
//    assert(locateMax(d, 4) == 3);
//    cerr << "5" << endl;
//    assert(locateMax(e, 5) ==4);
//
//    double a1[7] = {10,50,40,20,50,40,30};
//    double a2[3] = {50,40,30};
//    double a3[3] = {50,40,40};
//    double a4[3] = {50,30,20};
//    double a5[3] = {10,20,20};
//
//
//    cerr << "7" << endl;
//    assert(contains(a1, 7, a2, 3) == 1);
//    cerr << "7" << endl;
//    assert(contains(a1, 7, a3, 3) == 1);
//    cerr << "7" << endl;
//    assert(contains(a1, 7, a4, 3) ==0);
//    cerr << "7" << endl;
//    assert(contains(a1, 7, a5, 3)==0);
//    cerr << "3" << endl;
//    assert(contains(a2, 3, a1, 7) == 0);
//    assert( contains(a1, 7, a2, 0)==1);
//
//
//}
