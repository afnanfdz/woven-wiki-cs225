## Leading Question 
We have a dataset of Wikipedia articles, and all the articles they contain hyperlinks to. This gives us a directed node network of Wikipedia articles. What we wish to solve is: What is the minimum amount of link 'clicks' to get from article A to B? We wish to implement a shortest-path algorithm to solve this, and we wish to make said algorithm as efficient as possible, starting from the 'naive' Breadth-first search to the more nuanced algorithms.

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
We trust this dataset to be almost entirely unproblematic. According to the [source page](http://snap.stanford.edu/data/wiki-topcats.html), the articles in the set should only consist of strongly-connected components, so we don't believe we would find any 'uninteresting' articles with little to no inward or outward edges. If we do, we may remove them for being 'uninteresting'.

##### Data Storage
The data for article edges would be saved in our undirected edge graph implementation. The worst case for this is that every article has a link to all other articles (except itself). If every edge was 1 unit of space, then the worst case for $n$ articles would be $n (n-1)$ edges. We conclude that the Big-O for storing our data is $O(n^2)$.

As for how we represent the graph, we currently believe it's ideal to store a `map` of `<unsigned int, list<unsigned int>>`, i.e. an adjacency list.


## Graph Algorithms

Since our goals revolve around finding a shortest path from one node to another, we are looking to implement:

- For the traversal, the **Breadth-first Search**
- For the covered algorithms, **Djikstra's Algorithm** for finding a shortest path. We are open to considering the Floyd-Warshall if we find it is more suitable to our use case.
- For the complex/uncovered option, we are most likely considering the **A\* Search** as a natural continuation to Djikstra's. We have also considered Betweenness Centrality, as a fun and interesting option.

##### Function Inputs
To create the graph we believe it would be ideal to extract the edge data into a `vector` of `pair`s, where each `pair` represents an edge from `pair.first` to `pair.second`, which would then be the input of our graph class's constructor.

For the shortest-path function, our known inputs would be an `unsigned int` that represents a **starting** article ID, and another `unsigned int` of another article ID that would be our **destination**. 

##### Function Outputs
We wish to have the following outputs, in descending priority:
- At the very least, we can verify whether article A has a path to article B (the search function has found the destination.)
- If possible, we also wish to output the number of steps taken to reach article B. (the distance between two articles.)
- At best, we wish to print our shortest path, i.e. the sequence of Wikipedia articles traversed to reach article B.
- If it's somehow possible, we wish to verify that the output path was indeed the shortest path.

##### Function Efficiency
We understand a simple breadth-first search to be the most 'naive' implementation of this function, so the worst-case time performance for our function would be $O(V + E)$. We don't have a specific performance target yet, but we certainly hope as we attempt more nuanced algorithms we can achieve something better than $O(V + E)$ worst-case. As for memory, we have not figured this out as not only we are performing a search, we are also storing paths as the search happens, which takes up more memory. Our memory performance hinges strongly on how we choose to store and represent the paths taken during search.

## Timeline

By end of Week 1 (Nov 4): Get the proposal written to understand what's ahead of us; choose the algorithms we want to implement; possibly begin implementing importing data into a graph structure

By end of Week 2 (Nov 13): Conceptualize a method to store and track search paths; implement breadth-first search with path tracking

We won't consider the fall break as an official 'week' for work plans, but some of the group expects to get a lot done within that time.

By end of Week 4 (Nov 27): Implement a shortest-path algorithm (Djikstra's or Floyd-Warshall)

By end of Week 5 (Dec 4): Implement a 'complex' algorithm for better searching or something else that can be done with this data

By Deadline (Dec 8): Submission!
