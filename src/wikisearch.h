#pragma once

#include "graph.h"
#include "pathtrace.h"
#include "dsets.h"

#include <string>
#include <vector>
#include <list>
#include <unordered_map>

using std::list;
using std::string;
using std::unordered_map;
using std::vector;

/**
 * Class inheriting the Graph;
 * Information about Wikipedia articles, as well
 * as the project's search functions, are implemented here
 */
class WikiSearch : public Graph<int>
{
public: // Utilities
    using Graph<int>::getAdjacent;
    using Graph<int>::getGraph;

    /**
     * Default constructor. Does nothing as of now.
     */
    WikiSearch();

    void importData(string file_dir);

    /**
     * Imports the data for names of articles.
     */
    void importNames(string file_dir);

    /**
     * @param path A shortest path vector of ints from one of the search algorithms.
     * @returns The shortest path of articles by name.
     */
    vector<string> pathAsNames(const vector<int> &path) const;

    /**
     * @param name Exact name to look up
     * @returns The integer index of this name
     */
    int intFromName(string name) const;

    /**
     * @param path Fragment of name to look up
     * @returns A vector of possible article names
     */
    vector<string> lookupName(string name) const;

    const DisjointSets &getDisjointSet() const;

public: // Project Algorithms
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

private:
    vector<int> limitedDFS(int start, int goal, int limit) const;

private:
    unordered_map<int, string> names_;
    unordered_map<string, int> ints_;
    DisjointSets dsets_;
    const static int END_OF_PATH; // Used in IDDFS
};
