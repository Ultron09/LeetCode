# [315. Count of Smaller Numbers After Self](https://leetcode.com/problems/count-of-smaller-numbers-after-self/)

**Difficulty:** `Hard`  
**Topics:** [Binary Search](../../topics/binary-search.md), [Arrays & Hashing](../../topics/arrays-and-hashing.md), [Trees & BST](../../topics/trees.md)

---

## 📌 Problem Statement

Given an integer array `nums`, return an integer array `counts` where `counts[i]` is the number of smaller elements to the right of `nums[i]`.

### Example 1:
```
Input: nums = [5,2,6,1]
Output: [2,1,1,0]
Explanation:
To the right of 5 there are 2 smaller elements (2 and 1).
To the right of 2 there is only 1 smaller element (1).
To the right of 6 there is 1 smaller element (1).
To the right of 1 there is 0 smaller element.
```

### Example 2:
```
Input: nums = [-1]
Output: [0]
```

### Example 3:
```
Input: nums = [-1,-1]
Output: [0,0]
```

### Constraints:
- $1 \le \text{nums.length} \le 10^5$
- $-10^4 \le \text{nums}[i] \le 10^4$

---

## 💡 Intuition & Approach

### 1. The Right-to-Left Observation
If we process the elements from **right to left** (`i = n - 1 down to 0`):
- All elements previously processed are precisely the elements situated to the *right* of `nums[i]` in the original array.
- The question reduces to: *“How many elements in the seen multiset are strictly smaller than `nums[i]`?”*

### 2. Coordinate Compression + Fenwick Tree (Binary Indexed Tree)
1. **Coordinate Compression**:
   - Extract unique sorted values from `nums` to map values into continuous ranks $1, 2, \dots, M$ ($M \le N$).
   - Rank query via `std::lower_bound` takes $\mathcal{O}(\log M)$.
2. **Fenwick Tree (BIT)**:
   - Maintains frequency counts of ranks seen so far.
   - For `nums[i]` with rank $R$:
     - `counts[i] = bit.query(R - 1)` $\implies$ sum of frequencies strictly smaller than $R$ in $\mathcal{O}(\log M)$.
     - `bit.update(R, +1)` $\implies$ insert current element's rank in $\mathcal{O}(\log M)$.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N \log N)$ where $N \le 10^5$ (sorting for coordinate compression + $N$ BIT point-updates and prefix queries).
- **Space Complexity:** $\mathcal{O}(N)$ for the compressed rank array, BIT frequency array, and output result.

---

## 🔍 Edge Cases Considered

- **All Duplicate Elements (e.g. `[-1, -1]`)**: Handled correctly because `query(R - 1)` only counts elements strictly smaller than rank $R$, returning `[0, 0]`.
- **Negative Numbers**: Coordinate compression maps arbitrary integer ranges (including negatives) seamlessly into positive 1-based ranks.
- **Single Element (`N = 1`)**: Returns `[0]`.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
