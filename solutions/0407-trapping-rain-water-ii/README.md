# [407. Trapping Rain Water II](https://leetcode.com/problems/trapping-rain-water-ii/)

**Difficulty:** `Hard`  
**Topics:** [Heaps & Priority Queues](../../topics/heaps-and-priority-queues.md), [Graphs](../../topics/graphs.md), [Arrays & Hashing](../../topics/arrays-and-hashing.md)

---

## 📌 Problem Statement

Given an $m \times n$ integer matrix `heightMap` representing the height of each unit cell in a 2D elevation map, return the volume of water it can trap after raining.

### Example 1:
```
Input: heightMap = [[1,4,3,1,3,2],[3,2,1,3,2,4],[2,3,3,2,3,1]]
Output: 4
Explanation: After the rain, water is trapped between the blocks.
We have two small ponds 1 and 3 units trapped.
The total volume of water trapped is 4.
```

### Example 2:
```
Input: heightMap = [[3,3,3,3,3],[3,2,2,2,3],[3,2,1,2,3],[3,2,2,2,3],[3,3,3,3,3]]
Output: 10
Explanation: A concentric 5x5 bowl trapping 10 units of water in total.
```

### Constraints:
- $m == \text{heightMap.length}$
- $n == \text{heightMap}[i].\text{length}$
- $1 \le m, n \le 200$
- $0 \le \text{heightMap}[i][j] \le 2 \times 10^4$

---

## 💡 Intuition & Approach

### 1. From 1D to 2D: The Spillway Principle
In 1D Trapping Rain Water ([LeetCode 42](../0042-trapping-rain-water/README.md)), water is bounded by the shorter of the left and right maximum boundaries. We can sweep inward from both ends with two pointers.

In 2D Trapping Rain Water II, water can leak out in **four orthogonal directions** toward the entire 2D perimeter. Therefore, an interior cell $(r, c)$ can only hold water up to the **lowest escape spillway** on the path from $(r, c)$ to the outer edge of the grid. This is a **Minimax Path** problem:
$$\text{Water Level}(r, c) = \min_{\text{paths } P \text{ to boundary}} \left( \max_{(u, v) \in P} \text{heightMap}[u][v] \right)$$

### 2. Generalized Dijkstra with Min-Heap (Boundary Inward Shrink)
To find the lowest spillway for all cells efficiently:
1. **Initialize Outer Ring**:
   - Push all $2(m + n) - 4$ outer perimeter cells into a **Min-Heap** prioritized by height.
   - Mark all perimeter cells as visited. Water cannot be trapped on the outer boundary.
2. **Greedy Inward Propagation**:
   - Always extract the lowest cell $(r, c, h)$ from the Min-Heap. Because $h$ is the minimum among all currently active boundary cells, it represents the absolute **bottleneck / lowest spillway** for all its unvisited interior neighbors.
   - For each unvisited orthogonal neighbor $(nr, nc)$:
     - Mark $(nr, nc)$ as visited.
     - If $\text{heightMap}[nr][nc] < h$, the neighbor traps $h - \text{heightMap}[nr][nc]$ units of water.
     - Push $(nr, nc)$ into the Min-Heap with updated effective boundary height $\max(h, \text{heightMap}[nr][nc])$.
3. **Repeat** until all interior cells have been visited.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(M \cdot N \log(M \cdot N))$
  - The grid contains $M \times N \le 40,000$ cells.
  - Each cell is pushed and popped from the Min-Heap at most once.
  - Each priority queue operation takes $\mathcal{O}(\log(M \cdot N))$.
  - Total operations $\approx 40,000 \log_2(40,000) \approx 6.4 \times 10^5$, executing in $< 5\text{ ms}$.
- **Space Complexity:** $\mathcal{O}(M \cdot N)$
  - The `visited` 2D matrix requires $M \times N$ space.
  - The priority queue holds at most $M \times N$ elements simultaneously.

---

## 🔍 Edge Cases Considered

- **Trivial Dimensions ($m < 3$ or $n < 3$)**: All cells belong to the outer boundary; returns `0` immediately.
- **Flat Surface**: All heights are equal; water flows off the edges without trapping ($0$ volume).
- **Concentric Basin**: Interior lower than exterior wall; correctly accumulates volume across all interior depths.
- **Multiple Disjoint Ponds**: Handled naturally without separate connected component passes, as the min-heap processes lowest bottlenecks globally.
- **Unequal Wall Heights**: The water level of an interior cell is strictly governed by the lowest boundary gap.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
