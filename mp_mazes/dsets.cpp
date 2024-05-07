/* Your code here! */
#include "dsets.h"
#include <iostream>

/**
 *Creates n unconnected root nodes at the end of the vector.
 *
 *@param num: The number of nodes to create
 */
void DisjointSets::addelements(int num)
{
    for(int i=0; i<num; i++)
    {
        sets.push_back(-1);
    }
}

/**
 *This function should compress paths and works as described in lecture.
 * 
 *@return the index of the root of the up-tree in which the parameter element resides.
 */
int DisjointSets::find(int elem)
{
    if (sets[elem]<0)
    {
        return elem;
    }
    else
    {
        sets[elem]=find(sets[elem]);
        return sets[elem];
    }
}

/**
 *This function should be implemented as union-by-size. 
 * 
 *That is, when you setunion two disjoint sets, the smaller (in terms of number of nodes) 
 *should point at the larger. This function works as described in lecture, except that you
 *should not assume that the arguments to setunion are roots of existing uptrees.
 *
 *Your setunion function SHOULD find the roots of its arguments before combining the trees.
 *If the two sets are the same size, make the tree containing the second argument point to
 *the tree containing the first. (Note that normally we could break this tie arbitrarily,
 *but in this case we want to control things for grading.)
 *
 *@param a Index of the first element to union
 *@param b Index of the second element to union 
 *
 */ 
void DisjointSets::setunion(int a, int b)
{
    int roota=find(a);
    int rootb=find(b);
    int newSize=sets[roota]+sets[rootb];
    if(sets[roota]>sets[rootb])
    {
        sets[roota]=rootb;
        sets[rootb]=newSize;
    }
    else
    {
        sets[rootb]=roota;
        sets[roota]=newSize;
    }
}

/**
*This function should return the number of nodes in the up-tree containing the element.
 * 
 *@return number of nodes in the up-tree containing the element.
 */
int DisjointSets::size(int elem)
{
    int root=find(elem);
    int count=0;
    for(size_t i = 0; i<sets.size();i++)
    {
        if(find(i)==root)
        {
            count++;
        }
    }
    return count;
}

void DisjointSets::clearSets()
{
    sets.clear();
}