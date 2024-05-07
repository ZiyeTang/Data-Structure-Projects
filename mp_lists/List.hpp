/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List() 
{ 
  // @TODO: graded in MP3.1
    head_ = NULL;
    tail_ = NULL;
    length_=0;
}


/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const 
{
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_);

}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const 
{
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(tail_->next);
}


/*template <typename T>
List<T>& List<T>::operator=(const List<T>& rhs)
{
  
  return 
}*/

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() 
{
  /// @todo Graded in MP3.1
  while(head_!=NULL)
  {
    ListNode* temp=head_;
    head_=head_->next;
    delete temp;    
  }
  if(tail_!=NULL)
  {
    tail_=NULL;
  }
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) 
{
  /// @todo Graded in MP3.1
 
  ListNode * newNode = new ListNode(ndata);
  newNode -> next = head_;
  newNode -> prev = NULL;
  
  
  if (head_ != NULL) 
  {
    head_ -> prev = newNode;
  }
 
  head_=newNode;
  
  if (tail_ == NULL) 
  {
    tail_ = newNode;
  }  

  length_++;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) 
{
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  newNode -> prev = tail_;
  newNode -> next = NULL;
  
  
  if (tail_ != NULL) 
  {
    tail_ -> next = newNode;
  }
 
  tail_=newNode;
  
  if (head_ == NULL) 
  {
    head_ = newNode;
  }  

  length_++;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode* List<T>::split(ListNode* start, int splitPoint) 
{
  /// @todo Graded in MP3.1
  if(start==NULL||splitPoint<0)
  {
    return start;
  }
  ListNode * curr = start;

  for (int i = 0; i < splitPoint && curr != NULL; i++) 
  {
    curr = curr->next;
  }

  if (curr != NULL&&curr->prev!=NULL) 
  {
      curr->prev->next = NULL;
      curr->prev = NULL;

  }

  return curr;
}


/**
  * Modifies List using the rules for a TripleRotate.
  *
  * This function will to a wrapped rotation to the left on every three 
  * elements in the list starting for the first three elements. If the 
  * end of the list has a set of 1 or 2 elements, no rotation all be done 
  * on the last 1 or 2 elements.
  * 
  * You may NOT allocate ANY new ListNodes!
  */
template <typename T>
void List<T>::tripleRotate() 
{
  // @todo Graded in MP3.1
  if(length_<3)
    return;
  int numRot=length_/3;
  
  List<T>::ListNode* itr=head_;
  for(int i=0;i<numRot;i++)
  {
    if(i==0)
      head_=itr->next;

    itr->next->prev=itr->prev;
    if(itr->prev!=NULL)
      itr->prev->next=itr->next;

    itr->prev=itr->next->next;
    itr->next=itr->next->next->next;

    itr->prev->next=itr;
    if(itr->next!=NULL)
      itr->next->prev=itr;

    itr=itr->next;
  }
}


/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() 
{
  reverse(head_, tail_);
  List<T>::ListNode* swapHelper=head_;
  head_=tail_;
  tail_=swapHelper;

}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) 
{
  /// @todo Graded in MP3.2
  List<T>::ListNode* itr=startPoint;
  List<T>::ListNode* after=endPoint->next;
  
  while(itr!=after)
  {
    List<T>::ListNode* temp=itr->next;
    itr->next=itr->prev;
    itr->prev=temp;
    itr=itr->prev;
  }

  List<T>::ListNode* temp1=endPoint->prev;
  List<T>::ListNode* temp2=startPoint->next;
  endPoint->prev=temp2;
  if(temp2!=NULL)
    temp2->next=endPoint;
  startPoint->next=temp1;
  if(temp1!=NULL)
    temp1->prev=startPoint;

}


template <typename T>
typename List<T>::ListNode* List<T>::nodeAt(int idx,typename List<T>::ListNode* startPoint)
{
  typename List<T>::ListNode* res=startPoint;
  if(res==NULL)
    return res;
  for(int i=0;i<idx&&res->next!=NULL;i++)
  {
    res=res->next;
  }
  return res;
}
/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) 
{
  /// @todo Graded in MP3.2
  if(n>=length_)
  {
    reverse();
    return;
  }
  
  int numReverse = length_/n;
  ListNode* start = head_;
  ListNode* end=nodeAt(n-1,start);
  for(int i=0;i<numReverse;i++)
  {    
    reverse(start, end);
    List<T>::ListNode* swapHelper=start;
    start=end;
    end=swapHelper;

    if(i==0)
      head_=start;

    if(end->next==NULL)
      tail_=end;
    start=end->next;
    end=nodeAt(n-1,start);
  }
  if(length_-numReverse*n>1)
  {
    reverse(start,tail_);
    tail_=start;
  }  
}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) 
{
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode* first, ListNode* second) 
{
  /// @todo Graded in MP3.2
  ListNode* itr1=first;
  ListNode* itr2=second;
  ListNode* res=NULL; 
  ListNode* resHead=NULL;
  
  while(itr1!=NULL||itr2!=NULL)
  {
    ListNode* toInsert;
    if(itr1==NULL)
    {
      toInsert = itr2;
      itr2=itr2->next;
    }
    else if(itr2==NULL)
    {
      toInsert = itr1;
      itr1=itr1->next;
    }
    else if(itr1->data<itr2->data)
    {
      toInsert = itr1;
      itr1=itr1->next;
    }
    else
    {
      toInsert = itr2;
      itr2=itr2->next;
    }

    toInsert->next=NULL;
    toInsert->prev=NULL;
     
    if(resHead==NULL)
    {
      res = toInsert;
      resHead = toInsert;
    }
    else
    {
      res->next=toInsert;
      toInsert->prev=res;
      res=res->next;
    }
  }

  return resHead;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) 
{
  /// @todo Graded in MP3.2
  if(chainLength<=1||start==NULL)
    return start;
  
  ListNode* first=start;
  ListNode* firstHead=start;
  for(int i=0;i<chainLength/2-1;i++)
  {
    first=first->next;
  }
  ListNode* secondHead=first->next;
  first->next=NULL;
  secondHead->prev=NULL;
  firstHead=mergesort(firstHead, chainLength/2);
  secondHead=mergesort(secondHead, chainLength-chainLength/2);
  ListNode* res=merge(firstHead, secondHead);
  return res;
}
