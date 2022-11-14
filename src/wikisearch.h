#pragma once

#include "graph.h"
#include "pathtrace.h"

#include <string>
#include <vector>
#include <list>

using std::list;
using std::string;
using std::vector;

class WikiSearch
{
public:
    /**
     * Default constructor. Does nothing.
     */
    WikiSearch();

    /**
     * Imports edge data (assumed to be ints) to the graph
     */
    void importData(string file_dir);

    /**
     * Prints the graph. Tends to exceed readable limit.
     */
    void print() const;

    /**
     * Performs a Breadth-First Search
     * to find the shortest path from start to goal.
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
     * @param start The starting article index.
     * @param goal The destination article index.
     * @returns One shortest path from start to goal.
     */
    vector<int> shortestPathIDDFS(int start, int goal) const;

private:
    Graph<int> graph_;
};
