/**
 * @file Implementations of basic methods for WikiSearch, if any.
 */

#include "wikisearch.h"

#include <fstream>
#include <iostream>
#include <utility>
#include <algorithm>

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

const DisjointSets &WikiSearch::getDisjointSet() const
{
    return dsets_;
}

vector<string> WikiSearch::lookupName(string name) const
{
    if (name.size() < 4)
    {
        return vector<string>();
    }
    vector<string> poss_name;
    unordered_map<int, string>::iterator it;
    string upperName = name;
    string tempName;
    transform(upperName.begin(), upperName.end(), upperName.begin(), toupper);

    for (it == names_.begin(); it != names_.end(); it++)
    {
        tempName = it->second;
        transform(tempName.begin(), tempName.end(), tempName.begin(), toupper);
        if ((tempName.find(upperName)) != -1)
        {
            poss_name.push_back(it->second);
        }
    }

    return poss_name;
}