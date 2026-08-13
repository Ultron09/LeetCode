# [719. Find K-th Smallest Pair Distance](https://leetcode.com/problems/find-k-th-smallest-pair-distance/)

**Difficulty:** `Hard`  
**Topics:** [Binary Search](../../topics/binary-search.md), [Two Pointers](../../topics/two-pointers.md), [Sorting](../../topics/arrays-and-hashing.md)

---

## 📌 Problem Statement

The **distance** of a pair of integers `a` and `b` is defined as the absolute difference between `a` and `b`.

Given an integer array `nums` and an integer `k`, return the **k-th smallest distance** among all the pairs `nums[i]` and `nums[j]` where `0 <= i < j < nums.length`.

### Example 1:
```
Input: nums = [1,3,1], k = 1
Output: 0
Explanation: All pairs: (1,3)→2, (1,1)→0, (3,1)→2.
The 1st smallest distance is 0.
```

### Example 2:
```
Input: nums = [1,1,1], k = 2
Output: 0
```

### Example 3:
```
Input: nums = [1,6,1], k = 3
Output: 5
```

### Constraints:
- $n = \text{nums.length}$
- $2 \le n \le 10^4$
- $0 \le \text{nums}[i] \le 10^6$
- $1 \le k \le \frac{n \cdot (n - 1)}{2}$

---

## 💡 Intuition & Approach

### 1. Brute Force Idea — $\mathcal{O}(N^2 \log N)$

Generate all $\binom{N}{2}$ pair distances, sort them, and return the $k$-th element. With $N = 10^4$, this produces up to $\sim 5 \times 10^7$ pairs — too slow and memory-heavy.

### 2. Optimal Strategy — Binary Search on the Answer + Two-Pointer Counting

The key observation is that we don't need to enumerate all pair distances. We can **binary search on the distance value** itself:

- **Search space:** The answer lies in $[0, \max(\text{nums}) - \min(\text{nums})]$.
- **Monotonic predicate:** "How many pairs have distance $\le d$?" is a non-decreasing function of $d$.
- **Goal:** Find the smallest $d$ such that at least $k$ pairs have distance $\le d$.

#### Counting Pairs with Distance ≤ d in $\mathcal{O}(N)$

After sorting the array, use a **sliding window**:

```
For each right index j (from 1 to n-1):
    Advance left pointer until nums[j] - nums[left] <= d
    All indices in [left, j) form valid pairs with j
    count += (j - left)
```

This works because sorting ensures that if `nums[j] - nums[i] <= d`, then `nums[j] - nums[i'] <= d` for all `i' > i` (i.e., elements closer to `j` also satisfy the constraint).

### 3. Step-by-step Execution

Given `nums = [1, 6, 1]`, `k = 3`:

1. **Sort:** `[1, 1, 6]`
2. **Search space:** `lo = 0`, `hi = 6 - 1 = 5`
3. **Iteration 1:** `mid = 2`
   - Pairs with distance ≤ 2: `(1,1)=0 ✓`, `(1,6)=5 ✗`, `(1,6)=5 ✗` → count = 1 < 3
   - `lo = 3`
4. **Iteration 2:** `mid = 4`
   - Pairs with distance ≤ 4: `(1,1)=0 ✓`, `(1,6)=5 ✗`, `(1,6)=5 ✗` → count = 1 < 3
   - `lo = 5`
5. **`lo == hi == 5`** → return **5** ✓

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N \log N + N \log W)$
  - $\mathcal{O}(N \log N)$ for sorting.
  - $\mathcal{O}(\log W)$ binary search iterations, each with an $\mathcal{O}(N)$ sliding window scan.
  - $W = \max(\text{nums}) - \min(\text{nums}) \le 10^6$.
- **Space Complexity:** $\mathcal{O}(\log N)$ for sorting (in-place); $\mathcal{O}(1)$ auxiliary.

---

## 🔍 Edge Cases Considered

- **All identical elements** (`[1, 1, 1]`): Every pair distance is 0. Any $k$ returns 0.
- **Two elements** (`[a, b]`): Only one pair, $k = 1$, returns $|a - b|$.
- **$k = \binom{N}{2}$** (largest distance): Binary search converges to the maximum pair distance.
- **Maximum constraint values** ($N = 10^4$, values up to $10^6$): The algorithm handles this efficiently with $\sim 10^4 \times 20 = 2 \times 10^5$ operations.
- **Already sorted / reverse sorted input**: Sorting is idempotent; the sliding window works identically.

---

## 🔗 Related Problems

- [668. Kth Smallest Number in Multiplication Table](../0668-kth-smallest-number-in-multiplication-table/README.md) — Same "binary search on answer + counting" paradigm
- [410. Split Array Largest Sum](../0410-split-array-largest-sum/README.md) — Binary search on answer with greedy feasibility check
- [378. Kth Smallest Element in a Sorted Matrix](https://leetcode.com/problems/kth-smallest-element-in-a-sorted-matrix/) — Binary search on value space

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
