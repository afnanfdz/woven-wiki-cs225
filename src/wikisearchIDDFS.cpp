#include "wikisearch.h"

#include <stack>

using std::stack;

vector<int> WikiSearch::shortestPathIDDFS(int begin, int goal) const
{
    Pathtrace<int> pathtrace(begin, goal);

    return pathtrace.getShortestPath(); // Returns empty if not found
}