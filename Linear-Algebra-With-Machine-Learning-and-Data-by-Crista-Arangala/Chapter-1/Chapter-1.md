# Chapter 1
### Chapter 1.1
---
#### Terminology

- Degree of a vertex
    - number of incident edges 
        - where incident edges refers to an edge that connects two vertices
- Loop
    - An edge that only has one endpoint (can be a property of a graph)
    - **Beware** that this adds 2 to the degree of a vertex 
- Subgraph
    - a subset of a graph with the relevant vertices/edges
- Adjacency Matrix `S = AA^T`
    - Matrix with row/col corresponding to two vertices. 
        - 1 if adjacent else 0
    - If undirected, symmetric
- Path
    - Sequence of edges that link a pair of vertices
- Connected graph
    - A graph where there is a path between every pair of vertices
- Tree graph
    - Connected but no path back to the same vertex
- In-degree
    - numbr of edges going into a vertex
    - outdegree is the same but out

#### Beyond
- Handshaking Theorem
    - Basically says that the sum of the degree of each vertex is just double the number of edges
        - think abt how if there's an undirected edge between two vertices, they both have in-degree++
- Gramian Matrix
    - Useful tool in analysing relationships between vertices
        - Main diagonal shows total # adjacent vertices
        - Other entries tell you how many shared neighbours between vertex i and vertex j
    - Application found in analysing a subgroup of criminals to find the larger group

---
### Chapter 1.2


