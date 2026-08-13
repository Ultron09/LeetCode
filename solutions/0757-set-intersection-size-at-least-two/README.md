# [757. Set Intersection Size At Least Two](https://leetcode.com/problems/set-intersection-size-at-least-two/)

**Difficulty:** `Hard`  
**Topics:** [Intervals](../../topics/intervals.md), [Greedy](../../topics/greedy.md), Sorting

---

## 📌 Problem Statement

You are given a 2D integer array `intervals` where `intervals[i] = [starti, endi]` represents all the integers from `starti` to `endi` inclusively.

A **containing set** is an array `nums` where each interval from `intervals` has at least **two** integers in `nums`.

Return the minimum possible size of a containing set.

### Example 1:
```
Input: intervals = [[1,3],[3,7],[8,9]]
Output: 5
Explanation: let nums = [2, 3, 4, 8, 9].
It can be shown that there cannot be any containing array of size 4.
```

### Example 2:
```
Input: intervals = [[1,3],[1,4],[2,5],[3,5]]
Output: 3
Explanation: let nums = [2, 3, 4].
It can be shown that there cannot be any containing array of size 2.
```

### Constraints:
- `1 <= intervals.length <= 3000`
- `intervals[i].length == 2`
- `0 <= starti < endi <= 10^8`

---

## 💡 Intuition & Approach

This problem is a classic interval scheduling/greedy problem, similar to finding the minimum number of arrows to burst balloons, but with the constraint that we need *two* points per interval instead of one.

To minimize the total number of points, when we are forced to pick points for an interval, we should pick them as far to the right as possible (i.e., at the very end of the interval). Points placed further to the right are more likely to also fall into the boundaries of subsequent intervals.

1. **Sorting Strategy:**
   - Sort intervals primarily by their end points in **ascending** order.
   - If two intervals have the same end point, sort them by their start points in **descending** order.
   - *Why descending start points?* This ensures that for a set of intervals ending at the same point, the shortest interval (the one starting latest) is processed first. If we satisfy the shortest interval by picking points at its end, those same points will automatically satisfy any longer interval ending at the same location.

2. **Greedy Choice:**
   - Maintain a running count of the `size` of our containing set.
   - We don't need to keep all points; we only care about the **two largest** points we've added so far, let's call them `largest` and `second_largest`.
   - Iterate over the sorted intervals:
     - **Case 1**: `interval.start > largest`
       - Both our tracked points are strictly before this interval starts. We must add **two** new points. The optimal points are the very end of the interval: `end - 1` and `end`.
       - `size += 2`, `second_largest = end - 1`, `largest = end`.
     - **Case 2**: `interval.start > second_largest` (but $\le$ `largest`)
       - Exactly one of our points (`largest`) falls inside the interval. We need to add **one** more point. The optimal point is `end`.
       - `size += 1`, `second_largest = largest`, `largest = end`.
     - **Case 3**: `interval.start <= second_largest`
       - Both `second_largest` and `largest` are inside the interval. The interval is already satisfied. Do nothing.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N \log N)$ — Dominated by the sorting step. The single pass over the intervals takes $\mathcal{O}(N)$.
- **Space Complexity:** $\mathcal{O}(\log N)$ or $\mathcal{O}(1)$ — For the sorting stack overhead. The algorithm itself requires only a few integers to track the largest points.

---

## 🔍 Edge Cases Considered

- **Overlapping boundaries:** Intervals that share only boundaries (e.g., `[1, 2]` and `[2, 3]`). The greedy algorithm strictly checks `> largest`, correctly identifying if points need to be added.
- **Fully nested intervals:** Sorting ensures the most restrictive (shortest) intervals ending at the same position are handled first, enforcing correct point placement.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
