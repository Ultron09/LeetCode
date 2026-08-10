# [3534. Path Existence Queries in a Graph II](https://leetcode.com/problems/path-existence-queries-in-a-graph-ii/)

**Difficulty:** `Hard`  
**Topics:** [Graphs](../../topics/graphs.md), [Two Pointers](../../topics/two-pointers.md), [Binary Search](../../topics/binary-search.md)

---

## 📌 Problem Statement

You are given:
- An integer `n` representing the number of nodes in a graph (labeled `0` to `n - 1`).
- An integer array `nums` of length `n`.
- An integer `maxDiff`.
- A 2D array `queries` where each `queries[i] = [ui, vi]`.

An undirected edge exists between node $i$ and node $j$ if and only if $|nums[i] - nums[j]| \le maxDiff$.

For each query `[ui, vi]`, find the **minimum distance** (minimum number of edges in a path) between `ui` and `vi`. If no path exists between `ui` and `vi`, return `-1`.

Return an array `answer`, where `answer[i]` is the result for `queries[i]`.

### Example 1:
```
Input: n = 5, nums = [1, 8, 3, 4, 2], maxDiff = 3, queries = [[0, 3], [2, 4]]
Output: [1, 1]
Explanation:
- Query [0, 3]: nums[0]=1, nums[3]=4, |1-4|=3 <= 3 -> direct edge (dist 1).
- Query [2, 4]: nums[2]=3, nums[4]=2, |3-2|=1 <= 3 -> direct edge (dist 1).
```

### Example 2:
```
Input: n = 5, nums = [5, 3, 1, 9, 10], maxDiff = 2, queries = [[0, 1], [0, 2], [2, 3], [4, 3]]
Output: [1, 2, -1, 1]
Explanation:
- Query [0, 1]: Path 0 -> 1 (dist 1).
- Query [0, 2]: Path 0 -> 1 -> 2 (dist 2).
- Query [2, 3]: Disconnected components (return -1).
- Query [4, 3]: Path 3 -> 4 (dist 1).
```

### Example 3:
```
Input: n = 3, nums = [3, 6, 1], maxDiff = 1, queries = [[0, 0], [0, 1], [1, 2]]
Output: [0, -1, -1]
```

### Constraints:
- $1 \le n = \text{nums.length} \le 10^5$
- $0 \le \text{nums}[i] \le 10^9$
- $0 \le \text{maxDiff} \le 10^9$
- $1 \le \text{queries.length} \le 10^5$
- $\text{queries}[i] = [u_i, v_i]$ with $0 \le u_i, v_i < n$.

---

## 💡 Intuition & Approach

### 1. Value Sorting & Window Reachability
The condition $|nums[i] - nums[j]| \le maxDiff$ depends purely on the value difference.
If we sort `nums` in ascending order:
- Any node at sorted index $i$ can directly connect to all nodes in the contiguous sorted range $[i, R_i]$ where $nums[R_i] - nums[i] \le maxDiff$.
- To minimize the number of hops from a smaller sorted index towards a larger sorted index, a greedy jump to the **furthest reachable node** ($R_i$) is always optimal.
- Using a **Two Pointers / Sliding Window** technique, we compute $R_i$ for all $i \in [0, n-1]$ in $\mathcal{O}(n)$ time.

### 2. Binary Lifting (Exponential Jump Table)
Since answering queries by jumping $1$ step at a time would take $\mathcal{O}(n)$ per query ($\mathcal{O}(n \cdot q)$ overall, causing TLE), we precompute jumps using **Binary Lifting**:
- Let $\text{jump}[i][k]$ be the furthest sorted index reachable from index $i$ in at most $2^k$ jumps.
- Base case: $\text{jump}[i][0] = R_i$.
- State transition:
  $$\text{jump}[i][k] = \text{jump}[\text{jump}[i][k - 1]][k - 1]$$
- Precomputation takes $\mathcal{O}(n \log n)$ time and space.

### 3. Answering Queries in $\mathcal{O}(\log n)$
For query $[u, v]$:
1. Let $\text{start} = \min(\text{pos}[u], \text{pos}[v])$ and $\text{target} = \max(\text{pos}[u], \text{pos}[v])$.
2. If $\text{start} == \text{target}$, return $0$.
3. If $\text{jump}[\text{start}][0] \ge \text{target}$, return $1$.
4. If $\text{jump}[\text{start}][\text{maxLevel} - 1] < \text{target}$, the nodes are in disconnected components $\implies$ return $-1$.
5. Greedily attempt jumps from $k = \text{maxLevel} - 1$ down to $0$:
   - If $\text{jump}[\text{curr}][k] < \text{target}$, jump: $\text{curr} \leftarrow \text{jump}[\text{curr}][k]$ and add $2^k$ to `jumps`.
6. Finally, from `curr`, one additional jump reaches or passes `target`: return `jumps + 1`.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(n \log n + q \log n)$
  - Sorting `nums` with indices: $\mathcal{O}(n \log n)$.
  - Two pointers for 1-step reach: $\mathcal{O}(n)$.
  - Binary lifting table precomputation: $\mathcal{O}(n \log n)$.
  - Query answering: $q \times \mathcal{O}(\log n) \implies \mathcal{O}(q \log n)$.
- **Space Complexity:** $\mathcal{O}(n \log n)$ for the 2D binary lifting table.

---

## 🔍 Edge Cases Considered

- **$u == v$**: Returns $0$ immediately.
- **Disconnected Components**: Detected when the maximum reachable ancestor is strictly less than target $\implies$ returns $-1$.
- **$n = 1$**: Handled with $\log_2(1) = 0$, returns $0$.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
