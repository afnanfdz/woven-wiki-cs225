#pragma once

#include "graph.h"
#include "pathtrace.h"

#include <string>
#include <vector>
#include <list>

using std::list;
using std::string;
using std::vector;

/**
 * Class inheriting the Graph;
 * Information about Wikipedia articles, as well
 * as the project's search functions, are implemented here
 */
class WikiSearch : public Graph<int>
{
public:
    /**
     * Default constructor. Does nothing.
     */
    WikiSearch();

    /**
     * Performs a Breadth-First Search
     * to find the shortest path from start to goal.
     *
     * Worst case time: O(V).
     * Worst case memory: O(V).
     *
     * @param start The starting article index.
     * @param goal The destination article index.
     * @returns One shortest path from start to goal.
     */
    vector<int> shortestPathBFS(int start, int goal) const;

    /**
     * Performs an Iterative Deepening Depth-First Search
     * to find the shortest path from start to goal.
     *
     * Worst case time: O(V).
     * Worst case memory: O(max(depth)).
     *
     * @param start The starting article index.
     * @param goal The destination article index.
     * @returns One shortest path from start to goal.
     */
    vector<int> shortestPathIDDFS(int start, int goal) const;
};
