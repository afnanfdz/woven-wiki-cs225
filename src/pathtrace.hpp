/**
 * @file Method implementations for Path
 */

#include <exception>
#include <limits>

template <typename T>
const T Pathtrace<T>::END_OF_PATH = std::numeric_limits<T>::max();

template <typename T>
Pathtrace<T>::Pathtrace(T start, T goal) : start_(start), goal_(goal)
{
    found_ = start == goal;
    path_.insert({start, END_OF_PATH});
}

template <typename T>
void Pathtrace<T>::insert(pair<T, T> p)
{
    // END_OF_PATH is our one-past-end value.
    // It cannot be used in this implementation.
    if (p.first == END_OF_PATH || p.second == END_OF_PATH)
        throw std::invalid_argument("Pathtrace error: END_OF_PATH value was inserted");
    // Check if we're about to insert the goal
    if (p.first == goal_)
        found_ = true;
    path_.insert(p);
}

template <typename T>
void Pathtrace<T>::insert(T from, T to)
{
    // Overload to the pair-based insert
    insert({from, to});
}

template <typename T>
bool Pathtrace<T>::goalIsFound() const
{
    return found_;
}

template <typename T>
bool Pathtrace<T>::visited(T key) const
{
    return path_.find(key) != path_.end();
}

template <typename T>
vector<T> Pathtrace<T>::getShortestPath() const
{
    vector<T> shortest_path;

    // Generate the path if found
    for (T loc = goal_; loc != END_OF_PATH && goalIsFound(); loc = path_.at(loc))
        /**
         * @note: Insert at front, or push_back and reverse?
         */
        shortest_path.insert(shortest_path.begin(), loc);

    return shortest_path;
}
