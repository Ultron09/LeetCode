# [834. Sum of Distances in Tree](https://leetcode.com/problems/sum-of-distances-in-tree/)

**Difficulty:** `Hard`  
**Topics:** [Trees](../../topics/trees.md), [Dynamic Programming](../../topics/dynamic-programming.md)

---

## 📌 Problem Statement

There is an undirected connected tree with `n` nodes labeled from `0` to `n - 1` and `n - 1` edges.

You are given the integer `n` and the array `edges` where `edges[i] = [ai, bi]` indicates that there is an edge between nodes `ai` and `bi` in the tree.

Return an array `answer` of length `n` where `answer[i]` is the sum of the distances between the `ith` node in the tree and all other nodes.

### Example 1:
```
Input: n = 6, edges = [[0,1],[0,2],[2,3],[2,4],[2,5]]
Output: [8,12,6,10,10,10]
Explanation: The tree is shown above.
We can see that dist(0,1) + dist(0,2) + dist(0,3) + dist(0,4) + dist(0,5)
equals 1 + 1 + 2 + 2 + 2 = 8.
Hence, answer[0] = 8, and so on.
```

### Example 2:
```
Input: n = 1, edges = []
Output: [0]
```

### Example 3:
```
Input: n = 2, edges = [[1,0]]
Output: [1,1]
```

### Constraints:
- `1 <= n <= 3 * 10^4`
- `edges.length == n - 1`
- `edges[i].length == 2`
- `0 <= ai, bi < n`
- `ai != bi`
- The given input represents a valid tree

---

## 💡 Intuition & Approach

Computing the BFS distance from every single node would take $\mathcal{O}(N^2)$ time, which results in a Time Limit Exceeded (TLE) for $N = 30,000$.

Instead, we can use a highly optimized $\mathcal{O}(N)$ approach known as **Re-rooting Dynamic Programming (Tree DP)**. The core idea is that adjacent nodes in a tree have highly correlated distances to the rest of the network. If we shift our root from a parent $u$ to its child $v$:
- All nodes inside the subtree of $v$ get **$1$ step closer** to the new root.
- All nodes outside the subtree of $v$ get **$1$ step further away** from the new root.

This gives us the $\mathcal{O}(1)$ state transition:
`ans[v] = ans[u] - count[v] + (n - count[v])`

### Step-by-step Execution:

1. **Pass 1 (Post-order Traversal):**
   Arbitrarily pick `node 0` as the root. We run a post-order DFS to calculate two things for every node `u`:
   - `count[u]`: the number of nodes in the subtree rooted at `u`.
   - `ans[u]`: the sum of distances from `u` to all nodes strictly inside its subtree.
   Transitions:
   ```cpp
   count[u] = 1 + sum(count[children])
   ans[u] = sum(ans[child] + count[child])
   ```
   At the end of Pass 1, `ans[0]` contains the correct and final answer for `node 0`.

2. **Pass 2 (Pre-order Traversal):**
   Run a pre-order DFS starting from `node 0`. As we move from parent `u` to child `v`, we update the full tree answer for `v` using `ans[u]`:
   ```cpp
   ans[v] = ans[u] - count[v] + (n - count[v])
   ```
   This $\mathcal{O}(1)$ step leverages the solved state of the parent to instantly compute the solved state of the child.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N)$ — We visit every node exactly twice (once in `dfs1`, once in `dfs2`).
- **Space Complexity:** $\mathcal{O}(N)$ — To store the adjacency list representation of the tree, plus the memory utilized by the recursion stack and the `count`/`ans` vectors.

---

## 🔍 Edge Cases Considered

- **$N = 1$:** Empty edges array. Handled gracefully; `count[0] = 1`, `ans[0] = 0`.
- **Chain topologies (LinkedList-like trees):** Stack depth reaches $N$, but well within recursive stack limits for $N = 30,000$.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
