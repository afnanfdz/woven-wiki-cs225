#include "wikisearch.h"

#include <queue>
#include <iostream>

using std::queue;

// Flip this to allow prints
const bool DEBUG = false;

vector<int> WikiSearch::shortestPathBFS(int begin, int goal) const
{
    // Initialize the pathtrace to memorize visited articles
    Pathtrace<int> pathtrace(begin, goal);

    // Initialize the frontier to perform a breadth-first search
    queue<int> frontier;
    frontier.push(begin);

    if (DEBUG) /** DEBUG STATEMENT */
        std::cout << std::endl
                  << "Pushed " << begin << " to frontier" << std::endl;

    // Iterate while there's vertices to visit,
    // and while the goal is not visited
    while (!frontier.empty() && !pathtrace.goalIsFound())
    {
        // Pop and store the front value
        int front = frontier.front();
        frontier.pop();

        if (DEBUG) /** DEBUG STATEMENT */
            std::cout << "Popped " << front << " from frontier, accessing adjacents.." << std::endl;

        // Iterate over all articles it has a link to
        for (const int &adj : getAdjacent(front))
        {
            // If a linked article has not yet been discovered,
            // mark as visited and add it to the frontier
            if (!pathtrace.visited(adj))
            {
                pathtrace.insert({adj, front});
                frontier.push(adj);
            }
        }

        // Loop until one of the while conditions are violated.
    }

    return pathtrace.getShortestPath(); // Returns empty if not found
}