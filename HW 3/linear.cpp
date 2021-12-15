//
//  main.cpp
//  HW3Q2
//
//  Created by Noela Wheeler on 5/3/21.
//


// Return false if the somePredicate function returns false for at
// least one of the array elements; return true otherwise.
//array of strings + number of strings to examine in the array, call somePredicate, can't use for, while or goto, can use a pointer to represent a[]
bool allTrue(const string a[], int n)
{
    if (n<=0)
        return true;
    if (!somePredicate(a[0]))
        return false;
    return allTrue(a+1, n-1);
}

// Return the number of elements in the array for which the
// somePredicate function returns false.
int countFalse(const string a[], int n)
{
    if(0 >= n)
    {return 0;}
    
    int numFalse = 0;
    
    if(!somePredicate(a[0]))
    {numFalse++;}
    
    return countFalse(a+1, n-1) + numFalse;
}

// Return the subscript of the first element in the array for which
// the somePredicate function returns false.  If there is no such
// element, return -1.
int firstFalse(const string a[], int n)
{
        if(0 >= n)
        {return -1;}
    
        if(!somePredicate(a[0]))
        {return 0;}
        
        int FalseSubscript = 1 + firstFalse(a+1, n-1);

        if(FalseSubscript == 0)
        {return -1;}
    
        return FalseSubscript;
}

// Return the subscript of the least string in the array (i.e.,
// return the smallest subscript m such that a[m] <= a[k] for all
// k from 0 to n-1).  If the function is told to examine no
// elements, return -1.
int indexOfLeast(const string a[], int n)
{
    if ( n <= 0 )
    {return -1;}
    
    int leastSubscript = indexOfLeast(a+1, n-1)+1;
    if (a[leastSubscript] >= a[0])
    {return 0;}
    return leastSubscript;
}

// If all n2 elements of a2 appear in the n1 element array a1, in
// the same order (though not necessarily consecutively), then
// return true; otherwise (i.e., if the array a1 does not include
// a2 as a not-necessarily-contiguous subsequence), return false.
// (Of course, if a2 is empty (i.e., n2 is 0), return true.)
// For example, if a1 is the 7 element array
//    "stan" "kyle" "cartman" "kenny" "kyle" "cartman" "butters"
// then the function should return true if a2 is
//    "kyle" "kenny" "butters"
// or
//    "kyle" "cartman" "cartman"
// and it should return false if a2 is
//    "kyle" "butters" "kenny"
// or
//    "stan" "kenny" "kenny"
bool includes(const string a1[], int n1, const string a2[], int n2)
{
    if (n2<=0)
        return true;
    if (n1<=0)
        return false;
    if (a1[0]==a2[0])
        return(includes(a1+1,n1-1,a2+1,n2-1));
    return(includes(a1+1,n1-1,a2,n2));
}

