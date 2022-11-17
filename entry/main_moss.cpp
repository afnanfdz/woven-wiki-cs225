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
    WikiSearch ws;

    /*
    // small version
    std::cout << "Importing data..." << std::endl;
    ws.importData("../data/wiki-nodes.txt");
    std::cout << "Done. Importing names..." << std::endl;
    ws.importNames("../data/wiki-names.txt");
    */

    // regular version
    std::cout << "Importing data..." << std::endl;
    ws.importData("../data/wiki-topcats.txt");
    std::cout << "Done. Importing names..." << std::endl;
    ws.importNames("../data/wiki-topcats-page-names.txt");

    std::cout << "... Done" << std::endl << std::endl;

    bool tryAgain = true;
    bool escloop;
    string chosenBegin;
    int beginINT;
    string chosenEnd;
    int endINT;
    string begin;
    string goal;
    string yesno;

    while (tryAgain)
    {
        bool srch = true;

        while(srch){
            std::cout << "Enter the beginning article title, or type at least 3 characters to search: ";
            //std::cin >> begin;
            std::getline(std::cin >> std::ws, begin);

            while(begin.size() < 3){
                std::cout << std::endl << "Query is too short, please enter another: " << std::endl;
                //std::cin >> begin;
                std::getline(std::cin >> std::ws, begin);
            }

            std::cout << std::endl << "Searching with the phrase '" << begin << "'" << std::endl;

            std::vector<string> opts = ws.lookupName(begin);

            if(opts.size() > 0){
                std::cout << "List of potential options: " << std::endl;
                int i = 1;
                for(const string & op : opts){
                    std::cout << i << ". " << op << std::endl;
                    if((i % 15) == 0){
                        escloop = true;
                        while(escloop){
                            std::cout << "More options available, print more options (Yes / No): ";
                            std::cin >> yesno;
                            transform(yesno.begin(), yesno.end(), yesno.begin(), toupper);
                            if(yesno != "YES" && yesno != "NO"){
                                std::cout << std::endl << "Invalid input, Try again." << std::endl;
                                continue;
                            } else {
                                std::cout << std::endl;
                                escloop = false;
                            }
                        }
                        if(yesno == "NO"){
                            break;
                        }
                    }
                    i++;
                }
                bool optChosen = true;
                int option;
                while(optChosen){
                    std::cout << "Type the number of the option you would like: ";
                    std::cin >> option;
                    if((option < 1) || (option > i)){
                        std::cout << std::endl << "Invalid input, Try again." << std::endl;
                        continue;
                    } else {
                        std::cout << std::endl;
                        optChosen = false;
                        srch = false;
                        chosenBegin = opts[option - 1];
                        beginINT = ws.intFromName(chosenBegin);
                    }
                }
            } else {
                std::cout << "No search results found, try again." << std::endl << std::endl;
            }
        }

        srch = true;
        int beginOffset = 0;

        while(srch){
            std::cout << "Enter the ending article title, or type at least 3 characters to search: ";
            //std::cin >> goal;
            std::getline(std::cin >> std::ws, goal);

            while(goal == chosenBegin){
                std::cout << std::endl << "You may not use the same article, please enter another: ";
                //std::cin >> goal;
                std::getline(std::cin >> std::ws, goal);
            }

            while(begin.size() < 3){
                std::cout << std::endl << "Query is too short, please enter another: " << std::endl;
                //std::cin >> goal;
                std::getline(std::cin >> std::ws, goal);
            }
            std::cout << std::endl << "Searching with the phrase '" << goal << "'" << std::endl;

            std::vector<string> opts = ws.lookupName(goal);

            if(opts.size() > 0){
                std::cout << "List of potential options: " << std::endl;
                int i = 1;
                for(const string & op : opts){
                    if(op == chosenBegin){
                        beginOffset++;
                        continue;
                    }
                    std::cout << i << ". " << op << std::endl;
                    if((i % 15) == 0){
                        escloop = true;
                        while(escloop){
                            std::cout << "More options available, print more options (Yes / No): ";
                            std::cin >> yesno;
                            transform(yesno.begin(), yesno.end(), yesno.begin(), toupper);
                            if(yesno != "YES" && yesno != "NO"){
                                std::cout << std::endl << "Invalid input, Try again." << std::endl;
                                continue;
                            } else {
                                std::cout << std::endl;
                                escloop = false;
                            }
                        }
                        if(yesno == "NO"){
                            break;
                        }
                    }
                    i++;
                }
                bool optChosen = true;
                int option;
                while(optChosen){
                    std::cout << "Type the number of the option you would like: ";
                    std::cin >> option;
                    if((option < 1) || (option > i)){
                        std::cout << std::endl << "Invalid input, Try again." << std::endl;
                        continue;
                    } else {
                        std::cout << std::endl;
                        optChosen = false;
                        srch = false;
                        chosenEnd = opts[option + beginOffset - 1];
                        endINT = ws.intFromName(chosenEnd);
                    }
                }
            } else {
                std::cout << "No search results found, try again." << std::endl << std::endl;
            }
        }

        vector<string> path = ws.pathAsNames(ws.shortestPathBFS(beginINT, endINT));

        std::cout << "Shortest path is of length " << path.size() << ":" << std::endl;
        for (size_t i = 0; i < path.size(); i++)
        {
            std::cout << path.at(i);
            if (i != path.size() - 1)
            std::cout << " -> ";
        }

        escloop = true;
        while(escloop){
            std::cout << std::endl << "Want to try again? (Yes / No): ";
            std::cin >> yesno;
            transform(yesno.begin(), yesno.end(), yesno.begin(), toupper);
            if(yesno != "YES" && yesno != "NO"){
                std::cout << std::endl << "Invalid input, Try again." << std::endl;
                continue;
            } else {
                std::cout << std::endl;
                escloop = false;
            }
        }
        if(yesno == "NO"){
            tryAgain = false;
            break;
        }

        std::cout << std::endl << std::endl;
    }
    return 0;
}