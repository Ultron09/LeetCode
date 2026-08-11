# [391. Perfect Rectangle](https://leetcode.com/problems/perfect-rectangle/)

**Difficulty:** `Hard`  
**Topics:** [Math & Geometry](../../topics/math-and-geometry.md), [Arrays & Hashing](../../topics/arrays-and-hashing.md)

---

## 📌 Problem Statement

Given an array `rectangles` where `rectangles[i] = [xi, yi, ai, bi]` represents an axis-aligned rectangle with bottom-left `(xi, yi)` and top-right `(ai, bi)`.

Return `true` if all the rectangles together form an **exact cover** of a rectangular region.

### Example 1:
```
Input: rectangles = [[1,1,3,3],[3,1,4,2],[3,2,4,4],[1,3,2,4],[2,3,3,4]]
Output: true
Explanation: All 5 rectangles together form an exact cover.
```

### Example 2:
```
Input: rectangles = [[1,1,2,3],[1,3,2,4],[3,1,4,2],[3,2,4,4]]
Output: false
Explanation: There is a gap between the two rectangular regions.
```

### Example 3:
```
Input: rectangles = [[1,1,3,3],[3,1,4,2],[1,3,2,4],[2,2,4,4]]
Output: false
Explanation: Two of the rectangles overlap with each other.
```

### Constraints:
- $1 \le \text{rectangles.length} \le 2 \times 10^4$
- $\text{rectangles}[i].\text{length} == 4$
- $-10^5 \le x_i < a_i \le 10^5$
- $-10^5 \le y_i < b_i \le 10^5$

---

## 💡 Intuition & Approach

### 1. The Corner Parity Theorem
For axis-aligned rectangles to tile a region perfectly (no gaps, no overlaps), **two necessary and sufficient conditions** must hold:

#### Condition 1: Area Conservation
$$\sum_{i=1}^{N} \text{area}(R_i) = \text{area}(\text{Bounding Rectangle})$$

This rules out gaps (area too small) and overlaps beyond the bounding box.

#### Condition 2: Corner Parity
Every corner point in the tiling must appear an **even** number of times (corners of 2 or 4 adjacent rectangles cancel), **except** the 4 corners of the bounding rectangle which must each appear exactly **once** (odd parity).

**Why this works:**
- At any interior vertex of a perfect tiling, exactly 2 or 4 rectangles meet → even corner count → toggling removes them.
- At edge vertices (but not bounding corners), exactly 2 rectangles meet → even count.
- At the 4 bounding corners, exactly 1 rectangle contributes → odd count → they remain in the set.

### 2. Implementation: Toggle Set
- Use a `set<pair<int,int>>` of corners.
- For each rectangle's 4 corners: if present, **remove**; if absent, **insert** (XOR-like toggle).
- After processing all rectangles, exactly the 4 bounding corners should remain.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N \log N)$
  - Each rectangle contributes 4 corner toggle operations on a `std::set` ($\mathcal{O}(\log N)$ each).
  - Can be optimized to $\mathcal{O}(N)$ amortized with `unordered_set` and a custom hash.
- **Space Complexity:** $\mathcal{O}(N)$
  - The corner set stores at most $4N$ entries.

---

## 🔍 Edge Cases Considered

- **Single Rectangle**: Returns `true` — it is its own perfect cover.
- **Overlapping Rectangles**: Total area exceeds bounding area, or corner parity is violated.
- **Gap Between Rectangles**: Total area is less than bounding area.
- **T-junction Corners**: An interior T-junction contributes a corner with odd parity from 1 or 3 rectangles, which correctly triggers failure if the tiling is imperfect.
- **Negative Coordinates**: Fully supported; bounding box uses `min`/`max`.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
