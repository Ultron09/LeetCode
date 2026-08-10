# [3161. Block Placement Queries](https://leetcode.com/problems/block-placement-queries/)

**Difficulty:** `Hard`  
**Topics:** [Intervals](../../topics/intervals.md), [Binary Search](../../topics/binary-search.md), [Arrays & Hashing](../../topics/arrays-and-hashing.md)

---

## 📌 Problem Statement

There is an infinite number line with its origin at `0` extending towards positive $x$.

You are given a 2D array `queries` with two types of queries:
1. **Type 1 (`[1, x]`)**: Build an obstacle at distance $x$ from the origin. (Guaranteed that no obstacle exists at $x$).
2. **Type 2 (`[2, x, sz]`)**: Check if it is possible to place a block of size $sz$ anywhere inside $[0, x]$ such that the block does not intersect with any obstacle (it may touch obstacles/boundaries).

Return a boolean array `results` for all type 2 queries.

### Example 1:
```
Input: queries = [[1,2],[2,3,3],[2,3,1],[2,2,2]]
Output: [false, true, true]
Explanation:
- Query [1,2]: Obstacle placed at 2. Gaps: [0..2] (len 2).
- Query [2,3,3]: Max gap in [0, 3] is max(len(0..2)=2, len(2..3)=1) = 2 < 3 -> false.
- Query [2,3,1]: Max gap 2 >= 1 -> true.
- Query [2,2,2]: Max gap in [0, 2] is 2 >= 2 -> true.
```

### Example 2:
```
Input: queries = [[1,7],[2,7,6],[1,2],[2,7,5],[2,7,6]]
Output: [true, true, false]
```

### Constraints:
- $1 \le \text{queries.length} \le 1.5 \times 10^5$
- $1 \le x, sz \le \min(5 \times 10^4, 3 \times \text{queries.length})$

---

## 💡 Intuition & Approach

### 1. Dynamic Gap Maintenance
Every obstacle at position $p$ has an associated gap of size $p - \text{prev}(p)$ ending at $p$.
- When a new obstacle is built at $x$:
  - Find $prev < x$ and $next > x$ using an ordered set (`std::set<int>`).
  - The gap ending at $x$ becomes $x - prev$.
  - The gap ending at $next$ (if present) shrinks from $next - prev$ to $next - x$.

### 2. Segment Tree for Maximum Gap Queries
We maintain the gap ending at each obstacle position in a **Point-Update Range-Maximum Segment Tree**:
- When querying $[2, x, sz]$:
  1. Find the largest obstacle $p \le x$ using `prev(obstacles.upper_bound(x))`.
  2. The maximum gap inside $[0, x]$ is:
     $$\max\left(\text{SegmentTree.query}(0, p), \, x - p\right)$$
  3. If $\text{max\_gap} \ge sz$, return `true`, else `false`.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(Q \log M)$ where $M = \max(x) \le 5 \times 10^4$
  - Each Type 1 query performs $\mathcal{O}(\log M)$ `std::set` lookup and two Segment Tree updates ($\mathcal{O}(\log M)$).
  - Each Type 2 query performs $\mathcal{O}(\log M)$ `std::set` lookup and one Segment Tree range query ($\mathcal{O}(\log M)$).
  - Total runtime $\approx 1.5 \times 10^5 \times 16 \approx 2.4 \times 10^6$ operations ($< 35$ ms in C++).
- **Space Complexity:** $\mathcal{O}(M)$
  - Segment Tree of size $4 \times 50005$ integers ($\approx 800$ KB).
  - `std::set` holding at most $M$ obstacle positions.

---

## 🔍 Edge Cases Considered

- **Query boundary at obstacle ($x = p$)**: $x - p = 0$; properly handled by Segment Tree query up to $p$.
- **No obstacles between $0$ and $x$**: $p = 0 \implies \text{max\_gap} = x - 0 = x$.
- **Virtual Base Obstacle**: Initialized with `obstacles.insert(0)` to simplify predecessor lookups.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
