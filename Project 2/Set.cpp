//
//  Set.cpp
//  CS32Proj2
//
//

#include "Set.h"


Set::Set()
{
    //set size equal to zero
    m_size=0;
    //create dummy node with circular liked list and point head to dummy
    dummy=new node;
    head=dummy;
    head->next=head;
    head->previous=head;
}

bool Set::empty() const
{
    //if m_size equals 0 return true, otherwise false
    if (m_size==0)
    {return true;}
    return false;
}

int Set::size() const
{
    return m_size;
}

bool Set::insert(const ItemType& value)
{
    //if set is not empty, check that value is not already in set
    if (m_size>0)
    {
        for (node* p=head->next; p!=head;p=p->next)
        {
        if (p->data==value)
            //return false if value already exists in set
        {return false;}
        }
    }
    //create new node with data equal to value
    node* p=new node;
    p->data=value;
    //adjust pointers so that a the new node is inserted at end of set
    p->next=head;
    p->previous=head->previous;
    head->previous->next=p;
    head->previous=p;
    //increment size by one
    m_size++;
    return true;
}


bool Set::erase(const ItemType& value)
{
    //if the set is empty return false
    if (m_size==0)
    {return false;}
    //create temporary node and have it point to the node that will be
    //deleted
    node* temp;
    for (temp=head->next;temp!=head && temp->data!=value;temp=temp->next)
    {
        ;
    }
    //if temporary node equals head then object is not in set, so return
    //false
    if (temp==head)
    {return false;}
    //adjust pointers in list so they don't point to the object that will
    //be deleted
    node* temp2=temp->previous;
    temp2->next=temp->next;
    temp->next->previous=temp2;
    //delete the node and reduce the size of the set by 1
    delete temp;
    m_size--;
    return true;
}



bool Set::contains(const ItemType& value) const
{
    //loop through list (except dummy node)
    for (node* p = head->next; p != head; p = p->next)
    {
        //if node data equals value return true. Otherwise false
        if (p->data==value)
        {return true;}
    }
    return false;
}



bool Set::get(int i, ItemType& value) const
{
    //return false is i is less than 0 or i is greater than list size
    if (i < 0  ||  i >= m_size)
    {return false;}
    //create temporary node to loop through list
    node* temp;
    for (temp = head->next; temp != head; temp = temp->next)
    {
        int t=0;
        //for each temporary node value, loop through list again
        for(node* temp2 = head->next; temp2 != head; temp2 = temp2->next)
        {
            //if first temporary node equals second temporary node increment integer t
            if ((temp->data)<(temp2->data))
            {t++;}
        }
        //if integer t equals i then the first temporary node is less than exactly i items in the set. Therefore set value equal to first temporary node's data.
        if (t==i)
        {
            value=temp->data;
            return true;
        }
    }
    return false;
}

void Set::swap(Set& other)
{
    //swap head pointers
    node* temphead=head;
    head=other.head;
    other.head=temphead;
    //swap sizes
    int tempSize = m_size;
    m_size = other.m_size;
    other.m_size = tempSize;
}

Set::~Set()
{
    //if the set if not empty then loop through and delete each node except the dummy node
    if (m_size>0)
    {
    for (int i=1; i<=m_size;i++)
    {
        node* toBeDeleted=head->previous;
        head->previous=head->previous->previous;
        head->previous->next=head;
        delete toBeDeleted;
    }
    }
    //delete the dummy node and set the head pointer to null
    delete head;
    head=NULL;
}

Set::Set(const Set& other)
{
    //set size equal to other's size
    m_size=other.m_size;
    //create empty circular list with head pointing to dummy node
    dummy=new node;
    head=dummy;
    head->next=head;
    head->previous=head;
    //loop through other and insert each node's data value into the new set
    for (node* p = other.head->next; p != other.head; p = p->next)
    {insert(p->data);}
}

Set& Set::operator=(const Set& rhs)
{
    {
        //check that set is not equal to rhs set
        if (this != &rhs)
        {
            //create a temporary set equal to rhs set. Swap temporary set with current set.
            Set temp(rhs);
            swap(temp);
        }
        return *this;
    }
}

void unite(const Set& s1, const Set& s2, Set& result)
{
    //create empty set and swap it with result
    Set temp;
    temp.swap(result);
    //insert s2 into result
    for (int k = 0; k < s2.size(); k++)
    {
        ItemType x;
        s2.get(k, x);
        result.insert(x);
    }
    //insert s1 into result
    for (int k = 0; k < s1.size(); k++)
    {
        ItemType y;
        s1.get(k, y);
        result.insert(y);
    }
}

void difference(const Set& s1, const Set& s2, Set& result)
{
    //create empty set and swap it with result
    Set temp;
    temp.swap(result);
    //insert s2 into result. If insert fails then erase the value
    for (int k = 0; k < s2.size(); k++)
    {
        ItemType x;
        s2.get(k, x);
        if(!result.insert(x))
        {
            result.erase(x);
        }
    }
    //insert s1 into result. If insert fails then erase the value
    for (int k = 0; k < s1.size(); k++)
    {
        ItemType y;
        s1.get(k, y);
        if(!result.insert(y))
        {
            result.erase(y);
        }
    }
}
