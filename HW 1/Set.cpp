//
//  Set.cpp
//  CS32HW2
//
//  Created by Noela Wheeler on 4/11/21.
//



#include "Set.h"

Set::Set()
{
    isEmpty=0;
}

bool Set::empty() const // Return true if the set is empty, otherwise false.
{
    if (isEmpty==0){
        return true;
    }
    return false;
}

int Set::size() const    // Return the number of items in the set.
{
    return isEmpty;
}


bool Set::insert(const ItemType& value)
{
    int k=0;
    int j=size();
    int f=0;
    for (int i=0;i<=j-1;i++){
        if (s_array[i]==value)
        {k++;
            if(k==1)
            {
                f=i;
            }
        }
    }
        if((k==0) && (j<DEFAULT_MAX_ITEMS))
        {
            for(int p=j;p<=DEFAULT_MAX_ITEMS-1;p++){
            s_array[p]=value;
        }
            isEmpty++;
            return true;
        }
    return false;
}


bool Set::erase(const ItemType& value)
{
    int p=size(); //size of set
    int i;
    for (i=0;i<=(p-1);i++){
        if (s_array[i]==value && s_array[i]!=s_array[i+1])
        {
            for (int g=i;g<=DEFAULT_MAX_ITEMS-2;g++)
            {
                s_array[g]=s_array[g+1];
                
            }
            isEmpty--;
            return true;
        }
        if (s_array[i]==value && s_array[i]==s_array[i+1])
        {
            for (int g=i;g<=DEFAULT_MAX_ITEMS-1;g++)
            {
                s_array[g]=s_array[g-1];
            }
            isEmpty--;
            return true;
        }
    }
    return false;
}



bool Set::contains(const ItemType& value) const
{
    //
    for (int i=0;i<=size()-1;i++){
        if (s_array[i]==value)
        {return true;}
    }
    return false;
}
  
bool Set::get(int i, ItemType& value) const
{
    int j=size();
    if(i<0 || i>=size())
    {return false;}
    for (int n=0;n<=j-1;n++)
    {
        ItemType k=s_array[n];
        int t=0;
        for(int y=0;y<=j-1;y++)
        {
            if (k<s_array[y])
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


void Set::swap(Set& other)
{
    Set temp;
    for (int i=0;i<=DEFAULT_MAX_ITEMS-1;i++){
        temp.s_array[i]=s_array[i];
    }
    temp.isEmpty=isEmpty;
    for (int i=0;i<=DEFAULT_MAX_ITEMS-1;i++){
        s_array[i]=other.s_array[i];
    }
    isEmpty=other.isEmpty;
    for (int i=0;i<=DEFAULT_MAX_ITEMS-1;i++){
        other.s_array[i]=temp.s_array[i];
    }
    other.isEmpty=temp.isEmpty;
}


