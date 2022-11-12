/**
 * @file main.cpp
 *
 * Expected to be used for quick testing. A new entryfile should be made
 * if we expect to be doing something very often.
 */

#include "graph.h"

#include <string>
#include <iostream>

int main()
{
    Graph<unsigned int> g;

    g.importData("../data/gendata/wiki-nodes.txt");
    g.print();

    return 0;
}