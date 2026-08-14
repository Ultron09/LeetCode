# [936. Stamping The Sequence](https://leetcode.com/problems/stamping-the-sequence/)

**Difficulty:** `Hard`  
**Topics:** [Greedy](../../topics/greedy.md), String

---

## 📌 Problem Statement

You are given two strings `stamp` and `target`. Initially, there is a string `s` of length `target.length` with all `s[i] == '?'`.

In one turn, you can place `stamp` over `s` and replace every letter in the `s` with the corresponding letter from `stamp`.

For example, if `stamp = "abc"` and `target = "abcba"`, then `s` is `"?????"` initially. In one turn you can:
- place `stamp` at index `0` of `s` to obtain `"abc??"`,
- place `stamp` at index `1` of `s` to obtain `"?abc?"`, or
- place `stamp` at index `2` of `s` to obtain `"??abc"`.

Note that `stamp` must be fully contained in the boundaries of `s` in order to stamp (i.e., you cannot place `stamp` at index `3` of `s`).

We want to convert `s` to `target` using at most `10 * target.length` turns.

Return an array of the index of the left-most letter being stamped at each turn. If we cannot obtain `target` from `s` within `10 * target.length` turns, return an empty array.

### Example 1:
```
Input: stamp = "abc", target = "ababc"
Output: [0,2]
Explanation: Initially s = "?????".
- Place stamp at index 0 to get "abc??".
- Place stamp at index 2 to get "ababc".
[1,0,2] would also be accepted as an answer, as well as some other answers.
```

### Constraints:
- `1 <= stamp.length <= target.length <= 1000`
- `stamp` and `target` consist of lowercase English letters.

---

## 💡 Intuition & Approach

The key to this problem is to think **backwards**.

Instead of trying to figure out which stamps to apply first to an empty array of `'?'`, it is much easier to start with the fully finished `target` string and try to "un-stamp" it back into `'?'`s.

When we reverse the process, an "un-stamp" operation means finding a substring in `target` that matches `stamp` (where `'?'` acts as a wildcard because it could have been overwritten by a later stamp in the forward process).

1. **Greedy Matching**: We repeatedly scan the `target` string for windows of size `stamp.length()` that match `stamp`. A match is valid if:
   - Every character in the window matches the corresponding character in `stamp`, OR
   - The character in the window is `'?'` (acting as a wildcard).
   - The window must contain at least one non-`'?'` character (otherwise, we would just loop infinitely).
2. **Replacement**: Once a matching window is found, we convert all its characters to `'?'`s and record the starting index of this window.
3. **Termination**: We repeat this process until all characters in `target` are `'?'`s. If we make a full pass over the string without making any replacements, we are stuck and cannot reach the target, so we return `[]`.
4. **Result**: The order of recorded indices is exactly the reverse of the sequence needed to build `target` from `'?'`s. We reverse this array and return it.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N \times (N - M))$ in the worst case, where $N$ is `target.length()` and $M$ is `stamp.length()`. In each pass, we attempt to match substrings of length $M$. If we only successfully overwrite 1 character per pass, we might make up to $N$ passes. However, due to the aggressive string matching and early exits, the average case is exceedingly fast.
- **Space Complexity:** $\mathcal{O}(N)$ to store the `visited` array (which prevents checking the exact same index multiple times if it has already been completely converted to `'?'`s) and the result vector.

---

## 🔍 Edge Cases Considered

- Target is impossible to reach (returns empty array `[]`).
- Sequences where intermediate parts are heavily overwritten (handled perfectly by the wildcard `?` approach).

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
