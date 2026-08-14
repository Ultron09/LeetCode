# [854. K-Similar Strings](https://leetcode.com/problems/k-similar-strings/)

**Difficulty:** `Hard`  
**Topics:** [Graphs](../../topics/graphs.md), [Breadth-First Search](../../topics/graphs.md)

---

## 📌 Problem Statement

Strings `s1` and `s2` are `k`-similar (for some non-negative integer `k`) if we can swap the positions of two letters in `s1` exactly `k` times so that the resulting string equals `s2`.

Given two anagrams `s1` and `s2`, return the smallest `k` for which `s1` and `s2` are `k`-similar.

### Example 1:
```
Input: s1 = "ab", s2 = "ba"
Output: 1
Explanation: The two string are 1-similar because we can use one swap to change s1 to s2: "ab" --> "ba".
```

### Example 2:
```
Input: s1 = "abc", s2 = "bca"
Output: 2
Explanation: The two strings are 2-similar because we can use two swaps to change s1 to s2: "abc" --> "bac" --> "bca".
```

### Constraints:
- `1 <= s1.length <= 20`
- `s2.length == s1.length`
- `s1` and `s2` contain only lowercase letters from the set `{'a', 'b', 'c', 'd', 'e', 'f'}`.
- `s2` is an anagram of `s1`.

---

## 💡 Intuition & Approach

1. **Brute Force Idea**: Generating all possible string permutations via random swaps creates an enormous state space of size `O(N!)`.
2. **Optimal Strategy**: Model this as a shortest path problem using Breadth-First Search (BFS). Each state is a string configuration, and edges are valid single swaps.
3. **Pruning**: We can heavily prune the search tree. For any given string state, find the first index `i` where the character doesn't match the target string `s2`. We only need to swap `s1[i]` with some character at index `j` (`j > i`) that satisfies two conditions:
   - It matches the target character at index `i` (`s1[j] == s2[i]`).
   - It is currently mismatched at its own index (`s1[j] != s2[j]`).
   This ensures each transition fixes at least one position efficiently, vastly reducing the number of branches explored.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N \times 3^N)$ — Although in the worst-case BFS could explore many states, the maximum number of states is bounded, and the aggressive pruning restricts the search space significantly.
- **Space Complexity:** $\mathcal{O}(3^N)$ — The queue and the visited set store at most $3^N$ states in the worst case, but practically much less due to anagram constraints and pruning.

---

## 🔍 Edge Cases Considered

- Strings that are already identical (`s1 == s2`), which return `0` swaps immediately.
- Only exactly two letters mismatched, needing just 1 swap.
- Cascading swaps where $A \rightarrow B$, $B \rightarrow C$, $C \rightarrow A$.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
