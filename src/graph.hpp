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

            if (!hasVertex(to))
            {
                addVertex(to);
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

#include <exception>

template <class V>
const list<V> &Graph<V>::getAdjacent(V source) const
{
    if (!hasVertex(source))
    {
        string err = "Graph<V>::getAdjacent error: Tried to access " +
                     std::to_string(source) + " which isn't in the graph";
        throw std::invalid_argument(err);
    }

    return graph_.at(source);
}

template <class V>
const unordered_map<V, list<V>> &Graph<V>::getGraph() const
{
    return graph_;
}