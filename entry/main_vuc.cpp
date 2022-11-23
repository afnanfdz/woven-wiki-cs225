/**
 * @file main_vuc.cpp
 */

#include "wikisearch.h"
#include <iostream>

int main()
{
    WikiSearch ws;

    ws.importData("../data/wiki-nodes.txt");

    // ws.getDisjointSet().print();
    std::cout << "Number of disjoint sets: " << ws.getDisjointSet().getNumSets() << std::endl;

    int count = 0;
    for (int i : ws.getNodes())
    {
        ++count;

        std::cout << "Max depth of " << i << ": " << ws.getDisjointSet().size(i) << std::endl;

        if (count > 100)
        {
            break;
        }
    }
}