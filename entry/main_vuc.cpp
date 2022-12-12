/**
 * @file main_vuc.cpp
 */

#include "wikisearch.h"
#include <vector>
#include <iostream>
#include <string>

int main()
{
    WikiSearch ws;

    ws.importData("../data/wiki-topcats.txt");
    ws.importNames("../data/wiki-topcats-page-names.txt");

    std::vector<int> longest_path;
    int count = 1;
    size_t max = ws.getGraph().size();

    for (const int start_node : ws.getNodes())
    {
        int subcount = 1;
        for (const int end_node : ws.getNodes())
        {
            if (start_node == end_node)
                continue;

            std::cout << "Using start page " << count << " / " << max
                      << ": Finding shortest path of " << count << " -> " << subcount << "; "
                      << "Current longest path length = " << longest_path.size()
                      << "                                                             \r";

            std::vector<int> shortest_path = ws.shortestPathBFS(start_node, end_node);

            if (shortest_path.size() > longest_path.size())
            {
                longest_path = shortest_path;
            }
            ++subcount;
        }
        ++count;
    }

    std::cout << "Longest shortest-path: ";

    for (std::string page : ws.pathAsNames(longest_path))
    {
        std::cout << page << " -> ";
    }

    std::cout << std::endl;
}