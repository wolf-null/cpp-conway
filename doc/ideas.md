### Performance ###
#### Neighbour traverse ####
Which one is faster?
* Dynamic ```neighbour_count_<=MAX_NEIGHBOURS_```. Neighbor removal O(N).
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


### Arch ###
#### TopologyNodeStructure ####
Probably not all nodes has value.
*Solutions for traversing nodes:*
  1. Reserve value anyway. Set it to zero (could cause arithmetic problems when "zero is not zero")
  2. Add compile-time constant property ```.has_value```  for ```Node``` 
  3. Inherit ```TopologyNodeWithValue``` from ```Node``` and use ```std::derived_from``` during indexing

*Bad arch*
Having non-abstract base interface class indicates current solution (template derived from interface) to be bad formed.
Question: why do we need that abstract interface at the moment?
Answer: To build ```NodeDomain``` class. In particular: having NodeType explicitly allows it to declare 
Objection: 
   - ```NodeDomain``` could probably build multiple types of ```Node```s and inheritors.
   - But all it needs a-priori is a specific interface
   - But the return type of the interface is not fixed
   - Actually all NodeDomain needs is access to constructor and destructor

...

Okay. Why did i made NodeDomain for real?
1. For generating unique ID for each Node in the domain
(type of node doesn't matter). 
2. Ability to hold and pass the bunch of nodes in a system to some fuction
3. A thing which guarantees lifetime for all nodes at leas not less than that thing's lifetime
4. Simultaneous memory cleanup (deletion) from one point

Propositions:
- All destructors in C++ has no parameters. Polymorphism allows to invoke destructor of base (abstract) classwithout
knowing certain class of implementation. It also allows to store vector of a base class only.
- Setting node id requires only one method: set id
- Creation of a node implies having direct access to NodeDomain. So node creation is possible only if domain instance is accessible from the "creation point"
- Overloading Node with NodeDomain is not a good idea because of template args overcomplication.

Conclusion:
- Nodes are inherited from abstract class ```AbstractNode``` which has _id property, constructor and destructor (non-virtual).
- ```NodeDomain``` has method const int register_id(```AbstractNode&&```) which saves it into own array, sets the id and returns a pointer to registred object
Two scenarios:
1. ConcreteTopologyNode constructor receives NodeDomain as an argument. It then reqiest an ID for itself by ```register_id(this)```
   - Possible problem: nothing guarantees lifetime of ConcreteTopologyNodeInstance 
2. ConcreteTopologyNode constructor doesn't receive NodeDomain, but then TopologyNodeDomainInstance.register_id(&&ConcreteTopologyNodeInstance)
   - Seems better

Anyway i can make them both!



