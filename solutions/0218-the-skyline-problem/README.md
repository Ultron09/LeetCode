# [218. The Skyline Problem](https://leetcode.com/problems/the-skyline-problem/)

**Difficulty:** `Hard`  
**Topics:** [Heap (Priority Queue)](../../topics/heaps-and-priority-queues.md), [Line Sweep](../../topics/intervals.md), [Ordered Set](../../topics/arrays-and-hashing.md), [Divide and Conquer](../../topics/trees.md)

---

## 📌 Problem Statement

A city's skyline is the outer contour of the silhouette formed by all the buildings in that city when viewed from a distance. Given the locations and heights of all the buildings, return **the skyline formed by these buildings collectively**.

The geometric information of each building is given in the array `buildings` where `buildings[i] = [left_i, right_i, height_i]`:
- `left_i` is the x coordinate of the left edge of the $i$-th building.
- `right_i` is the x coordinate of the right edge of the $i$-th building.
- `height_i` is the height of the $i$-th building.

The skyline should be represented as a list of "key points" sorted by their x-coordinate in the form `[[x1,y1],[x2,y2],...]`. Each key point is the left endpoint of some horizontal segment in the skyline except the last point in the list, which always has a y-coordinate $0$.

### Example 1:
```
Input: buildings = [[2,9,10],[3,7,15],[5,12,12],[15,20,10],[19,24,8]]
Output: [[2,10],[3,15],[7,12],[12,0],[15,10],[20,8],[24,0]]
```

### Example 2:
```
Input: buildings = [[0,2,3],[2,5,3]]
Output: [[0,3],[5,0]]
```

### Constraints:
- $1 \le \text{buildings.length} \le 10^4$
- $0 \le \text{left}_i < \text{right}_i \le 2^{31} - 1$
- $1 \le \text{height}_i \le 2^{31} - 1$
- `buildings` is sorted by `left_i` in non-decreasing order.

---

## 💡 Intuition & Approach

### 1. Line Sweep with Critical Event Encoding
Every building $[L, R, H]$ induces two critical vertical boundary events:
- **Left Edge (Start)**: Building enters with height $+H$. We encode this as `(L, -H)`.
- **Right Edge (End)**: Building leaves with height $-H$. We encode this as `(R, +H)`.

### 2. Event Sorting Tie-Breakers
By sorting events with `std::pair<int, int>` $(x, h)$:
1. **Primary sort**: By $x$-coordinate ascending.
2. **Tie-breaking at the same $x$**:
   - Two start events: higher building (`-H` more negative) is processed first.
   - Two end events: lower building (`+H` smaller positive) is processed first.
   - One start and one end event: start event (`-H` < `+H`) is processed before the end event, preventing spurious drops to height $0$ at abutting boundaries.

### 3. Tracking Max Height via `std::multiset`
Maintain an active height container initialized with ground level $\{0\}$.
- On start event: `activeHeights.insert(-h)`
- On end event: `activeHeights.erase(activeHeights.find(h))`
- Whenever $\max(\text{activeHeights}) \ne \text{prevMaxHeight}$, a new skyline key point $[x, \max(\text{activeHeights})]$ is emitted.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N \log N)$ where $N \le 10^4$ is the number of buildings ($2N$ event sorting and $\mathcal{O}(\log N)$ multiset operations).
- **Space Complexity:** $\mathcal{O}(N)$ auxiliary space to store $2N$ boundary events and the active multiset.

---

## 🔍 Edge Cases Considered

- **Abutting Buildings of Equal Height**: $[0, 2, 3]$ and $[2, 5, 3] \implies [[0,3], [5,0]]$ (correctly merged into a single segment).
- **Nested Buildings**: A smaller building completely inside a taller one triggers no skyline points.
- **Overlapping Starts/Ends**: Handled seamlessly by signed height tie-breakers.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
