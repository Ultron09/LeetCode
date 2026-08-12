# [699. Falling Squares](https://leetcode.com/problems/falling-squares/)

**Difficulty:** `Hard`  
**Topics:** [Intervals](../../topics/intervals.md)

---

## 📌 Problem Statement

There are several squares being dropped onto the X-axis of a 2D plane. You are given a 2D integer array `positions` where `positions[i] = [lefti, sideLengthi]` represents the i-th square with a side length of `sideLengthi` that is dropped with its left edge aligned with X-coordinate `lefti`.

Each square is dropped one at a time from a height above any landed squares. It then falls downward until it either lands on **the top side** of another square or on the X-axis. A square **brushing** the left/right side of another square does **not** count as landing on it.

After each square is dropped, record the height of the **current tallest stack** of squares.

### Example 1:
```
Input: positions = [[1,2],[2,3],[6,1]]
Output: [2,5,5]
Explanation:
  Square 1: [1,3) at height 2.
  Square 2: [2,5) overlaps square 1 → lands at height 2 → top at 5.
  Square 3: [6,7) no overlap → lands on ground → top at 1.
  Running max: [2, 5, 5].
```

### Example 2:
```
Input: positions = [[100,100],[200,100]]
Output: [100,100]
Explanation: Square 2 occupies [200,300) which only *brushes* square 1's
right edge at x=200. No overlap → lands on ground.
```

### Constraints:
- `1 <= positions.length <= 1000`
- `1 <= lefti <= 10^8`
- `1 <= sideLengthi <= 10^6`

---

## 💡 Intuition & Approach

### 1. Key Observation — Interval Overlap

Each square occupies a half-open interval `[left, left + side)` on the X-axis. Two squares overlap (and thus one can land on the other) if and only if:

$$l_1 < r_2 \quad \text{AND} \quad l_2 < r_1$$

This is the **standard open-interval overlap test**. Using strict inequalities ensures that squares that merely "brush" at a shared endpoint are **not** considered overlapping — matching the problem's requirement.

### 2. Brute Force Scan (Optimal for N ≤ 1000)

For each new square $i$:
1. Compute its interval $[\text{left}_i, \text{left}_i + \text{side}_i)$.
2. **Scan all previously placed squares** $j < i$. For each overlapping square, track the maximum top-height.
3. The new square's top height = `maxOverlapHeight + side_i`.
4. Update the running global maximum.

With $N \le 1000$, this gives $\sim 500K$ comparisons — trivially fast.

### 3. Alternative: Coordinate Compression + Segment Tree (O(N log N))

For larger $N$, one can:
1. **Coordinate compress** all left/right endpoints to indices $[0, 2N)$.
2. Maintain a **segment tree with lazy propagation** supporting:
   - **Range max query** over $[\text{left}_i, \text{right}_i)$ to find the base height.
   - **Range set update** to set the height of $[\text{left}_i, \text{right}_i)$ to the new top.
3. This achieves $\mathcal{O}(N \log N)$ total.

For $N \le 1000$ the brute force is cleaner and equally fast, so we use that.

### 4. Step-by-Step Trace (Example 1)

```
positions = [[1,2],[2,3],[6,1]]

Drop 1: [1,3), side=2
  No previous squares → base=0, top=2
  globalMax = 2 → ans[0] = 2

Drop 2: [2,5), side=3
  Check [1,3): 2 < 3 && 1 < 5 → overlap! height=2
  base=2, top=2+3=5
  globalMax = 5 → ans[1] = 5

Drop 3: [6,7), side=1
  Check [1,3): 6 < 3? NO → no overlap
  Check [2,5): 6 < 5? NO → no overlap
  base=0, top=1
  globalMax = max(5,1) = 5 → ans[2] = 5

Result: [2, 5, 5] ✓
```

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N^2)$ — for each of $N$ squares, scan up to $N-1$ previous squares.
- **Space Complexity:** $\mathcal{O}(N)$ — store intervals and heights for all placed squares.

---

## 🔍 Edge Cases Considered

- **Brushing at endpoints:** `[100,200)` and `[200,300)` do NOT overlap — handled by strict `<` comparisons.
- **Complete overlap:** A small square dropped inside a large one lands on top.
- **Identical positions:** Two squares at the same position stack directly.
- **Single square:** Returns `[side]`.
- **No overlaps at all:** Each square lands on the ground; running max is the largest side seen so far.
- **Cascade stacking:** Square A on ground, B partially on A, C partially on B — each query finds the correct max base.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
