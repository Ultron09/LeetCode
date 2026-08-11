# [330. Patching Array](https://leetcode.com/problems/patching-array/)

**Difficulty:** `Hard`  
**Topics:** [Greedy](../../topics/greedy.md), [Arrays & Hashing](../../topics/arrays-and-hashing.md), [Math & Geometry](../../topics/math-and-geometry.md)

---

## 📌 Problem Statement

Given a sorted integer array `nums` and an integer `n`, add/patch elements to the array such that any number in the range `[1, n]` inclusive can be formed by the sum of some elements in the array.

Return the minimum number of patches required.

### Example 1:
```
Input: nums = [1,3], n = 6
Output: 1
Explanation:
Combinations of nums are [1], [3], [1,3], which form possible sums of: 1, 3, 4.
Now if we add/patch 2 to nums, the combinations are: [1], [2], [3], [1,3], [2,3], [1,2,3].
Possible sums are 1, 2, 3, 4, 5, 6, which now covers the range [1, 6].
So we only need 1 patch.
```

### Example 2:
```
Input: nums = [1,5,10], n = 20
Output: 2
Explanation: The two patches can be [2, 4].
```

### Example 3:
```
Input: nums = [1,2,2], n = 5
Output: 0
```

### Constraints:
- $1 \le \text{nums.length} \le 1000$
- $1 \le \text{nums}[i] \le 10^4$
- `nums` is sorted in ascending order.
- $1 \le n \le 2^{31} - 1$

---

## 💡 Intuition & Approach

### 1. Reachability Invariant
Let `miss` denote the **smallest positive integer** that cannot be formed by the sum of any subset of elements processed or patched so far.
- This implies that **all integers in the continuous range $[1, \text{miss} - 1]$ can already be formed**.
- Initial state: $\text{miss} = 1$, because $[1, 0]$ is the empty set (no positive sums formed yet).

### 2. Greedy Decision Rules
At each iteration while $\text{miss} \le n$:
1. **Case 1: `nums[i] <= miss`**
   - Since we can already form all values in $[1, \text{miss} - 1]$, adding `nums[i]` allows us to form all sums in:
     $$[1, \text{miss} - 1] \cup [\text{nums}[i], \text{miss} - 1 + \text{nums}[i]] = [1, \text{miss} + \text{nums}[i] - 1]$$
   - There are no gaps between the two intervals because $\text{nums}[i] \le \text{miss}$.
   - We extend our reach: $\text{miss} \gets \text{miss} + \text{nums}[i]$ and advance the array pointer $i \gets i + 1$.

2. **Case 2: `i >= nums.length` or `nums[i] > miss`**
   - The next available number in `nums` is too large (or exhausted), leaving a gap at `miss`.
   - To cover `miss` with the maximum possible future range extension, the optimal greedy element to patch is **`miss` itself**!
   - Patching `miss` expands our covered range from $[1, \text{miss} - 1]$ to $[1, 2 \cdot \text{miss} - 1]$.
   - We update: $\text{miss} \gets \text{miss} + \text{miss} = 2 \cdot \text{miss}$ and increment $\text{patches} \gets \text{patches} + 1$.

### 3. Why Patching `miss` is Globally Optimal
- Any patch value $x > \text{miss}$ would still leave $\text{miss}$ unformable (invalid).
- Any patch value $x < \text{miss}$ would extend the range to $\text{miss} + x - 1 < 2 \cdot \text{miss} - 1$, providing strictly less coverage than choosing $x = \text{miss}$.
- Hence, choosing $x = \text{miss}$ maximizes interval expansion at each step (doubling reach).

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(M + \log N)$
  - $M = \text{nums.length} \le 1000$.
  - Each existing element is consumed at most once ($M$ steps).
  - Every patch doubles `miss`, requiring at most $\lceil \log_2 n \rceil \le 31$ patches.
  - Overall time complexity is $\mathcal{O}(M + \log N)$, running in $< 1\text{ ms}$.
- **Space Complexity:** $\mathcal{O}(1)$
  - Only scalar counters (`miss`, `patches`, `i`) using $\mathcal{O}(1)$ auxiliary space.

---

## 🔍 Edge Cases Considered

- **64-bit Integer Overflow**: Since $n \le 2^{31}-1$, `miss` can grow up to $2 \times (2^{31}-1) \approx 4 \times 10^9$. `miss` is typed as `long long` to prevent signed 32-bit integer overflow.
- **Empty Array (`nums = []`)**: Generates consecutive powers of 2 ($1, 2, 4, 8, \dots$), producing $\lceil \log_2(n + 1) \rceil$ patches.
- **Already Sufficient Array (e.g. `[1, 2, 2], n = 5`)**: Returns 0 patches without triggering any artificial additions.
- **First Element $> 1$ (e.g. `nums = [2], n = 5`)**: Correctly patches 1 first before consuming `nums[0] = 2`.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
