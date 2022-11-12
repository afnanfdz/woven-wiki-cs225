#pragma once

#include "edge.h"

#include <unordered_map>
#include <list>

using std::list;
using std::unordered_map;

/**
 * Graph class. Inspired by the CS225 lib but meant to be more lightweight.
 *
 */
template <class V>
class Graph
{
private:
    struct Edge
    {
        V from;
        V to;
        int weight;

        bool operator==(Edge &other) const;
        bool operator>(Edge &other) const;
        bool operator<(Edge &other) const;
    };

public:
    /**
     * Default constructor. Does nothing.
     */
    Graph();

    /**
     * Copy constructor. Creates a deep copy of the input Graph
     * @param other Reference to the Graph object
     */
    Graph(Graph &other);

    /**
     * Copy assignment. Creates a deep copy of the RHS Graph
     * @param other Reference to the Graph object
     *
     * @return Reference to the LHS Graph
     */
    Graph &operator=(Graph &other);

    /**
     * Destructor.
     *
     * @returns Deletes all node pointers stored.
     */
    ~Graph();

    /**
     * Adds an edge to the graph.
     * Ensure that 'from' and 'to' are already registered vertices
     *
     * @returns whether the operation was succesful. (false if edge exists already)
     */
    bool addEdge(V from, V to);

    /**
     * Adds a vertex to the graph.
     */
    bool addVertex(V val);

    /**
     * Returns whether the edge exists in the graph.
     */
    bool hasEdge(V from, V to);

    /**
     * Returns whether the vertex exists in the graph.
     */
    bool hasVertex(V val);

private:
    /**
     * Helper for the copy and assignment constructor.
     */
    void copy(Graph &other);

    /**
     * Helper for the copy constructors and destructor
     */
    void clear();

private:
    unordered_map<V, list<Edge>> graph_;
};