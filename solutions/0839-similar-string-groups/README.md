# [839. Similar String Groups](https://leetcode.com/problems/similar-string-groups/)

**Difficulty:** `Hard`  
**Topics:** [Graphs](../../topics/graphs.md), String, Union Find

---

## 📌 Problem Statement

Two strings, `X` and `Y`, are considered similar if either they are identical or we can make them equivalent by swapping at most two letters (in distinct positions) within the string `X`.

For example, `"tars"` and `"rats"` are similar (swapping at positions 0 and 2), and `"rats"` and `"arts"` are similar, but `"star"` is not similar to `"tars"`, `"rats"`, or `"arts"`.

Together, these form two connected groups by similarity: `{"tars", "rats", "arts"}` and `{"star"}`. Notice that `"tars"` and `"arts"` are in the same group even though they are not similar. Formally, each group is such that a word is in the group if and only if it is similar to at least one other word in the group.

We are given a list `strs` of strings where every string in `strs` is an anagram of every other string in `strs`. How many groups are there?

### Example 1:
```
Input: strs = ["tars","rats","arts","star"]
Output: 2
```

### Example 2:
```
Input: strs = ["omv","ovm"]
Output: 1
```

### Constraints:
- `1 <= strs.length <= 300`
- `1 <= strs[i].length <= 300`
- `strs[i]` consists of lowercase letters only.
- All words in `strs` have the same length and are anagrams of each other.

---

## 💡 Intuition & Approach

This problem asks us to find the number of connected components in an undirected graph where nodes are strings and edges represent similarity.

Two strings are similar if they differ by at most two characters. Because we know all strings in the input are strictly anagrams of one another, it is impossible for two strings to differ by exactly one character. Hence, two strings are similar if and only if they differ in **exactly 0 or exactly 2** positions.

1. **Graph Construction**: Since $N \le 300$, the number of string pairs is at most $N(N-1)/2 \approx 45,000$. We can afford to directly compare every pair of strings which takes $\mathcal{O}(L)$ time per pair, where $L \le 300$ is the length of the string.
2. **Component Tracking**: We can use a **Disjoint Set Union (DSU / Union-Find)** data structure. Initially, we assume every string is in its own isolated group (total $N$ groups). Whenever we find two strings that are similar and currently belong to different groups, we union them and decrement the group count by 1.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N^2 \cdot L)$ — We iterate through all $N(N-1)/2$ pairs of strings. Comparing a pair takes $\mathcal{O}(L)$ time. Given the constraints ($N \le 300$, $L \le 300$), this evaluates to roughly $2.7 \times 10^7$ iterations, comfortably executing in $\approx 10-30\text{ms}$ in C++.
- **Space Complexity:** $\mathcal{O}(N)$ — The DSU requires an array of size $N$ to store parent pointers.

---

## 🔍 Edge Cases Considered

- **Identical Strings:** Differ by $0$ positions, which our comparison handles correctly, leaving the difference count at $0 \le 2$.
- **High Length strings but sparse similarities:** DSU skips string similarity checks if the nodes are already known to be in the same connected component (`find(i) == find(j)`), providing a real-world runtime speedup.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
