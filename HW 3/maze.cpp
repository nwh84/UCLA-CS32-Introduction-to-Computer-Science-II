//
//  main.cpp
//  HW3Q3
//
//  Created by Noela Wheeler on 5/3/21.
//


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
    if (sr==er && sc==ec)
    {return true;}
    maze[sr][sc]=',';
    
    //test if you can move south
    if (maze[sr+1][sc]=='.'){
        if(pathExists(maze, sr+1, sc, er, ec)==true)
        {return true;}
    }
    //test if you can move west
    if(maze[sr][sc-1]=='.')
    {
        if(pathExists(maze, sr, sc-1, er, ec))
            return true;
    }
    //test if you can move north
    if(maze[sr-1][sc]=='.')
    {
        if(pathExists(maze, sr-1, sc, er, ec))
            return true;
    }
    //test if you can move east
    if(maze[sr][sc+1]=='.'){
        if(pathExists(maze, sr, sc+1, er, ec))
            return true;
    }
    return false;
}
          
