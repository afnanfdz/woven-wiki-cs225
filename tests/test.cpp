#include <catch2/catch_test_macros.hpp>

// stl imports
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <list>
#include <array>
#include <utility>

using std::array;
using std::ifstream;
using std::list;
using std::pair;
using std::string;
using std::stringstream;
using std::unordered_map;
using std::vector;

// src imports
#include "wikisearch.h"

///////////////////////////////////////////////////
//////////////////////////////////////////////////
//////////////////////////////////////////////////

/** DATA & CONSTS */

/**
 * Files should be in /tests,
 * and has a SOLUTIONS_ counterpart
 */
vector<string> testfiles{
    "list",
    "dl_list",
    "cycles",
    "threepaths",
    "twosets"};

///////////////////////////////////////////////////
//////////////////////////////////////////////////
//////////////////////////////////////////////////

/** UTILITIES FOR TESTS */

/**
 * @author Vuc
 * Iterates over two vectors of 'article' / vertex paths
 * Asserts they are of the same size. Asserts the contents are identical.
 */
void comparePaths(const vector<int> &path_1, const vector<int> &path_2)
{
    REQUIRE(path_1.size() == path_2.size());

    for (size_t idx = 0; idx < path_1.size(); idx++)
    {
        REQUIRE(path_1.at(idx) == path_2.at(idx));
    }
}

/**
 * @author Vuc
 * Imports the handwritten true shortest path for a given graph.
 * Assumes the handwritten true shottest path was... correctly written.
 *
 * @returns An unordered map of solutions.
 * The key contains the begin/goal inputs,
 * The value contains the correct shortest path.
 */

unordered_map<string, string> readSolutions(string file_dir)
{
    unordered_map<string, string> result;

    ifstream file;
    file.open(file_dir);

    if (file.is_open())
    {
        string line_1;
        string line_2;
        while (getline(file, line_1) && getline(file, line_2))
        {
            result.insert({line_1, line_2});
        }
    }

    return result;
}

/**
 * @author Vuc
 *
 * Takes a map of solutions and tests it against our implementations
 * @param file_name Name of the .txt data file.
 * Assumed to have a SOLUTIONS_ counterpart.
 * Assumed to be in the ./tests folder.
 */
void compareSolutionBFS(string file_name)
{
    const unordered_map<string, string> &sols = readSolutions("../tests/SOLUTIONS_" + file_name + ".txt");
    WikiSearch ws;
    ws.importData("../tests/" + file_name + ".txt");

    for (const pair<const string, string> &p : sols)
    {
        stringstream ss_inputs(p.first);
        int start;
        int goal;
        ss_inputs >> start >> goal;

        stringstream ss_path(p.second);
        vector<int> solution;
        if (p.second != "EMPTY")
        {
            int loc;
            while (ss_path >> loc)
                solution.push_back(loc);
        }

        // std::cout << "Inputs: " << start << ", " << goal << std::endl
        //           << "Solution: [ ";

        // for (int i : solution)
        //     std::cout << i << ", ";
        // std::cout << "]" << std::endl
        //           << std::endl;

        vector<int> implementation_solution = ws.shortestPathBFS(start, goal);
        comparePaths(solution, implementation_solution);
    }
}

/** END OF TEST UTILITIES */

//////////////////////////////////////////////////
//////////////////////////////////////////////////
//////////////////////////////////////////////////

/** TEST CASES */

TEST_CASE("Example Test", "[tag]")
{
    REQUIRE(true);
}

TEST_CASE("Correct Shortest Paths (BFS)", "[correctBFS]")
{
    for (string filename : testfiles)
    {
        compareSolutionBFS(filename);
    }
}

/** END OF TEST CASES */
///////////////////////////////////////////////////
//////////////////////////////////////////////////
//////////////////////////////////////////////////