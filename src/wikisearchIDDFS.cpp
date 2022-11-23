#include "wikisearch.h"

#include <stack>
#include <limits>

using std::stack;

const int WikiSearch::END_OF_PATH = std::numeric_limits<int>::max();

vector<int> WikiSearch::limitedDFS(int start, int goal, int limit) const
{
    return vector<int>(); // Returns empty if not found
}

vector<int> WikiSearch::shortestPathIDDFS(int begin, int goal) const
{
    int max_depth = getDisjointSet().size(begin);

    return vector<int>(); // Returns empty if not found
}