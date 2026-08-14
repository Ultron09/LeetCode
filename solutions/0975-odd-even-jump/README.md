# [975. Odd Even Jump](https://leetcode.com/problems/odd-even-jump/)

**Difficulty:** `Hard`  
**Topics:** [Array](../../topics/arrays-and-hashing.md), [Dynamic Programming](../../topics/dynamic-programming.md), Stack, Ordered Set

---

## 📌 Problem Statement

You are given an integer array `arr`. From some starting index, you can make a series of jumps. The (1st, 3rd, 5th, ...) jumps in the series are called odd-numbered jumps, and the (2nd, 4th, 6th, ...) jumps in the series are called even-numbered jumps. Note that the jumps are numbered, not the indices.

You may jump forward from index `i` to index `j` (with `i < j`) in the following way:
- During **odd-numbered jumps**, you jump to the index `j` such that `arr[i] <= arr[j]` and `arr[j]` is the smallest possible value. If there are multiple such indices, you can only jump to the smallest such index `j`.
- During **even-numbered jumps**, you jump to the index `j` such that `arr[i] >= arr[j]` and `arr[j]` is the largest possible value. If there are multiple such indices, you can only jump to the smallest such index `j`.
- It may be the case that for some index `i`, there are no legal jumps.

A starting index is **good** if, starting from that index, you can reach the end of the array (index `arr.length - 1`) by jumping some number of times.

Return the number of good starting indices.

### Example 1:
```
Input: arr = [10,13,12,14,15]
Output: 2
Explanation: 
From starting index i = 3, we can make our 1st jump to i = 4, so we have reached the end.
From starting index i = 4, we have reached the end already.
In total, there are 2 different starting indices i = 3 and i = 4.
```

### Constraints:
- `1 <= arr.length <= 2 * 10^4`
- `0 <= arr[i] < 10^5`

---

## 💡 Intuition & Approach

The problem involves determining if a sequence of jumps reaches the final element of the array. Because we always jump strictly to the right (`i < j`), this forms a Directed Acyclic Graph (DAG) and suggests a Dynamic Programming approach processing from right to left.

At any index `i`, we need to know two boolean states:
1. `higher[i]`: Can we reach the end if our **next jump is an odd jump**?
2. `lower[i]`: Can we reach the end if our **next jump is an even jump**?

If we know the exact destination index `j_odd` for an odd jump from `i`, then `higher[i] = lower[j_odd]` (because the jump after an odd jump must be an even jump).
Similarly, if we know the destination index `j_even` for an even jump from `i`, then `lower[i] = higher[j_even]`.

To find `j_odd` and `j_even` efficiently as we scan from right to left, we can maintain an Ordered Map (`std::map` in C++) that stores the `<value, index>` of all elements we've seen so far to the right of `i`.

- **Odd Jump** (`arr[i] <= arr[j_odd]`, minimum possible value):
  Use `map::lower_bound(arr[i])`. This gives the smallest value $\ge \text{arr}[i]$.
- **Even Jump** (`arr[i] >= arr[j_even]`, maximum possible value):
  Use `map::upper_bound(arr[i])`. This gives the smallest value $> \text{arr}[i]$. By decrementing this iterator by one, we get the largest value $\le \text{arr}[i]$.

When inserting into the map as we iterate from right to left, if a value already exists, we intentionally overwrite it with the current index `i`. This elegantly guarantees that the map always stores the **smallest index** (the leftmost index) for any duplicate values, adhering precisely to the problem rules.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N \log N)$ where $N$ is the length of `arr`. For each of the $N$ elements, we perform up to two logarithmic operations (`lower_bound` and `upper_bound`) and one insertion into the balanced BST (map).
- **Space Complexity:** $\mathcal{O}(N)$ to maintain the two boolean DP arrays (`higher` and `lower`) and the Map containing at most $N$ elements.

---

## 🔍 Edge Cases Considered

- `arr.length == 1`: Instantly return 1 since the starting index is already at the end.
- No valid jumps: Iterators failing the bound checks gracefully result in the boolean state remaining `false`.
- Duplicates: Overwriting map keys when scanning right-to-left correctly updates to the smallest index.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
