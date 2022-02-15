//
//  main.cpp
//  Hw2
//
//  Created by Lily Zhou on 1/29/22.
//

#include <iostream>
#include <stack>
using namespace std;
class Coord
  {
    public:
      Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
      int r() const { return m_r; }
      int c() const { return m_c; }
    private:
      int m_r;
      int m_c;
  };
//(Our convention is that (0,0) is the northwest (upper left) corner, with south (down) being the increasing r direction and east (right) being the increasing c direction.)



bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
    stack<Coord> cStack; //make stack of coordinates
    
    cStack.push(Coord(sr,sc)); //push starting coordinate onto stack
    maze[sr][sc] = '@';
    while (!cStack.empty())
    {
        Coord a = cStack.top();
        cerr << "r = " << a.r() << " c = " << a.c() << endl << " stack empty: " << cStack.empty() << endl;

        cStack.pop();
        for (int i = 0;i<nRows;i++)
        {
            for (int j = 0; j<nCols;j++)
                cerr << maze[i][j];
            cerr << endl;
        }
        cerr <<endl;
        if (a.r() == er && a.c() == ec)
            return true;
        if (maze[a.r()][a.c()-1] == '.') //W
        {
            maze[a.r()][a.c()-1] = '@';
            cStack.push(Coord(a.r(), a.c()-1));
        }
        if (maze[a.r()+1][a.c()] == '.') //S
        {
            maze[a.r()+1][a.c()] = '@';
            cStack.push(Coord(a.r()+1, a.c()));
        }
        if (maze[a.r()][a.c()+1] == '.') //E
        {
            maze[a.r()][a.c()+1] = '@';
            cStack.push(Coord(a.r(), a.c()+1));
        }
        if (maze[a.r()-1][a.c()] == '.') //N
        {
            maze[a.r()-1][a.c()] = '@';
            cStack.push(Coord(a.r()-1, a.c()));
        }


    }
    return false;
};
          // Return true if there is a path from (sr,sc) to (er,ec)
          // through the maze; return false otherwise

//int main(int argc, const char * argv[]) {
//    string maze[10] = {
//        "XXXXXXXXXX",
//        "X.X..X...X",
//        "X....XXX.X",
//        "X.XXXX.X.X",
//        "X......XXX",
//        "X.XX.X...X",
//        "X.X..X.X.X",
//        "X.X.XXXX.X",
//        "X.X...X..X",
//        "XXXXXXXXXX"
//    };
//
//    if (pathExists(maze, 10,10, 4,6, 1,9))
//        cout << "Solvable!" << endl;
//    else
//        cout << "Out of luck!" << endl;
//}
