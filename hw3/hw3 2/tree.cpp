//
//  tree.cpp
//  hw3
//
//  Created by Lily Zhou on 2/7/22.
//
//
//#include <iostream>
//using namespace std;

int countContains(const double a1[], int n1, const double a2[], int n2)
{
    if (n2 <= 0)
        return 1;
    if (n2>n1)
        return 0;
    if (a1[0] == a2[0])
    {
        return countContains(a1+1, n1-1, a2+1, n2-1) + countContains(a1+1, n1-1, a2, n2);
    }
    else
        return countContains(a1+1, n1-1, a2, n2); 
}


void exchange(double& x, double& y)
{
  double t = x;
  x = y;
  y = t;
}

void separate(double a[], int n, double separator,
                  int& firstNotGreater, int& firstLess)
{
  if (n < 0)
  n = 0;

  firstNotGreater = 0;
  firstLess = n;
  int firstUnknown = 0;
  while (firstUnknown < firstLess)
  {
  if (a[firstUnknown] < separator)
  {
      firstLess--;
      exchange(a[firstUnknown], a[firstLess]);
  }
  else
  {
      if (a[firstUnknown] > separator)
      {
      exchange(a[firstNotGreater], a[firstUnknown]);
      firstNotGreater++;
      }
      firstUnknown++;
  }
  }
}

void order(double a[], int n)
{
    if (n<=1) return;
    int firstNotGreater, firstLess;
    separate(a,n, a[n/2], firstNotGreater, firstLess);
    order(a,firstNotGreater);
    order(a+firstLess,n-firstLess);
}
//
//
//int main()
//{
//    double a1[7] = {10,50,40,20,50,40,30};
//    double ab[7] = {50,50,40,40,30,30,30};
//    double ac[7] = {50,50,50,50,50,50,50};
//    double a2[3] = {10,20,40};
//    double a3[3] = {10,40,30};
//    double a4[3] = {20,10,40};
//    double a5[3] = {50,40,30};
//    cerr << countContains(a1, 0, a1, 0) <<endl;
//    cerr << countContains(a1, -7, a1, 1) <<endl;
//    cerr << countContains(a1, 7, a3, 3) <<endl;
//    cerr << countContains(a1, 7, a4, 3) <<endl;
//    cerr << countContains(a1, 7, a5, 3) <<endl;
//    cerr << countContains(ac, 7, a5, 0) <<endl;
//
//    double a[12]  = {-1,9,10,-382,3,19,0,7,-9,-33333,282023,23};
//    double b[20] = {-1,8,19,289,-94820,1819,48,2790,-29849,2684,194004,-27,0,3839,3839.278,84920,217128949,8292.2892,-17320320.238293,283};
//    double c[1] = {1};
//    order(a, 12);
//
//    int i;
//    for ( i=0;i<12;i++)
//    {
//        cerr << a[i] << " ";
//    }
//    cerr <<  endl;
//    order(a1, 7);
//    for (i = 0; i<7;i++)
//    {
//        cerr << a1[i] <<" ";
//    }
//    cerr <<  endl;
//    order(b,20);
//    for (i = 0; i< 20;i++)
//    {
//        cerr << b[i] << " ";
//    }
//    cerr <<  endl;
//    order(c, 1);
//    cerr << c[0] << endl;
//}
//
