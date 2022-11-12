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
 * Unweighted. Directed.
 *
 */
template <class V>
class Graph
{
private:
public:
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
     * @returns Whether the edge exists in the graph.
     */
    bool hasEdge(V from, V to) const;

    /**
     * Adds an edge to the graph.
     * Will not add duplicate edges.
     */
    void addEdge(V from, V to);

    /**
     * @returns Whether the vertex exists in the graph.
     */
    bool hasVertex(V val) const;

    /**
     * Adds a vertex to the graph.
     * Will replace old vertex data if existing.
     */
    void addVertex(V val);

    /**
     * Gets all adjacent vertices to the parameter vertex
     * @param source - vertex to get neighbors from
     * @return a vector of vertices
     */
    list<V> &getAdjacent(V source) const;

    /**
     * Prints each node and all its children
     */
    void print();

private:
    unordered_map<V, list<V>>
        graph_;
};

/**
 * This line is why I cried for a whole three hours, and shidded and farded
 * @author Vucirrha Skye
 * */
#include "graph.hpp"