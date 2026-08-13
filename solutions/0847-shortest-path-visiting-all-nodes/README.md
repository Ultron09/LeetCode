# [847. Shortest Path Visiting All Nodes](https://leetcode.com/problems/shortest-path-visiting-all-nodes/)

**Difficulty:** `Hard`  
**Topics:** [Graphs](../../topics/graphs.md), Breadth-First Search, Bit Manipulation, Dynamic Programming

---

## 📌 Problem Statement

You have an undirected, connected graph of `n` nodes labeled from `0` to `n - 1`. You are given an array `graph` where `graph[i]` is a list of all the nodes connected with node `i` by an edge.

Return the length of the shortest path that visits every node. You may start and stop at any node, you may revisit nodes multiple times, and you may reuse edges.

### Example 1:
```
Input: graph = [[1,2,3],[0],[0],[0]]
Output: 4
Explanation: One possible path is [1,0,2,0,3]
```

### Example 2:
```
Input: graph = [[1],[0,2,4],[1,3,4],[2],[1,2]]
Output: 4
Explanation: One possible path is [0,1,4,2,3]
```

### Constraints:
- `n == graph.length`
- `1 <= n <= 12`
- `0 <= graph[i].length < n`
- `graph[i]` does not contain `i`.
- If `graph[a]` contains `b`, then `graph[b]` contains `a`.
- The input graph is always connected.

---

## 💡 Intuition & Approach

Because $N \le 12$, this is a classic scenario for using a **Bitmask** to represent visited states. 

A standard BFS on a graph only needs to track `visited[node]`. But since we are allowed to revisit nodes and edges, the state is no longer just "where am I?", but "where am I AND what other nodes have I already visited?".

We define a state as `(current_node, visited_mask)`:
- `current_node` ranges from $0$ to $N - 1$.
- `visited_mask` is an integer where the $i$-th bit is `1` if node $i$ has been visited, and `0` otherwise. It ranges from $0$ to $2^N - 1$.

**Algorithm:**
1. **Initialization:** We can start the path at any node. Thus, we enqueue all states `(i, 1 << i)` with an initial distance of `0`. We also mark these states as visited in a boolean matrix `visited[i][1 << i]`.
2. **BFS Traversal:** We pop the front state `(u, mask, dist)`. We iterate through all neighbors `v` of `u`.
3. **Transition:** For each neighbor `v`, the new mask becomes `nextMask = mask | (1 << v)`. 
   - If `nextMask` equals $(1 \ll N) - 1$ (which means all bits from $0$ to $N-1$ are `1`), we have visited all nodes and can immediately return `dist + 1`.
   - Otherwise, if we haven't seen the state `(v, nextMask)` before, we mark it as seen and push it into the queue with distance `dist + 1`.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N \cdot 2^N)$ — The state space has $N \cdot 2^N$ possible states. In the worst case, we process each state once, and traversing the edges takes proportional time. For $N = 12$, $12 \cdot 4096 = 49,152$ operations, which easily runs in $< 5 \text{ms}$.
- **Space Complexity:** $\mathcal{O}(N \cdot 2^N)$ — We need memory for the BFS queue and the `visited[N][2^N]` boolean matrix to prevent visiting duplicate states.

---

## 🔍 Edge Cases Considered

- **$N = 1$:** The target mask is already reached before taking any steps. The loop will not catch this unless explicitly checked. We handle this trivially with `if (n == 1) return 0;`.
- **Revisiting nodes:** Covered correctly because revisiting a node `v` with a mask that has *more* bits flipped (more nodes discovered) is treated as a completely new, valid BFS state. 

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
