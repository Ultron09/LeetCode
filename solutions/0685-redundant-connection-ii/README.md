# [685. Redundant Connection II](https://leetcode.com/problems/redundant-connection-ii/)

**Difficulty:** `Hard`  
**Topics:** [Union Find](../../topics/graphs.md), [Graph](../../topics/graphs.md), [Tree](../../topics/trees.md)

---

## 📌 Problem Statement

In this problem, a **rooted tree** is a directed graph such that:
1. There is exactly one node (the root) for which all other nodes are descendants of this node.
2. Every node has exactly one parent, except for the root node which has no parents.

The given input is a directed graph that started as a rooted tree with $n$ nodes (values $1 \dots n$), with **one additional directed edge added**.

The graph is represented as a 2D array `edges` where `edges[i] = [ui, vi]` represents a directed edge from $u_i$ to $v_i$.

Return an edge that can be removed so that the resulting graph is a rooted tree of $n$ nodes. If there are multiple answers, return the answer that occurs **last** in the given 2D array.

### Example 1:
```
Input: edges = [[1,2],[1,3],[2,3]]
Output: [2,3]
```

### Example 2:
```
Input: edges = [[1,2],[2,3],[3,4],[4,1],[1,5]]
Output: [4,1]
```

### Constraints:
- `n == edges.length`
- $3 \le n \le 1000$
- `edges[i].length == 2`
- $1 \le u_i, v_i \le n$
- $u_i \neq v_i$

---

## 💡 Intuition & Approach

### 1. Directed Rooted Tree Invariants
In a valid directed rooted tree with $N$ vertices:
- Exactly $N - 1$ edges exist.
- In-degree of root is $0$, and in-degree of all other nodes is $1$.
- No directed cycles exist.

Adding an extra edge produces one of three structural anomalies:
1. **Case 1: A node has in-degree 2, and no cycle is formed with the first edge.**
   - Candidate edges to $v$ are `cand1` (earlier) and `cand2` (later).
   - Removing `cand2` restores in-degrees to 1 and leaves the graph cycle-free.
2. **Case 2: A node has in-degree 2, and `cand1` is part of a directed cycle.**
   - Skipping `cand2` still leaves a cycle detected by Union-Find.
   - Therefore, `cand1` must be removed to break both the cycle and the in-degree-2 violation.
3. **Case 3: No node has in-degree 2 (all nodes have in-degree 1), but a directed cycle exists.**
   - Exactly one directed cycle exists.
   - The edge that closes the cycle during Union-Find traversal is the redundant edge.

### 2. DSU Algorithm Workflow
1. Scan `edges` to check for any node $v$ with two incoming edges:
   - Record `cand1 = [parent[v], v]` and `cand2 = [u, v]`.
2. Run Disjoint Set Union (DSU) across all edges, **skipping `cand2`**:
   - If `dsu.unite(u, v)` fails (cycle detected):
     - If `cand1` exists, return `cand1` (Case 2).
     - Otherwise, return `[u, v]` (Case 3).
3. If no cycle is encountered after processing all edges, return `cand2` (Case 1).

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N \cdot \alpha(N))$
  - Single pass to detect in-degree 2 nodes: $\mathcal{O}(N)$.
  - DSU operations with path compression take nearly linear $\mathcal{O}(N \cdot \alpha(N))$ time.
- **Space Complexity:** $\mathcal{O}(N)$
  - Storage for parent array and DSU disjoint sets.

---

## 🔍 Edge Cases Considered

- **Cycle without in-degree 2 node**: Example 2 (`[4, 1]` forms a pure directed loop).
- **Two parents where second edge is culprit**: Example 1 (`[2, 3]` creates in-degree 2 without cycle).
- **Two parents where first edge is in the loop**: `[[2,1],[3,1],[4,2],[1,4]]` $\to `[2, 1]`$.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
