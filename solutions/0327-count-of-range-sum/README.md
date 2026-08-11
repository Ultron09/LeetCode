# [327. Count of Range Sum](https://leetcode.com/problems/count-of-range-sum/)

**Difficulty:** `Hard`  
**Topics:** [Binary Search](../../topics/binary-search.md), [Arrays & Hashing](../../topics/arrays-and-hashing.md), [Two Pointers](../../topics/two-pointers.md)

---

## 📌 Problem Statement

Given an integer array `nums` and two integers `lower` and `upper`, return the number of range sums that lie in `[lower, upper]` inclusive.

Range sum $S(i, j)$ is defined as the sum of the elements in `nums` between indices $i$ and $j$ inclusive, where $i \le j$.

### Example 1:
```
Input: nums = [-2,5,-1], lower = -2, upper = 2
Output: 3
Explanation: The three ranges are: [0,0], [2,2], and [0,2] and their respective sums are: -2, -1, 2.
```

### Example 2:
```
Input: nums = [0], lower = 0, upper = 0
Output: 1
```

### Constraints:
- $1 \le \text{nums.length} \le 10^5$
- $-2^{31} \le \text{nums}[i] \le 2^{31} - 1$
- $-10^5 \le \text{lower} \le \text{upper} \le 10^5$
- The answer is guaranteed to fit in a 32-bit integer.

---

## 💡 Intuition & Approach

### 1. Mathematical Formulation with Prefix Sums
Let $P[k] = \sum_{m=0}^{k-1} \text{nums}[m]$ for $k = 0, 1, \dots, N$ with $P[0] = 0$.

The range sum between indices $i$ and $j$ ($0 \le i \le j < N$) can be rewritten in terms of prefix sums:
$$S(i, j) = P[j+1] - P[i]$$

The condition $\text{lower} \le S(i, j) \le \text{upper}$ becomes:
$$\text{lower} \le P[j+1] - P[i] \le \text{upper}$$

Rearranging the inequalities for a fixed $j+1$:
$$P[j+1] - \text{upper} \le P[i] \le P[j+1] - \text{lower} \quad \text{where } 0 \le i < j+1 \le N$$

The problem reduces to: *For each index $k \in [1, N]$, count how many previous prefix sums $P[i]$ ($i < k$) fall into the interval $[P[k] - \text{upper}, P[k] - \text{lower}]$.*

### 2. Divide & Conquer via Merge Sort
A naive search over all pairs $(i, j)$ takes $\mathcal{O}(N^2)$ time, which is too slow for $N = 10^5$. 

We can count valid pairs efficiently in $\mathcal{O}(N \log N)$ time using **Merge Sort** (Divide and Conquer), analogous to counting inversions:
1. When dividing the prefix sum array $P[\text{left}\dots\text{right}]$ into two halves $[ \text{left}, \text{mid} ]$ and $[ \text{mid}+1, \text{right} ]$, recursively solve and sort both subproblems.
2. For each element $P[j]$ in the right half ($j \in [\text{mid}+1, \text{right}]$), find all indices $i$ in the left half ($i \in [\text{left}, \text{mid}]$) satisfying:
   $$P[j] - \text{upper} \le P[i] \le P[j] - \text{lower}$$
3. Because both the left and right halves are already sorted in ascending order:
   - As $j$ advances from $\text{mid}+1$ to $\text{right}$, the query window $[P[j] - \text{upper}, P[j] - \text{lower}]$ shifts monotonically upwards.
   - We maintain two pointers `low_ptr` and `high_ptr` in the left half:
     - `low_ptr`: first index where $P[\text{low\_ptr}] \ge P[j] - \text{upper}$
     - `high_ptr`: first index where $P[\text{high\_ptr}] > P[j] - \text{lower}$
   - The number of valid left endpoints for $P[j]$ is simply $(\text{high\_ptr} - \text{low\_ptr})$.
   - Across all $j$ in the right half, both `low_ptr` and `high_ptr` only move forward, achieving $\mathcal{O}(\text{right} - \text{left} + 1)$ linear time for the cross-split counting step.
4. Merge the two sorted subarrays in $\mathcal{O}(\text{right} - \text{left} + 1)$ using a linear merge step.

### 3. Alternative: Coordinate Compression + Fenwick Tree (BIT)
We can also collect all $P[k]$, $P[k] - \text{upper}$, and $P[k] - \text{lower}$ values, compress them into discrete ranks $[1, M]$ ($M \le 3N + 3$), and use a Fenwick Tree to maintain prefix frequencies while querying range sums in $\mathcal{O}(\log N)$ per element. The Merge Sort approach is preferred here due to lower memory overhead, $\mathcal{O}(N)$ space, zero coordinate compression hashing cost, and optimal cache locality.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N \log N)$
  - Generating prefix sums takes $\mathcal{O}(N)$ time.
  - The recurrence relation for the divide-and-conquer merge sort is $T(N) = 2T(N/2) + \mathcal{O}(N)$.
  - By the Master Theorem, $T(N) = \mathcal{O}(N \log N)$ operations.
- **Space Complexity:** $\mathcal{O}(N)$
  - $\mathcal{O}(N)$ for the 64-bit integer prefix sum array $P$ and temporary merge buffer.
  - $\mathcal{O}(\log N)$ recursion stack space.

---

## 🔍 Edge Cases Considered

- **64-bit Integer Overflow**: Since $\text{nums}[i] \in [-2^{31}, 2^{31}-1]$, prefix sums can exceed the range of standard signed 32-bit `int`. Using `long long` for all prefix sum calculations and boundary checks avoids overflow.
- **Single Element Arrays ($N = 1$)**: Works seamlessly; $P$ contains 2 elements ($P[0]=0, P[1]=\text{nums}[0]$) and single split evaluates correctly.
- **All Duplicate/Zero Values (`nums = [0, 0]`, `lower = 0, upper = 0`)**: `high_ptr` correctly advances past all equal zero values to count all valid empty/zero-sum subarrays.
- **Negative Lower / Upper Bounds**: Negative values shift the window boundaries consistently without breaking monotonic order.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
