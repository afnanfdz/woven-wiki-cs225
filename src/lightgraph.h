#pragma once

#include <unordered_map>
#include <list>
#include <string>

using std::list;
using std::string;
using std::unordered_map;

/**
 * Graph class. Inspired by the CS225 lib but meant to be more lightweight.
 * Unweighted. Directed.
 *
 */
template <typename V>
class LightGraph
{
private:
public:
    /**
     * Default constructor. Does nothing.
     */
    LightGraph();

    /**
     * Takes data from a .txt file of lines of whitespace-seperated pairs.
     *
     */
    void extractData(string file_dir);

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
     * Gets all adjacent vertices to the parameter vertex.
     * @param source - vertex to get neighbors from
     * @return a vector of vertices
     */
    list<V> &getAdjacent(V source) const;

private:
    unordered_map<V, list<V>> graph_;
};