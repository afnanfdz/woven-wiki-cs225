#include <unordered_map>
#include <utility>

using std::pair;
using std::unordered_map;

/**
 * Wrapper for an unordered map.
 * Stores vertex / parent vertex pairs.
 */
template <class T>
class Path
{
public:
    Path();
    Path(T start, T goal);
    void insert(pair<T, T>);

private:
    unordered_map<T, T> path_;
    T start_;
    T goal_;
};

#include "pathfinder.hpp"