# [3620. Network Recovery Pathways](https://leetcode.com/problems/network-recovery-pathways/)

**Difficulty:** `Hard`  
**Topics:** [Graphs](../../topics/graphs.md), [Binary Search](../../topics/binary-search.md), [Heaps & Priority Queues](../../topics/heaps-and-priority-queues.md)

---

## 📌 Problem Statement

You are given a directed acyclic graph (DAG) of `n` nodes numbered from `0` to `n - 1`. This is represented by a 2D array `edges` of length `m`, where `edges[i] = [ui, vi, costi]` indicates a one-way communication from node `ui` to node `vi` with a recovery cost of `costi`.

Some nodes may be offline. You are given a boolean array `online` where `online[i] = true` means node `i` is online. Nodes `0` and `n - 1` are always online.

A path from `0` to `n - 1` is **valid** if:
1. All intermediate nodes on the path are online (`online[v] == true`).
2. The total recovery cost of all edges on the path does not exceed `k`.

For each valid path, define its **score** as the **minimum edge-cost** along that path.

Return the **maximum path score** (i.e., the largest minimum-edge cost) among all valid paths. If no valid path exists, return `-1`.

### Example 1:
```
Input: edges = [[0,1,5],[1,3,10],[0,2,3],[2,3,4]], online = [true,true,true,true], k = 10
Output: 3
Explanation:
- Path 0 -> 1 -> 3: Total cost = 5 + 10 = 15 > 10 (invalid).
- Path 0 -> 2 -> 3: Total cost = 3 + 4 = 7 <= 10 (valid). Score = min(3, 4) = 3.
Maximum valid score = 3.
```

### Example 2:
```
Input: edges = [[0,1,7],[1,4,5],[0,2,6],[2,3,6],[3,4,2],[2,4,6]], online = [true,true,true,false,true], k = 12
Output: 6
Explanation:
- Node 3 is offline, so paths through 3 are invalid.
- Path 0 -> 1 -> 4: Total cost = 7 + 5 = 12 <= 12 (valid). Score = min(7, 5) = 5.
- Path 0 -> 2 -> 4: Total cost = 6 + 6 = 12 <= 12 (valid). Score = min(6, 6) = 6.
Maximum valid score = 6.
```

### Constraints:
- `n == online.length`
- $2 \le n \le 5 \times 10^4$
- $0 \le m = \text{edges.length} \le \min(10^5, \frac{n(n - 1)}{2})$
- `edges[i] = [ui, vi, costi]` with $0 \le u_i, v_i < n$, $u_i \ne v_i$.
- $0 \le \text{cost}_i \le 10^9$
- $0 \le k \le 5 \times 10^{13}$
- `online[0] == true` and `online[n - 1] == true`.
- The given graph is a directed acyclic graph.

---

## 💡 Intuition & Approach

### 1. Monotonicity & Binary Search on Answer
The objective is to find a path that maximizes the **minimum edge cost** (bottleneck value) subject to a sum constraint $\le k$.
- If there exists a valid path where every edge has $\text{cost} \ge X$ with total sum $\le k$, then any smaller threshold $X' < X$ is also achievable.
- This strict monotonicity enables **Binary Search on the Answer**:
  - Collect and sort all distinct edge costs in `uniqueCosts`.
  - Binary search for the maximum threshold $X \in \text{uniqueCosts}$ such that a path from $0$ to $n-1$ exists using only edges with $\text{cost} \ge X$ and total recovery cost $\le k$.

### 2. Feasibility Check with Dijkstra's Algorithm
For a candidate threshold $X$:
1. Filter out all edges with $\text{cost} < X$.
2. Filter out all transitions to offline intermediate nodes (`!online[v]` where $v \ne n - 1$).
3. Find the **minimum total cost path** from $0$ to $n-1$ using Dijkstra's algorithm.
4. If the shortest distance to $n - 1$ is $\le k$, then threshold $X$ is feasible $\implies$ search higher ($\text{low} = \text{mid} + 1$).
5. Otherwise, threshold $X$ is infeasible $\implies$ search lower ($\text{high} = \text{mid} - 1$).

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}((N + M) \log N \log M)$
  - Deduplicating edge costs: $\mathcal{O}(M \log M)$.
  - Binary search iterations: $\log_2(M) \approx 17$.
  - Each check runs Dijkstra's algorithm in $\mathcal{O}((N + M) \log N)$ time.
  - Total operations: $\approx 1.5 \times 10^5 \times 16 \times 17 \approx 4 \times 10^7$ ($< 50$ ms in C++).
- **Space Complexity:** $\mathcal{O}(N + M)$ for adjacency list, priority queue, and distance arrays.

---

## 🔍 Edge Cases Considered

- **No Valid Path Exists**: Handled by returning `-1`.
- **Large Budget ($k \le 5 \times 10^{13}$)**: Handled using `long long` for distance calculations to prevent integer overflow.
- **Offline Intermediate Nodes**: Correctly checked before queueing next states, while destination node $n - 1$ is always reachable.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
