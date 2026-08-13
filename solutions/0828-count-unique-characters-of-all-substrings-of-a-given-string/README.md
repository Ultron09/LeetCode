# [828. Count Unique Characters of All Substrings of a Given String](https://leetcode.com/problems/count-unique-characters-of-all-substrings-of-a-given-string/)

**Difficulty:** `Hard`  
**Topics:** [Arrays & Hashing](../../topics/arrays-and-hashing.md), [Math & Geometry](../../topics/math-and-geometry.md)

---

## 📌 Problem Statement

Let's define a function `countUniqueChars(s)` that returns the number of unique characters in `s`.

For example, calling `countUniqueChars(s)` if `s = "LEETCODE"` then `"L"`, `"T"`, `"C"`, `"O"`, `"D"` are the unique characters since they appear only once in `s`, therefore `countUniqueChars(s) = 5`.

Given a string `s`, return the sum of `countUniqueChars(t)` where `t` is a substring of `s`. The test cases are generated such that the answer fits in a 32-bit integer.

Notice that some substrings can be repeated, so in this case, you have to count the repeated ones too.

### Example 1:
```
Input: s = "ABC"
Output: 10
Explanation: All possible substrings are: "A","B","C","AB","BC" and "ABC".
Every substring is composed with only unique letters.
Sum of lengths of all substring is 1 + 1 + 1 + 2 + 2 + 3 = 10
```

### Example 2:
```
Input: s = "ABA"
Output: 8
Explanation: The same as example 1, except countUniqueChars("ABA") = 1.
```

### Example 3:
```
Input: s = "LEETCODE"
Output: 92
```

### Constraints:
- `1 <= s.length <= 10^5`
- `s` consists of uppercase English letters only.

---

## 💡 Intuition & Approach

Generating all $\mathcal{O}(N^2)$ substrings and finding the unique characters in each would take $\mathcal{O}(N^3)$ time (or $\mathcal{O}(N^2)$ with optimization), resulting in Time Limit Exceeded for $N = 10^5$. 

Instead, we can use the **Contribution Technique**: shift the perspective from counting unique characters per substring, to counting how many substrings each character is unique in.

For a specific character $s[i]$ to be unique in a substring, that substring must:
1. Include the index $i$.
2. Start *after* the previous occurrence of $s[i]$ (let's call its index `prev`). If it doesn't exist, it can start anywhere up to the beginning of the string (index $0$).
3. End *before* the next occurrence of $s[i]$ (let's call its index `next`). If it doesn't exist, it can end anywhere up to the end of the string (index $N-1$).

The number of valid starting positions is $(i - \text{prev})$.
The number of valid ending positions is $(\text{next} - i)$.
Therefore, the character $s[i]$ contributes exactly $(i - \text{prev}) \times (\text{next} - i)$ to our final answer.

### Implementation Details:
1. Maintain an array of 26 lists/vectors, one for each letter `'A'` to `'Z'`.
2. For each list, initially push a `-1` to represent the left boundary.
3. Iterate through `s` and push the index $i$ into `pos[s[i] - 'A']`.
4. After traversing `s`, push $N$ into each list to represent the right boundary.
5. Loop through every character's positions array and apply the formula `(pos[j] - pos[j-1]) * (pos[j+1] - pos[j])`. Accumulate the sum.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N)$ where $N$ is the length of string `s`. We iterate over the string once to map the indices, and then we iterate over the collected indices once to compute the answer.
- **Space Complexity:** $\mathcal{O}(N)$ to store the indices of each character occurrence in the `pos` array.

---

## 🔍 Edge Cases Considered

- **All identical characters** (e.g., `"AAAA"`): Each character contributes `(i - (i-1)) * ((i+1) - i) = 1`. Total equals $N$. Handled correctly by boundaries.
- **All unique characters** (e.g., `"ABC"`): The previous boundary is `-1` and next boundary is $N$ for all characters. Handled flawlessly.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
