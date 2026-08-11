# [224. Basic Calculator](https://leetcode.com/problems/basic-calculator/)

**Difficulty:** `Hard`  
**Topics:** [Stack](../../topics/stack-and-queue.md), [Math](../../topics/math-and-geometry.md), [String](../../topics/sliding-window.md), [Recursion](../../topics/backtracking.md)

---

## 📌 Problem Statement

Given a string `s` representing a valid expression, implement a basic calculator to evaluate it, and return **the result of the evaluation**.

Note: You are not allowed to use any built-in function which evaluates strings as mathematical expressions, such as `eval()`.

### Example 1:
```
Input: s = "1 + 1"
Output: 2
```

### Example 2:
```
Input: s = " 2-1 + 2 "
Output: 3
```

### Example 3:
```
Input: s = "(1+(4+5+2)-3)+(6+8)"
Output: 23
```

### Constraints:
- $1 \le \text{s.length} \le 3 \times 10^5$
- `s` consists of digits, `+`, `-`, `(`, `)`, and `' '`.
- `s` represents a valid expression.
- `+` is not used as a unary operation.
- `-` could be used as a unary operation.
- There will be no two consecutive operators in the input.
- Every number and running calculation will fit in a signed 32-bit integer.

---

## 💡 Intuition & Approach

### 1. Unified Sign-Distributive Stack Machine
Because the operators are strictly additive (`+` and `-`) with parentheses:
- We can maintain a running accumulation `currentResult` and a sign tracker `sign` ($+1$ or $-1$).
- When parsing a number $V$, we instantly update:
  $$\text{currentResult} += \text{sign} \times V$$

### 2. Context Switching on Parentheses
- **Entering Parenthesis `(`**:
  1. Push `currentResult` onto the stack (the outer accumulated value).
  2. Push `sign` onto the stack (the overall sign modifying the upcoming parenthesized block).
  3. Reset `currentResult = 0` and `sign = 1` to start accumulating the inner sub-expression.
- **Exiting Parenthesis `)`**:
  1. Pop the block sign `prevSign`.
  2. Pop the outer result `prevResult`.
  3. Merge:
     $$\text{currentResult} = \text{prevResult} + \text{prevSign} \times \text{currentResult}$$

### 3. Handling Unary Negations Seamlessly
Expressions like `-(2 + 3)` or `- (3 - (- (4 + 5)))` naturally work:
- Encountering `-` sets `sign = -1`.
- Immediately encountering `(` pushes `prevSign = -1` and resets.
- When `)` closes, the entire evaluated inner block is multiplied by $-1$.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N)$ where $N = |s| \le 3 \times 10^5$ (single pass with $\mathcal{O}(1)$ per character).
- **Space Complexity:** $\mathcal{O}(N)$ auxiliary memory for the evaluation stack proportional to the nesting depth.

---

## 🔍 Edge Cases Considered

- **Leading Unary Minus**: `"-2 + 1" \implies -1` and `"-(2 + 3)" \implies -5`.
- **Arbitrary Whitespace**: Skipped smoothly without interrupting token accumulation.
- **Deeply Nested Expressions**: Handled with linear stack frames.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
