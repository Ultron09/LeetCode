# [3312. Sorted GCD Pair Queries](https://leetcode.com/problems/sorted-gcd-pair-queries/)

**Difficulty:** `Hard`  
**Topics:** [Math & Geometry](../../topics/math-and-geometry.md), [Binary Search](../../topics/binary-search.md), [Arrays & Hashing](../../topics/arrays-and-hashing.md)

---

## 📌 Problem Statement

You are given an integer array `nums` of length `n` and an integer array `queries`.

1. Compute the greatest common divisor (GCD) for all pairs $(nums[i], nums[j])$ with $0 \le i < j < n$.
2. Store all these GCD values in an array `gcdPairs` and sort it in ascending order.
3. For each query `queries[i]`, return the GCD value at index `queries[i]` in the sorted `gcdPairs` array (0-indexed).

Return an array `answer`, where `answer[i]` is the result for `queries[i]`.

### Example 1:
```
Input: nums = [2,3,4], queries = [0,2,2]
Output: [1,2,2]
Explanation:
All GCD pairs: [gcd(2, 3), gcd(2, 4), gcd(3, 4)] = [1, 2, 1].
Sorted gcdPairs = [1, 1, 2].
- queries[0] = 0 -> gcdPairs[0] = 1
- queries[1] = 2 -> gcdPairs[2] = 2
- queries[2] = 2 -> gcdPairs[2] = 2
```

### Example 2:
```
Input: nums = [4,4,2,1], queries = [5,3,1,0]
Output: [4,2,1,1]
Explanation:
Sorted gcdPairs = [1, 1, 1, 2, 2, 4].
```

### Example 3:
```
Input: nums = [2,2], queries = [0,0]
Output: [2,2]
Explanation:
gcdPairs = [gcd(2, 2)] = [2].
Sorted gcdPairs = [2].
- queries[0] = 0 -> gcdPairs[0] = 2
- queries[1] = 0 -> gcdPairs[0] = 2
```

### Constraints:
- $n = \text{nums.length}$
- $2 \le n \le 10^5$
- $1 \le \text{nums}[i] \le 5 \times 10^4$
- $1 \le \text{queries.length} \le 10^5$
- $0 \le \text{queries}[i] < \frac{n \times (n - 1)}{2}$

---

## 💡 Intuition & Approach

### 1. Why Brute Force Fails
Given $n \le 10^5$, the total number of pairs is $\frac{n(n - 1)}{2} \approx 5 \times 10^9$. Generating and sorting all pairs explicitly requires $\mathcal{O}(n^2)$ time and memory, which exceeds time limits (TLE) and memory limits (MLE).

### 2. Value-Space Harmonic Sieve + Inclusion-Exclusion
Rather than enumerating pairs of indices, notice that the range of possible GCD values is small:
$$1 \le \text{GCD} \le M \quad \text{where } M = \max(nums) \le 5 \times 10^4$$

Instead of finding the GCD of each pair, we count **how many pairs produce each exact GCD value $g$**:

1. **Count Multiples**:
   For any integer $g \in [1, M]$, the number of elements in `nums` divisible by $g$ is:
   $$\text{multiplesCount}(g) = \sum_{k=1}^{\lfloor M/g \rfloor} \text{freq}[k \cdot g]$$
   The total number of pairs whose GCD is a multiple of $g$ (i.e. $\text{GCD} \in \{g, 2g, 3g, \dots\}$) is:
   $$\text{totalPairs}(g) = \frac{\text{multiplesCount}(g) \times (\text{multiplesCount}(g) - 1)}{2}$$

2. **Inclusion-Exclusion Principle (Backwards Traversal)**:
   To isolate the exact number of pairs with $\text{GCD} = g$, traverse $g$ from $M$ down to $1$ and subtract all counts of pairs whose GCD is a strictly larger multiple of $g$ ($2g, 3g, \dots$):
   $$\text{gcdCounts}[g] = \text{totalPairs}(g) - \sum_{k=2}^{\lfloor M/g \rfloor} \text{gcdCounts}[k \cdot g]$$
   The total operations across all $g$ follow the Harmonic Series:
   $$\sum_{g=1}^M \frac{M}{g} = M \sum_{g=1}^M \frac{1}{g} = \mathcal{O}(M \log M)$$
   For $M = 50,000$, $M \ln M \approx 5.4 \times 10^5$ operations (less than $2$ ms).

### 3. Prefix Sum & Binary Search
1. Compute the prefix sum of GCD frequencies:
   $$\text{prefixSum}[g] = \sum_{i=1}^g \text{gcdCounts}[i]$$
   $\text{prefixSum}[g]$ represents the total number of pairs with $\text{GCD} \le g$.
2. For each 0-indexed query $q \in \text{queries}$, find the smallest $g$ such that $\text{prefixSum}[g] > q$.
3. In C++, this is computed in $\mathcal{O}(\log M)$ time using `std::upper_bound(prefixSum.begin(), prefixSum.end(), q)`.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(n + M \log M + Q \log M)$
  - Frequency counting: $\mathcal{O}(n)$.
  - Harmonic sieve & inclusion-exclusion: $\mathcal{O}(M \log M)$ where $M = \max(\text{nums}) \le 5 \times 10^4$.
  - Prefix sums: $\mathcal{O}(M)$.
  - Answering $Q$ queries via binary search: $\mathcal{O}(Q \log M)$.
- **Space Complexity:** $\mathcal{O}(M)$ to store `freq`, `gcdCounts`, and `prefixSum` tables.

---

## 🔍 Edge Cases Considered

- **Small $n$ ($n = 2$)**: Works accurately without out-of-bounds errors.
- **Identical Elements**: All pairs produce the same GCD, handled properly by combinations formula $\binom{c}{2}$.
- **Large Queries**: Handled with `long long` for $q$ and cumulative pair counts up to $\approx 5 \times 10^9$.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
