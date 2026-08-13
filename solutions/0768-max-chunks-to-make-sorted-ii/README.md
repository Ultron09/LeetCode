# [768. Max Chunks To Make Sorted II](https://leetcode.com/problems/max-chunks-to-make-sorted-ii/)

**Difficulty:** `Hard`  
**Topics:** [Arrays & Hashing](../../topics/arrays-and-hashing.md), Greedy

---

## 📌 Problem Statement

You are given an integer array `arr`.

We split `arr` into some number of chunks (i.e., partitions), and individually sort each chunk. After concatenating them, the result should equal the sorted array.

Return the largest number of chunks we can make to sort the array.

### Example 1:
```
Input: arr = [5,4,3,2,1]
Output: 1
Explanation:
Splitting into two or more chunks will not return the required result.
For example, splitting into [5, 4], [3, 2, 1] will result in [4, 5, 1, 2, 3], which isn't sorted.
```

### Example 2:
```
Input: arr = [2,1,3,4,4]
Output: 4
Explanation:
We can split into two chunks, such as [2, 1], [3, 4, 4].
However, splitting into [2, 1], [3], [4], [4] is the highest number of chunks possible.
```

### Constraints:
- `1 <= arr.length <= 2000`
- `0 <= arr[i] <= 10^8`

---

## 💡 Intuition & Approach

The core idea is to figure out the exact condition under which a cut between index `i` and index `i+1` is valid.

For a chunk ending at index `i` to be valid, sorting that chunk independently shouldn't disrupt the overall sorted order of the array. This happens if and only if **all elements to the left of the cut are less than or equal to all elements to the right of the cut.**

Mathematically, a cut after index `i` is valid if:
`max(arr[0 ... i]) <= min(arr[i+1 ... N-1])`

### Algorithm:
1. **Precompute Suffix Minimums:** Create an array `minOfRight` where `minOfRight[i]` holds the minimum value from `arr[i]` to the end of the array. Initialize `minOfRight[N] = INT_MAX` for boundary convenience.
2. **Track Prefix Maximum:** Iterate through the array from left to right, updating a running `maxOfLeft` variable.
3. **Evaluate Cuts:** At each index `i`, check if `maxOfLeft <= minOfRight[i+1]`. If it is, we can successfully seal a chunk here and safely move to the next. Increment our chunk counter.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N)$ — We perform one right-to-left pass to populate `minOfRight`, and one left-to-right pass to count the chunks.
- **Space Complexity:** $\mathcal{O}(N)$ — We use an auxiliary array of size $N+1$ to store the suffix minimums.

*(Note: There is also an alternative $\mathcal{O}(N)$ monotonic stack approach that pushes the maximum of each chunk, resolving merges when a smaller element is encountered).*

---

## 🔍 Edge Cases Considered

- **Already Sorted Array**: `[1, 2, 3, 4, 5]` — At every index, the running max is $\le$ the remaining min, yielding $N$ chunks.
- **Reverse Sorted Array**: `[5, 4, 3, 2, 1]` — The running max will always be 5, which is never $\le$ the remaining minimums until the very end, yielding exactly $1$ chunk.
- **Duplicate Elements**: `[2, 1, 3, 4, 4]` — The `<= ` check gracefully handles duplicates allowing splits even when elements are identical across chunks.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
