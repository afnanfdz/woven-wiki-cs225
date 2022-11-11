#pragma once

#include <unordered_map>
#include <list>

/**
 * Graph class. Stores nodes in an unordered map to optimize for access time.
 * Stores neighbors in a list to optimize insertion time.
 *
 */
template <class T>
class Graph
{
private:
    /**
     * Simple container for data
     * Expected to be used on the heap
     */
    struct Vertex
    {
        T val_;
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

    bool addEdge(T from, T to);
    bool addVertex(T val);
    bool hasEdge(T from, T to);
    bool hasVertex(T val);

private:
    /**
     * Helper for the copy and assignment constructor.
     */
    void copy(Graph &other);

    /**
     * Helper for the copy constructors and destructor
     */
    void clear();

    bool hasEdge(T from, T to);
    bool hasVertex(T node);

private:
    std::unordered_map<Node *, std::list<Vertex *>> graph_;
};