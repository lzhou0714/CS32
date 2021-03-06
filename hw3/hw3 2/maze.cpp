//
//  maze.cpp
//  hw3
//
//  Created by Lily Zhou on 2/7/22.
//

//#include <stack>
//#include <string>
//#include <iostream>
//
//using namespace std;

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{

    if (sr  == er && sc == ec)
    {
        return true;
    }
    maze[sr][sc] = '@';
    if (maze[sr][sc-1] == '.')
        if (pathExists(maze, nRows, nCols, sr, sc-1, er, ec))
            return true;
    if (maze[sr+1][sc] == '.')
        if (pathExists(maze, nRows, nCols, sr+1, sc, er, ec))
            return true;
    if (maze[sr][sc+1] == '.')
        if (pathExists(maze, nRows, nCols, sr, sc+1, er, ec))
            return true;
    if (maze[sr-1][sc] == '.')
        if (pathExists(maze, nRows, nCols, sr-1, sc, er, ec))
            return true;
    
    return false;
}
//int main()
//{
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
//    if (pathExists(maze, 10,10, 4,6, 1,1))
//        cout << "Solvable!" << endl;
//    else
//        cout << "Out of luck!" << endl;
//}
