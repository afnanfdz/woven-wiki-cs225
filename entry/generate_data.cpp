#include "utils.h"

#include <iostream>
#include <string>

using std::string;

int main(int argc, char *argv[])
{
    if (argc < 2 || argc > 5)
    {
        std::cout << "USAGE: ./generate_data [num_nodes] [optional: path_to_output]  [optional: output_edge_data_filename] [optional: output_node_names_filename]" << std::endl;
        return 1;
    }

    int num_nodes = atoi(argv[1]);
    string output_path = (argc >= 3 ? argv[2] : "../data/gendata");
    string edge_data_filename = (argc >= 4 ? argv[3] : "wiki-nodes.txt");
    string node_names_filename = (argc >= 5 ? argv[4] : "wiki-names.txt");

    shrinkEdgeData("../data/wiki-topcats.txt", output_path + "/" + edge_data_filename, num_nodes);
    shrinkNames("../data/wiki-topcats-page-names.txt", output_path + "/" + node_names_filename, num_nodes);

    std::cout << "Files '" << edge_data_filename << "' and '" << node_names_filename << "' saved to " << output_path << std::endl;

    return 0;
}