#include "wikisearch.h"

#include <stack>
#include <limits>
#include <algorithm>

using std::stack;

vector<int> WikiSearch::limitedDFS(int source, int goal, int limit) const
{
    // Base case 1: We reached the goal
    if (source == goal)
    {
        return vector<int>({goal}); // Found!
    }

    // Base case 2: End of search
    if (limit <= 0)
    {
        return vector<int>(); // Empty
    }

    vector<int> result;

    for (const int &adj : getAdjacent(source))
    {
        result = limitedDFS(adj, goal, limit - 1);

        // If not empty, it's been found; collapse it up!
        if (!result.empty())
        {
            result.push_back(source);
            break;
        }
    }

    return result;
}

vector<int> WikiSearch::shortestPathIDDFS(int start, int goal) const
{
    int max_depth = getDisjointSet().size(start);
    vector<int> result;

    for (int depth = 0; depth <= max_depth; depth++)
    {
        result = limitedDFS(start, goal, depth);
        if (!result.empty())
        {
            std::reverse(result.begin(), result.end());
            break;
        }
    }

    return result; // Returns empty if not found
}