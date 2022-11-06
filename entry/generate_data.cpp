/**
 * @file generate_data.cpp
 *
 * Uses functions written in utils.h to generate shrunken
 * versions of the original topcats data, either so that
 * we can fit it in the GitHub or want quicker result
 * times during testing
 */

#include "utils.h"

#include <iostream>
#include <string>

using std::string;

int main(int argc, char *argv[])
{

    // There should only be two to four separate inputs
    if (argc < 2 || argc > 6)
    {
        std::cout << "USAGE: ./generate_data [num_nodes] [optional: path_to_output]  [optional: output_edge_data_filename] [optional: output_node_names_filename] [optional: output_category_data_filename]" << std::endl;
        return 1;
    }

    // Variable setup
    int num_nodes = atoi(argv[1]);
    string output_path = (argc >= 3 ? argv[2] : "../data/gendata");
    string edge_data_filename = (argc >= 4 ? argv[3] : "wiki-nodes.txt");
    string node_names_filename = (argc >= 5 ? argv[4] : "wiki-names.txt");
    string node_categories_filename = (argc >= 6 ? argv[5] : "wiki-categories.txt");

    // Perform shrinks on the topcats data based on user input
    shrinkEdgeData("../data/wiki-topcats.txt", output_path + "/" + edge_data_filename, num_nodes);
    shrinkNames("../data/wiki-topcats-page-names.txt", output_path + "/" + node_names_filename, num_nodes);
    shrinkCategories("../data/wiki-topcats-categories.txt", output_path + "/" + node_categories_filename, num_nodes);

    // Tell the user where the files went, and what they were named
    std::cout
        << "Files '" << edge_data_filename
        << "', '" << node_names_filename
        << "' and '" << node_categories_filename
        << "' saved to " << output_path << std::endl;

    return 0;
}