#include "wikisearch.h"

#include <queue>
#include <stack>
#include <vector>
#include <iostream>

unordered_map<int, double> WikiSearch::betweennessCentrality() const
{
  unordered_map<int, double> betweenness_centrality;
  for (auto pair : getGraph()) {
    betweenness_centrality[pair.first] = 0;
  }
  auto num_nodes = betweenness_centrality.size();

  // loop through start nodes
  for (auto pair : betweenness_centrality) {
    int start = pair.first;
    
    unordered_map<int, std::list<int>> predecessors;

    unordered_map<int, int> num_paths;
    num_paths[start] = 1;
    
    unordered_map<int, int> dist;
    for (auto pair : getGraph()) {
      int vertex = pair.first;
      dist[vertex] = -1;
    }
    dist[start] = 0;

    std::stack<int> stack;
    // bfs
    std::queue<int> queue;
    queue.push(start);
    while (!queue.empty()) {
      int v = queue.front();
      queue.pop();
      stack.push(v);
      for (int w : getAdjacent(v)) {
        if (dist[w] == -1) {
          dist[w] = 1 + dist[v];
          queue.push(w);
        }
        if (dist[w] == dist[v] + 1) {
          num_paths[w] += num_paths.at(v);
          predecessors[w].push_front(v);
        }
      }
    }

    // update cb
    unordered_map<int, double> delta;
    for (auto pair : getGraph()) {
      delta[pair.first] = 0.0;
    }
    while (!stack.empty()) {
      int w = stack.top();
      stack.pop();

      for (int v : predecessors[w]) {
        delta[v] += (static_cast<double>(num_paths[v]) / num_paths[w]) * (1 + delta[w]);
        if (w != start) {
          betweenness_centrality[w] += delta[w];
        }
      }
    }
  } // for start
  
  return betweenness_centrality;
}