# [32. Longest Valid Parentheses](https://leetcode.com/problems/longest-valid-parentheses/)

**Difficulty:** `Hard`  
**Topics:** [Stack & Queue](../../topics/stack-and-queue.md), [Dynamic Programming](../../topics/dynamic-programming.md), [String](../../topics/sliding-window.md)

---

## 📌 Problem Statement

Given a string containing just the characters `'('` and `')'`, return the length of the longest valid (well-formed) parentheses substring.

### Example 1:
```
Input: s = "(()"
Output: 2
Explanation: The longest valid parentheses substring is "()".
```

### Example 2:
```
Input: s = ")()())"
Output: 4
Explanation: The longest valid parentheses substring is "()()".
```

### Example 3:
```
Input: s = ""
Output: 0
```

### Constraints:
- $0 \le \text{s.length} \le 3 \times 10^4$
- `s[i]` is `'('` or `')'`.

---

## 💡 Intuition & Approach

### 1. Stack of Boundary Indices
A valid parentheses substring must balance every open bracket with a corresponding closing bracket.
Instead of storing characters, we store **indices** of unmatched characters:
- Initialize the stack with a base boundary index `-1`.
- For index $i$ from $0$ to $N - 1$:
  - If `s[i] == '('`: Push index $i$ onto the stack.
  - If `s[i] == ')'`:
    - Pop the top index (representing the matching `'('`).
    - If the stack is now empty, push $i$ as the new baseline boundary (the current `')'` was unmatched).
    - If the stack is not empty, the valid substring extends from `st.top() + 1` to $i$, with length `i - st.top()`. Update `maxLen = max(maxLen, i - st.top())`.

### 2. Alternative: Two-Pass Counter ($\mathcal{O}(1)$ Auxiliary Space)
- **Forward Pass**: Increment `left` on `'('` and `right` on `')'`.
  - When `left == right`, update `maxLen = max(maxLen, 2 * right)`.
  - If `right > left`, reset counters `left = right = 0`.
- **Backward Pass**: Symmetrically traverse right-to-left.
  - When `left == right`, update `maxLen = max(maxLen, 2 * left)`.
  - If `left > right`, reset counters `left = right = 0`.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N)$ where $N \le 3 \times 10^4$ (single pass over the string).
- **Space Complexity:** $\mathcal{O}(N)$ auxiliary space for the index stack (or $\mathcal{O}(1)$ with the two-pass approach).

---

## 🔍 Edge Cases Considered

- **Empty String** (`""`): Handled immediately, returns 0.
- **No valid pairs** (`"((("` or `")))"`): Returns 0.
- **Nested valid sequences** (`"()(())"`): Correctly accumulates to 6.
- **Interrupted sequences** (`"())(()"`): Resets baseline properly, giving max length 2.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
