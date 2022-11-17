/**
 * @file wikisearch_small.cpp
 */

#include "wikisearch.h"
#include <iostream>
#include <vector>
#include <string>

int main()
{

    WikiSearch ws;

    std::cout << "Importing data..." << std::endl;
    ws.importData("../data/wiki-nodes.txt");
    std::cout << "Done. Importing names..." << std::endl;
    ws.importNames("../data/wiki-names.txt");
    std::cout << "... Done" << std::endl
              << std::endl;

    while (true)
    {
        int begin;
        int goal;

        std::cout << "Enter a pair of vertex numbers: " << std::endl;
        std::cin >> begin >> goal;

        vector<string> path = ws.pathAsNames(ws.shortestPathBFS(begin, goal));

        std::cout << "Shortest path is of length " << path.size() << ":" << std::endl;
        for (size_t i = 0; i < path.size(); i++)
        {
            std::cout << path.at(i);
            if (i != path.size() - 1)
                std::cout << " -> ";
        }
        std::cout << std::endl
                  << std::endl;
    }

    return 0;
}