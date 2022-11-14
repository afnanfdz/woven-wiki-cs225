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
     * @param from The edge source
     * @param to The edge destination
     * @returns Whether the edge exists in the graph.
     */
    bool hasEdge(V from, V to) const;

    /**
     * @param val The unique vertex value to check
     * @returns Whether the vertex exists in the graph.
     */
    bool hasVertex(V val) const;

    /**
     * Gets all adjacent vertices to the parameter vertex
     * @param source vertex to get neighbors from
     * @returns a vector of vertices
     */
    list<V> &getAdjacent(V source) const;

    /**
     * @returns a const reference to the unordered map storing vertices and edge
     */
    unordered_map<V, list<V>> &getGraph() const;

    /**
     * Prints each node and all its children
     */
    void print();

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
 * This line is why I cried for a whole three hours
 * @author Vucirrha Skye
 * */
#include "graph.hpp"
#include "graphutils.hpp"