# The `./data` folder

Due to the files being larger than 25mB, [the data for this project must be downloaded from the source](http://snap.stanford.edu/data/wiki-topcats.html) and placed into this folder.

We have three datasets:

## `wiki-topcats.txt`
 
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

## `wiki-topcats-page-names.txt` 

A list of Wikipedia article IDs paired to their article name. Interpret as: 'key' has the name 'value'. We expect this dataset to be useful for user interface for knowing which article belongs to an ID. 

Preview (first five lines):
```
0 Chiasmal syndrome
1 Kleroterion
2 Pinakion
3 LyndonHochschildSerre spectral sequence
4 Zariski's main theorem
```

##  `wiki-topcats-categories.txt`

A list of Wikipedia categories and its corresponding list of associated IDs. Interpret as 'key' is the category for 'values'. Possibly fun for filtering.

Preview (first three lines, shortened):
```
Category:Buprestoidea; 301 302 303 304 305 306 307 308 [...]
Category:People_from_Worcester; 1056 1057 1058 1059 1060 [...]
Category:Skin_conditions_resulting_from_physical_factors; 971 973 1166 [...]
```