# [3464. Maximize the Distance Between Points on a Square](https://leetcode.com/problems/maximize-the-distance-between-points-on-a-square/)

**Difficulty:** `Hard`  
**Topics:** [Binary Search](../../topics/binary-search.md), [Greedy](../../topics/greedy.md), [Math & Geometry](../../topics/math-and-geometry.md)

---

## 📌 Problem Statement

You are given an integer `side`, representing the edge length of a square with corners at $(0, 0)$, $(0, side)$, $(side, 0)$, and $(side, side)$ on a Cartesian plane.

You are also given a positive integer $k$ and a 2D integer array `points`, where `points[i] = [xi, yi]` represents a point on the boundary of the square.

Select $k$ elements among `points` such that the **minimum Manhattan distance** between any two selected points is **maximized**.

Return the **maximum possible minimum Manhattan distance** between the selected $k$ points.

The Manhattan Distance between $(x_1, y_1)$ and $(x_2, y_2)$ is $|x_1 - x_2| + |y_1 - y_2|$.

### Example 1:
```
Input: side = 2, points = [[0,2],[2,0],[2,2],[0,0]], k = 4
Output: 2
Explanation: Select all four points (0,0), (2,0), (2,2), (0,2). The minimum Manhattan distance is 2.
```

### Example 2:
```
Input: side = 2, points = [[0,0],[1,2],[2,0],[2,2],[2,1]], k = 4
Output: 1
Explanation: Select (0,0), (2,0), (2,2), and (2,1).
```

### Example 3:
```
Input: side = 2, points = [[0,0],[0,1],[0,2],[1,2],[2,0],[2,2],[2,1]], k = 5
Output: 1
```

### Constraints:
- $1 \le \text{side} \le 10^9$
- $4 \le \text{points.length} \le \min(4 \times \text{side}, 1.5 \times 10^4)$
- $4 \le k \le \min(25, \text{points.length})$
- Points are unique and lie on the boundary of the square.

---

## 💡 Intuition & Approach

### 1. 1D Perimeter Linearization
Because all points lie strictly on the boundary of the square of perimeter $P = 4 \times side$, we map each 2D point $(x, y)$ to a 1D position along the perimeter in $[0, 4 \times side)$:
- **Bottom edge** ($y = 0$): $pos = x$
- **Right edge** ($x = side$): $pos = side + y$
- **Top edge** ($y = side$): $pos = 3 \times side - x$
- **Left edge** ($x = 0$): $pos = 4 \times side - y$

### 2. Manhattan Distance on Boundary $\equiv$ Perimeter Distance
Since $k \ge 4$, by Pigeonhole Principle, the optimal minimum distance $D$ satisfies:
$$D \le \frac{4 \times side}{k} \le side$$
- For points on the **same edge** or **adjacent edges**, Manhattan distance is *identically equal* to perimeter distance.
- For points on **opposite edges** (e.g. left and right), Manhattan distance is $side + |y_1 - y_2| \ge side \ge D$.

Therefore, maintaining a **perimeter distance $\ge D$ between consecutive points in cyclic order** strictly guarantees that **all pairwise Manhattan distances are $\ge D$**.

### 3. Binary Search on Answer + Greedy Check with `std::lower_bound`
- We binary search for $D \in [1, side]$.
- For a candidate distance $D$:
  - By Pigeonhole Principle, at least one chosen point must lie in the first interval $[pos[0], \, pos[0] + P / k]$.
  - We test each candidate starting point $i$ with $pos[i] - pos[0] \le P / k$.
  - From starting index $i$, we greedily select $k - 1$ subsequent points using `std::lower_bound` on the doubled array $extPositions$.
  - If $k$ points are selected and the wrap-around distance back to the first point is $\ge D$, candidate $D$ is feasible.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N \log N + \log(\text{side}) \cdot \frac{N}{k} \cdot k \log N) = \mathcal{O}(N \log N \log(\text{side}))$
  - Mapping and sorting $N$ points: $\mathcal{O}(N \log N)$.
  - Binary search iterations: $\log_2(10^9) \approx 30$.
  - Feasibility check: $\le N/k$ starting points $\times (k - 1)$ binary searches $= \mathcal{O}(N \log N)$.
  - Total runtime: $< 25$ ms for $N = 1.5 \times 10^4$.
- **Space Complexity:** $\mathcal{O}(N)$ for linearized and doubled perimeter coordinate arrays.

---

## 🔍 Edge Cases Considered

- **$side \le 10^9$**: Use 64-bit integers (`long long`) to prevent overflow when calculating $4 \times side$ or extended positions.
- **Wrap-around Circular Distance**: Checked with $(extPositions[i] + P - extPositions[currIdx] \ge D)$.
- **$k = 4$ corners**: Handled optimally and returns $side$.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
