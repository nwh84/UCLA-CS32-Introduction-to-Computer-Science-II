//
//  main.cpp
//  Project3
//
//

#include "provided.h"
#include <iostream>
#include <cassert>
using namespace std;

void doGameTests()
{
    BadPlayer bp1("Bart");
    BadPlayer bp2("Homer");
    Game g(2, 2, 2, &bp1, &bp2);
    int winner;
    assert(!g.completed(winner));
    g.takeTurn();  // Red's first move
    assert(!g.completed(winner)  &&
                (g.checkerAt(1, 1) == RED  ||  g.checkerAt(2, 1) == RED));
    g.takeTurn();  // Black's first move
    assert(!g.completed(winner));
    g.takeTurn();  // Red's second move; Red must win
    assert(g.completed(winner)  &&  winner == RED);
}

int main()
{
    doGameTests();
    cout << "Passed all tests" << endl;
}

