# [899. Orderly Queue](https://leetcode.com/problems/orderly-queue/)

**Difficulty:** `Hard`  
**Topics:** [Math](../../topics/math-and-geometry.md), [String](../../topics/arrays-and-hashing.md), [Sorting](../../topics/math-and-geometry.md)

---

## 📌 Problem Statement

You are given a string `s` and an integer `k`. You can choose one of the first `k` letters of `s` and append it at the end of the string.

Return the lexicographically smallest string you could have after applying the mentioned step any number of moves.

### Example 1:
```
Input: s = "cba", k = 1
Output: "acb"
Explanation: 
In the first move, we move the 1st character 'c' to the end, obtaining the string "bac".
In the second move, we move the 1st character 'b' to the end, obtaining the final result "acb".
```

### Example 2:
```
Input: s = "baaca", k = 3
Output: "aaabc"
Explanation: 
In the first move, we move the 1st character 'b' to the end, obtaining the string "aacab".
In the second move, we move the 3rd character 'c' to the end, obtaining the final result "aaabc".
```

### Constraints:
- `1 <= k <= s.length <= 1000`
- `s` consists of lowercase English letters.

---

## 💡 Intuition & Approach

This problem seems complex due to the potentially infinite number of operations, but it boils down to an elegant mathematical observation based on permutation theory:

1. **Case `k > 1`:**
   - If we have $k \ge 2$, it is possible to swap any two adjacent characters in the string.
   - Proof: By continually moving the front element to the back, we can rotate the string until the two elements we want to swap are at the front (at indices 0 and 1). We can then move the 2nd element to the back, followed by the 1st element, effectively swapping their order relative to the rest of the string.
   - Since we can perform any adjacent swap, this behaves identically to Bubble Sort. We can generate *any* permutation of the string.
   - Therefore, the lexicographically smallest string achievable is simply the fully **sorted** version of the original string.

2. **Case `k == 1`:**
   - If $k = 1$, we are restricted to taking only the first character and moving it to the back. This means we can only perform **cyclic rotations** of the string.
   - To find the lexicographically smallest result, we just generate all $N$ possible cyclic rotations and return the smallest one.

---

## ⚡ Complexity Analysis

- **Time Complexity:** 
  - For $k > 1$: $\mathcal{O}(N \log N)$ to sort the string.
  - For $k == 1$: $\mathcal{O}(N^2)$ to generate all rotations and perform string comparisons. (Can be optimized to $\mathcal{O}(N)$ using Booth's Algorithm for lexicographically minimal string rotation, but $\mathcal{O}(N^2)$ is perfectly acceptable for $N \le 1000$).
- **Space Complexity:** $\mathcal{O}(N)$ to store temporary rotation strings for $k = 1$. $\mathcal{O}(1)$ auxiliary space for sorting when $k > 1$.

---

## 🔍 Edge Cases Considered

- `k = 1` vs `k > 1`: Binary logic split handled flawlessly.
- Small strings or already sorted strings: Processed correctly in both conditions.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
