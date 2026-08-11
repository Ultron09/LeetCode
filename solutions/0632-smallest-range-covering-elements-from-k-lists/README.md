# [632. Smallest Range Covering Elements from K Lists](https://leetcode.com/problems/smallest-range-covering-elements-from-k-lists/)

**Difficulty:** `Hard`  
**Topics:** [Sliding Window](../../topics/sliding-window.md), [Heaps / Priority Queue](../../topics/heaps-and-priority-queues.md), [Two Pointers](../../topics/two-pointers.md), [Greedy](../../topics/greedy.md)

---

## 📌 Problem Statement

You have `k` lists of sorted integers in **non-decreasing order**. Find the **smallest range** that includes at least one number from each of the `k` lists.

We define the range `[a, b]` is smaller than range `[c, d]` if:
- `b - a < d - c`, or
- `a < c` if `b - a == d - c`.

### Example 1:
```
Input: nums = [[4,10,15,24,26],[0,9,12,20],[5,18,22,30]]
Output: [20,24]
Explanation: 
List 1: [4, 10, 15, 24, 26], 24 is in range [20,24].
List 2: [0, 9, 12, 20], 20 is in range [20,24].
List 3: [5, 18, 22, 30], 22 is in range [20,24].
```

### Example 2:
```
Input: nums = [[1,2,3],[1,2,3],[1,2,3]]
Output: [1,1]
```

### Constraints:
- `nums.length == k`
- $1 \le k \le 3500$
- $1 \le \text{nums}[i].\text{length} \le 50$
- $-10^5 \le \text{nums}[i][j] \le 10^5$
- `nums[i]` is sorted in **non-decreasing order**.

---

## 💡 Intuition & Approach

### 1. K-Pointer Simultaneous Window
To cover at least one number from all $k$ lists, we must simultaneously choose an element $x_i \in \text{nums}[i]$ for each $i \in [0, k - 1]$. The valid range covering this configuration is:
$$[\min_{0 \le i < k} x_i, \; \max_{0 \le i < k} x_i]$$
The width of this range is $\max(x_i) - \min(x_i)$.

### 2. Min-Heap Multi-Pointer Sweep (Optimal $\mathcal{O}(N \log k)$)
1. **Initialize Min-Heap**: Insert the first element `nums[i][0]` of each list along with its coordinates `(val, row, col)`. Keep track of the global maximum `currentMax` among all elements currently inside the heap.
2. **Evaluate & Advance**:
   - Extract the minimum element `(currentMin, row, col)` from the min-heap.
   - The current active window is `[currentMin, currentMax]`.
   - If `currentMax - currentMin < rangeEnd - rangeStart`, update the best range.
   - Advance the pointer in list `row`: if `col + 1 < nums[row].size()`, push `nums[row][col + 1]` into the heap and update `currentMax = max(currentMax, nums[row][col + 1])`.
   - If list `row` is exhausted (`col + 1 == nums[row].size()`), any further advancement cannot cover all $k$ lists, so we terminate the search.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N \log k)$
  - Where $N = \sum |\text{nums}[i]| \le 3500 \times 50 = 1.75 \times 10^5$.
  - The min-heap contains at most $k$ elements at any moment.
  - Each element is pushed and popped at most once ($\mathcal{O}(N \log k)$ total heap operations $\approx 2 \times 10^6$ ops, $< 15\text{ ms}$).
- **Space Complexity:** $\mathcal{O}(k)$
  - Min-heap stores exactly $k$ elements (one per list).

---

## 🔍 Edge Cases Considered

- **$k = 1$**: Handled properly; window has width 0 `[nums[0][0], nums[0][0]]`.
- **Identical Arrays**: Correctly identifies single-point range `[x, x]`.
- **Lists of Varying Lengths**: Gracefully terminates as soon as the shortest list is exhausted.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
