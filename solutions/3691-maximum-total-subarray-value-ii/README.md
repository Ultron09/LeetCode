# [3691. Maximum Total Subarray Value II](https://leetcode.com/problems/maximum-total-subarray-value-ii/)

**Difficulty:** `Hard`  
**Topics:** [Heaps & Priority Queues](../../topics/heaps-and-priority-queues.md), [Arrays & Hashing](../../topics/arrays-and-hashing.md), [Greedy](../../topics/greedy.md)

---

## 📌 Problem Statement

You are given an integer array `nums` of length $n$ and an integer $k$.

You must select exactly $k$ distinct subarrays `nums[l..r]` of `nums`. Subarrays may overlap, but the exact same subarray (same $l$ and $r$) cannot be chosen more than once.

The **value** of a subarray `nums[l..r]` is defined as:
$$\text{Value}(l, r) = \max(nums[l..r]) - \min(nums[l..r])$$

The **total value** is the sum of the values of all chosen subarrays.

Return the **maximum possible total value** you can achieve.

### Example 1:
```
Input: nums = [1,3,2], k = 2
Output: 4
Explanation:
- Choose nums[0..1] = [1, 3] -> max 3, min 1 -> 3 - 1 = 2.
- Choose nums[0..2] = [1, 3, 2] -> max 3, min 1 -> 3 - 1 = 2.
Total = 2 + 2 = 4.
```

### Example 2:
```
Input: nums = [4,2,5,1], k = 3
Output: 12
Explanation:
- Choose nums[0..3] = [4, 2, 5, 1] -> max 5, min 1 -> 4.
- Choose nums[1..3] = [2, 5, 1] -> max 5, min 1 -> 4.
- Choose nums[2..3] = [5, 1] -> max 5, min 1 -> 4.
Total = 4 + 4 + 4 = 12.
```

### Constraints:
- $1 \le n = \text{nums.length} \le 5 \times 10^4$
- $0 \le \text{nums}[i] \le 10^9$
- $1 \le k \le \min(10^5, n(n+1)/2)$

---

## 💡 Intuition & Approach

### 1. Monotonicity of Subarray Range
For a fixed left boundary $l$:
- Expanding the right endpoint $r$ adds elements, meaning $\max(nums[l..r])$ is non-decreasing and $\min(nums[l..r])$ is non-increasing.
- Therefore, the subarray value $V(l, r) = \max(nums[l..r]) - \min(nums[l..r])$ is **monotonically non-decreasing** as $r$ increases from $l$ to $n - 1$.
- Consequently, for any starting index $l$, the largest possible subarray value is achieved at $r = n - 1$. The next best is at $r = n - 2$, and so on.

### 2. Fast RMQ via Sparse Table
To evaluate $V(l, r) = \max(nums[l..r]) - \min(nums[l..r])$ in $\mathcal{O}(1)$ time:
- Construct two Sparse Tables `st_max` and `st_min` in $\mathcal{O}(N \log N)$ time and space.
- Query range maximum and minimum with length $len = r - l + 1$ and $j = \lfloor \log_2(len) \rfloor$:
  $$\text{RMQ}(l, r) = \max(st[j][l], st[j][r - 2^j + 1])$$

### 3. Greedy K-Way Max-Heap Selection
- Maintain a **Max-Heap** of candidates $(V(l, r), l, r)$.
- Initially push the best candidate for every left index $l \in [0, n - 1]$, which is $(V(l, n - 1), l, n - 1)$.
- Repeat $k$ times:
  1. Pop the maximum element $(v, l, r)$.
  2. Add $v$ to `totalValue`.
  3. If $r - 1 \ge l$, push the next best candidate $(V(l, r - 1), l, r - 1)$ for that same left index $l$ into the heap.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}((N + K) \log N)$
  - Sparse Table construction: $\mathcal{O}(N \log N)$.
  - Heap initialization: $\mathcal{O}(N \log N)$.
  - $K$ pop and push iterations: $\mathcal{O}(K \log N)$.
  - Total operations $\approx (50000 + 100000) \times 16 \approx 2.4 \times 10^6$ ($< 25$ ms in C++).
- **Space Complexity:** $\mathcal{O}(N \log N)$
  - Sparse Table size $17 \times N \times 4$ bytes $\approx 3.4$ MB.
  - Max-Heap size at most $N$ elements.

---

## 🔍 Edge Cases Considered

- **$K = 1$**: Pops the single globally maximal subarray.
- **Identical Elements ($nums[i] = c$)**: Values are all 0; correctly accumulates 0.
- **Large $N = 5 \times 10^4, K = 10^5$**: Uses 64-bit integer (`long long`) for `totalValue` to avoid overflow up to $10^{14}$.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
