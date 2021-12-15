//
//  newSet.cpp
//  CS32HW2
//
//  Created by Noela Wheeler on 4/13/21.
//


#include "newSet.h"

Set::Set()
{
    ptr = new ItemType[DEFAULT_MAX_ITEMS];
    //for (int i = 0; i <= DEFAULT_MAX_ITEMS-1; i++)
    //{ptr[i] = nullptr;}
    arraySize=0;
    arrayMax=DEFAULT_MAX_ITEMS;
}

Set::Set(int a)
{
    ptr = new ItemType[a];
    arraySize=0;
    arrayMax=a;
}

Set::~Set()
{
    delete [] ptr;
}

Set::Set(const Set& other)
{
    arraySize=other.arraySize;
    arrayMax=other.arrayMax;
    ptr = new ItemType[arrayMax];
    //switch the array values
    for (int i = 0; i <= other.arraySize-1; i++)
    {ptr[i] = other.ptr[i];}
}

Set& Set::operator=(const Set& rhs)
{
    if (this!=&rhs)
    {
        delete [] ptr;
        arraySize=rhs.arraySize;
        arrayMax=rhs.arrayMax;
        ptr = new ItemType[arrayMax];
        //switch the array values
        for (int i = 0; i <= rhs.arraySize-1; i++)
        {ptr[i] = rhs.ptr[i];}
    }
    return *this;
}

bool Set::empty() const // Return true if the set is empty, otherwise false.
{
    if (arraySize==0){
        return true;
    }
    return false;
}

int Set::size() const    // Return the number of items in the set.
{
    return (arraySize);
}

bool Set::insert(const ItemType& value)
{
    for (int i=0;i<=size()-1;i++)
    {
    if (ptr[i]==value)
        return false;
    }

      //check that the size is not already at max
    if (arraySize == arrayMax)
    {return false;}
    
    //insert the value
    int j=size();
    ptr[j]=value;
    arraySize++;
    return true;
}


bool Set::erase(const ItemType& value)
{
    int p=size(); //size of set
    int k=0; //increment if value is in set
    int j=0; //index of item to be erased
    for (int i=0;i<=p-1;i++)
    {
        if (ptr[i]==value){
            k++;
            j=i;}
    }
    if (k==0)
    {
        return false;
    }
    if(j==(p-1))
    {   arraySize--;
        return true;
    }
    for (int n=j;n<=p-2;n++)
    {
        ptr[n]=ptr[n+1];
    }
    //last element remains in array but arraySize is updated to be smaller
    arraySize--;
    return true;
}


bool Set::contains(const ItemType& value) const
{
    int s=size();
    int k=0; //increment if value is in set
    for (int i=0;i<=s-1;i++)
    {
    if (ptr[i]==value)
    {k++;}
    }
    if (k==0)
    {
        return false;
    }
    return true;
}
  
bool Set::get(int i, ItemType& value) const
{
    int j=size();
    if(i<0 || i>=size())
    {return false;}
    for (int n=0;n<=j-1;n++)
    {
        ItemType k=ptr[n];
        int t=0;
        for(int y=0;y<=j-1;y++)
        {
            if (k<ptr[y])
            {t++;}
        }
        if (t==i)
        {
            value=k;
            return true;
        }
    }
    return false;
}
  // If 0 <= i < size(), copy into value the item in the set that is
  // strictly less than exactly i items in the set and return true.
  // Otherwise, leave value unchanged and return false.

void Set::swap(Set& other)
{
    Set temp;
    temp=*this;
    *this=other;
    other=temp;
}



