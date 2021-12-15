//
//  main.cpp
//  HW4Q2b
//
//  Created by Noela Wheeler on 5/20/21.
//


void removeBad(list<Movie*>& li)
{
    list<Movie*>::iterator start = li.begin();
    for (;start != li.end(); start++)
        if ((*start)->rating()<55)
        {
            delete *start;
            start = li.erase(start);
            start--;
        }
}
