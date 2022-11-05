#include "utils.h"

#include <fstream>
#include <vector>
#include <string>
#include <exception>

#include <sstream>
#include <iostream>

vector<pair<unsigned int, unsigned int>> importEdges(string file_dir)
{
    vector<pair<unsigned int, unsigned int>> result;

    ifstream file;
    string line;

    file.open(file_dir);

    if (file.is_open())
    {
        unsigned int node_1;
        unsigned int node_2;

        while (file >> node_1 >> node_2)
        {
            result.push_back({node_1, node_2});
        }
    }

    return result;
}

void shrinkEdgeData(string file_dir, string file_out_dir, int max_idx)
{
    ofstream output;
    ifstream file;

    file.open(file_dir);
    output.open(file_out_dir);

    if (file.is_open())
    {
        int node_1;
        int node_2; // eg of a line: 12 245325

        while (file >> node_1 >> node_2)
        {
            if (node_1 <= max_idx && node_2 <= max_idx)
            {
                output << node_1 << " " << node_2 << "\n";
            }
        }
    }
    else
    {
        string err = "Could not find input directory " + file_dir + "; assuming this is used on the Topcats data please manually install it first (see data/README.md)";
        throw std::invalid_argument(err);
    }

    file.close();
    output.close();
}

void shrinkNames(string file_dir, string file_out_dir, int max_idx)
{
    ofstream output;
    ifstream file;

    file.open(file_dir);
    output.open(file_out_dir);

    if (file.is_open())
    {
        string line; // eg. 29 Missouri Route 147

        while (getline(file, line))
        {
            if (stoi(line.substr(0, line.find(' '))) > max_idx)
                break;
            else
                output << line << "\n";
        }
    }
    else
    {
        string err = "Could not find input directory " + file_dir + "; assuming this is used on the Topcats data please manually install it first (see data/README.md)";
        throw std::invalid_argument(err);
    }

    file.close();
    output.close();
}