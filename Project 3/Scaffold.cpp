//
//  Scaffold.cpp
//  Project3
//
//

#include "provided.h"
#include <utility>
#include <vector>
#include <iostream>
#include <stack>

using namespace std;

class ScaffoldImpl
{
  public:
    ScaffoldImpl(int nColumns, int nLevels);
    int cols() const;
    int levels() const;
    int numberEmpty() const;
    int checkerAt(int column, int level) const;
    void display() const;
    bool makeMove(int column, int color);
    int undoMove();
private:
    int m_columns;
    int m_levels;
    int vectColumns;
    int numCheckers;
    vector<vector<char>> m_grid;
    stack<int> coordstack;
};

//Construct a Scaffold with the indicated number of columns and levels. If either is not positive, you may terminate the program after writing a message to cerr.
ScaffoldImpl::ScaffoldImpl(int nColumns, int nLevels)
{
    if (nColumns<0)
        {cerr<<"column number must be positive."<<endl;
        exit(1);}
    if (nLevels<0)
        {cerr<<"column number must be positive."<<endl;
        exit(1);}
    m_columns=nColumns;
    m_levels=nLevels;
    numCheckers=0;
    vectColumns=(m_columns*2)+1;
    
     m_grid.resize(m_levels+1);  // grid now has M empty rows
     for (int i = 0; i <= m_levels; i++)
        {m_grid[i].resize(vectColumns);}  // row i now has N columns
    
    for (int i = 0; i < vectColumns; i=i+2)
        {m_grid[0][i] = '+';}
    for (int i = 1; i < vectColumns; i=i+2)
        {m_grid[0][i] = '-';}
    
    for (int i = 0; i < vectColumns; i=i+2)
        {
            for (int j = 1; j <= m_levels; j++)
            {
                m_grid[j][i] = '|';
            }
        }
    
    for (int i = 1; i < vectColumns; i=i+2)
        {
            for (int j = 1; j <= m_levels; j++)
            {
                m_grid[j][i] = ' ';
            }
        }
}

//Return the number of columns in the scaffold.
int ScaffoldImpl::cols() const
{
    return m_columns;
}

//Return the number of levels in the scaffold.
int ScaffoldImpl::levels() const
{
    return m_levels;
}

//Return the number of positions in the scaffold not occupied by a checker.
int ScaffoldImpl::numberEmpty() const
{
    int i=0;
    i=(m_levels*m_columns)-numCheckers;
    return i;
}

//If there is a red checker at the indicated column and level, return RED; if there's a black checker there, return BLACK; otherwise, return VACANT.
int ScaffoldImpl::checkerAt(int column, int level) const
{
    if (column>m_columns || column<=0 || level>m_levels || level<=0)
        return VACANT;
    int vectcolumn=1+(column-1)*2;
    
    if (m_grid[level][vectcolumn]=='R')
        return RED;
    if (m_grid[level][vectcolumn]=='B')
        return BLACK;
    else
        return VACANT;
}

//Display the scaffold to the screen in the following manner:
void ScaffoldImpl::display() const
{
    for (int r = m_levels; r >=0; r--)
    {
        for (int c = 0; c < vectColumns; c++)
            cout << m_grid[r][c];
        cout << endl;
    }
    cout << endl;
}

//If the first parameter is a valid column number with at least one vacant position in that column, and if color is RED or BLACK, drop a checker of the appropriate color into that column and return true. Otherwise, do nothing and return false
bool ScaffoldImpl::makeMove(int column, int color)
{
    //vector column number
    if (column>m_columns)
        return false;
    if (color!= RED && color!=BLACK)
        return false;
    int j=1+(column-1)*2;
    for (int r = 1; r <= m_levels; r++)
    {
        if (m_grid[r][j]==' ')
        {
            if (color==RED)
                m_grid[r][j]='R';
            if (color==BLACK)
                m_grid[r][j]='B';
            numCheckers++;
            coordstack.push(r);
            coordstack.push(j);
            return true;
        }
    }
    return false;
}

//Undo the most recently made move that has not already been undone (i.e., remove the checker in the scaffold that was most recently added), and return the number of the column from which that checker was removed. If there are no checkers in the scaffold, do nothing and return 0.
int ScaffoldImpl::undoMove()
{
    int column=0;
    if (numCheckers==0)
        return 0;
    //take coordinate off stack and store them  in variables
    column=coordstack.top();
    coordstack.pop();
    int level=coordstack.top();
    coordstack.pop();
    m_grid[level][column]=' ';
    numCheckers--;
    //find column number
    int i=0;
    i=((column-1)/2)+1;
    return i;
}

//******************** Scaffold functions *******************************

//  These functions simply delegate to ScaffoldImpl's functions.
//  You probably don't want to change any of this code.

Scaffold::Scaffold(int nColumns, int nLevels)
{
    m_impl = new ScaffoldImpl(nColumns, nLevels);
}
 
Scaffold::~Scaffold()
{
    delete m_impl;
}
 
Scaffold::Scaffold(const Scaffold& other)
{
    m_impl = new ScaffoldImpl(*other.m_impl);
}
 
Scaffold& Scaffold::operator=(const Scaffold& rhs)
{
    if (this != &rhs)
    {
        Scaffold temp(rhs);
        swap(m_impl, temp.m_impl);
    }
    return *this;
}
 
int Scaffold::cols() const
{
    return m_impl->cols();
}

int Scaffold::levels() const
{
    return m_impl->levels();
}

int Scaffold::numberEmpty() const
{
    return m_impl->numberEmpty();
}

int Scaffold::checkerAt(int column, int level) const
{
    return m_impl->checkerAt(column, level);
}
 
void Scaffold::display() const
{
    m_impl->display();
}
 
bool Scaffold::makeMove(int column, int color)
{
    return m_impl->makeMove(column, color);
}
 
int Scaffold::undoMove()
{
    return m_impl->undoMove();
}
