### Performance ###
#### Neighbour traverse ####
Which one is faster?
* Dynamic ```_neighborCount<=maxNeighbours```. Neighbor removal O(N).
* Dynamic count=```maxNeighbours```. Neighbor removal O(1) -> nullptr.

### Conway ###
### Milestones towards the implementation ###
1. **Two-index Domain subtype based on static arrays?** Probably one shouldn't use a *Domain* for index organization. *Domain* is only for node initializing. The specialized index manager is to be created! So...

2. **Index**. Organizes indexing, random access and traverse (iteration) over Domain's nodes. Destructor of the Index doesn't affect the Domain or Nodes. Target:
   1. We need two types of access:
      1. Model access. *Use case*: generating of cell grids. Class: ```Taxicab2DIndex```
         * ```operator[i, j]``` for model access (for instance, padding or toroidal topology support)
         * ```.data[][]``` for direct access
         * ```neighborhood(i,j,r)``` for iterating neighbors of (i, j)

      2. Direct access. Use case: fast traverse for node visiting. Class ```LinearIndex```

3. Taxicab generator over ```Taxicab2DIndex```. 

4. Conway cell

5. Evaluator (visitor)



