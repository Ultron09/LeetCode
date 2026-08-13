# [761. Special Binary String](https://leetcode.com/problems/special-binary-string/)

**Difficulty:** `Hard`  
**Topics:** [Stack & Queue](../../topics/stack-and-queue.md), Recursion, Sorting, String

---

## 📌 Problem Statement

Special binary strings are binary strings with the following two properties:
1. The number of `0`'s is equal to the number of `1`'s.
2. Every prefix of the binary string has at least as many `1`'s as `0`'s.

You are given a special binary string `s`.

A move consists of choosing two consecutive, non-empty, special substrings of `s`, and swapping them. Two strings are consecutive if the last character of the first string is exactly one index before the first character of the second string.

Return the lexicographically largest resulting string possible after applying the mentioned operations on the string.

### Example 1:
```
Input: s = "11011000"
Output: "11100100"
Explanation: The strings "10" [occuring at s[1]] and "1100" [at s[3]] are swapped.
This is the lexicographically largest string possible after some number of swaps.
```

### Constraints:
- `1 <= s.length <= 50`
- `s[i]` is either `'0'` or `'1'`.
- `s` is a special binary string.

---

## 💡 Intuition & Approach

The definition of a "Special Binary String" is mathematically identical to the definition of a **Valid Parentheses String** (if we map `'1'` $\to$ `'('` and `'0'` $\to$ `')'`). 

A valid parenthesis string can also be mapped to a general tree. 
- A "primitive" valid string (one that cannot be split into smaller valid strings, e.g., `(A)`) corresponds to a subtree.
- Swapping two consecutive special substrings is equivalent to swapping two adjacent sibling subtrees in our conceptual tree.
- Since we can swap *any* two adjacent siblings, we can use a bubble-sort-like logic to arbitrarily permute the siblings. To achieve the lexicographically largest string, we must sort the string representations of the sibling subtrees in **descending order**.

### Algorithm
1. **Split into Primitives**: Iterate through `s` and keep a balance counter (`+1` for `'1'`, `-1` for `'0'`). Whenever the balance returns to `0`, we have isolated a primitive special substring.
2. **Peel and Recurse**: A primitive special substring always starts with `'1'` and ends with `'0'`. We strip these outer characters and recursively call our function on the inner string to ensure its inner subtrees are also sorted optimally.
3. **Sort**: Reattach the `'1'` and `'0'` to the processed inner string, and add it to a list. Sort this list of primitive strings in descending order.
4. **Combine**: Concatenate the sorted primitives to form the answer for the current level.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N^2)$ — In the worst-case scenario (like `111...000`), the recursion goes $N/2$ levels deep, and at each level, we do string slicing and concatenation which takes $\mathcal{O}(N)$. Sorting takes $\mathcal{O}(K \log K)$ where $K$ is the number of primitives. Since $N \le 50$, $N^2$ is incredibly small and will run in sub-milliseconds.
- **Space Complexity:** $\mathcal{O}(N)$ — The depth of the recursion tree is at most $N/2$, and we create new strings at each level which take linear space.

---

## 🔍 Edge Cases Considered

- **Flat Sibling Structure**: E.g., `101010` splits into three `10` primitives which are then sorted and concatenated.
- **Deeply Nested**: E.g., `111000` splits into one primitive `111000`, peels to `1100`, then `10`. Handled perfectly by recursion.
- **Empty Inner String**: A simple `10` peels to `""`, which returns `""`, and re-wraps to `10`.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
