# [20. Valid Parentheses](https://leetcode.com/problems/valid-parentheses/)

**Difficulty:** `Easy`  
**Topics:** [Stack & Queue](../../topics/stack-and-queue.md)

---

## 📌 Problem Statement

Given a string `s` containing just the characters `'('`, `')'`, `'{'`, `'}'`, `'['` and `']'`, determine if the input string is valid.

An input string is valid if:
1. Open brackets must be closed by the same type of brackets.
2. Open brackets must be closed in the correct order.
3. Every close bracket has a corresponding open bracket of the same type.

### Example 1:
```
Input: s = "()"
Output: true
```

### Example 2:
```
Input: s = "()[]{}"
Output: true
```

### Example 3:
```
Input: s = "(]"
Output: false
```

### Constraints:
- `1 <= s.length <= 10^4`
- `s` consists of parentheses only `'()[]{}'`.

---

## 💡 Intuition & Approach

1. **Brute Force Idea**: We could repeatedly use string replacement to remove occurrences of `"()"`, `"{}"`, and `"[]"`. If the string eventually becomes empty, it's valid. This approach is highly inefficient taking $\mathcal{O}(N^2)$ time.
2. **Optimal Strategy (Stack)**: The properties of valid parentheses perfectly match the Last-In-First-Out (LIFO) behavior of a stack. When we encounter an opening bracket, we don't know when it will be closed, but we know the *most recently* opened bracket must be closed *first*.
3. **Step-by-step Execution**:
    - Iterate through the string character by character.
    - If the character is an opening bracket (`(`, `{`, `[`), push it onto the stack.
    - If it's a closing bracket (`)`, `}`, `]`):
        - Check if the stack is empty (meaning there's no corresponding open bracket). If so, return `false`.
        - Check if the top of the stack matches the closing bracket. If it does, pop it from the stack.
        - If it doesn't match, return `false`.
    - After processing all characters, the string is valid if and only if the stack is empty (all opened brackets were matched and closed).

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N)$ — We iterate through the string of length $N$ exactly once. Stack `push`, `pop`, and `top` operations all take $\mathcal{O}(1)$ time.
- **Space Complexity:** $\mathcal{O}(N)$ — In the worst-case scenario (e.g., `"(((((("`), all characters are opening brackets and will be pushed onto the stack.

---

## 🔍 Edge Cases Considered

- Empty string (though constraints specify length $\ge 1$).
- String containing only closing brackets (e.g., `"]]]]"`). Handled by checking `st.empty()`.
- String where not all brackets are closed (e.g., `"()("`). Handled by returning `st.empty()` at the end instead of just `true`.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
