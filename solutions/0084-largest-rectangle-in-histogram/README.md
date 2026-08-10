# [84. Largest Rectangle in Histogram](https://leetcode.com/problems/largest-rectangle-in-histogram/)

**Difficulty:** `Hard`  
**Topics:** [Stack & Queue](../../topics/stack-and-queue.md), [Arrays & Hashing](../../topics/arrays-and-hashing.md), [Monotonic Stack](../../topics/stack-and-queue.md)

---

## 📌 Problem Statement

Given an array of integers `heights` representing the histogram's bar height where the width of each bar is `1`, return the area of the largest rectangle in the histogram.

### Example 1:
```
Input: heights = [2,1,5,6,2,3]
Output: 10
Explanation: The largest rectangle is formed by bars [5, 6] with height 5 and width 2, giving area = 10.
```

### Example 2:
```
Input: heights = [2,4]
Output: 4
```

### Constraints:
- $1 \le \text{heights.length} \le 10^5$
- $0 \le \text{heights}[i] \le 10^4$

---

## 💡 Intuition & Approach

### 1. Monotonic Increasing Stack ($\mathcal{O}(N)$ Time)
For each bar $i$, consider the maximum rectangle that uses `heights[i]` as its bottleneck (minimum height):
- Left boundary: First bar to the left with height $< \text{heights}[i]$.
- Right boundary: First bar to the right with height $< \text{heights}[i]$.
- Width of this rectangle: $\text{width} = \text{right} - \text{left} - 1$.
- Area: $\text{area} = \text{heights}[i] \times \text{width}$.

### 2. Single-Pass Execution with Sentinel Flushing
- Maintain a stack of bar indices in **strictly increasing** order of heights.
- Append a virtual sentinel bar with height $0$ at index $n$ to flush all remaining elements in the stack.
- When encountering `heights[i] < heights[stack.top()]`:
  - Pop height $h = \text{heights}[\text{st.top()}]$.
  - The popped bar's right boundary is $i$.
  - Its left boundary is the new stack top (or $-1$ if stack becomes empty).
  - Calculate area: $h \times (i - \text{st.top()} - 1)$ and update `maxArea`.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N)$ — Each bar index is pushed and popped from the stack at most once.
- **Space Complexity:** $\mathcal{O}(N)$ in the worst case for strictly increasing histogram bars.

---

## 🔍 Edge Cases Considered

- **Monotonically increasing heights** (`[1, 2, 3, 4]`): Flushed correctly by sentinel $0$ at index $n$.
- **All bars of identical height** (`[2, 2, 2, 2]`): Computed correctly without undercounting.
- **Single element** (`[1]`): Area = 1.
- **Heights with zero** (`[0, 9]`): Zero heights correctly boundary positive bars.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
