//
//  main.cpp
//  HW4Q2
//
//  Created by Noela Wheeler on 5/20/21.
//

void removeOdds(vector<int>& v)
{
    vector<int>::iterator start = v.begin();
    for (;start != v.end(); start++)
        if (*start%2 != 0)
        {
            start = v.erase(start);
            start--;
        }
}
