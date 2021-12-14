//
//  main.cpp
//  CS32Proj2
//
//

#include "Set.h"
#include <iostream>
#include <cassert>
using namespace std;


int main()
{
    Set ss;
    ss.insert("hi");
    Set ss2;
    ss2.insert("hello");
    ss2.insert("now");
    ss.swap(ss2);
    assert(ss.size() == 2); //swap functions swaps list sizes
    assert(ss2.size()==1);  //swap function swaps list sizes
    assert(ss.contains("hello")); //swap function swaps items in list
    assert(ss.contains("now")); //swap function swaps items in list
    assert(!ss.contains("hi")); //swap function swaps items in list
    assert(ss2.contains("hi")); //swap function swaps items in list
    assert(!ss2.contains("now")); //swap function swaps items in list


    cout << "Passed all tests" << endl;
    return 0;
}
