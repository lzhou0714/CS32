//
//  History.cpp
//  proj1
//
//  Created by Lily Zhou on 1/6/22.
//

#include "History.h"

#include <iostream>
using namespace std;

History::History(int nRows, int nCols)
{
    m_cols = nCols;
    m_rows = nRows;
    int i, j;
    for (i = 0;i<nRows;i++)
    {
        for (j = 0; j<nCols; j++)
            grid[i][j] = '.';
    }
};
bool History::record(int r, int c)
{
    

    if (r <1 || c <1 || r > rows() || c>cols())
    {
        return false;
    }
    if (grid[r-1][c-1] >= 'A' && grid[r-1][c-1]-'A'<=24)
    {
        grid[r-1][c-1]++;
    }
    if (grid[r-1][c-1] == '.')
    {
        grid[r-1][c-1] = 'A';
    }
    return true;
    
    
};
int History::rows() const
{
    return m_rows;
};
int History::cols() const
{
    return m_cols;
}
void History::display() const
{
    int r = rows();
    int c = cols();
    
    
    
    int i,j;
    //draw grid
    clearScreen();
    for (i = 0;i<r;i++)
    {
        for (j = 0; j<c; j++)
            cout << grid[i][j];
        cout << endl;
    }
    cout << endl;
    
    
};
