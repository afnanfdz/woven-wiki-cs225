
/**
 * @file heap.cpp
 * Implementation of a heap class.
 */
#include <cstddef>

template <class T, class Compare>
class heap;

template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
    return 1; // MY CHOICE
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const
{
    return 2 * currentIdx;
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const
{
    return 2 * currentIdx + 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const
{
    return currentIdx / 2; // floor division
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const
{
    return leftChild(currentIdx) < _elems.size();
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the child with highest priority
    ///   as defined by higherPriority()
    size_t l = leftChild(currentIdx);
    size_t r = rightChild(currentIdx);
    return r < _elems.size() ? higherPriority(_elems.at(l), _elems.at(r)) ? l : r
                             : l;
}

// MY HELPER
template <class T>
void mySwap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx)
{
    // @TODO Implement the heapifyDown algorithm.
    if (!hasAChild(currentIdx)) {
        return;
    }
    size_t childIdx = maxPriorityChild(currentIdx);
    if (higherPriority(_elems[childIdx], _elems[currentIdx])) {
        mySwap(_elems[childIdx], _elems[currentIdx]);
        heapifyDown(childIdx);
    }
}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx)
{
    if (currentIdx <= root())
        return;
    size_t parentIdx = parent(currentIdx);
    if (higherPriority(_elems[currentIdx], _elems[parentIdx])) {
        std::swap(_elems[currentIdx], _elems[parentIdx]);
        heapifyUp(parentIdx);
    }
}

template <class T, class Compare>
heap<T, Compare>::heap() : _elems(1, T()) // TODO can I do this?
{
    // @TODO Depending on your implementation, this function may or may
    ///   not need modifying
}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems) : _elems(1, T())
{
    // @TODO Construct a heap using the buildHeap algorithm
    _elems.reserve(elems.size() + root());
    for (auto elem : elems) {
        _elems.push_back(elem);
    }
    for (size_t i = parent(_elems.size() - 1); i >= 1; --i) {
        heapifyDown(i);
    }
}

template <class T, class Compare>
T heap<T, Compare>::pop()
{
    // @TODO Remove, and return, the element with highest priority
    if (_elems.size() < 2) {
        return T();
    }
    T result = peek();
    size_t lastIdx = _elems.size() - 1;
    _elems[1] = _elems[lastIdx];
    _elems.pop_back();
    heapifyDown(1);
    return result;
}

template <class T, class Compare>
T heap<T, Compare>::peek() const
{
    // @TODO Return, but do not remove, the element with highest priority
    return _elems.size() >= 2 ? _elems[1] : T();
}

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{
    // @TODO Add elem to the heap
    _elems.push_back(elem);
    size_t lastIdx = _elems.size() - 1;
    heapifyUp(lastIdx);
}

template <class T, class Compare>
void heap<T, Compare>::updateElem(const size_t & idx, const T& elem)
{
    // @TODO In-place updates the value stored in the heap array at idx
    // Corrects the heap to remain as a valid heap even after update
    // ASSUME VALID ????????
    _elems[idx] = elem;
    heapifyUp(idx);
    heapifyDown(idx); // assume that only one of them will run
}


template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
    // @TODO Determine if the heap is empty
    return _elems.size() <= root();
}

template <class T, class Compare>
void heap<T, Compare>::getElems(std::vector<T> & heaped) const
{
    for (size_t i = root(); i < _elems.size(); i++) {
        heaped.push_back(_elems[i]);
    }
}
