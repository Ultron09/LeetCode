# [42. Trapping Rain Water](https://leetcode.com/problems/trapping-rain-water/)

**Difficulty:** `Hard`  
**Topics:** [Two Pointers](../../topics/two-pointers.md), [Dynamic Programming](../../topics/dynamic-programming.md), [Stack & Queue](../../topics/stack-and-queue.md)

---

## 📌 Problem Statement

Given `n` non-negative integers representing an elevation map where the width of each bar is `1`, compute how much water it can trap after raining.

### Example 1:
```
Input: height = [0,1,0,2,1,0,1,3,2,1,2,1]
Output: 6
Explanation: The elevation map traps 6 units of rain water.
```

### Example 2:
```
Input: height = [4,2,0,3,2,5]
Output: 9
```

### Constraints:
- `n == height.length`
- $1 \le n \le 2 \times 10^4$
- $0 \le \text{height}[i] \le 10^5$

---

## 💡 Intuition & Approach

### 1. The Min-Max Water Boundary Principle
The amount of water trapped above any bar at index $i$ is governed by:
$$\text{water}[i] = \max(0, \, \min(\text{leftMax}[i], \text{rightMax}[i]) - \text{height}[i])$$

### 2. Space Optimization via Two Pointers
Instead of precomputing prefix and suffix max arrays ($\mathcal{O}(N)$ space), maintain two converging pointers `left = 0` and `right = n - 1` along with running maximums `leftMax` and `rightMax`:
- If `height[left] < height[right]`:
  - The water level at `left` is strictly constrained by `leftMax` (since `height[right]` guarantees that the right boundary is $\ge \text{leftMax}$).
  - If `height[left] >= leftMax`, update `leftMax = height[left]`.
  - Else, add `leftMax - height[left]` to `waterTrapped`.
  - Advance `left++`.
- Otherwise:
  - Symmetrically, the water level at `right` is strictly constrained by `rightMax`.
  - If `height[right] >= rightMax`, update `rightMax = height[right]`.
  - Else, add `rightMax - height[right]` to `waterTrapped`.
  - Advance `right--`.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N)$ where $N \le 2 \times 10^4$ (each bar is visited once).
- **Space Complexity:** $\mathcal{O}(1)$ auxiliary space.

---

## 🔍 Edge Cases Considered

- **Flat elevation map** (`[3, 3, 3]`): Correctly traps 0 water.
- **Strictly increasing / decreasing maps**: Correctly traps 0 water.
- **$N < 3$**: Cannot form any enclosed valley $\implies$ returns 0.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
