#pragma once

#include <unordered_map>
#include <list>
#include <string>
#include <iostream>

using std::list;
using std::string;
using std::unordered_map;

/**
 * Graph class. Inspired by the CS225 lib but meant to be more lightweight.
 * Unweighted. Directed. Values should be unique.
 */
template <class V>
class Graph
{
private: // Structs, if any! (None right now)
public:  // Public methods
    /**
     * Default constructor. Does nothing.
     */
    Graph();

    /**
     * Takes data from a .txt file of lines of whitespace-seperated pairs.
     *
     */
    void importData(string file_dir);

    /**
     * Checks the map whether the key exists;
     * if so, check if its list contains the second input
     *
     * Worst-case O(n) time (constant unordered_map access, then iterates through a list).
     *
     * @param from The edge source
     * @param to The edge destination
     * @returns Whether the edge exists in the graph.
     */
    bool hasEdge(V from, V to) const;

    /**
     * Checks the map whether the input exists as a key.
     *
     * Average O(1) time (unordered_map access time).
     *
     * @param val The unique vertex value to check
     * @returns Whether the vertex exists in the graph.
     */
    bool hasVertex(V val) const;

    /**
     * Gets all adjacent vertices to the parameter vertex.
     *
     * Average O(1) time (unordered_map access time).
     *
     * @param source The vertex to get neighbors from
     * @returns A const reference to a list of vertices
     */
    const list<V> &getAdjacent(V source) const;

    /**
     * @returns a const reference to the unordered map storing vertices and edge
     */
    unordered_map<V, list<V>> &getGraph() const;

    /**
     * Prints each node and all its children
     */
    void print() const;

private: // Private methods
    /**
     * Adds an edge to the graph.
     * Will not add duplicate edges.
     */
    void addEdge(V from, V to);
    /**
     * Adds a vertex to the graph.
     * Will replace old vertex data if existing.
     */
    void addVertex(V val);

private: // Private members
    unordered_map<V, list<V>> graph_;
};

/**
 * Missing this line is why I cried while debugging for too many hours
 * @author Vucirrha Skye
 * */
#include "graph.hpp"
#include "graphutils.hpp"