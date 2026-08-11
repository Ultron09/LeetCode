# [335. Self Crossing](https://leetcode.com/problems/self-crossing/)

**Difficulty:** `Hard`  
**Topics:** [Math & Geometry](../../topics/math-and-geometry.md), [Arrays & Hashing](../../topics/arrays-and-hashing.md)

---

## 📌 Problem Statement

You are given an array of integers `distance`.

You start at the point `(0, 0)` on an X-Y plane, and you move `distance[0]` meters to the north, then `distance[1]` meters to the west, `distance[2]` meters to the south, `distance[3]` meters to the east, and so on. In other words, after each move, your direction changes counter-clockwise.

Return `true` if your path crosses itself or `false` if it does not.

### Example 1:
```
Input: distance = [2,1,1,2]
Output: true
Explanation: The path crosses itself at the point (0, 1).
```

### Example 2:
```
Input: distance = [1,2,3,4]
Output: false
Explanation: The path does not cross itself at any point (expanding spiral).
```

### Example 3:
```
Input: distance = [1,1,1,2,1]
Output: true
Explanation: The path crosses itself at the point (0, 0).
```

### Constraints:
- $1 \le \text{distance.length} \le 10^5$
- $1 \le \text{distance}[i] \le 10^5$

---

## 💡 Intuition & Approach

### 1. Geometric Spiral Classification
In a 2D plane with consecutive $90^\circ$ counter-clockwise turns, a path cannot intersect segments drawn 6 or more steps prior without having already intersected an intermediate segment.

Thus, self-crossing can occur in **exactly three fundamental geometric configurations**:

```
 Case 1: Line i crosses Line i-3      Case 2: Line i meets Line i-4       Case 3: Line i crosses Line i-5
             i-2                                    i-2                                    i-2
        +-----------+                          +-----------+                          +-----------+
        |           |                          |           |                          |           |
        |           |                          |           |                          |           |
        |       i   |                          |   i       |                          |           |
    i-1 |     +---> |                      i-1 |   ^       |                      i-1 |      i    |
        |     |     |                          |   | (i-4) |                          |    +--->  |
        +-----+-----+                          +---+-------+                          |    | (i-5)|
             i-3                                    i-3                               +----+------+
                                                                                           i-3
```

### 2. The 3 Crossing Conditions

1. **Case 1: Line $i$ crosses Line $i-3$ ($i \ge 3$)**
   - The current step extends far enough to cross the segment drawn 3 turns ago:
     $$\text{distance}[i] \ge \text{distance}[i-2] \quad \land \quad \text{distance}[i-1] \le \text{distance}[i-3]$$

2. **Case 2: Line $i$ meets / overlaps with Line $i-4$ ($i \ge 4$)**
   - The path forms a closed loop corner where line $i$ meets the starting ray of line $i-4$:
     $$\text{distance}[i-1] == \text{distance}[i-3] \quad \land \quad \text{distance}[i] + \text{distance}[i-4] \ge \text{distance}[i-2]$$

3. **Case 3: Line $i$ crosses Line $i-5$ ($i \ge 5$)**
   - Transitioning from an outwardly expanding spiral to an inwardly contracting spiral:
     $$\begin{cases} 
     \text{distance}[i-2] \ge \text{distance}[i-4] \\
     \text{distance}[i-1] \le \text{distance}[i-3] \\
     \text{distance}[i-1] + \text{distance}[i-5] \ge \text{distance}[i-3] \\
     \text{distance}[i] + \text{distance}[i-4] \ge \text{distance}[i-2]
     \end{cases}$$

Iterating through `distance` from $i = 3$ to $N - 1$ and testing these three disjoint conditions in $\mathcal{O}(1)$ time guarantees finding any self-intersection.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N)$  
  A single linear scan through the array with $\mathcal{O}(1)$ constant-time condition evaluations per index.
- **Space Complexity:** $\mathcal{O}(1)$  
  Operates in-place with zero additional memory allocation.

---

## 🔍 Edge Cases Considered

- **Short Arrays ($N < 4$)**: It takes at least 4 segments to cross. Automatically returns `false`.
- **Pure Expanding Spiral (e.g. `[1, 2, 3, 4, 5]`)**: Distance strictly grows at each step; returns `false`.
- **Pure Contracting Spiral (e.g. `[5, 4, 3, 2, 1]`)**: Distance strictly shrinks at each step; returns `false`.
- **Corner Closure (e.g. `[1, 2, 3, 2, 2]`)**: Case 2 catches the touching/overlapping corner.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
