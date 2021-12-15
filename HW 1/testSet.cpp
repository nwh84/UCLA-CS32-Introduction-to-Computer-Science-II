//
//  main.cpp
//  CS32HW2
//
//  Created by Noela Wheeler on 4/11/21.
//

#include "Set.h"
#include <iostream>
#include <string>
#include <cassert>
using namespace std;


int main()
{
    Set s;
    assert(s.empty());
    ItemType x = "hi";
    assert( !s.get(42, x)  &&  x == "hi"); // x unchanged by get failure
    s.insert("hello");
    s.insert("hi");
    assert(s.size() == 2);
    s.erase("hello");
    assert(s.size()==1);
    assert(s.get(0, x));
    assert(x == "hi");
    Set h;
    s.swap(h);
    assert(h.contains("hi"));
    assert(s.size()==0);
    cout << "Passed all tests" << endl;
    return 0;
}

 


