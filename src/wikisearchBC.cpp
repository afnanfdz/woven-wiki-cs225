#include "wikisearch.h"

#include <stack>
#include <queue>
#include <iostream>

using std::queue;
using std::stack;

unordered_map<int, int> WikiSearch::betweennessCentrality() const
{
    unordered_map<int, int> result;

    for (int idx : getNodes())
    {
        result[idx] = 0;
    }

    int count = 1;
    int max = getGraph().size();

    for (int starting_node : getNodes())
    {
        std::cout << count++ << " / " << max << " complete..." << std::endl;

        stack<int> s;
        unordered_map<int, vector<int>> predecessors;

        unordered_map<int, double> sigma;
        sigma[starting_node] = 1;

        unordered_map<int, int> dist_from_start;
        dist_from_start[starting_node] = 0;

        queue<int> q;
        q.push(starting_node);

        while (!q.empty())
        {
            int v_current = q.front();
            q.pop();

            s.push(v_current);

            for (int neighbor : getAdjacent(v_current))
            {
                // Found for the first time?
                if (dist_from_start.find(neighbor) == dist_from_start.end())
                {
                    q.push(neighbor);
                    dist_from_start[neighbor] = dist_from_start.at(v_current) + 1;
                }

                // Shortest path to w via v_current?
                if (dist_from_start.at(neighbor) == dist_from_start.at(v_current) + 1)
                {
                    if (sigma.find(neighbor) == sigma.end())
                    {
                        sigma[neighbor] = 0;
                    }

                    sigma.at(neighbor) = sigma.at(neighbor) + sigma.at(v_current);
                    predecessors[neighbor].push_back(v_current);
                }
            }
        }
        unordered_map<int, double> delta;

        while (!s.empty())
        {
            int current = s.top();
            s.pop();

            if (delta.find(current) == delta.end())
            {
                delta[current] = 0;
            }

            for (int pred : predecessors[current])
            {
                if (delta.find(pred) == delta.end())
                {
                    delta[pred] = 0;
                }

                delta.at(pred) = delta.at(pred) + ((sigma.at(pred) / sigma.at(current)) * (1 + delta.at(current)));

                if (current != starting_node)
                {
                    result.at(current) = result.at(current) + delta.at(current);
                }
            }
        }
    }

    return result;
}