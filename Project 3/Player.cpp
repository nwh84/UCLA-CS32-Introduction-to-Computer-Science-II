//
//  Player.cpp
//  Project3
//
//


#include "provided.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;


class HumanPlayerImpl
{
  public:
    int chooseMove(const Scaffold& s, int N, int color);
};

class BadPlayerImpl
{
  public:
    int chooseMove(const Scaffold& s, int N, int color);
};


class SmartPlayerImpl
{
  public:
    int chooseMove(const Scaffold& s, int N, int color);
  private:
    bool completed( Scaffold& s, int& winner, int N) const;
    int minimax(Scaffold& temp,int& WorstScore,int& BestScore, AlarmClock& ac, int N, int MaximizingPlayer, int& color);
    int bestScore;
    vector<int> coord;
    vector<double> TimeValue;
};


//A HumanPlayer chooses its move by prompting a person running the program for a move (reprompting if necessary until the person enters a valid move), and returning that choice. You may assume that the user will enter an integer when prompted for a column number, although it might not be within the range of valid column numbers.
int HumanPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
    //check if there is any space on board
    if (s.numberEmpty()==0)
        return 0;
    //check if someone has won already
    //find level and column numbers
    int m_levels=s.levels();
    int m_columns=s.cols();
    //check for horizontal N in a row
    for (int r = m_levels; r>0; r--)
    {
        int i=0;
        for (int c = 1; c < m_columns; c++)
        {
            if (s.checkerAt(c,r)==s.checkerAt(c+1,r) && s.checkerAt(c,r)!=VACANT)
            {i++;}
            if (s.checkerAt(c,r)!=s.checkerAt(c+1,r))
            {i=0;}
            if (i==N-1)
            {return 0;}
        }
    }
    //check for vertical N in a row
    for (int c = 1; c <= m_columns; c++)
    {
        int i=0;
        for (int r = 1; r < m_levels; r++)
        {
            if (s.checkerAt(c,r)==s.checkerAt(c,r+1) && s.checkerAt(c,r)!=VACANT)
            {i++;}
            if (s.checkerAt(c,r)!=s.checkerAt(c,r+1))
            {i=0;}
            if (i==N-1)
            {return 0;}
        }
    }
    //check for upward diagonal N in a row going from column 1
    for (int r = 1; r < m_levels; r++)
    {
        int i=r;
        int j=1;
        int num=0;
        do
        {
            if (s.checkerAt(j,i)==s.checkerAt(j+1,i+1) && s.checkerAt(j,i)!=VACANT)
            {num++;}
            if (s.checkerAt(j,i)!=s.checkerAt(j+1,i+1))
            {num=0;}
            if (num==N-1)
            {return 0;}
            i++;
            j++;
        } while (i<m_levels && j<m_columns);
    }
    //check for upward diagonal N in a row going from level 1
    for (int r = 1; r < m_columns; r++)
    {
        int i=1;
        int j=r;
        int num=0;
        do
        {
            if (s.checkerAt(j,i)==s.checkerAt(j+1,i+1) && s.checkerAt(j,i)!=VACANT)
            {num++;}
            if (s.checkerAt(j,i)!=s.checkerAt(j+1,i+1))
            {num=0;}
            if (num==N-1)
            {return 0;}
            i++;
            j++;
        } while (i<m_levels && j<m_columns);
    }
    //check for downward diagonal N in a row going from column 1// checking this one
    for (int r = m_levels; r >= 1; r--)
    {
        int i=r;
        int j=1;
        int num=0;
        do
        {
            if (s.checkerAt(j,i)==s.checkerAt(j+1,i-1) && s.checkerAt(j,i)!=VACANT)
            {num++;}
            if (s.checkerAt(j,i)!=s.checkerAt(j+1,i-1))
            {num=0;}
            if (num==N-1)
            {return 0;}
            i--;
            j++;
        } while (i>1 && j<m_columns);
    }
    //check for downward diagonal N in a row going from level 1
    for (int r = 1; r < m_columns; r++)
    {
        int i=m_levels;
        int j=r;
        int num=0;
        do
        {
            if (s.checkerAt(j,i)==s.checkerAt(j+1,i-1) && s.checkerAt(j,i)!=VACANT)
            {num++;}
            if (s.checkerAt(j,i)!=s.checkerAt(j+1,i-1))
            {num=0;}
            if (num==N-1)
            {return 0;}
            i--;
            j++;
        } while (i>1 && j<m_columns);
    }
    
    //choose move
    //prompt user for column number and repeat until the user inputs a valid column. Return that input
    int columnNum=0;
    while (columnNum==0)
    {
    cout<< "enter a column number" <<endl;
    int i=0;
    cin>>i;
    cin.ignore(1000, '\n');
    if (i<= s.cols() && i>0)
    {
        for(int j=s.levels();j>=1;j--)
        {
            if (s.checkerAt(i,j)==VACANT)
            {columnNum=i;
                break;}
        }
    }
    }
    return columnNum;
}

//A BadPlayer is a computer player that chooses an arbitrary valid column and returns that choice. "Arbitrary" can be what you like (e.g., always the leftmost non-full column, or always the column with the fewest checkers, or a randomly selected non-full column, or whatever) provided the move is legal. The point of this class is to have an easy-to-implement class that at least plays legally.
int BadPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
    //check if there is any space on board
    if (s.numberEmpty()==0)
        return 0;
    //check if someone has won already
    //find level and column values
    int m_levels=s.levels();
    int m_columns=s.cols();
    //check for horizontal N in a row
    for (int r = m_levels; r>0; r--)
    {
        int i=0;
        for (int c = 1; c < m_columns; c++)
        {
            if (s.checkerAt(c,r)==s.checkerAt(c+1,r) && s.checkerAt(c,r)!=VACANT)
            {i++;}
            if (s.checkerAt(c,r)!=s.checkerAt(c+1,r))
            {i=0;}
            if (i==N-1)
            {return 0;}
        }
    }
    //check for vertical N in a row
    for (int c = 1; c <= m_columns; c++)
    {
        int i=0;
        for (int r = 1; r < m_levels; r++)
        {
            if (s.checkerAt(c,r)==s.checkerAt(c,r+1) && s.checkerAt(c,r)!=VACANT)
            {i++;}
            if (s.checkerAt(c,r)!=s.checkerAt(c,r+1))
            {i=0;}
            if (i==N-1)
            {return 0;}
        }
    }
    //check for upward diagonal N in a row going from column 1
    for (int r = 1; r < m_levels; r++)
    {
        int i=r;
        int j=1;
        int num=0;
        do
        {
            if (s.checkerAt(j,i)==s.checkerAt(j+1,i+1) && s.checkerAt(j,i)!=VACANT)
            {num++;}
            if (s.checkerAt(j,i)!=s.checkerAt(j+1,i+1))
            {num=0;}
            if (num==N-1)
            {return 0;}
            i++;
            j++;
        } while (i<m_levels && j<m_columns);
    }
    //check for upward diagonal N in a row going from level 1
    for (int r = 1; r < m_columns; r++)
    {
        int i=1;
        int j=r;
        int num=0;
        do
        {
            if (s.checkerAt(j,i)==s.checkerAt(j+1,i+1) && s.checkerAt(j,i)!=VACANT)
            {num++;}
            if (s.checkerAt(j,i)!=s.checkerAt(j+1,i+1))
            {num=0;}
            if (num==N-1)
            {return 0;}
            i++;
            j++;
        } while (i<m_levels && j<m_columns);
    }
    //check for downward diagonal N in a row going from column 1// checking this one
    for (int r = m_levels; r >= 1; r--)
    {
        int i=r;
        int j=1;
        int num=0;
        do
        {
            if (s.checkerAt(j,i)==s.checkerAt(j+1,i-1) && s.checkerAt(j,i)!=VACANT)
            {num++;}
            if (s.checkerAt(j,i)!=s.checkerAt(j+1,i-1))
            {num=0;}
            if (num==N-1)
            {return 0;}
            i--;
            j++;
        } while (i>1 && j<m_columns);
    }
    //check for downward diagonal N in a row going from level 1
    for (int r = 1; r < m_columns; r++)
    {
        int i=m_levels;
        int j=r;
        int num=0;
        do
        {
            if (s.checkerAt(j,i)==s.checkerAt(j+1,i-1) && s.checkerAt(j,i)!=VACANT)
            {num++;}
            if (s.checkerAt(j,i)!=s.checkerAt(j+1,i-1))
            {num=0;}
            if (num==N-1)
            {return 0;}
            i--;
            j++;
        } while (i>1 && j<m_columns);
    }
    
    //find farthest left available column. Return that column number
    for(int i=1;i<=m_columns;i++)
    {
        for(int j=m_levels;j>0;j--)
        {
            if (s.checkerAt(i,j)==VACANT)
                return (i);
        }
    }
    return 0; 
}

int SmartPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
    //alarm clock will time out after 9.8 seconds
    AlarmClock ac(9800);
    //make temporary copy of scaffold
    Scaffold temp=s;
    int WorstScore=0;
    int BestScore=0;
    int FirstPlayer=color;
    return minimax(temp,WorstScore,BestScore,ac,N, FirstPlayer, FirstPlayer);
}

int SmartPlayerImpl::minimax(Scaffold& temp, int& WorstScore,int& BestScore, AlarmClock& ac, int N, int MaximizingPlayer, int& color)
{
    int columns= temp.cols();
    int levels= temp.levels();
    //in case the timer runs out, return leftmmost vacant column
    
    if (ac.timedOut())
    {
        for (int j=levels;j>0;j--)
        {
            for (int i=1;i<=columns;i++)
            {
                if (temp.checkerAt(i,j)==VACANT)
                {
                    return i;
                }
            }
        }
    }
     
    //if the board is completely empty return a column near the middle
    if(temp.numberEmpty()==(columns*levels))
        {return columns/2;}
    //if it is the maximizing player's turn
    if (MaximizingPlayer == color)
    {
        for (int c = 1; c <= columns; c++) //iterate through each column
            {
                if(temp.checkerAt(c,levels)==VACANT)
                {
                    temp.makeMove(c,color); //make every available move
                    int winner=2;
                    completed(temp,winner,N);
                    if (winner==color) //if the maximizing player won push that column number and board score
                    {
                        coord.push_back(c);
                        int score =+(9999-((columns*levels)-temp.numberEmpty()));
                        TimeValue.push_back(score);
                    }
                    if(winner==TIE_GAME) //if the maximizing player tied push that column number and board score (0)
                    {
                        coord.push_back(c);
                        TimeValue.push_back(0);
                    }
                    else //if maximizing player did not win or tie make it next player's turn and call minimax again push the column number returned from minimax and the worstScore that the user could get
                    {
                        if(color==BLACK)
                        {color=RED;}
                        else
                        {color=BLACK;}
                        int j=minimax(temp,WorstScore,BestScore,ac,N,MaximizingPlayer,color);
                        coord.push_back(j);
                        TimeValue.push_back(WorstScore);
                    }
                    temp.undoMove(); //undo each test move
                }
            }
        BestScore=-100000;
        int maxIndex=0;
        for (int i=(TimeValue.size()-1);i>=0;i--)   //find the highest score for the maximizing player and return the corresponding column index
            {
            if (TimeValue[i]>BestScore)
                {
                    BestScore=TimeValue[i];
                    maxIndex=i;
                    TimeValue.pop_back();
                    coord.pop_back();
                }
            }
        return (coord[maxIndex]);
    }
    else //if it is the non maximizing player's turn
    {
        for (int c = 1; c <= columns; c++)
            {
                if(temp.checkerAt(c,levels)==VACANT)
                {
                    temp.makeMove(c,color); //make each available move
                    int winner=2;
                    completed(temp,winner,N);
                    if (winner==color) //if the non maximizing player won from this move push the score onto the vector and push the column index onto another vector
                    {
                        coord.push_back(c);
                        int score= -(9999-((columns*levels)-temp.numberEmpty()));
                        TimeValue.push_back(score);
                    }
                    if(winner==TIE_GAME) //if the non maximizing plyer tied from this move push the score of zero onto the vector and push the column index onto another vector
                    {
                        coord.push_back(c);
                        TimeValue.push_back(0);
                    }
                    else //if the player did not win or tie, make it the other player's turn and call the function again
                    {
                        if(color==BLACK)
                        {color=RED;}
                        else
                        {color=BLACK;}
                        int j=minimax(temp,WorstScore,BestScore,ac,N,MaximizingPlayer,color);
                        coord.push_back(j);
                        TimeValue.push_back(BestScore);
                    }
                    temp.undoMove(); //undo each test move the player makes
                    }
                ;
                }
    }
    WorstScore=100000;
    int maxIndex=0;
    for (int i=(TimeValue.size()-1);i>=0;i--)//find the lowest score for the non maximizing player and return the corresponding column index
        {
        if (TimeValue[i]<WorstScore)
            {
                WorstScore=TimeValue[i];
                maxIndex=i;
                TimeValue.pop_back();
                coord.pop_back();
            }
        }
    return (coord[maxIndex]);
}




// function that rates a given Connect N scaffold
bool SmartPlayerImpl::completed(Scaffold& m_scaffold, int& winner, int N) const
{
     //find number of columns and levels
    int columns= m_scaffold.cols();
    int levels= m_scaffold.levels();
    int winNum=N;
    //check is anyone has won the game yet
    //check for horizontal N in a row
    for (int r = levels; r >0; r--)
    {
        int i=0;
        for (int c = 1; c < columns; c++)
        {
            if (m_scaffold.checkerAt(c,r)==m_scaffold.checkerAt(c+1,r) && m_scaffold.checkerAt(c,r)!=VACANT)
            {i++;}
            if (m_scaffold.checkerAt(c,r)!=m_scaffold.checkerAt(c+1,r))
            {i=0;}
            if (i==(winNum-1) && m_scaffold.checkerAt(c,r)==BLACK)
            {winner= BLACK;
            return true;}
            if (i==(winNum-1) && m_scaffold.checkerAt(c,r)==RED)
            {winner=RED;
                return true;
            }
        }
    }
    //check for vertical N in a row
    for (int c = 1; c <= columns; c++)
    {
        int i=0;
        for (int r = 1; r < levels; r++)
        {
            if (m_scaffold.checkerAt(c,r)==m_scaffold.checkerAt(c,r+1) && m_scaffold.checkerAt(c,r)!=VACANT)
            {i++;}
            if (m_scaffold.checkerAt(c,r)!=m_scaffold.checkerAt(c,r+1))
            {i=0;}
            if (i==(winNum-1) && m_scaffold.checkerAt(c,r)==BLACK)
            {winner= BLACK;
                return true;
            }
            if (i==(winNum-1) && m_scaffold.checkerAt(c,r)==RED)
            {winner= RED;
                return true;
            }
        }
    }
    
    //check for upward diagonal N in a row going from column 1
    for (int r = 1; r < levels; r++)
    {
        int i=r;
        int j=1;
        int num=0;
        do
        {
            if (m_scaffold.checkerAt(j,i)==m_scaffold.checkerAt(j+1,i+1) && m_scaffold.checkerAt(j,i)!=VACANT)
            {num++;}
            if (m_scaffold.checkerAt(j,i)!=m_scaffold.checkerAt(j+1,i+1))
            {num=0;}
            if (num==(winNum-1) && m_scaffold.checkerAt(j,i)==BLACK)
            {winner= BLACK;
                return true;
            }
            if (num==(winNum-1) && m_scaffold.checkerAt(j,i)==RED)
            {winner= RED;
                return true;
            }
            i++;
            j++;
        } while (i<levels && j<columns);
    }
    //check for upward diagonal N in a row going from level 1
    for (int r = 1; r < columns; r++)
    {
        int i=1;
        int j=r;
        int num=0;
        do
        {
            if (m_scaffold.checkerAt(j,i)==m_scaffold.checkerAt(j+1,i+1) && m_scaffold.checkerAt(j,i)!=VACANT)
            {num++;}
            if (m_scaffold.checkerAt(j,i)!=m_scaffold.checkerAt(j+1,i+1))
            {num=0;}
            if (num==(winNum-1) && m_scaffold.checkerAt(j,i)==BLACK)
            {winner= BLACK;
                return true;
            }
            if (num==(winNum-1) && m_scaffold.checkerAt(j,i)==RED)
            {winner= RED;
                return true;
            }
            i++;
            j++;
        } while (i<levels && j<columns);
    }
    //check for downward diagonal N in a row going from column 1
    for (int r = levels; r >= 1; r--)
    {
        int i=r;
        int j=1;
        int num=0;
        do
        {
            if (m_scaffold.checkerAt(j,i)==m_scaffold.checkerAt(j+1,i-1) && m_scaffold.checkerAt(j,i)!=VACANT)
            {num++;}
            if (m_scaffold.checkerAt(j,i)!=m_scaffold.checkerAt(j+1,i-1))
            {num=0;}
            if (num==(winNum-1) && m_scaffold.checkerAt(j,i)==BLACK)
            {
                winner= BLACK;
                return true;
            }
            if (num==(winNum-1) && m_scaffold.checkerAt(j,i)==RED)
            {
                winner= RED;
                return true;
            }
            i--;
            j++;
        } while (i>1 && j<columns);
    }
    //check for downward diagonal N in a row going from level 1
    for (int r = 1; r < columns; r++)
    {
        int i=levels;
        int j=r;
        int num=0;
        do
        {
            if (m_scaffold.checkerAt(j,i)==m_scaffold.checkerAt(j+1,i-1) && m_scaffold.checkerAt(j,i)!=VACANT)
            {num++;}
            if (m_scaffold.checkerAt(j,i)!=m_scaffold.checkerAt(j+1,i-1))
            {num=0;}
            if (num==(winNum-1) && m_scaffold.checkerAt(j,i)==BLACK)
            {winner= BLACK;
                return true;
            }
            if (num==(winNum-1) && m_scaffold.checkerAt(j,i)==RED)
            {winner= RED;
                return true;
            }
            i--;
            j++;
        } while (i>1 && j<columns);
    }
    //if the board is full return TIE_GAME
    if (m_scaffold.numberEmpty()==0)
        {
            winner= TIE_GAME;
            return true;
        }
    //if the game is not over return false and don't update winner
    return false;
}

//******************** Player derived class functions *************************

//  These functions simply delegate to the Impl classes' functions.
//  You probably don't want to change any of this code.

HumanPlayer::HumanPlayer(string nm)
 : Player(nm)
{
    m_impl = new HumanPlayerImpl;
}
 
HumanPlayer::~HumanPlayer()
{
    delete m_impl;
}
 
int HumanPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}

BadPlayer::BadPlayer(string nm)
 : Player(nm)
{
    m_impl = new BadPlayerImpl;
}
 
BadPlayer::~BadPlayer()
{
    delete m_impl;
}
 
int BadPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}

SmartPlayer::SmartPlayer(string nm)
 : Player(nm)
{
    m_impl = new SmartPlayerImpl;
}
 
SmartPlayer::~SmartPlayer()
{
    delete m_impl;
}
 
int SmartPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}
