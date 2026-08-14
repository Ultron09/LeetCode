# [882. Reachable Nodes In Subdivided Graph](https://leetcode.com/problems/reachable-nodes-in-subdivided-graph/)

**Difficulty:** `Hard`  
**Topics:** [Graphs](../../topics/graphs.md)

---

## 📌 Problem Statement

You are given an undirected graph (the "original graph") with `n` nodes labeled from `0` to `n - 1`. You decide to subdivide each edge in the graph into a chain of nodes, with the number of new nodes varying between each edge.

The graph is given as a 2D array of edges where `edges[i] = [ui, vi, cnti]` indicates that there is an edge between nodes `ui` and `vi` in the original graph, and `cnti` is the total number of new nodes that you will subdivide the edge into. Note that `cnti == 0` means you will not subdivide the edge.

To subdivide the edge `[ui, vi]`, replace it with `(cnti + 1)` new edges and `cnti` new nodes. The new nodes are `x1, x2, ..., xcnti`, and the new edges are `[ui, x1], [x1, x2], [x2, x3], ..., [xcnti-1, xcnti], [xcnti, vi]`.

In this new graph, you want to know how many nodes are reachable from the node `0`, where a node is reachable if the distance is `maxMoves` or less.

Given the original graph and `maxMoves`, return the number of nodes that are reachable from node `0` in the new graph.

### Example 1:
```
Input: edges = [[0,1,10],[0,2,1],[1,2,2]], maxMoves = 6, n = 3
Output: 13
Explanation: The nodes that are reachable are node 0, node 2, and 11 subdivided nodes.
```

### Constraints:
- `0 <= edges.length <= min(n * (n - 1) / 2, 10^4)`
- `edges[i].length == 3`
- `0 <= ui < vi < n`
- There are no multiple edges in the graph.
- `0 <= cnti <= 10^4`
- `0 <= maxMoves <= 10^9`
- `1 <= n <= 3000`

---

## 💡 Intuition & Approach

1. **Dijkstra's Algorithm on the Original Graph**:
   - Despite the subdivision of edges into many nodes, we can treat each subdivided edge `(u, v)` with `cnt` new nodes as a single edge of weight `cnt + 1`.
   - The shortest path to reach an original node remains purely dependent on these edge weights. Therefore, we can run Dijkstra's Algorithm starting from node `0` on the original nodes to compute the shortest distance `dist[u]` for every original node `u`.

2. **Counting Reachable Original Nodes**:
   - After Dijkstra completes, any original node `u` with `dist[u] <= maxMoves` is completely reachable. We increment our reachable count for each such node.

3. **Counting Reachable Subdivided Nodes**:
   - For every edge `(u, v)` with `cnt` subdivided nodes, we can travel onto these new nodes from both `u` and `v`.
   - The number of subdivided nodes we can reach walking from `u` into the edge is `max(0, maxMoves - dist[u])`.
   - The number of subdivided nodes we can reach walking from `v` into the edge is `max(0, maxMoves - dist[v])`.
   - The total reachable new nodes on this specific edge is the sum of those two values, capped at `cnt` to ensure we do not double-count overlapping reaches.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(E \log V)$ — Running Dijkstra's algorithm where $E$ is the number of edges (up to $10^4$) and $V$ is the number of nodes (up to $3000$).
- **Space Complexity:** $\mathcal{O}(E + V)$ — Storing the adjacency list and distance array. Priority Queue also requires at most $\mathcal{O}(E)$ space.

---

## 🔍 Edge Cases Considered

- Unreachable nodes: Dijkstra skips updating distances exceeding `maxMoves` effectively. Original nodes completely disconnected from node `0` will simply have an initial huge distance (e.g., `2e9`) and are filtered out correctly.
- Partial reach onto an edge from both ends: Summation `reachable_from_u + reachable_from_v` handles the bounds gracefully. Capping this summation at `cnt` ensures we don't accidentally overcount if `maxMoves` is huge.
- `maxMoves = 0`: Node `0` is still reachable. `max(0, maxMoves - dist[u])` elegantly covers these edge cases since distances will be $>0$ for all other nodes, making reach onto subdivided nodes exactly $0$.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
