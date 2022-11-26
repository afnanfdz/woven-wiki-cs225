/**
 * @file main_moss.cpp
 */

#include "wikisearch.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

int main()
{
    // the wiki search class
    WikiSearch ws;

    // test case on if we want to keep on searching
    bool tryAgain = true;

    // test case for ecaping some loops
    bool escloop;

    // beginning article title index
    int beginINT;

    // ending article title index
    int endINT;

    // string for testing yes and no options
    string yesno;

    /*
    // small version
    std::cout << "Importing limited data..." << std::endl;
    ws.importData("../data/wiki-nodes.txt");
    std::cout << "Done. Importing names..." << std::endl;
    ws.importNames("../data/wiki-names.txt");
    */

    // regular version
    std::cout << "Importing full data... (this may take some time)" << std::endl;
    ws.importData("../data/wiki-topcats.txt");
    std::cout << "Done. Importing names..." << std::endl;
    ws.importNames("../data/wiki-topcats-page-names.txt");

    std::cout << "... Done" << std::endl << std::endl;

    // test case for if we want to do more searches
    while (tryAgain)
    {
        // search the beginning title, use a placeholder article title that does not exist, will not matter
        beginINT = ws.findName(true, "qqqqqqqqqqqq");

        // find the endingle title. use the title from the first one
        endINT = ws.findName(false, ws.nameFromInt(beginINT));

        // find the path and then their names
        vector<string> path = ws.pathAsNames(ws.shortestPathBFS(beginINT, endINT));

        // print out the path
        std::cout << "Shortest path is of length " << path.size() << ":" << std::endl;
        for (size_t i = 0; i < path.size(); i++)
        {
            std::cout << path.at(i);
            if (i != path.size() - 1)
            std::cout << " -> ";
        }

        // find out if the user wants to run again
        escloop = true;
        while(escloop){
            // ask if more options should be printed
            std::cout << std::endl << "Want to try again? (Yes / No): ";
            std::cin >> yesno;

            // modify answer to upper case, and change y into yes and n into no for better usability
            transform(yesno.begin(), yesno.end(), yesno.begin(), toupper);
            if(yesno == "Y"){
                yesno = "YES";
            } else if(yesno == "N"){
                yesno = "NO";
            }

            // test case
            if(yesno != "YES" && yesno != "NO"){
                // if its not yes or no, its an invalid input
                std::cout << std::endl << "Invalid input, Try again." << std::endl;
            } else {
                // if its yes or no, its an valid input, act accordingly
                std::cout << std::endl;
                escloop = false;
            }
        }
        std::cout << std::endl << std::endl;

        // if the user wants to stop, break the search.
        if(yesno == "NO"){
            tryAgain = false;
            break;
        }
    }
    std::cout << "Thank you." << std::endl;
    return 0;
}