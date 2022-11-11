## Leading Question 
We have a dataset of Wikipedia articles, and all the articles they contain hyperlinks to. This gives us a directed vertex network of Wikipedia articles. What we wish to solve is: What is the minimum amount of link 'clicks' to get from article A to B? We wish to implement a shortest-path algorithm to solve this, and we wish to make said algorithm as efficient as possible, starting from the 'naive' Breadth-first search to the more nuanced algorithms.

ADDITIONAL THOUGHT: Motivated from the lectures on Monte Carlo simulation, we also find it interesting to attempt to answer: "What is the average path length from one Wikipedia article to another?" We may solve this by utilizing our search algorithms, alongside random start- and end-vertex selection.

## Dataset Acquisition and Processing

##### Data Format
We are using the [topcats](http://snap.stanford.edu/data/wiki-topcats.html) dataset from the Stanford Network Analysis Project (SNAP). The largest dataset is 400mB and all must reside on our devices locally. If the dataset *must* be present in the Github then we will generate and push a shortened version of this dataset. There are three files from this source:

###### `wiki-topcats.txt`
 
A list of pairs of Wikipedia article IDs. Interpret each line as as: 'key' has a link to 'value'. This means we're working with directed edges. This dataset will be what we use to construct our graph(s).
  
Preview (first ten lines):

```
0 10772
1 2
1 170193
1 598775
2 1
3 1100919
3 1101709
3 1101724
3 1101808
3 1101827
```

###### `wiki-topcats-page-names.txt` 

A list of Wikipedia article IDs paired to their article name. Interpret as: 'key' has the name 'value'. We expect this dataset to be useful for user interface for knowing which article belongs to an ID. 

Preview (first five lines):

```
0 Chiasmal syndrome
1 Kleroterion
2 Pinakion
3 LyndonHochschildSerre spectral sequence
4 Zariski's main theorem
```

######  `wiki-topcats-categories.txt`

A list of Wikipedia categories and its corresponding list of associated IDs. Interpret as 'key' is the category for 'values'. Possibly fun for filtering.

Preview (first three lines, shortened):

```
Category:Buprestoidea; 301 302 303 304 305 306 307 308 [...]
Category:People_from_Worcester; 1056 1057 1058 1059 1060 [...]
Category:Skin_conditions_resulting_from_physical_factors; 971 973 1166 [...]
```

##### Data Correction

| Possibile "Problems" | Source | Method of Detection | Method of Correction | Worth Removing? |
| --- | :--- | --- | --- | --- |
The graph is disconnected | Using a reduced dataset (we lessen the range of nodes because the original dataset is too large); also generally highly possible given we're using directed edges. | Implement a DisjointedSet class; graph is disconnected if number of DSet roots $>1$ | Choose a 'primary' graph; delete all vertices belonging to the other(s) | Probably not; search algorithms can simply return a 'not found' status. Possibly required for Betweenness Centrality though
A vertex is childless | Corresponding Wikipedia article has no outgoing links | Iterate through all vertices; childless vertex has empty list of edges | Remove vertex from data structure | No. It's simply a "dead end" and still searchable as a destination.
A vertex is an orphan | No other Wikipedia article has links to this article | Starting at each vertex, mark all its unfound children (but NOT itself) as 'found'. Unfound vertices are orphans | Remove vertex from data structure | No. It is still a valid starting point.
A vertex is a childless orphan | Both of the above | Satisfies both above conditions | Remove vertex from data structure | Yes. It cannot be found and it cannot be a starting point. It's as "uninteresting" for this project as a piece of data can get.


##### Data Storage
The data for article edges would be saved in our undirected edge graph implementation. The worst case for this is that every article has a link to all other articles (except itself). If every edge was 1 unit of space, then the worst case for $n$ articles would be $n (n-1)$ edges. We conclude that the Big-O for storing our data is $O(n^2)$.

As for how we represent the graph of directed, unweighted edges and vertices, we currently believe it's ideal to store a `unordered_map` of `<Vertex, list<Vertex>>`, i.e. an adjacency list.


## Graph Algorithms

Since our goals revolve around finding a shortest path from one vertex to another, we are looking to implement:

| Algorithm | Description | Input | Output | Worst-Case Time Efficiency | Worst-Case Space Efficiency | Information Sources
| --- | --- | --- | --- | --- | --- | --- |
| Breadth-First Search | Simple BFS | Beginning & destination vertex | The shortest path, or its length, or its existence | Worst case, all vertices and edges are visited once: $O(\|V\| + \|E\|)$ | All the vertices have been committed to memory: $O(\|V\|)$ | [Wikipedia: BFS](https://en.wikipedia.org/wiki/Breadth-first_search)
| Iterative Deepening Depth-First Search | Same time complexity as BFS but more space-efficient | Beginning & destination vertex | The shortest path, or its length, or its existence | $O(\|V\|+ \|E\|)$ | The maximum depth of the graph, $O(d)$ | [Wikipedia: IDDFS](https://en.wikipedia.org/wiki/Iterative_deepening_depth-first_search)
| Betweenness Centrality | A measure of centrality of vertices, based on how many shortest-paths of vertex pairs pass through them | A whole graph | A graph or at least a list of Wikipedia articles and their measure of betweenness centrality | $O(\|V\|\|E\|)$ using Brandes's algorithm with unweighted graph, or, ADaptive Algorithm for Betweenness via Random Approximation (KADABRA) gives $\|E\|^{1/2 + O(1)}$ time complexity.| Either the memory required to store information for each vertex, $O(\|V\|)$, or the worst-case of our best search algorithm ($O(d)$ if IDDFS) |[Wikipedia: Betweenness Centrality](https://en.wikipedia.org/wiki/Betweenness_centrality), [Brandes's Algorithm](http://snap.stanford.edu/class/cs224w-readings/brandes01centrality.pdf), [Brandes's Algorithm alternative reference](https://www.cl.cam.ac.uk/teaching/1617/MLRD/handbook/brandes.pdf), [KADABRA](https://drops.dagstuhl.de/opus/volltexte/2016/6371/)

### Other Choices

| Algorithm | Description | Input | Output | Worst-Case Time Efficiency | Worst-Case Space Efficiency | Information Sources
| --- | --- | --- | --- | --- | --- | --- |
Djikstra's Algorithm | We *can* add weights to the graph. Let's say we wanted higher edge weightages for vertices of the same Category, so that our search tries to make minimal category jumps to its destination. | Beginning & destination vertex | The shortest path, the path length, or its existence | $O(\|E\| + \|V\|\log\|V\|)$  | All the vertices have been committed to memory: $O(\|V\|)$ | [Wikipedia: Djikstra's Algorithm](https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm)


## Timeline

By end of Week 1 (Nov 4): Get the proposal written to understand what's ahead of us; choose the algorithms we want to implement; possibly begin implementing importing data into a graph structure

By end of Week 2 (Nov 13): Conceptualize a method to store and track search paths; implement breadth-first search

We won't consider the fall break as an official 'week' for work plans, but some of the group expects to get a lot done within that time.

By end of Week 4 (Nov 27): Implement IDDFS and Betweenness Centrality

By end of Week 5 (Dec 4): Begin working on the presentation

By Deadline (Dec 8): Submission!
