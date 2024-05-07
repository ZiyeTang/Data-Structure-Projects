/**
 * @file binarytree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include "TreeTraversals/InorderTraversal.h"
#include <iostream>

/**
 * @return The height of the binary tree. Recall that the height of a binary
 *  tree is just the length of the longest path from the root to a leaf, and
 *  that the height of an empty tree is -1.
 */
template <typename T>
int BinaryTree<T>::height() const
{
    // Call recursive helper function on root
    return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node* subRoot) const
{
    // Base case
    if (subRoot == NULL)
        return -1;

    // Recursive definition
    return 1 + std::max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that
 * node itself, and everything to the right of a node will be printed out after
 * that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
    // Call recursive helper function on the root
    printLeftToRight(root);

    // Finish the line
    std::cout << std::endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node* subRoot) const
{
    // Base case - null node
    if (subRoot == NULL)
        return;

    // Print left subtree
    printLeftToRight(subRoot->left);

    // Print this node
    std::cout << subRoot->elem << ' ';

    // Print right subtree
    printLeftToRight(subRoot->right);
}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
template <typename T>
void BinaryTree<T>::mirror()
{
    //your code here
    mirror(root);
}

template <typename T>
void BinaryTree<T>::mirror(Node* subRoot)
{
    if(subRoot==NULL)
        return;
    if(subRoot->left==NULL && subRoot->right==NULL)
        return;
    else
    {
        Node* temp=subRoot->left;
        subRoot->left=subRoot->right;
        subRoot->right=temp;
        mirror(subRoot->left);
        mirror(subRoot->right);
    }
}


/**
 * isOrdered() function iterative version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedIterative() const
{
    // your code here
    std::vector<T> nodes;
    InorderTraversal<T> t(root);
    for(typename TreeTraversal<T>::Iterator it = t.begin(); it!=t.end(); ++it)
    {
        nodes.push_back((*it)->elem);
    }
    for(size_t i=0; i<nodes.size()-1; ++i)
    {
        for(size_t j = i+1; j<nodes.size(); ++j)
        {
            if(nodes[i]>nodes[j])
                return false;
        }
    }
    return true;
}

/**
 * isOrdered() function recursive version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedRecursive() const
{
    // your code here    
    return isOrderedRecursive(root);
}

template <typename T>
bool BinaryTree<T>::isOrderedRecursive(Node* subRoot) const
{
    if(subRoot==NULL)
        return true;
    if(subRoot->left==NULL && subRoot->right==NULL)
        return true;
    if(subRoot->left==NULL)
    {
        if(subRoot->right->elem < subRoot->elem)
            return false;
        return isOrderedRecursive(subRoot->right) && findSmallest(subRoot->right) > subRoot->elem;
    }
    if(subRoot->right==NULL)
    {
        if(subRoot->left->elem > subRoot->elem)
            return false;
        return isOrderedRecursive(subRoot->left) && findLargest(subRoot->left) < subRoot->elem;
    }
    
    if(subRoot->right->elem < subRoot->elem || subRoot->left->elem > subRoot->elem)
        return false;
    bool f1 = isOrderedRecursive(subRoot->left) && isOrderedRecursive(subRoot->right);
    bool f2 = findSmallest(subRoot->right) > subRoot->elem && findLargest(subRoot->left) < subRoot->elem;
    return f1 && f2;
}



template <typename T>
T BinaryTree<T>::findSmallest(const Node* subRoot) const
{
    T currentMin = subRoot->elem;
    if(subRoot->left!=NULL)
    {
        currentMin  = std::min(currentMin,findSmallest(subRoot->left));
    }
    if(subRoot->right!=NULL)
    {
        currentMin = std::min(currentMin, findSmallest(subRoot->right));
    }
    return currentMin;
}


template <typename T>
T BinaryTree<T>::findLargest(const Node* subRoot) const
{
    T currentMax = subRoot->elem;
    if(subRoot->left!=NULL)
    {
        currentMax = std::max(currentMax,findLargest(subRoot->left));
    }
    if(subRoot->right!=NULL)
    {
        currentMax = std::max(currentMax, findLargest(subRoot->right));
    }
    return currentMax;
}
