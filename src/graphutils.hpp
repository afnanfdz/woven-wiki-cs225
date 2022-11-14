
/**
 * Ignore any errors about Graph<V> not being a template.
 */

template <class V>
void Graph<V>::print() const
{
    for (const std::pair<const V, list<V>> &p : graph_)
    {
        std::cout << p.first << " -> [ ";

        for (V dest : p.second)
        {
            std::cout << dest << " ";
        }
        std::cout << "]" << std::endl;
    }
}