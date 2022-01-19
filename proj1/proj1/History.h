//
//  History.hpp
//  proj1
//
//  Created by Lily Zhou on 1/6/22.
//

#ifndef History_hpp
#define History_hpp
#include "globals.h"

class History
{
    public:
        History(int nRows, int nCols);
        bool record(int r, int c);
        void display() const;
    private:
        int m_cols;
        int m_rows;
        char grid[MAXROWS][MAXCOLS];
        int rows() const;
        int cols() const;
    
    
        
    
    
};


#endif /* History_hpp */
