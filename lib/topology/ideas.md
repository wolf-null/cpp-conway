### Performance ###
#### Neighbour traverse ####
Which one is faster?
* Dynamic ```_neighborCount<=MAX_NEIGHBOURS_```. Neighbor removal O(N).
* Dynamic count=```MAX_NEIGHBOURS_```. Neighbor removal O(1) -> nullptr.

### Conway ###
### Milestones towards the implementation ###
1. **Two-index Domain subtype based on static arrays?** Probably one shouldn't use a *Domain* for index organization. *Domain* is only for node initializing. The specialized index manager is to be created! So...

2. **Index**. Organizes indexing, random access and traverse (iteration) over Domain's nodes. Destructor of the Index doesn't affect the Domain or Nodes. Target:
   1. We need two types of access:
      1. Model access. *Use case*: generating of cell grids. Class: ```Taxicab2DIndex```
         * ```operator[i, j]``` for model access (for instance, padding or toroidal topology support)
           * Access to (i, j) if not itinialized causes initialization
         * ```.data[][]``` for direct access
         * ```neighborhood(i,j,r)``` for iterating neighbors of (i, j) 
         * (i, j) traverse iterator

      2. Direct access. Use case: fast traverse for node visiting. Class ```LinearIndex```

3. Taxicab generator over ```Taxicab2DIndex```. 
   * Connects 1-neighbours to each node using (i,j)-treverse 

4. Conway cell
   1. Has ```evaluate()``` method which calculates next stated based on ```.sumCache``` and ```.value()```

5. Evaluator (visitor)


### ValueTypes ###
#### HistoricalInt ####
1. Remembers N previous states.
2. ```.iteration``` is increased each time ```operator=(HistoricalInt)``` is called like y.t = x.t + 1
3. Implementation of ```operator=(&&HistoricalInt)``` is reasonable (but more like just for fun)
