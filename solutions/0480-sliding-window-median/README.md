# [480. Sliding Window Median](https://leetcode.com/problems/sliding-window-median/)

**Difficulty:** `Hard`  
**Topics:** [Sliding Window](../../topics/sliding-window.md), [Heaps / Priority Queue](../../topics/heaps-and-priority-queues.md)

---

## 📌 Problem Statement

The **median** is the middle value in an ordered integer list. If the size of the list is even, there is no middle value, and the median is the mean of the two middle values.

- For example, if `arr = [2,3,4]`, the median is `3`.
- For example, if `arr = [1,2,3,4]`, the median is `(2 + 3) / 2 = 2.5`.

You are given an integer array `nums` and an integer `k`. There is a sliding window of size `k` moving from the very left of the array to the very right. You can only see the `k` numbers in the window. Each time the sliding window moves right by one position.

Return the *median array* for each window in the original array. Answers within $10^{-5}$ of the actual value will be accepted.

### Example 1:
```
Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
Output: [1.00000,-1.00000,-1.00000,3.00000,5.00000,6.00000]
Explanation: 
Window position                Median
---------------                -----
[1  3  -1] -3  5  3  6  7        1
 1 [3  -1  -3] 5  3  6  7       -1
 1  3 [-1  -3  5] 3  6  7       -1
 1  3  -1 [-3  5  3] 6  7        3
 1  3  -1  -3 [5  3  6] 7        5
 1  3  -1  -3  5 [3  6  7]       6
```

### Example 2:
```
Input: nums = [1,2,3,4,2,3,1,4,2], k = 3
Output: [2.00000,3.00000,3.00000,3.00000,2.00000,3.00000,2.00000]
```

### Constraints:
- $1 \le k \le \text{nums.length} \le 10^5$
- $-2^{31} \le \text{nums}[i] \le 2^{31} - 1$

---

## 💡 Intuition & Approach

### 1. Dual Heaps Partitioning
To dynamically maintain the median of a sliding window of size $k$, partition the window into two halves:
- **`small` (Max-Heap)**: Stores the smaller $\lceil k / 2 \rceil$ elements.
- **`large` (Min-Heap)**: Stores the remaining $\lfloor k / 2 \rfloor$ elements.
- **Size Invariant**:
  $$\text{smallSize} = \left\lceil \frac{k}{2} \right\rceil = \frac{k + 1}{2}, \quad \text{largeSize} = \left\lfloor \frac{k}{2} \right\rfloor = \frac{k}{2}$$
- **Ordering Invariant**:
  $$\max(\text{small}) \le \min(\text{large})$$

### 2. Lazy Deletion Mechanism
Standard binary heaps (`std::priority_queue`) do not support arbitrary element deletion in $\mathcal{O}(\log k)$ time. We resolve this using **lazy deletion with a frequency hash map**:
1. When an outgoing element `nums[i - k]` exits the sliding window:
   - Record its deletion count in a hash map `delayed[nums[i - k]]++`.
   - Decrement the active logical counter `smallSize` or `largeSize`.
2. **Pruning**: Whenever the top element of `small` or `large` matches an entry in `delayed`, pop it from the heap and decrement its count in `delayed`.
3. **Rebalancing**: If `smallSize > largeSize + 1` or `smallSize < largeSize`, shift elements across heaps and prune invalid tops immediately.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N \log k)$
  - Each element is inserted into a heap at most once and deleted at most once.
  - Heap operations and pruning take amortized $\mathcal{O}(\log k)$ time per window slide.
  - Overall time for $N$ elements is $\mathcal{O}(N \log k)$.
- **Space Complexity:** $\mathcal{O}(N)$ worst case ($\mathcal{O}(k)$ average)
  - At most $N$ elements accumulate in the dual heaps and `delayed` hash map across the entire sliding window trajectory.

---

## 🔍 Edge Cases Considered

- **$k = 1$**: Median is just the element itself. Handled trivially by `small.top()`.
- **$k = N$**: Exact single window median evaluated once.
- **32-bit Integer Overflow**: When adding `small.top() + large.top()` for even $k$, using `long long` prevents signed 32-bit overflow when values are near `INT_MAX` (e.g. `2147483647 + 2147483647`).
- **Duplicate Values**: Handled naturally via frequency tracking in `delayed`.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
