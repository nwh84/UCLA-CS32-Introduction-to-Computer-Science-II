//
//  mazestack.cpp
//  CS32Homework2
//
//  Created by Noela Wheeler on 4/24/21.
//


#include <iostream>
#include <stack>
using namespace std;

bool pathExists(char maze[][10], int sr, int sc, int er, int ec);
         // Return true if there is a path from (sr,sc) to (er,ec)
         // through the maze; return false otherwise

class Coord
{
  public:
    Coord(int r, int c) : m_row(r), m_col(c) {}
    int r() const { return m_row; }
    int c() const { return m_col; }
  private:
    int m_row;
    int m_col;
};

// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise
bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
{
    stack<Coord> coordStack;
    //push starting coordinates onto stack and update maze
    coordStack.push(Coord(sr,sc));
    maze[sr][sc]=',';
    Coord end(er,ec);
    while (!coordStack.empty())
    {
        Coord current = coordStack.top();
        coordStack.pop();
        //return true if current location equals ending coordinates
        if (current.r()==end.r() && current.c()==end.c())
        {return true;}
        //test if you can move south
        if (maze[current.r()+1][current.c()]=='.'){
            coordStack.push(Coord(current.r()+1,current.c()));
            maze[current.r()+1][current.c()]=',';
        }
        //test if you can move west
        if(maze[current.r()][current.c()-1]=='.')
        {
            coordStack.push(Coord(current.r(),current.c()-1));
            maze[current.r()][current.c()-1]=',';
        }
        //test if you can move north
        if(maze[current.r()-1][current.c()]=='.')
        {
            coordStack.push(Coord(current.r()-1,current.c()));
            maze[current.r()-1][current.c()]=',';
        }
        //test if you can move east
        if(maze[current.r()][current.c()+1]=='.'){
            coordStack.push(Coord(current.r(),current.c()+1));
            maze[current.r()][current.c()+1]=',';
        }
    }
    return false;
}
          

int main()
    {
        
            char maze[10][10] = {
                { 'X','X','X','X','X','X','X','X','X','X' },
                { 'X','.','.','.','.','X','.','.','X','X' },
                { 'X','.','X','X','.','X','X','.','.','X' },
                { 'X','X','X','.','.','.','.','X','.','X' },
                { 'X','.','X','X','X','.','X','X','X','X' },
                { 'X','.','X','.','.','.','X','X','.','X' },
                { 'X','.','.','.','X','.','X','.','.','X' },
                { 'X','X','X','X','X','.','X','.','X','X' },
                { 'X','.','.','.','.','.','X','.','.','X' },
                { 'X','X','X','X','X','X','X','X','X','X' }
            };
            if (pathExists(maze, 3,5, 8,8))
                cout << "Solvable!" << endl;
            else
                cout << "Out of luck!" << endl;
        

    return 0;
}


