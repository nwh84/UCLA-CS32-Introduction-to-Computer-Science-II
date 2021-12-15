//
//  main.cpp
//  HW4Q4
//
//  Created by Noela Wheeler on 5/20/21.
//


void listAll(string path, const MenuItem* m) // two-parameter overload
{
    
    if (m->name() != "")
    {cout << path << m->name() << endl;}
    
    if (m->menuItems() == nullptr || m->menuItems()->size() == 0)
    {return;}

    if (m->name() != "")
    {path = path + m->name() + "/";}

    for (MenuItem* Ptr : *(m->menuItems()))
    {listAll(path, Ptr);}
}
