//
//  testAccountSet.cpp
//  CS32HW2
//
//  Created by Noela Wheeler on 4/13/21.
//


#include "AccountSet.h"

#include <iostream>
#include <cassert>
using namespace std;


int main()
{
    AccountSet s;
    s.add(9876543);
    s.add(123456789);
    s.add(123456789);
    s.add(723856289);
    assert(s.size()==3);
    s.print();
    return 0;
}



