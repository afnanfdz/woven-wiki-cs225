/**
 * @file Implementations of basic methods for WikiSearch, if any.
 */

#include "wikisearch.h"

#include <fstream>
#include <iostream>
#include <algorithm>

using std::ifstream;

WikiSearch::WikiSearch() : Graph<int>() {}

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

vector<string> WikiSearch::lookupName(string name) const
{
    if(name.size() < 3){
        return vector<string>();
    }
    vector<string> poss_name;
    string upperName = name;
    string tempName;
    transform(upperName.begin(), upperName.end(), upperName.begin(), toupper);

    for(std::unordered_map<int, std::string>::const_iterator it = names_.begin(); it != names_.end(); it++){
        tempName = it->second;
        transform(tempName.begin(), tempName.end(), tempName.begin(), toupper);
        if(int(tempName.find(upperName)) != -1){
            poss_name.push_back(it->second);
        }
    }
    return poss_name;
}