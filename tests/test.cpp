#include <catch2/catch_test_macros.hpp>

// stl imports
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <list>

using std::ifstream;
using std::list;
using std::string;
using std::stringstream;
using std::unordered_map;
using std::vector;

// src imports

///////////////////////////////////////////////////
//////////////////////////////////////////////////
//////////////////////////////////////////////////

/** UTILITIES FOR TESTS */

/**
 * @author Vuc
 * Imports the handwritten true shortest path for a given graph.
 * Assumes the handwritten true shottest path was... correctly written.
 */
vector<int> readSolutionPath(string file_dir)
{
    ifstream file;
    file.open(file_dir);

    stringstream ss;

    return vector<int>();
}

/**
 * @author Vuc
 * Iterates over two vectors of 'article' / vertex paths
 * Asserts they are of the same size. Asserts the contents are identical.
 */
void comparePaths(const vector<int> &path_1, const vector<int> &path_2)
{
    REQUIRE(path_1.size() == path_2.size());

    for (size_t idx = 0; i < path_1.size(); i++)
    {
        REQUIRE(path_1.at(idx) == path_2.at(idx));
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

TEST_CASE("Correct Shortest Paths", "[correctShortestPaths]")
{
    REQUIRE(true);
}

/** END OF TEST CASES */
///////////////////////////////////////////////////
//////////////////////////////////////////////////
//////////////////////////////////////////////////