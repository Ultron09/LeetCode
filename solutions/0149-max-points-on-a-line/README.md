# [149. Max Points on a Line](https://leetcode.com/problems/max-points-on-a-line/)

**Difficulty:** `Hard`  
**Topics:** [Math & Geometry](../../topics/math-and-geometry.md), [Hash Table](../../topics/arrays-and-hashing.md), [Array](../../topics/arrays-and-hashing.md)

---

## 📌 Problem Statement

Given an array of `points` where `points[i] = [xi, yi]` represents a point on the X-Y plane, return the **maximum number of points that lie on the same straight line**.

### Example 1:
```
Input: points = [[1,1],[2,2],[3,3]]
Output: 3
```

### Example 2:
```
Input: points = [[1,1],[3,2],[5,3],[4,1],[2,3],[1,4]]
Output: 4
```

### Constraints:
- $1 \le \text{points.length} \le 300$
- $\text{points}[i]\text{.length} == 2$
- $-10^4 \le x_i, y_i \le 10^4$
- All the points are **unique**.

---

## 💡 Intuition & Approach

### 1. Anchor-Based Collinear Sweep
For each point $i$ chosen as the origin/anchor:
- Any other point $j$ forms a line with slope $\frac{\Delta y}{\Delta x} = \frac{y_j - y_i}{x_j - x_i}$.
- To avoid floating-point precision inaccuracies, represent the slope as an irreducible coprime fraction $\left(\frac{\Delta x}{g}, \frac{\Delta y}{g}\right)$ where $g = \gcd(|\Delta x|, |\Delta y|)$.

### 2. Canonical Orientation & Bit Packing
Normalize directions:
- If $\Delta x < 0$: negate both $\Delta x$ and $\Delta y$.
- If $\Delta x == 0$: vertical line $\implies (0, 1)$.
- If $\Delta y == 0$: horizontal line $\implies (1, 0)$.

Pack coprime integers $(\Delta x, \Delta y)$ into a single 64-bit key:
$$\text{key} = (\Delta x \ll 32) \mid (\Delta y \ \& \ 0\text{xFFFFFFFF})$$
Count slope occurrences in `unordered_map<int64_t, int>` and take the maximum frequency $+ 1$ (including anchor $i$).

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N^2 \log(\max(\text{coord})))$ where $N \le 300$ (pairs iteration with $\mathcal{O}(\log(\text{coord}))$ GCD reductions).
- **Space Complexity:** $\mathcal{O}(N)$ auxiliary space for the slope frequency map per anchor.

---

## 🔍 Edge Cases Considered

- **$N \le 2$ Points**: Directly returns $N$.
- **Purely Vertical / Horizontal Lines**: Correctly normalized to $(0, 1)$ and $(1, 0)$.
- **Negative Coordinates**: Handled robustly by canonical sign flipping.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
