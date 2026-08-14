# [862. Shortest Subarray with Sum at Least K](https://leetcode.com/problems/shortest-subarray-with-sum-at-least-k/)

**Difficulty:** `Hard`  
**Topics:** [Stack & Queue](../../topics/stack-and-queue.md), [Sliding Window](../../topics/sliding-window.md), [Arrays & Hashing](../../topics/arrays-and-hashing.md)

---

## 📌 Problem Statement

Given an integer array `nums` and an integer `k`, return the length of the shortest non-empty subarray of `nums` with a sum of at least `k`. If there is no such subarray, return `-1`.

A subarray is a contiguous part of an array.

### Example 1:
```
Input: nums = [1], k = 1
Output: 1
```

### Example 2:
```
Input: nums = [1,2], k = 4
Output: -1
```

### Example 3:
```
Input: nums = [2,-1,2], k = 3
Output: 3
```

### Constraints:
- `1 <= nums.length <= 10^5`
- `-10^5 <= nums[i] <= 10^5`
- `1 <= k <= 10^9`

---

## 💡 Intuition & Approach

1. **Prefix Sums**: To quickly find the sum of any subarray `nums[i..j]`, we can precompute the prefix sum array `prefix`. The sum of `nums[i..j]` is simply `prefix[j+1] - prefix[i]`. We want to find the minimum `j + 1 - i` such that `prefix[j+1] - prefix[i] >= k`.
2. **Negative Values Complication**: Because there are negative values in `nums`, the prefix sum array is not monotonically increasing. This means we cannot use a simple sliding window / two pointers technique.
3. **Monotonic Deque Strategy**:
   - We maintain a double-ended queue (deque) of indices. We iterate through `prefix[j]` from `0` to `n`.
   - **Condition 1 (Finding Shortest Valid Subarray)**: If the difference between the current prefix sum `prefix[j]` and the prefix sum at the front of the deque `prefix[dq.front()]` is $\ge k$, we have found a valid subarray. We update our minimum length. Importantly, we can then `pop_front()` because any future `j` (which will be larger) would result in a longer subarray if paired with `dq.front()`. We already found the optimal window ending for `dq.front()`.
   - **Condition 2 (Maintaining Monotonicity)**: Before adding `j` to the back of the deque, we check the back elements. If `prefix[j] <= prefix[dq.back()]`, we can `pop_back()`. Why? Because `prefix[j]` is both smaller and appears later than `prefix[dq.back()]`. Any future index $X > j$ looking for a starting point to satisfy `prefix[X] - prefix[start] >= k` would strictly prefer `j` over `dq.back()`, since $j$ yields a shorter length and requires a less demanding difference.
   - Doing this ensures the prefix values referenced by indices in the deque are monotonically strictly increasing.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N)$ — We iterate through the prefix sums array of size $N+1$. Each index is pushed into the deque exactly once and popped at most once, meaning operations on the deque take amortized $\mathcal{O}(1)$ time.
- **Space Complexity:** $\mathcal{O}(N)$ — To store the prefix sum array and the deque, both of which take at most $\mathcal{O}(N)$ extra space.

---

## 🔍 Edge Cases Considered

- Arrays containing negative elements disrupting the monotonic property.
- Extremely large elements or a large $k$ requiring 64-bit integers (`long long` for prefix sums).
- Single element satisfying $k$, requiring length 1 bounds checking.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
