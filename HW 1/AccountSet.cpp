//
//  AccountSet.cpp
//  CS32HW2
//
//  Created by Noela Wheeler on 4/13/21.
//


#include "AccountSet.h"
//can't use for or while except in print funtion. [ and * cannot appear. Don't have to change unsigned long to ItemType

AccountSet::AccountSet()
{
    Set mySet;
    NumAcct=0;
}

bool AccountSet::add(unsigned long acctNum)
{
    if(mySet.insert(acctNum)==true)
    {
        NumAcct++;
        return true;
    }
    return false;
}

int AccountSet::size() const
{
    return NumAcct;
}


void AccountSet::print() const
{
    unsigned long x;
    for (int i=0;i<=NumAcct-1;i++)
    {
        mySet.get(i,x);
        std::cout<<x<<std::endl;
    }

}



