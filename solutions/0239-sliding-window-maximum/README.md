# [239. Sliding Window Maximum](https://leetcode.com/problems/sliding-window-maximum/)

**Difficulty:** `Hard`  
**Topics:** [Array](../../topics/arrays-and-hashing.md), [Sliding Window](../../topics/sliding-window.md), [Queue](../../topics/stack-and-queue.md), [Monotonic Queue](../../topics/sliding-window.md), [Heap (Priority Queue)](../../topics/heaps-and-priority-queues.md)

---

## 📌 Problem Statement

You are given an array of integers `nums`, there is a sliding window of size `k` which is moving from the very left of the array to the very right. You can only see the `k` numbers in the window. Each time the sliding window moves right by one position.

Return **the max sliding window**.

### Example 1:
```
Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
Output: [3,3,5,5,6,7]
Explanation: 
Window position                Max
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7
```

### Example 2:
```
Input: nums = [1], k = 1
Output: [1]
```

### Constraints:
- $1 \le \text{nums.length} \le 10^5$
- $-10^4 \le \text{nums}[i] \le 10^4$
- $1 \le k \le \text{nums.length}$

---

## 💡 Intuition & Approach

### 1. Why Not a Heap ($\mathcal{O}(N \log K)$)?
A standard max-heap requires $\mathcal{O}(N \log K)$ with delayed/lazy deletions. Using a **Monotonic Queue (Double-Ended Queue / `std::deque`)** achieves optimal linear $\mathcal{O}(N)$ time.

### 2. Monotonic Decreasing Deque Invariant
We store **indices** in a `std::deque<int>` such that the corresponding array elements are strictly decreasing:
- **Evict Expired Elements**: If the index at `dq.front()` falls outside $[i - k + 1, i]$, pop from the front.
- **Maintain Monotonicity**: Before inserting index $i$, pop all elements from the back where $\text{nums}[\text{dq.back()}] \le \text{nums}[i]$. Since index $i$ appears later and has a greater or equal value, older smaller elements can never be the maximum of any future window.
- **Extract Maximum**: The front of the deque `dq.front()` always indexes the maximum element of the current window.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N)$ where $N = \text{nums.length} \le 10^5$ (each index enters and leaves the deque at most once).
- **Space Complexity:** $\mathcal{O}(K)$ auxiliary memory for the double-ended queue.

---

## 🔍 Edge Cases Considered

- **$k = 1$**: Handled natively $\implies \text{returns } \text{nums}$.
- **$k = N$**: Deque processes entire array and returns a single element representing the global maximum.
- **Strictly Increasing / Strictly Decreasing Arrays**: Queue length stays minimal ($\le K$) without edge anomalies.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
