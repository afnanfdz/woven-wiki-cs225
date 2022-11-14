#include <fstream>
#include <utility>

using std::ifstream;

template <class V>
Graph<V>::Graph()
{
}

template <class V>
void Graph<V>::importData(string file_dir)
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

template <class V>
bool Graph<V>::hasEdge(V from, V to) const
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

template <class V>
void Graph<V>::addEdge(V from, V to)
{
    if (!hasEdge(from, to))
    {
        graph_.at(from).push_back(to);
    }
}

template <class V>
bool Graph<V>::hasVertex(V val) const
{
    return graph_.find(val) != graph_.end();
}

template <class V>
void Graph<V>::addVertex(V val)
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

template <class V>
const list<V> &Graph<V>::getAdjacent(V source) const
{
    return graph_.at(source);
}

template <class V>
unordered_map<V, list<V>> &Graph<V>::getGraph() const
{
    return graph_;
}