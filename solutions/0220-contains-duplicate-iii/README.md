# [220. Contains Duplicate III](https://leetcode.com/problems/contains-duplicate-iii/)

**Difficulty:** `Hard`  
**Topics:** [Array](../../topics/arrays-and-hashing.md), [Sliding Window](../../topics/sliding-window.md), [Bucket Sort](../../topics/arrays-and-hashing.md), [Ordered Set](../../topics/arrays-and-hashing.md)

---

## 📌 Problem Statement

You are given an integer array `nums` and two integers `indexDiff` and `valueDiff`.

Find a pair of indices `(i, j)` such that:
- $i \ne j$,
- $|i - j| \le \text{indexDiff}$, and
- $|\text{nums}[i] - \text{nums}[j]| \le \text{valueDiff}$.

Return `true` if such a pair exists or `false` otherwise.

### Example 1:
```
Input: nums = [1,2,3,1], indexDiff = 3, valueDiff = 0
Output: true
Explanation: We can choose (i, j) = (0, 3).
i != j --> 0 != 3
abs(i - j) <= indexDiff --> abs(0 - 3) <= 3
abs(nums[i] - nums[j]) <= valueDiff --> abs(1 - 1) <= 0
```

### Example 2:
```
Input: nums = [1,5,9,1,5,9], indexDiff = 2, valueDiff = 3
Output: false
```

### Constraints:
- $2 \le \text{nums.length} \le 10^5$
- $-10^9 \le \text{nums}[i] \le 10^9$
- $1 \le \text{indexDiff} \le \text{nums.length}$
- $0 \le \text{valueDiff} \le 10^9$

---

## 💡 Intuition & Approach

### 1. Bucketing / Pigeonhole Partitioning ($\mathcal{O}(N)$)
Instead of an $\mathcal{O}(N \log(\text{indexDiff}))$ ordered set search, we can partition values into discrete buckets of width:
$$w = \text{valueDiff} + 1$$

- **Within the same bucket**: Any two numbers mapped to the same bucket differ by at most $(w - 1) = \text{valueDiff}$. Thus, if a bucket already has an element, we immediately have a valid pair!
- **Between adjacent buckets**: A number in bucket $B$ could potentially be close to elements in $B - 1$ or $B + 1$. We only need to check the single stored element in each neighboring bucket.
- **Other buckets**: Numbers in any bucket $|B_1 - B_2| \ge 2$ are guaranteed to differ by at least $w > \text{valueDiff}$, so they can be safely ignored.

### 2. Negative Number Floor Division
In C++, integer division truncates towards zero. To preserve uniform bucket width:
$$\text{bucketId}(x) = \begin{cases} x / w & x \ge 0 \\ (x + 1) / w - 1 & x < 0 \end{cases}$$

### 3. Window Maintenance
Maintain an `unordered_map<long long, long long> buckets` holding at most `indexDiff` active elements. When $i \ge \text{indexDiff}$, remove the bucket corresponding to $\text{nums}[i - \text{indexDiff}]$.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N)$ average where $N = \text{nums.length} \le 10^5$ (constant-time bucket lookups and deletions).
- **Space Complexity:** $\mathcal{O}(\min(N, \text{indexDiff}))$ auxiliary hash table storage.

---

## 🔍 Edge Cases Considered

- **`valueDiff == 0`**: Bucket width becomes $1$; behaves as an exact duplicate detector within the sliding window.
- **Negative Values & Integer Overflow**: Handled via `long long` arithmetic and consistent mathematical floor bucketing.
- **Large Coordinates**: Numbers span $[-10^9, 10^9]$, differences easily exceed standard 32-bit integer limits without `long long`.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
