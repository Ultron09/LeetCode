# [56. Merge Intervals](https://leetcode.com/problems/merge-intervals/)

**Difficulty:** `Medium`  
**Topics:** [Intervals](../../topics/intervals.md)

---

## 📌 Problem Statement

Given an array of `intervals` where `intervals[i] = [start_i, end_i]`, merge all overlapping intervals, and return an array of the non-overlapping intervals that cover all the intervals in the input.

### Example 1:
```
Input: intervals = [[1,3],[2,6],[8,10],[15,18]]
Output: [[1,6],[8,10],[15,18]]
Explanation: Since intervals [1,3] and [2,6] overlap, merge them into [1,6].
```

### Example 2:
```
Input: intervals = [[1,4],[4,5]]
Output: [[1,5]]
Explanation: Intervals [1,4] and [4,5] are considered overlapping.
```

### Constraints:
- `1 <= intervals.length <= 10^4`
- `intervals[i].length == 2`
- `0 <= start_i <= end_i <= 10^4`

---

## 💡 Intuition & Approach

1. **Sorting**: If the intervals are not sorted, it's hard to find overlapping elements without doing an $O(N^2)$ comparison between every pair. If we sort them by their start times, any overlapping intervals will be adjacent to each other in the sorted list.
2. **Greedy Merging**: Once sorted, we can iterate through the intervals and maintain a "current" interval.
   - For each interval, check if its start time is less than or equal to the end time of the "current" merged interval.
   - If it is, the intervals overlap. Update the end time of the "current" interval to the maximum of both end times (since one might fully enclose the other).
   - If it's not, they do not overlap. The "current" interval is finalized and pushed to our result, and the new interval becomes the new "current" interval.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N \log N)$ — Sorting the array of $N$ intervals dominates the time complexity. The linear scan takes $\mathcal{O}(N)$.
- **Space Complexity:** $\mathcal{O}(\log N)$ or $\mathcal{O}(N)$ — Depending on the language's built-in sorting algorithm, sorting takes some auxiliary space. Excluding the space for the output, in C++ `std::sort` generally takes $\mathcal{O}(\log N)$ space.

---

## 🔍 Edge Cases Considered

- Empty array (`intervals.size() == 0`). Handled explicitly (though constraints say length $\ge 1$).
- Fully enclosed intervals (e.g., `[1, 4]` and `[2, 3]`). This is handled properly by using `max()` to find the furthest end time.
- Unsorted intervals (e.g., `[2, 3]` before `[1, 4]`). The sorting step correctly orders these.
- Identical intervals (e.g., `[1, 2], [1, 2]`). They will be merged seamlessly into `[1, 2]`.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
