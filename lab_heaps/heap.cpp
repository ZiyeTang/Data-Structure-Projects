
/**
 * @file heap.cpp
 * Implementation of a heap class.
 */

template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
    // @TODO Update to return the index you are choosing to be your root.
    return 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the left child.
    return 2*currentIdx;
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the right child.
    return 2*currentIdx+1;
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const
{
    // @TODO Update to return the index of the parent.
    return currentIdx/2;
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const
{
    // @TODO Update to return whether the given node has a child
    return 2*currentIdx<=size;
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the child with highest priority
    ///   as defined by higherPriority()
    if(!hasAChild(currentIdx))
        return currentIdx;
    if(rightChild(currentIdx)>size)
        return leftChild(currentIdx);
    if(higherPriority(_elems[rightChild(currentIdx)],_elems[leftChild(currentIdx)]))
        return rightChild(currentIdx);
    return leftChild(currentIdx);
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx)
{
    // @TODO Implement the heapifyDown algorithm.
    if (!hasAChild(currentIdx))
        return;
    size_t childIdx;
    if(rightChild(currentIdx)<=size)
        childIdx = maxPriorityChild(currentIdx);
    else
        childIdx = leftChild(currentIdx);
    if (higherPriority(_elems[childIdx], _elems[currentIdx])) {
        std::swap(_elems[currentIdx], _elems[childIdx]);
        heapifyDown(childIdx);
    }
}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx)
{
    if (currentIdx == root())
        return;
    size_t parentIdx = parent(currentIdx);
    if (higherPriority(_elems[currentIdx], _elems[parentIdx])) {
        std::swap(_elems[currentIdx], _elems[parentIdx]);
        heapifyUp(parentIdx);
    }
}

template <class T, class Compare>
heap<T, Compare>::heap()
{
    // @TODO Depending on your implementation, this function may or may
    ///   not need modifying
    _elems.push_back(T());
    size=0;
}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems) 
{
    // @TODO Construct a heap using the buildHeap algorithm
    _elems.push_back(T());
    size=0;
    for(size_t i=0;i<elems.size();i++)
    {
        _elems.push_back(elems[i]);
        size++;
    }
    size_t startIdx=0;
    for(size_t i=1;i<=size;i++)
    {
        if(!hasAChild(i))
        {
            startIdx=i-1;
            break;
        }
    }
    for(size_t i=startIdx;i>=1;i--)
    {
        heapifyDown(i);
    }
}

template <class T, class Compare>
T heap<T, Compare>::pop()
{
    // @TODO Remove, and return, the element with highest priority
    if(!empty())
    {
        T toReturn=_elems[1]; 
        std::swap(_elems[1], _elems[size]);
        _elems.pop_back();
        size--;
        if(!empty())
        {
            heapifyDown(1);
        }
        return toReturn;                  
    }    
    return T();
}

template <class T, class Compare>
T heap<T, Compare>::peek() const
{
    // @TODO Return, but do not remove, the element with highest priority
    if(!empty())
        return _elems[1];
    return T();
}

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{
    // @TODO Add elem to the heap
    _elems.push_back(elem);
    size++;
    heapifyUp(size);
}

template <class T, class Compare>
void heap<T, Compare>::updateElem(const size_t & idx, const T& elem)
{
    // @TODO In-place updates the value stored in the heap array at idx
    // Corrects the heap to remain as a valid heap even after update
    size_t trueIdx=idx;
    _elems[trueIdx]=elem;
    if(trueIdx==1)
        heapifyDown(1);
    else if(!hasAChild(trueIdx))
        heapifyUp(trueIdx);
    else
    {
        if(higherPriority(_elems[trueIdx],_elems[parent(trueIdx)]))
        {
            heapifyUp(trueIdx);
        }
        else
        {
            heapifyDown(trueIdx);
        }
    }
}


template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
    // @TODO Determine if the heap is empty
    return size==0;
}

template <class T, class Compare>
void heap<T, Compare>::getElems(std::vector<T> & heaped) const
{
    for (size_t i = root(); i < _elems.size(); i++) {
        heaped.push_back(_elems[i]);
    }
}
