/*
 *
 * 2. **Index**. Organizes indexing, random access and traverse (iteration) over Domain's nodes. Destructor of the Index doesn't affect the Domain or Nodes. Target:
   1. We need two types of access:
      1. Model access. *Use case*: generating of cell grids. Class: ```Taxicab2DIndex```
         * ```operator[i, j]``` for model access (for instance, padding or toroidal topology support)
           * Access to (i, j) if not itinialized causes initialization
         * ```.data[][]``` for direct access
         * ```neighborhood(i,j,r)``` for iterating neighbors of (i, j)
         * (i, j) traverse iterator

      2. Direct access. Use case: fast traverse for node visiting. Class ```LinearIndex```
 */

#include "topology/node.h"
#include "topology/domain.h"
#include "topology/summation_node.cpp"

