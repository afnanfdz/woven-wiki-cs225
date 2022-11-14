#include "wikisearch.h"

#include <queue>

using std::queue;

vector<int> WikiSearch::shortestPathBFS(int begin, int goal) const
{
    Pathtrace<int> pathtrace(begin, goal);
    queue<int> frontier;

    frontier.push(begin);

    while (!frontier.empty() && !pathtrace.goalIsFound())
    {
        int front = frontier.front();
        frontier.pop();

        for (const int &adj : graph_.getAdjacent(front))
        {
            if (!pathtrace.visited(adj))
            {
                pathtrace.insert({adj, front});
                frontier.push(adj);
            }
        }
    }

    return pathtrace.getShortestPath(); // Returns empty if not found
}