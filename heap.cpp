/**
 * @file heap.cpp
 * Implementation of a heap class.
 */

template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
    /// @todo Update to return the index you are choosing to be your root.
    return 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const
{
    /// @todo Update to return the index of the left child.
    return currentIdx*2;
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const
{
    /// @todo Update to return the index of the right child.
    return (currentIdx*2)+1;
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const
{
    /// @todo Update to return the index of the parent.
    return currentIdx/2;
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const
{
    /// @todo Update to return whether the given node has a child
    size_t leftChildIndex = leftChild(currentIdx);
	if(leftChildIndex>=_elems.size()){
		return false;
	}
	return true;
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const
{
    /// @todo Update to return the index of the child with highest priority
    ///   as defined by higherPriority()
    size_t left = leftChild(currentIdx);
	size_t right = rightChild(currentIdx);

	if(right >= _elems.size()) return left;
	if(higherPriority(_elems[left], _elems[right])){
		return left;
	}
	else{
		return right;
	}
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx)
{
    /// @todo Implement the heapifyDown algorithm.
	if(hasAChild(currentIdx) == false) return;

	size_t maxChild = maxPriorityChild(currentIdx);
	if(higherPriority(_elems[maxChild], _elems[currentIdx])){
		std::swap(_elems[maxChild], _elems[currentIdx]);
		heapifyDown(maxChild);
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
    /// @todo Depending on your implementation, this function may or may
    ///   not need modifying
	_elems = std::vector<T>();
	_elems.push_back(T());
}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems)
{
    /// @todo Construct a heap using the buildHeap algorithm
/*	_elems = std::vector<T>();
	//_elems.push_back(T());
	_elems.push_back(0);
	for(auto i = elems.begin(); i != elems.end(); i++){
		push(*i);
	}
	for(size_t i = 2; i<_elems.size(); i++){
		heapifyUp(i);
*/	
	_elems.push_back(0);
    for (size_t i = 0; i < elems.size(); i++)
    {
        _elems.push_back(elems[i]);
    }
    for (size_t i = parent(_elems.size()); i > 0; i--)
    {
        heapifyDown(i);
    }
}


template <class T, class Compare>
T heap<T, Compare>::pop()
{
    /// @todo Remove, and return, the element with highest priority
	T temp = peek();
	std::swap(_elems[root()], _elems[_elems.size()-1]);
	auto it = _elems.end();
	it--;
	_elems.erase(it);
	heapifyDown(root());
	return temp;
}

template <class T, class Compare>
T heap<T, Compare>::peek() const
{
    /// @todo Return, but do not remove, the element with highest priority
	return _elems[root()];
}

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{
    /// @todo Add elem to the heap
	_elems.push_back(elem);
	heapifyUp(_elems.size()-1);

}

template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
    /// @todo Determine if the heap is empty
	return _elems.size() < 2;

}
