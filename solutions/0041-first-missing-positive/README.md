# [41. First Missing Positive](https://leetcode.com/problems/first-missing-positive/)

**Difficulty:** `Hard`  
**Topics:** [Arrays & Hashing](../../topics/arrays-and-hashing.md), [Hash Table](../../topics/arrays-and-hashing.md)

---

## 📌 Problem Statement

Given an unsorted integer array `nums`, return the smallest positive integer that is not present in `nums`.

You must implement an algorithm that runs in $\mathcal{O}(n)$ time and uses $\mathcal{O}(1)$ auxiliary space.

### Example 1:
```
Input: nums = [1,2,0]
Output: 3
Explanation: The numbers in the range [1,2] are all in the array.
```

### Example 2:
```
Input: nums = [3,4,-1,1]
Output: 2
Explanation: 1 is in the array but 2 is missing.
```

### Example 3:
```
Input: nums = [7,8,9,11,12]
Output: 1
Explanation: The smallest positive integer 1 is missing.
```

### Constraints:
- $1 \le \text{nums.length} \le 10^5$
- $-2^{31} \le \text{nums}[i] \le 2^{31} - 1$

---

## 💡 Intuition & Approach

### 1. The $[1, N + 1]$ Pigeonhole Bound
For an array of length $N$, the smallest missing positive integer **must** be an integer in the range $[1, N + 1]$:
- If all numbers $1, 2, \dots, N$ are present in `nums`, the answer is $N + 1$.
- Otherwise, the answer is the first number in $[1, N]$ that is missing.

### 2. In-Place Cycle Sort ($\mathcal{O}(N)$ Time, $\mathcal{O}(1)$ Space)
Treat the array itself as a hash table where value $x \in [1, N]$ belongs at target index $x - 1$:
- Traverse $i$ from $0$ to $N - 1$:
  - While `1 <= nums[i] <= N` and `nums[nums[i] - 1] != nums[i]`:
    - Swap `nums[i]` with `nums[nums[i] - 1]`.
- Each swap places at least one previously misplaced number into its correct position, ensuring at most $N$ swaps overall.

### 3. Linear Scan for the First Misplaced Slot
- Iterate $i$ from $0$ to $N - 1$:
  - If `nums[i] != i + 1`, return $i + 1$.
- If every slot is correct, return $N + 1$.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N)$
  - The `while` loop swaps each element into its correct target index at most once $\implies \le 2N$ operations total.
  - Final scanning pass takes $\mathcal{O}(N)$ operations.
  - Total runtime $\approx 2$ ms in C++.
- **Space Complexity:** $\mathcal{O}(1)$ auxiliary space (in-place modification).

---

## 🔍 Edge Cases Considered

- **Duplicates**: Handled cleanly by checking `nums[nums[i] - 1] != nums[i]` before swapping, avoiding infinite loops.
- **Negatives and Values $> N$**: Ignored by the boundary condition and overwritten/skipped.
- **Complete $[1..N]$ range present**: Correctly returns $N + 1$.
- **Empty / Single element**: Robust for $N = 1$ with positive, zero, or negative inputs.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
