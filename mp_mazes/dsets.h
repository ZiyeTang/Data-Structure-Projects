/* Your code here! */
#pragma once
#include <iostream>
#include <vector>
using namespace std;

class DisjointSets 
{
    private:
        vector<int> sets;
    public:
        /**
         *Creates n unconnected root nodes at the end of the vector.
         *
         *@param num: The number of nodes to create
         */
        void addelements(int num);

        /**
         *This function should compress paths and works as described in lecture.
         * 
         *@return the index of the root of the up-tree in which the parameter element resides.
         */
        int find(int elem);

         
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
        void setunion(int a, int b);

        /**
         *This function should return the number of nodes in the up-tree containing the element.
         * 
         *@return number of nodes in the up-tree containing the element.
         */
        int size(int elem);

        void clearSets();
};