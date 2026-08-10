# [1840. Maximum Building Height](https://leetcode.com/problems/maximum-building-height/)

**Difficulty:** `Hard`  
**Topics:** [Greedy](../../topics/greedy.md), [Math & Geometry](../../topics/math-and-geometry.md), [Arrays & Hashing](../../topics/arrays-and-hashing.md)

---

## 📌 Problem Statement

You want to build $n$ new buildings in a city in a line, labeled from $1$ to $n$.

City restrictions on building heights:
1. The height of each building must be a non-negative integer.
2. The height of the first building must be `0` ($h_1 = 0$).
3. The height difference between any two adjacent buildings cannot exceed `1` ($|h_i - h_{i+1}| \le 1$).
4. Specific building height limits are given in `restrictions[i] = [idi, maxHeighti]`.

Return the **maximum possible height** of the tallest building.

### Example 1:
```
Input: n = 5, restrictions = [[2,1],[4,1]]
Output: 2
Explanation:
Building heights: [0, 1, 2, 1, 2]. Tallest building has height 2.
```

### Example 2:
```
Input: n = 6, restrictions = []
Output: 5
Explanation:
Building heights: [0, 1, 2, 3, 4, 5]. Tallest building has height 5.
```

### Example 3:
```
Input: n = 10, restrictions = [[5,3],[2,5],[7,4],[10,3]]
Output: 5
Explanation:
Building heights: [0, 1, 2, 3, 3, 4, 4, 5, 4, 3]. Tallest building has height 5.
```

### Constraints:
- $2 \le n \le 10^9$
- $0 \le \text{restrictions.length} \le \min(n - 1, 10^5)$
- $2 \le id_i \le n$
- $id_i$ is unique.
- $0 \le maxHeight_i \le 10^9$

---

## 💡 Intuition & Approach

### 1. Two-Pass Constraint Relaxation
Each building height constraint $|h_i - h_{i+1}| \le 1$ means between any two restricted positions $x_1$ and $x_2$ ($x_1 < x_2$), the height cannot grow by more than $x_2 - x_1$:
$$h_2 \le h_1 + (x_2 - x_1) \quad \text{and} \quad h_1 \le h_2 + (x_2 - x_1)$$

Some given restrictions may be impossible to reach or loose. We tighten all restrictions by performing two passes:
1. **Left-to-Right Pass**: Starting from $h_1 = 0$, tighten each restriction using the maximum reachable height from its left neighbor:
   $$h_i = \min(h_i, h_{i-1} + (x_i - x_{i-1}))$$
2. **Right-to-Left Pass**: Starting from the rightmost restriction, tighten each restriction using the maximum reachable height from its right neighbor:
   $$h_i = \min(h_i, h_{i+1} + (x_{i+1} - x_i))$$

### 2. Triangular Peak Formula Between Adjacent Restrictions
After both passes, for any two adjacent tight restrictions $(x_1, h_1)$ and $(x_2, h_2)$ with $x_1 < x_2$, the height can rise from $h_1$ to a maximum peak $H$ and then descend to $h_2$:
- Horizontal distance ascending: $H - h_1$.
- Horizontal distance descending: $H - h_2$.
- Total horizontal distance: $(H - h_1) + (H - h_2) \le x_2 - x_1$.
- Solving for $H$:
  $$2H \le (x_2 - x_1) + h_1 + h_2 \implies H = \left\lfloor \frac{(x_2 - x_1) + h_1 + h_2}{2} \right\rfloor$$

The answer is simply $\max(H)$ across all adjacent pairs of restrictions.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(R \log R)$
  - Sorting $R$ restrictions: $\mathcal{O}(R \log R)$.
  - Two linear relaxation passes and peak calculation: $\mathcal{O}(R)$.
  - Total runtime is $\approx 10^5 \log(10^5) \approx 1.7 \times 10^6$ operations ($< 15$ ms in C++).
- **Space Complexity:** $\mathcal{O}(R)$ auxiliary space for sorting and storing restrictions.

---

## 🔍 Edge Cases Considered

- **Empty Restrictions (`restrictions = []`)**: Handled by inserting $(1, 0)$ and $(n, n-1)$, yielding peak $n - 1$.
- **Building $n$ not restricted**: Handled by appending $(n, n - 1)$ to allow full upward growth to the end.
- **Large $n = 10^9$**: Handled in $\mathcal{O}(R \log R)$ independent of $n$.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
