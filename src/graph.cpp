#include <graph.h>

template <class V>
bool Graph<V>::Edge::operator==(Edge &other) const
{
    return (other.from == from && other.to == to);
}

template <class V>
bool Graph<V>::Edge::operator>(Edge &other) const
{
    return (weight > other.weight);
}

template <class V>
bool Graph<V>::Edge::operator<(Edge &other) const
{
    return (weight < other.weight);
}

template <class V>
Graph<V>::Graph()
{
}

template <class V>
Graph<V>::Graph(Graph &other)
{
}

template <class V>
Graph<V> &Graph<V>::operator=(Graph &other)
{
}

template <class V>
Graph<V>::~Graph()
{
}

template <class V>
void Graph<V>::copy(Graph &other)
{
}

template <class V>
void Graph<V>::clear()
{
    // for (Node *n : graph_)
    // {
    //     delete n;
    // }
}
