/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
using namespace std;

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    Node* rc = t->right;
    Node* rcLeftTemp = rc->left;

    t->height=1+max(heightOrNeg1(t->left),heightOrNeg1(rcLeftTemp));
    rc->height=1+max(t->height,heightOrNeg1(rc->right));

    t->right=rcLeftTemp;
    rc->left=t;
    
    t=rc;
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node* lc = t->left;
    Node* lcRightTemp = lc->right;

    t->height=1+max(heightOrNeg1(t->right),heightOrNeg1(lcRightTemp ));
    lc->height=1+max(t->height,heightOrNeg1(lc->left));

    t->left=lcRightTemp;
    lc->right=t;
    
    t=lc;
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    int balance = heightOrNeg1(subtree->right)-heightOrNeg1(subtree->left);
    if(balance==-2)
    {
        int l_balance=heightOrNeg1(subtree->left->right)-heightOrNeg1(subtree->left->left);
        if(l_balance==-1)
            rotateRight(subtree);
        else
            rotateLeftRight(subtree);
    }
    else if(balance==2)
    {
        int r_balance=heightOrNeg1(subtree->right->right)-heightOrNeg1(subtree->right->left);
        if(r_balance==1)
            rotateLeft(subtree);
        else
            rotateRightLeft(subtree);
    }
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if(subtree==NULL)
    {
        subtree=new Node(key,value);
    }
    else if(key<subtree->key)
    {
        insert(subtree->left, key, value);
        subtree->height=1+max(heightOrNeg1(subtree->left),heightOrNeg1(subtree->right));
    }
    else if(key>subtree->key)
    {
        insert(subtree->right, key, value);
        subtree->height=1+max(heightOrNeg1(subtree->left),heightOrNeg1(subtree->right));
    }
    rebalance(subtree);
}

template <class K, class V>
typename AVLTree<K, V>::Node*& AVLTree<K, V>::find_right(Node*& node)
{
    if(node->right==NULL)
        return node;
    return find_right(node->right);
}

template <class K, class V>
typename AVLTree<K, V>::Node*& AVLTree<K, V>::find_left(Node*& node)
{
    if(node->left==NULL)
        return node;
    return find_left(node->left);
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
    {
        return;
    }
    if (key < subtree->key) 
    {
        // your code here
        remove(subtree->left, key);
        subtree->height=1+max(heightOrNeg1(subtree->left),heightOrNeg1(subtree->right));
        rebalance(subtree);
    } 
    else if (key > subtree->key) 
    {
        // your code here
        remove(subtree->right, key);
        subtree->height=1+max(heightOrNeg1(subtree->left),heightOrNeg1(subtree->right));
        rebalance(subtree);
    }
    else 
    {
        if (subtree->left == NULL && subtree->right == NULL) 
        {
            /* no-child remove */
            // your code here
            delete subtree;
            subtree=NULL;
        } 
        else if (subtree->left != NULL && subtree->right != NULL) 
        {
            /* two-child remove */
            // your code here
            if(subtree->left->right!=NULL)
            {
                Node*& rightMost=find_right(subtree->left->right);
                swap(rightMost, subtree);
                if(rightMost->left==NULL)
                {
                    delete rightMost;
                    rightMost=NULL;
                }
                else
                {                    
                    Node* temp=rightMost;
                    rightMost=rightMost->left;
                    delete temp;
                }
                subtree->height=1+max(heightOrNeg1(subtree->left),heightOrNeg1(subtree->right));
            }
            else if(subtree->right->left!=NULL)
            {
                Node*& leftMost=find_left(subtree->right->left);
                swap(leftMost, subtree);
                if(leftMost->right==NULL)
                {
                    delete leftMost;
                    leftMost=NULL;
                }
                else
                {                    
                    Node* temp=leftMost;
                    leftMost=leftMost->right;
                    delete temp;
                }
                subtree->height=1+max(heightOrNeg1(subtree->left),heightOrNeg1(subtree->right));
            }
            else
            {
                Node* temp=subtree;
                subtree=subtree->left;
                subtree->right=temp->right;
                delete temp;
                subtree->height=1+max(heightOrNeg1(subtree->left),heightOrNeg1(subtree->right));
            }
        } 
        else 
        {
            /* one-child remove */
            // your code here
            if(subtree->left != NULL)
            {
                Node* temp=subtree;
                subtree=subtree->left;
                delete temp;
            }
            else
            {
                Node* temp=subtree;
                subtree=subtree->right;
                delete temp;
            }
        }
        // your code here
        
    }
}
