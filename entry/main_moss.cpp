/**
 * @file main_moss.cpp
 */

#include "wikisearch.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <chrono>

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

    // find out if the user wants to use full or limited data set
    escloop = true;
    while(escloop){
        // ask full 
        std::cout << "Would you like to use the full dataset? (Yes / No): ";
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

    if(yesno == "YES"){
        // regular version
        // time the import
        std::cout << "Importing full data... (this may take some time)." << std::endl;
        auto startIMDAT = std::chrono::high_resolution_clock::now();
        ws.importData("../data/wiki-topcats.txt");
        auto stopIMDAT = std::chrono::high_resolution_clock::now();

        // calculate time
        auto durationIMDAT = std::chrono::duration_cast<std::chrono::microseconds>(stopIMDAT - startIMDAT);
        double IMDATseconds = double((durationIMDAT.count()) % 60000000) / 1000000;
        int IMDATminutes = (durationIMDAT.count()) / 60000000;
        std::cout << "Import took: " << IMDATminutes << " minutes and " << IMDATseconds << " seconds." << std::endl;
        std::cout << "Importing names..." << std::endl;
        ws.importNames("../data/wiki-topcats-page-names.txt");
    } else {
        // small version
        // time the import
        std::cout << "Importing limited data..." << std::endl;
        auto startIMDAT = std::chrono::high_resolution_clock::now();
        ws.importData("../data/wiki-nodes.txt");
        auto stopIMDAT = std::chrono::high_resolution_clock::now();

        // calculate time
        auto durationIMDAT = std::chrono::duration_cast<std::chrono::microseconds>(stopIMDAT - startIMDAT);
        double IMDATseconds = double((durationIMDAT.count()) % 60000000) / 1000000;
        int IMDATminutes = (durationIMDAT.count()) / 60000000;
        std::cout << "Import took: " << IMDATminutes << " minutes and " << IMDATseconds << " seconds." << std::endl;
        std::cout << "Importing names..." << std::endl;
        ws.importNames("../data/wiki-names.txt");
    }

    std::cout << "... Done" << std::endl << std::endl;

    // test case for if we want to do more searches
    while (tryAgain)
    {
        // search the beginning title, use a placeholder article title that does not exist, will not matter
        beginINT = ws.findName(true, "qqqqqqqqqqqq");

        // find the endingle title. use the title from the first one
        endINT = ws.findName(false, ws.nameFromInt(beginINT));

        // find the path using BFS and then their names, and time it
        auto startBFS = std::chrono::high_resolution_clock::now();
        vector<string> pathBFS = ws.pathAsNames(ws.shortestPathBFS(beginINT, endINT));
        auto stopBFS = std::chrono::high_resolution_clock::now();

        // calculate time
        auto durationBFS = std::chrono::duration_cast<std::chrono::microseconds>(stopBFS - startBFS);
        double BFSinSec = double(durationBFS.count()) / 1000000;

        // print out the path
        std::cout << "Search using BFS took " << BFSinSec << " seconds." << std::endl;
        std::cout << "Path is of length " << pathBFS.size() << ":" << std::endl;
        for (size_t i = 0; i < pathBFS.size(); i++)
        {
            std::cout << pathBFS.at(i);
            if(i != pathBFS.size() - 1){
                std::cout << " -> ";
            }
        }

        // find the path using IDDFS and then their names, and time it
        auto startIDDFS = std::chrono::high_resolution_clock::now();
        vector<string> pathIDDFS = ws.pathAsNames(ws.shortestPathIDDFS(beginINT, endINT));
        auto stopIDDFS = std::chrono::high_resolution_clock::now();

        // calculate time
        auto durationIDDFS = std::chrono::duration_cast<std::chrono::microseconds>(stopIDDFS - startIDDFS);
        double IDDFSinSec = double(durationIDDFS.count()) / 1000000;

        // print out the path
        std::cout << std::endl << std::endl << "Search using IDDFS took: " << IDDFSinSec << " seconds." << std::endl;
        std::cout << "Path is of length " << pathIDDFS.size() << ":" << std::endl;
        for (size_t i = 0; i < pathIDDFS.size(); i++)
        {
            std::cout << pathIDDFS.at(i);
            if(i != pathIDDFS.size() - 1){
                std::cout << " -> ";
            }
        }

        // ask if user wants to see the options in reverse
        escloop = true;
        while(escloop){
            // ask if you want to try again
            std::cout << std::endl << std::endl << "Want to try try search in reverse? (Yes / No): ";
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

        // if yes, perform the previous in reverse
        if(yesno == "YES"){
            // find the path using BFS and then their names, and time it
            startBFS = std::chrono::high_resolution_clock::now();
            pathBFS.clear();
            pathBFS = ws.pathAsNames(ws.shortestPathBFS(endINT, beginINT));
            stopBFS = std::chrono::high_resolution_clock::now();

            // calculate time
            durationBFS = std::chrono::duration_cast<std::chrono::microseconds>(stopBFS - startBFS);
            BFSinSec = double(durationBFS.count()) / 1000000;

            // print out the path
            std::cout << "Search using BFS took " << BFSinSec << " seconds." << std::endl;
            std::cout << "Path is of length " << pathBFS.size() << ":" << std::endl;
            for (size_t i = 0; i < pathBFS.size(); i++)
            {
                std::cout << pathBFS.at(i);
                if(i != pathBFS.size() - 1){
                    std::cout << " -> ";
                }
            }

            // find the path using IDDFS and then their names, and time it
            startIDDFS = std::chrono::high_resolution_clock::now();
            pathIDDFS.clear();
            pathIDDFS = ws.pathAsNames(ws.shortestPathIDDFS(endINT, beginINT));
            stopIDDFS = std::chrono::high_resolution_clock::now();

            // calculate time
            durationIDDFS = std::chrono::duration_cast<std::chrono::microseconds>(stopIDDFS - startIDDFS);
            IDDFSinSec = double(durationIDDFS.count()) / 1000000;

            // print out the path
            std::cout << std::endl << std::endl << "Search using IDDFS took: " << IDDFSinSec << " seconds." << std::endl;
            std::cout << "Path is of length " << pathIDDFS.size() << ":" << std::endl;
            for (size_t i = 0; i < pathIDDFS.size(); i++)
            {
                std::cout << pathIDDFS.at(i);
                if(i != pathIDDFS.size() - 1){
                    std::cout << " -> ";
                }
            }
        }

        // find out if the user wants to run again
        escloop = true;
        while(escloop){
            // ask if you want to try again
            std::cout << std::endl << std::endl << "Want to try again? (Yes / No): ";
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