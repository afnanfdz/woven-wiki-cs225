# WOVEN WIKIS 

Our project is about getting from article A to article B with as few steps as possible, and revealing the significance of each Wikipedia article as a step in shortest paths.

Wikipedia articles have outgoing links to other Wikipedia articles. We can express this network as a graph with directed and (in our case) unweighted edges.

We have implemented **Breadth-First Search** and **Iterative Deepening Depth-First Search** as a means of finding the shortest path between two articles. Both have the same theoretical running time, but IDDFS has an improved memory performance.

We have also implemented the calculation of the **Betweenness Centrality** of Wikipedia articles via Brandes's algorithm, to show how often a given Wikipedia article appears in all possible shortest paths between all nodes.

## Datasets

[The data for this project can be obtained here](http://snap.stanford.edu/data/wiki-topcats.html) and should be extracted into the `./data` folder.

## Using our Functions

The entryfile `entry/main_moss.cpp` contains the interface for selecting a starting and ending Wikipedia article and finding the shortest path between them. It uses both DFS and IDDFS, compares their timings, and prints the shortest path both have found (which should be the same almost all of the time). It is made to be as user-friendly as possible and makes selecting Wikipedia articles easier. Using the full dataset will require time to import all the data, while using the shrunk dataset pre-existing in the `/data` folder may yield failed searches more frequently, as that graph is not fully-connected.