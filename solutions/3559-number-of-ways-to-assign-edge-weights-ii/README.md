# [3559. Number of Ways to Assign Edge Weights II](https://leetcode.com/problems/number-of-ways-to-assign-edge-weights-ii/)

**Difficulty:** `Hard`  
**Topics:** [Trees & BST](../../topics/trees.md), [Math & Geometry](../../topics/math-and-geometry.md), [Graphs](../../topics/graphs.md)

---

## 📌 Problem Statement

There is an undirected tree with $n$ nodes labeled from $1$ to $n$, rooted at node $1$. The tree is represented by `edges` of length $n - 1$, where `edges[i] = [ui, vi]`.

Initially, all edges have weight 0. You must assign each edge a weight of either `1` or `2`.

The cost of a path between any two nodes $u$ and $v$ is the total weight of all edges on the unique path connecting them.

Given a 2D array `queries` where `queries[i] = [ui, vi]`:
- Determine the number of ways to assign weights to edges on the path such that the cost of the path between $u_i$ and $v_i$ is **odd**.
- Note: Disregard all edges not on the path between $u_i$ and $v_i$.

Return an array `answer` modulo $10^9 + 7$.

### Example 1:
```
Input: edges = [[1,2]], queries = [[1,1],[1,2]]
Output: [0,1]
Explanation:
- Query [1,1]: 0 edges on path -> cost = 0 (even) -> 0 valid ways.
- Query [1,2]: 1 edge on path -> assign 1 -> cost = 1 (odd) -> 1 valid way.
```

### Example 2:
```
Input: edges = [[1,2],[1,3],[3,4],[3,5]], queries = [[1,4],[3,4],[2,5]]
Output: [2,1,4]
Explanation:
- Query [1,4]: Path length 2 (1->3, 3->4) -> (1,2) or (2,1) -> 2 ways.
- Query [3,4]: Path length 1 (3->4) -> (1) -> 1 way.
- Query [2,5]: Path length 3 (2->1, 1->3, 3->5) -> (1,2,2), (2,1,2), (2,2,1), (1,1,1) -> 4 ways.
```

### Constraints:
- $2 \le n \le 10^5$
- `edges.length == n - 1`
- $1 \le \text{queries.length} \le 10^5$
- $1 \le u_i, v_i \le n$
- `edges` represents a valid tree.

---

## 💡 Intuition & Approach

### 1. Parity Combinatorics
Let $d$ be the number of edges on the path between $u$ and $v$:
- Each edge can be assigned weight 1 (odd) or 2 (even).
- An assignment has an odd sum if and only if an odd number of edges are assigned weight 1.
- Total valid assignments:
  $$\sum_{k \text{ odd}} \binom{d}{k} = 2^{d - 1} \quad (\text{for } d \ge 1)$$
- If $d = 0$ ($u = v$), there are no edges, so the sum is 0 (even), yielding **0** ways.

### 2. Distance in a Tree via Lowest Common Ancestor (LCA)
The path length $d$ between nodes $u$ and $v$ is:
$$d = \text{depth}[u] + \text{depth}[v] - 2 \times \text{depth}[\text{LCA}(u, v)]$$

We use **Binary Lifting** to precompute $2^k$-th ancestors:
- Precomputation time: $\mathcal{O}(N \log N)$.
- LCA query time: $\mathcal{O}(\log N)$.
- Path distance calculation and answer lookup: $\mathcal{O}(1)$.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}((N + Q) \log N)$
  - BFS traversal + Binary lifting jump table: $\mathcal{O}(N \log N)$.
  - Processing $Q$ queries: $\mathcal{O}(Q \log N)$.
  - Total runtime $\approx 2 \times 10^5 \log_2(10^5) \approx 3.4 \times 10^6$ operations ($< 45$ ms in C++).
- **Space Complexity:** $\mathcal{O}(N \log N)$
  - Binary lifting ancestor table of size $18 \times (N + 1)$.

---

## 🔍 Edge Cases Considered

- **Query $[u, u]$ ($d = 0$)**: Evaluates to 0 ways (cost is 0, which is even).
- **Single Edge Path ($d = 1$)**: Returns $2^{1-1} = 1$ way.
- **Large Tree ($N = 10^5, Q = 10^5$)**: Handled optimally via binary lifting and precomputed powers of 2 modulo $10^9 + 7$.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
