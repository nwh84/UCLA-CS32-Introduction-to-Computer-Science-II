//
//  Game.cpp
//  Project3
//
//

#include "provided.h"
#include <iostream>
using namespace std;

class GameImpl
{
  public:
    GameImpl(int nColumns, int nLevels, int N, Player* red, Player* black);
    bool completed(int& winner) const;
    bool takeTurn();
    void play();
    int checkerAt(int c, int r) const;
    ~GameImpl();
private:
    Scaffold* m_scaffold;
    int winNum;
    Player* Red;
    Player* Black;
    int turn;
    int columns;
    int levels;
};

GameImpl::GameImpl(int nColumns, int nLevels, int N, Player* red, Player* black)
{
    //check column and level inputs
    if (nColumns<=0)
    {
        cout << "***** Cannot create game with given column number!" << endl;
        exit(1);
    }
    
    if (nLevels<=0)
    {
        cout << "***** Cannot create game with given level number!" << endl;
        exit(1);
    }
    m_scaffold = new Scaffold(nColumns, nLevels);
    winNum = N;
    Red=red;
    Black=black;
    turn= RED;
    columns= nColumns;
    levels=nLevels;
}

GameImpl::~GameImpl()
{
    delete m_scaffold;
}

//If the game isn't over (i.e., more moves are possible), return false and do not change winner. Otherwise, set winner to RED, BLACK, or TIE_GAME, reflecting the outcome of the game, and return true.
bool GameImpl::completed(int& winner) const
{
    //check if the game is over yet
    //check for horizontal N in a row
    for (int r = levels; r >0; r--)
    {
        int i=0;
        for (int c = 1; c < columns; c++)
        {
            if (m_scaffold->checkerAt(c,r)==m_scaffold->checkerAt(c+1,r) && m_scaffold->checkerAt(c,r)!=VACANT)
            {i++;}
            if (m_scaffold->checkerAt(c,r)!=m_scaffold->checkerAt(c+1,r))
            {i=0;}
            if (i==(winNum-1) && m_scaffold->checkerAt(c,r)==BLACK)
            {winner= BLACK;
            return true;}
            if (i==(winNum-1) && m_scaffold->checkerAt(c,r)==RED)
            {winner=RED;
                return true;
            }
        }
    }
    //check for vertical N in a row
    for (int c = 1; c < columns; c++)
    {
        int i=0;
        for (int r = 1; r < levels; r++)
        {
            if (m_scaffold->checkerAt(c,r)==m_scaffold->checkerAt(c,r+1) && m_scaffold->checkerAt(c,r)!=VACANT)
            {i++;}
            if (m_scaffold->checkerAt(c,r)!=m_scaffold->checkerAt(c,r+1))
            {i=0;}
            if (i==(winNum-1) && m_scaffold->checkerAt(c,r)==BLACK)
            {winner= BLACK;
                return true;
            }
            if (i==(winNum-1) && m_scaffold->checkerAt(c,r)==RED)
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
            if (m_scaffold->checkerAt(j,i)==m_scaffold->checkerAt(j+1,i+1) && m_scaffold->checkerAt(j,i)!=VACANT)
            {num++;}
            if (m_scaffold->checkerAt(j,i)!=m_scaffold->checkerAt(j+1,i+1))
            {num=0;}
            if (num==(winNum-1) && m_scaffold->checkerAt(j,i)==BLACK)
            {winner= BLACK;
                return true;
            }
            if (num==(winNum-1) && m_scaffold->checkerAt(j,i)==RED)
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
            if (m_scaffold->checkerAt(j,i)==m_scaffold->checkerAt(j+1,i+1) && m_scaffold->checkerAt(j,i)!=VACANT)
            {num++;}
            if (m_scaffold->checkerAt(j,i)!=m_scaffold->checkerAt(j+1,i+1))
            {num=0;}
            if (num==(winNum-1) && m_scaffold->checkerAt(j,i)==BLACK)
            {winner= BLACK;
                return true;
            }
            if (num==(winNum-1) && m_scaffold->checkerAt(j,i)==RED)
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
            if (m_scaffold->checkerAt(j,i)==m_scaffold->checkerAt(j+1,i-1) && m_scaffold->checkerAt(j,i)!=VACANT)
            {num++;}
            if (m_scaffold->checkerAt(j,i)!=m_scaffold->checkerAt(j+1,i-1))
            {num=0;}
            if (num==(winNum-1) && m_scaffold->checkerAt(j,i)==BLACK)
            {
                winner= BLACK;
                return true;
            }
            if (num==(winNum-1) && m_scaffold->checkerAt(j,i)==RED)
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
            if (m_scaffold->checkerAt(j,i)==m_scaffold->checkerAt(j+1,i-1) && m_scaffold->checkerAt(j,i)!=VACANT)
            {num++;}
            if (m_scaffold->checkerAt(j,i)!=m_scaffold->checkerAt(j+1,i-1))
            {num=0;}
            if (num==(winNum-1) && m_scaffold->checkerAt(j,i)==BLACK)
            {winner= BLACK;
                return true;
            }
            if (num==(winNum-1) && m_scaffold->checkerAt(j,i)==RED)
            {winner= RED;
                return true;
            }
            i--;
            j++;
        } while (i>1 && j<columns);
    }
    //if the board is full return TIE_GAME
    if (m_scaffold->numberEmpty()==0)
        {
            winner= TIE_GAME;
            return true;
        }
    //if the game is not over return false
    return false;
}

//If the game is over, return false. Otherwise, make a move for the player whose turn it is (so that it becomes the other player's turn) and return true.
bool GameImpl::takeTurn()
{
    if (turn==RED)
    {
        int column=0;
        //if there are no available moves for the red player return false, otherwise make the move given by chooseMove
        column=Red->chooseMove(*m_scaffold,winNum,RED);
        if (column==0)
        {return false;}
        m_scaffold->makeMove(column,RED);
        turn=BLACK; //made it the next players turn
        return true;
    }
    
    if (turn==BLACK)
    {
        int column=0;
        //if there are no available moves for the black player return false, otherwise make the move given by chooseMove
        column=Black->chooseMove(*m_scaffold,winNum,BLACK);
        if (column==0)
        {return false;}
        m_scaffold->makeMove(column, BLACK);
        turn=RED; //made it the next players turn
    }
    return true;
}

//Play the game. Display the progress of the game in a manner of your choosing, provided that someone looking at the screen can follow what's happening. If neither player is interactive, then to keep the display from quickly scrolling through the whole game, it would be reasonable periodically to prompt the viewer to press ENTER to continue and not proceed until ENTER is pressed. Announce the winner at the end of the game.
void GameImpl::play()
{
    //display the starting board and prompt for the user to press enter to continue
    int winner=0;
    cout<<"Board:"<<endl;
    m_scaffold->display();
    cout<<"Press enter to continue."<<endl;
    cin.ignore(10000, '\n');
    while (completed(winner)==false) //continue will the game is not completed
    {
        if (turn==RED)
        {
            if (takeTurn()!=false) //if Red is able to make a move, make that move and display the updated board
            {
                cout<<"Red turn:"<<endl;
                m_scaffold->display();
                cout<<"Press enter to continue."<<endl;
                cin.ignore(10000, '\n');
            }
        }
        if (turn==BLACK && completed(winner)==false) //if Red is able to make a move and the game is not over, make that move and display the updated board
        {
            if (takeTurn()!=false)
            {
                cout<<"Black turn:"<<endl;
                m_scaffold->display();
                cout<<"Press enter to continue."<<endl;
                cin.ignore(10000, '\n');
            }
        }
    }
    //output the who won or if it was a tie
    if (winner==RED)
    {
        cout<<"Red was the winner."<<endl;
    }
    if (winner==BLACK)
    {
        cout<<"Black was the winner."<<endl;
    }
    if (winner==TIE_GAME)
    {
        cout<<"The game was a tie."<<endl;
    }
}

//In the Game's scaffold, if there is a red checker at the indicated column and level, return RED; if there's a black checker there, return BLACK; otherwise, return VACANT. This function exists so that we and you can more easily test your program; a real client would never use it.
int GameImpl::checkerAt(int c, int r) const
{
    return m_scaffold->checkerAt(r,c);
}

//******************** Game functions *******************************

//  These functions simply delegate to GameImpl's functions.
//  You probably don't want to change any of this code.

Game::Game(int nColumns, int nLevels, int N, Player* red, Player* black)
{
    m_impl = new GameImpl(nColumns, nLevels, N, red, black);
}
 
Game::~Game()
{
    delete m_impl;
}
 
bool Game::completed(int& winner) const
{
    return m_impl->completed(winner);
}

bool Game::takeTurn()
{
    return m_impl->takeTurn();
}

void Game::play()
{
    m_impl->play();
}
 
int Game::checkerAt(int c, int r) const
{
    return m_impl->checkerAt(c, r);
}
