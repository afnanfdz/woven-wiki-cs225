/**
 * @file The class definition for Path.
 */

#include <unordered_map>
#include <utility>
#include <vector>

using std::pair;
using std::unordered_map;
using std::vector;

/**
 * Wrapper for an unordered map.
 * Stores vertex / parent vertex pairs.
 */
template <class T>
class Pathtrace
{
public:
    /**
     * Default constructor; deleted.
     * The start and goal MUST be defined.
     */
    Pathtrace() = delete;

    /**
     * Parametrized constructor
     * @param start The beginning, or 'root' of the path
     * @param goal The destination, or endgoal of the path
     */
    Pathtrace(T start, T goal);

    /**
     * Inserts a new vertex / parent vertex pair into the map.
     *
     * Average O(1). Worst case O(n) time (unordered_map insertion).
     *
     * Side effect: also checks whether the path is found after a given insertion
     * @param p The edge to insert
     */
    void insert(pair<T, T> p);

    /**
     * Inserts a new vertex / parent vertex pair into the map.
     *
     * Average O(1). Worst case O(n).
     *
     * Side effect: also checks whether the path is found after a given insertion
     * @param to The source vertex
     * @param from The destination vertex
     */
    void insert(T from, T to);

    /**
     * Average O(1) time.
     *
     * @returns Whether the map contains a path from goal to start.
     */
    bool goalIsFound() const;

    /**
     * Average O(1) time (access of an unordered map).
     *
     * @returns Whether the input value has been recorded / visited.
     */
    bool visited(T key) const;

    /**
     * @returns A vector of the shortest path to the goal.
     * Empty if not yet found, or the start and goal are the same...
     */
    vector<T> getShortestPath() const;

public:
    const static T END_OF_PATH;

private:
    unordered_map<T, T> path_;
    T start_;
    T goal_;
    bool found_;
};

#include "pathtrace.hpp"