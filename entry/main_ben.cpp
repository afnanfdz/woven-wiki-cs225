/**
 * @file main_ben.cpp
 */

#include "wikisearch.h"
#include "utils.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <chrono>

int main()
{
  WikiSearch ws;

  // small version
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

  std::ofstream ofs { "../outputs/betweenness_centrality/nodes10000.txt" };
  auto bc = ws.betweennessCentrality();
  std::pair<int, double> max = *bc.begin();
  for (auto p : bc) {
    int id = p.first;
    ofs << id << "\t(" << ws.nameFromInt(id) << ")\t:\t " << p.second << std::endl;
    if (p.second > max.second) {
      max = p;
    }
  }
  ofs << "max: " << max.first << "(" << ws.nameFromInt(max.first) << ") " << max.second << std::endl;
}