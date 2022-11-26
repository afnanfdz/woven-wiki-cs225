/**
 * @file Implementations of basic methods for WikiSearch, if any.
 */

#include "wikisearch.h"

#include <fstream>
#include <iostream>
#include <utility>
#include <algorithm>
#include <vector>
#include <string>

using std::ifstream;

WikiSearch::WikiSearch() : Graph<int>() {}

void WikiSearch::importData(string file_dir)
{
    Graph<int>::importData(file_dir);

    // Disjoint set information
    dsets_.addelements(getNodes());
    for (const std::pair<const int, std::list<int>> &p : getGraph())
    {
        for (const int &neighbor : p.second)
        {
            dsets_.setunion(p.first, neighbor);
        }
    }
}

void WikiSearch::importNames(string file_dir)
{
    ifstream file;
    file.open(file_dir);

    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            int index;
            string name;

            index = std::stoi(line.substr(0, line.find(' ')));
            name = line.substr(line.find(' ') + 1, line.size());

            names_.insert({index, name});
            ints_.insert({name, index});
        }
    }
}

vector<string> WikiSearch::pathAsNames(const vector<int> &path) const
{
    vector<string> name_path;

    for (const int &i : path)
    {
        name_path.push_back(names_.at(i));
    }

    return name_path;
}

int WikiSearch::intFromName(string name) const
{
    return ints_.at(name);
}

string WikiSearch::nameFromInt(int titleIDX) const
{
    return names_.at(titleIDX);
}

const DisjointSets &WikiSearch::getDisjointSet() const
{
    return dsets_;
}

int WikiSearch::findName(bool startName, string begTitle) const
{
    // strings:
    // title of this article fragment
    string title;

    // temporary storage for questioning user
    string yesno;

    // store full title of article once found
    string fullTitle;
    
    // integers:
    // title of the article found
    int titleINT;

    // offset used in search if beginning article is skipped
    int searchOffset;

    // storing option chosen from question
    int option;

    // the current option the screen is printing out
    int dispOPT;

    // how many option we want to display in the terminal per search cycle. less is better IMO
    int numDispOPT = 15;

    // test case for if we still need to be searching
    bool srch = true;

    // test case for escaping some other loops
    bool escloop;

    // test case for escaping some other loops
    bool optChosen;

    // keep on going until we get an exact search result
    while(srch){
        // test case
        if(startName){
            // if we're getting the beginning article title, no need to check if title was used already
            std::cout << "Enter the beginning article title, or type at least 3 characters to search: ";
            std::getline(std::cin >> std::ws, title);
        } else {
            // if we're getting the ending article title, we must check if title was used already
            std::cout << "Enter the ending article title, or type at least 3 characters to search: ";
            std::getline(std::cin >> std::ws, title);

            // require them to not use the same title as the beginning article
            while(title == begTitle){
                std::cout << std::endl << "You may not use the same article, please enter another: ";
                std::getline(std::cin >> std::ws, title);
            }
        }

        // we dont wan't to confuse users by giving them too many results.
        // require them for a longer, more specific search, to make life easier
        while(title.size() < 3){
            std::cout << std::endl << "Query is too short, please enter another: " << std::endl;
            std::getline(std::cin >> std::ws, title);
        }

        // if they were able to get through all the other test cases, then search
        std::cout << std::endl << "Searching with the phrase '" << title << "'" << std::endl;

        // calling searching method...
        std::vector<string> opts = this->lookupName(title);

        // set the search offset to zero, this is only relevant if we are finding the ending title
        searchOffset = 0;

        // test case
        if(opts.size() > 0){
            // if we produce 1 or more options, then we can print them out
            std::cout << "List of potential options: " << std::endl;

            // set the option being displayed to 1
            dispOPT = 1;

            // cycle through all the options we have available from the search
            for(const string & op : opts){
                // skip printing the title if we get the beginning title
                if(op == begTitle){
                    // increment the search offset
                    searchOffset++;

                    // continue, which will also skip incrementing dispOPT
                    continue;
                }

                // print the display option, and the search result for this associated option
                std::cout << dispOPT << ". " << op << std::endl;

                // if we reach the number of search results we allowed to be printed earlier in the program
                // we will now ask the user if they want more, or to search with what they have
                if((dispOPT % numDispOPT) == 0){

                    // test case for if we have determined whether or not the user correctly inputted yes or no
                    escloop = true;
                    while(escloop){
                        // ask if more options should be printed
                        std::cout << "More options available, print more options (Yes / No): ";
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
                            escloop = false;
                        }
                    }
                    // if no specified, then stop printing search results
                    if(yesno == "NO"){
                        dispOPT++;
                        break;
                    }
                }
                dispOPT++;
            }

            // test case for if we correctly chose an option
            optChosen = true;
            while(optChosen){
                // find the option a user wants
                std::cout << "Type the number of the option you would like: ";
                std::cin >> option;

                // test case
                if((option < 1) || (option > dispOPT)){
                    // if the option is 0 or greater than the options available, tell them they need to try again
                    std::cout << std::endl << "Invalid input, Try again." << std::endl;
                } else {
                    // if the option is valid, we can now choose the right article
                    std::cout << std::endl;

                    // leave the option loop
                    optChosen = false;

                    // search complete, we can leave the main loop
                    srch = false;

                    // find the full title
                    fullTitle = opts[option + searchOffset - 1];

                    // find the int of the title, this will be returned
                    titleINT = this->intFromName(fullTitle);
                }
            }
        } else {
            // if we produce no options, make them do everything over again
            std::cout << "No search results found, try again." << std::endl << std::endl;
        }
    }
    // return the proper int of the article
    return titleINT;
}

vector<string> WikiSearch::lookupName(string name) const
{
    // if the lookup name is less than 3 we really don't want to bother looking them up
    if(name.size() < 3)
    {
        return vector<string>();
    }

    // return array of possible names
    vector<string> poss_name;

    // turn the name to uppercase to make comparison easier
    string upperName = name;
    transform(upperName.begin(), upperName.end(), upperName.begin(), toupper);

    // temporary name used for search
    string tempName;
    
    // go through all of names_
    for(std::unordered_map<int, std::string>::const_iterator it = names_.begin(); it != names_.end(); it++){
        // set the current search option in uppercase
        tempName = it->second;
        transform(tempName.begin(), tempName.end(), tempName.begin(), toupper);

        // if the name includes a fragment of the search query,
        // then we can add it to the vector of names
        if(int(tempName.find(upperName)) != -1){
            poss_name.push_back(it->second);
        }
    }

    // return the vector of names
    return poss_name;
}