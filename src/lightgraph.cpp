#include "lightgraph.h"

#include <fstream>

using std::ifstream;

template <typename V>
LightGraph<V>::LightGraph()
{
}

template <typename V>
void LightGraph<V>::extractData(string file_dir)
{
    ifstream file;
    string line;

    file.open(file_dir);

    if (file.is_open())
    {
        V from;
        V to;

        while (file >> from >> to)
        {
            if (!hasVertex(from))
            {
                addVertex(from);
            }

            addEdge(from, to);
        }
    }
}

template <typename V>
bool LightGraph<V>::hasEdge(V from, V to) const
{
    bool result = false;

    if (graph_.find(from) != graph_.end())
    {
        for (V edge_to : graph_.at(from))
        {
            if (edge_to == to)
            {
                result = true;
                break;
            }
        }
    }

    return result;
}

template <typename V>
void LightGraph<V>::addEdge(V from, V to)
{
    if (hasEdge(from, to))
    {
        graph_.at(from).push_back(to);
    }
}

template <typename V>
bool LightGraph<V>::hasVertex(V val) const
{
    return graph_.find(val) != graph_.end();
}

template <typename V>
void LightGraph<V>::addVertex(V val)
{
    if (hasVertex(val))
    {
        graph_.at(val).clear();
    }
    else
    {
        graph_.insert({val, list<V>()});
    }
}

template <typename V>
list<V> &LightGraph<V>::getAdjacent(V source) const
{
    return graph_.at(source);
}