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

    std::cout << "Importing..." << std::endl;

    ws.importData("../data/wiki-topcats.txt");
    ws.importNames("../data/wiki-topcats-page-names.txt");

    std::cout << "Done!" << std::endl;

    ws.betweennessCentrality();
}