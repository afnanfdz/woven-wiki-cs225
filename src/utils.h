#pragma once

#include <fstream>
#include <vector>
#include <utility>
#include <string>

using std::ifstream;
using std::ofstream;
using std::pair;
using std::string;
using std::vector;

/***
 * @param file_dir: directory to the .txt file
 * @return a vector of directed edge relationships of numbered nodes
 **/
vector<pair<unsigned int, unsigned int>> importEdges(string file_dir);

/***
 * Takes edge data (int to int) and filters it to only contain
 * relations for nodes equal to or below the input max_idx.
 *
 * Does NOT assume the nodes are indexed in order, nor are without gaps.
 *
 * Within the scope of the CS225 project, we only expect this function to be used
 * on the topcats data.
 *
 * @param file_dir: Directory to the .txt file
 * @param file_out_dir: Directory to output the new file
 * @param new_size: The largest node index to allow
 *
 * @return Writes the file to `file_out_dir`
 */
void shrinkEdgeData(string file_dir, string file_out_dir, int max_idx);

/***
 * Takes node name data (int to string) and filters it to only contain
 * the names of nodes equal to or below the input max_idx
 *
 * Assumes the nodes are listed in increasing index number.
 *
 * Within the scope of the CS225 project, we only expect this function to be used
 * on the topcats data.
 *
 * @param file_dir: Directory to the .txt file
 * @param file_out_dir: Directory to output the new file
 * @param new_size: The largest node index to allow
 *
 * @return Writes the file to `file_out_dir`
 */
void shrinkNames(string file_dir, string file_out_dir, int max_idx);