/**
 * @file main_awelotta.cpp
 *
 * Uses functions written in utils.h to generate shrunken
 * versions of the original topcats data, either so that
 * we can fit it in the GitHub or want quicker result
 * times during testing
 */

#include "utils.h"
#include "../lib/heap/heap.h"

#include <iostream>
#include <string>
#include "wikisearch.h"
#include "utils.h"
#include <vector>
#include <fstream>
#include <algorithm>
#include <chrono>

using std::string;

int main(int argc, char *argv[])
{
    /*** gen shrunk data ***/

    // There should only be two to four separate inputs
    if (argc < 2 || argc > 6)
    {
        std::cout << "USAGE: ./main_awelotta [num_nodes] [optional: path_to_output]  [optional: output_edge_data_filename] [optional: output_node_names_filename]" << std::endl;
        std::cout << "note: picking num_nodes = 10 000 takes around 15 minutes on my laptop. Brandes's algorithm is O(n^3)" << std::endl;
        return 1;
    }
    // Variable setup
    int num_nodes = atoi(argv[1]);
    string output_path = (argc >= 3 ? argv[2] : "../data/gendata");
    string edge_data_filename = (argc >= 4 ? argv[3] : "wiki-nodes.txt");
    string node_names_filename = (argc >= 5 ? argv[4] : "wiki-names.txt");
    // Perform shrinks on the topcats data based on user input
    shrinkEdgeData("../data/wiki-nodes.txt", output_path + "/" + edge_data_filename, num_nodes);
    shrinkNames("../data/wiki-names.txt", output_path + "/" + node_names_filename, num_nodes);
    // Tell the user where the files went, and what they were named
    std::cout
        << "Files '" << edge_data_filename
        << "', '" << node_names_filename
        << "' saved to " << output_path << std::endl;

    /*** import data ***/
    WikiSearch ws;
    // code stolen from austin
    // time the import
    std::cout << "Importing limited data..." << std::endl;
    auto startIMDAT = std::chrono::high_resolution_clock::now();
    ws.importData("../data/gendata/wiki-nodes.txt");
    auto stopIMDAT = std::chrono::high_resolution_clock::now();

    // calculate time
    auto durationIMDAT = std::chrono::duration_cast<std::chrono::microseconds>(stopIMDAT - startIMDAT);
    double IMDATseconds = double((durationIMDAT.count()) % 60000000) / 1000000;
    int IMDATminutes = (durationIMDAT.count()) / 60000000;
    std::cout << "Import took: " << IMDATminutes << " minutes and " << IMDATseconds << " seconds." << std::endl;

    std::cout << "Importing names..." << std::endl;
    ws.importNames("../data/wiki-names.txt");
    std::cout << "... Done" << std::endl << std::endl;

    /*** BC calc ***/
    auto bc = ws.betweennessCentrality();
    struct BCNode {
        int id;
        double betweenness;
        BCNode(std::pair<int,double> x): id(x.first), betweenness(x.second) {}
        bool operator<(BCNode other) const { return betweenness < other.betweenness; }
        BCNode(): id(0), betweenness(0.0) {}
    };
    std::vector<BCNode> as_vector(bc.begin(), bc.end());
    heap<BCNode> as_heap(as_vector);

    /*** write to file ***/
    std::string ofs_filename = "../outputs/betweenness_centrality/sorted/nodes" + std::to_string(num_nodes) + ".txt";
    std::ofstream ofs { ofs_filename };
    while (!as_heap.empty()) {
        auto node = as_heap.peek();
        auto id = node.id;
        auto betweenness = node.betweenness;
        as_heap.pop();
        ofs << id << "\t(" << ws.nameFromInt(id) << "):\t " << betweenness << std::endl;
    }

    std::cout << "written to " << ofs_filename << std::endl;

    return 0;
}