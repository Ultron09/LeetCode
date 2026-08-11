# [295. Find Median from Data Stream](https://leetcode.com/problems/find-median-from-data-stream/)

**Difficulty:** `Hard`  
**Topics:** [Heaps & Priority Queues](../../topics/heaps-and-priority-queues.md), [Design](../../topics/arrays-and-hashing.md), [Data Stream](../../topics/heaps-and-priority-queues.md), [Two Pointers](../../topics/two-pointers.md)

---

## 📌 Problem Statement

The **median** is the middle value in an ordered integer list. If the size of the list is even, there is no middle value, and the median is the mean of the two middle values.

- For example, for `arr = [2,3,4]`, the median is `3`.
- For example, for `arr = [2,3]`, the median is `(2 + 3) / 2 = 2.5`.

Implement the `MedianFinder` class:
- `MedianFinder()` initializes the `MedianFinder` object.
- `void addNum(int num)` adds the integer `num` from the data stream to the data structure.
- `double findMedian()` returns the median of all elements so far. Answers within $10^{-5}$ of the actual answer will be accepted.

### Example 1:
```
Input:
["MedianFinder", "addNum", "addNum", "findMedian", "addNum", "findMedian"]
[[], [1], [2], [], [3], []]
Output:
[null, null, null, 1.5, null, 2.0]

Explanation:
MedianFinder medianFinder = new MedianFinder();
medianFinder.addNum(1);    // arr = [1]
medianFinder.addNum(2);    // arr = [1, 2]
medianFinder.findMedian(); // return 1.5 (i.e., (1 + 2) / 2)
medianFinder.addNum(3);    // arr[1, 2, 3]
medianFinder.findMedian(); // return 2.0
```

### Constraints:
- $-10^5 \le \text{num} \le 10^5$
- There will be at least one element in the data structure before calling `findMedian`.
- At most $5 \times 10^4$ calls will be made to `addNum` and `findMedian`.

---

## 💡 Intuition & Approach

### 1. Two-Heaps Dual Invariant Strategy
To track the median dynamically without re-sorting the whole array on each insertion, split the incoming numbers into two halves:
- **`maxHeap` (Lower Half)**: Stores the smaller $\lceil N/2 \rceil$ numbers. Its root gives the maximum element of the lower half.
- **`minHeap` (Upper Half)**: Stores the larger $\lfloor N/2 \rfloor$ numbers. Its root gives the minimum element of the upper half.

### 2. Invariants Maintained:
1. **Value Ordering**: $\max(\text{maxHeap}) \le \min(\text{minHeap})$.
2. **Size Balance**: $|\text{maxHeap}| - |\text{minHeap}| \in \{0, 1\}$.

### 3. Step-by-Step Execution:
- **`addNum(num)`**:
  1. Push `num` into `maxHeap`.
  2. Balance values: Transfer the top of `maxHeap` to `minHeap`.
  3. Balance size: If $|\text{minHeap}| > |\text{maxHeap}|$, transfer the top of `minHeap` back to `maxHeap`.
- **`findMedian()`**:
  - If total count is odd ($|\text{maxHeap}| > |\text{minHeap}|$), return `maxHeap.top()`.
  - If total count is even, return `(maxHeap.top() + minHeap.top()) / 2.0`.

---

## 🚀 Follow-Up Optimizations

1. **If numbers are in range $[0, 100]$**:
   - Maintain a frequency bucket array `count[101]` and a running total count $N$.
   - `addNum(num)` takes $\mathcal{O}(1)$ (`count[num]++`).
   - `findMedian()` takes $\mathcal{O}(1)$ time (at most 101 bucket iterations to find the $\lfloor N/2 \rfloor$-th element).
2. **If 99% of numbers are in range $[0, 100]$**:
   - Keep `count[101]` for $[0, 100]$, and two smaller heaps/counters for outlier values $< 0$ and $> 100$.

---

## ⚡ Complexity Analysis

- **Time Complexity:**
  - `addNum(num)`: $\mathcal{O}(\log N)$ per insertion.
  - `findMedian()`: $\mathcal{O}(1)$ immediate query.
- **Space Complexity:** $\mathcal{O}(N)$ to store all $N$ elements across both heaps.

---

## 🔍 Edge Cases Considered

- **Negative Numbers**: Handled natively by max/min priority queues.
- **Duplicates**: Handled without order corruption.
- **Odd vs Even Totals**: Automatically toggles between single median and average of pair.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
