# [410. Split Array Largest Sum](https://leetcode.com/problems/split-array-largest-sum/)

**Difficulty:** `Hard`  
**Topics:** [Binary Search](../../topics/binary-search.md), [Dynamic Programming](../../topics/dynamic-programming.md), [Greedy](../../topics/greedy.md), [Arrays & Hashing](../../topics/arrays-and-hashing.md)

---

## 📌 Problem Statement

Given an integer array `nums` and an integer `k`, split `nums` into `k` non-empty subarrays such that the largest sum of any subarray is minimized.

Return the minimized largest sum of the split.

A **subarray** is a contiguous part of the array.

### Example 1:
```
Input: nums = [7,2,5,10,8], k = 2
Output: 18
Explanation: There are four ways to split nums into two subarrays.
The best way is to split it into [7,2,5] and [10,8], where the largest sum among the two subarrays is only 18.
```

### Example 2:
```
Input: nums = [1,2,3,4,5], k = 2
Output: 9
Explanation: There are four ways to split nums into two subarrays.
The best way is to split it into [1,2,3] and [4,5], where the largest sum among the two subarrays is only 9.
```

### Constraints:
- $1 \le \text{nums.length} \le 1000$
- $0 \le \text{nums}[i] \le 10^6$
- $1 \le k \le \min(50, \text{nums.length})$

---

## 💡 Intuition & Approach

### 1. Identifying Search on Answer Space
The problem asks to **minimize the maximum subarray sum**. This minimax structure on a contiguous partition exhibits strict monotonicity:
- If a maximum subarray sum $S$ is feasible with $\le k$ partitions, then any larger threshold $S' > S$ is also feasible.
- If $S$ is infeasible (requiring $> k$ partitions), then any smaller threshold $S' < S$ is strictly impossible.

The feasibility predicate $P(S)$ evaluates to a monotonic sequence:
$$[\text{false}, \text{false}, \dots, \text{false}, \mathbf{true}, \text{true}, \dots]$$
Thus, we can binary search directly over the optimal threshold $S$.

### 2. Search Space Bounds
- **Lower Bound (`low`)**: $\max(\text{nums})$. No subarray can split an individual element; therefore, the maximum single element must fit into at least one partition.
- **Upper Bound (`high`)**: $\sum \text{nums}$. If $k = 1$, the entire array is placed in a single subarray.
- The search range is $[\max(\text{nums}), \sum \text{nums}]$, bounded by $[0, 10^9]$.

### 3. Greedy Feasibility Verification
Given a candidate threshold `targetMaxSum`:
1. Start with `currentSum = 0` and `subarraysCount = 1`.
2. Iterate through each element `num` in `nums`:
   - If `currentSum + num > targetMaxSum`: start a new partition (`subarraysCount++`, `currentSum = num`). If `subarraysCount > k`, immediately return `false`.
   - Else: `currentSum += num`.
3. Return `subarraysCount <= k`.

Because all elements are non-negative ($\text{nums}[i] \ge 0$), making each subarray as large as possible without exceeding `targetMaxSum` leaves the maximum possible remaining capacity for subsequent partitions, proving greedy choice optimality.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N \log(\sum \text{nums} - \max(\text{nums})))$
  - Binary search over the range of size $\le 10^9$ requires $\log_2(10^9) \approx 30$ iterations.
  - Each iteration evaluates the feasibility function in $\mathcal{O}(N)$ linear time.
  - Total operations: $30 \times 1000 = 3 \times 10^4 \ll 10^8$ operations (executes in $< 1\text{ ms}$).
- **Space Complexity:** $\mathcal{O}(1)$
  - Only scalar variables are maintained for the binary search pointers and greedy accumulator.

---

## 🔍 Edge Cases Considered

- **$k = 1$**: Output is the total sum of the entire array ($\sum \text{nums}$).
- **$k = N$**: Each element forms its own subarray; output is $\max(\text{nums})$.
- **Single Element Array ($N = 1, k = 1$)**: Returns `nums[0]`.
- **All Zeroes**: Correctly outputs `0` without division-by-zero or infinite loop.
- **Large Values ($nums[i] = 10^6$)**: Total sum can reach $10^9$; 64-bit integer arithmetic (`long long`) prevents 32-bit signed overflow during midpoint calculation.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
