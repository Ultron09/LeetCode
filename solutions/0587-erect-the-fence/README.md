# [587. Erect the Fence](https://leetcode.com/problems/erect-the-fence/)

**Difficulty:** `Hard`  
**Topics:** [Math & Geometry](../../topics/math-and-geometry.md), [Array](../../topics/arrays-and-hashing.md)

---

## 📌 Problem Statement

You are given an array `trees` where `trees[i] = [xi, yi]` represents the location of a tree in the garden.

Fence the entire garden using the **minimum length of rope**, as it is expensive. The garden is well-fenced only if all the trees are enclosed.

Return the coordinates of trees that are **exactly located on the fence perimeter**. You may return the answer in any order.

### Example 1:
![Example 1](https://assets.leetcode.com/uploads/2021/04/24/erect2-plane.jpg)
```
Input: trees = [[1,1],[2,2],[2,0],[2,4],[3,3],[4,2]]
Output: [[1,1],[2,0],[4,2],[3,3],[2,4]]
Explanation: All the trees will be on the perimeter of the fence except the tree at [2, 2], which will be inside the fence.
```

### Example 2:
![Example 2](https://assets.leetcode.com/uploads/2021/04/24/erect1-plane.jpg)
```
Input: trees = [[1,2],[2,2],[4,2]]
Output: [[4,2],[2,2],[1,2]]
Explanation: The fence forms a line that passes through all the trees.
```

### Constraints:
- $1 \le \text{trees.length} \le 3000$
- $\text{trees}[i].\text{length} == 2$
- $0 \le x_i, y_i \le 100$
- All given positions are **unique**.

---

## 💡 Intuition & Approach

### 1. Convex Hull & Collinear Edge Preservation
The minimum enclosing rope defines the **Convex Hull** of the 2D point set. A crucial specification is that **collinear trees located on perimeter edges must also be included**.

### 2. Andrew's Monotone Chain Algorithm
Andrew's variant of Graham Scan builds the lower and upper hulls separately:
1. **Sort Points**: Sort points lexicographically by $x$-coordinate, breaking ties by $y$-coordinate.
2. **2D Cross Product Orientation**:
   $$\text{cross}(O, A, B) = (A_x - O_x)(B_y - O_y) - (A_y - O_y)(B_x - O_x)$$
   - $\text{cross} > 0$: Counter-clockwise turn (left turn)
   - $\text{cross} < 0$: Clockwise turn (right turn)
   - $\text{cross} == 0$: Collinear points
3. **Modified Hull Construction**:
   - In standard convex hull algorithms, we pop when $\text{cross} \le 0$ to discard collinear points.
   - To **preserve collinear perimeter trees**, we pop **strictly when $\text{cross} < 0$** (only clockwise turns violate the hull's convexity).
4. **Merge & Deduplicate**:
   - Concatenate the lower and upper hulls.
   - Sort and remove duplicates (since the leftmost and rightmost endpoints—and all points if completely collinear—appear in both hulls).

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N \log N)$
  - Sorting $N$ 2D points takes $\mathcal{O}(N \log N)$.
  - Constructing lower and upper hulls takes $\mathcal{O}(N)$ amortized time as each point is pushed and popped at most once.
  - Final deduplication takes $\mathcal{O}(N \log N)$.
- **Space Complexity:** $\mathcal{O}(N)$
  - Auxiliary storage for lower hull, upper hull, and result vector.

---

## 🔍 Edge Cases Considered

- **$N \le 3$**: Automatically all points are on the perimeter; returned immediately.
- **Degenerate Collinear Input**: All trees lie on a straight line; the modified strict pop rule ($\text{cross} < 0$) preserves all intermediate points on both passes.
- **Strictly Interior Points**: Successfully popped out during left/right hull passes.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
