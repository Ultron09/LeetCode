# [3739. Count Subarrays With Majority Element II](https://leetcode.com/problems/count-subarrays-with-majority-element-ii/)

**Difficulty:** `Hard`  
**Topics:** [Arrays & Hashing](../../topics/arrays-and-hashing.md), [Sliding Window](../../topics/sliding-window.md)

---

## 📌 Problem Statement

You are given an integer array `nums` and an integer `target`.

A subarray of `nums` is called **valid** if `target` is the **majority element** of that subarray (i.e., `target` appears strictly more than half the time in that subarray).

Return the total number of valid subarrays.

### Example 1:
```
Input: nums = [1, 2, 2, 3], target = 2
Output: 5
Explanation:
The valid subarrays where 2 is the majority element are:
- nums[1..1] = [2]
- nums[2..2] = [2]
- nums[1..2] = [2, 2]
- nums[0..2] = [1, 2, 2]
- nums[1..3] = [2, 2, 3]
Total = 5 valid subarrays.
```

### Example 2:
```
Input: nums = [1, 1, 1, 1], target = 1
Output: 10
Explanation:
All 10 possible contiguous subarrays contain 1 as the majority element.
```

### Constraints:
- $1 \le \text{nums.length} \le 10^5$
- $1 \le \text{nums}[i] \le 10^9$
- $1 \le \text{target} \le 10^9$

---

## 💡 Intuition & Approach

### 1. Value Transformation & Prefix Sum Formulation
Map the array values as follows:
- If $\text{nums}[i] == \text{target}$, map to $+1$.
- If $\text{nums}[i] \ne \text{target}$, map to $-1$.

Under this transformation, `target` is the majority element in subarray $\text{nums}[l \dots r]$ if and only if:
$$\sum_{i=l}^r \text{transformed}[i] > 0 \iff s[r+1] - s[l] > 0 \iff s[l] < s[r+1]$$
where $s[k]$ is the prefix sum up to index $k-1$ with $s[0] = 0$.

For each right boundary $r$, we need to count how many previous indices $l \le r$ satisfy $s[l] < s[r+1]$.

### 2. Incremental Range Maintenance in $\mathcal{O}(1)$
Because prefix sums lie in the bounded range $[-n, +n]$, we maintain a frequency array `pre` shifted by $n$ such that `pre[v + n]` records how many times prefix sum value $v$ has appeared so far.

Notice that between consecutive elements, the prefix sum changes by **at most $\pm 1$**:
- **When $\text{nums}[r] == \text{target}$ ($+1$ transition)**:
  - The new prefix sum is $s[r+1] = s[r] + 1$.
  - The set of strictly smaller prefix sum values expands to include $s[r]$.
  - Increment the running counter: $\text{presum} \leftarrow \text{presum} + \text{pre}[s[r] + n]$, then $s[r+1] \leftarrow s[r] + 1$.
- **When $\text{nums}[r] \ne \text{target}$ ($-1$ transition)**:
  - The new prefix sum is $s[r+1] = s[r] - 1$.
  - The set of strictly smaller prefix sum values shrinks by excluding the newly formed value $s[r+1]$.
  - Decrement current prefix sum first, then update running counter: $\text{presum} \leftarrow \text{presum} - \text{pre}[s[r+1] + n]$.

After updating `presum` in $\mathcal{O}(1)$ time:
1. Add `presum` to the cumulative answer: $\text{ans} \leftarrow \text{ans} + \text{presum}$.
2. Record the current prefix sum in the frequency table: $\text{pre}[s[r+1] + n] \leftarrow \text{pre}[s[r+1] + n] + 1$.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N)$
  - Single pass through the array of length $N$, with constant-time $\mathcal{O}(1)$ updates per element.
- **Space Complexity:** $\mathcal{O}(N)$
  - Array `pre` of size $2N + 1$ to store frequency counts of shifted prefix sums.

---

## 🔍 Edge Cases Considered

- **All Elements Equal Target**: Subarray count is $N(N+1)/2$, requiring `long long` for `ans`.
- **Target Not Present**: Prefix sums strictly decrease; `presum` correctly stays at 0.
- **Alternating Pattern**: Accurately counts majority windows without recomputing prefix distributions.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
