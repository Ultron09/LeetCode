# [282. Expression Add Operators](https://leetcode.com/problems/expression-add-operators/)

**Difficulty:** `Hard`  
**Topics:** [Backtracking](../../topics/backtracking.md), [Math](../../topics/math-and-geometry.md), [String](../../topics/arrays-and-hashing.md)

---

## 📌 Problem Statement

Given a string `num` that contains only digits and an integer `target`, return all possibilities to insert the binary operators `'+'`, `'-'`, and/or `'*'` between the digits of `num` so that the resultant expression evaluates to the `target` value.

Note that operands in the returned expressions should not contain leading zeros. Note that a number can contain multiple digits.

### Example 1:
```
Input: num = "123", target = 6
Output: ["1*2*3","1+2+3"]
Explanation: Both "1*2*3" and "1+2+3" evaluate to 6.
```

### Example 2:
```
Input: num = "232", target = 8
Output: ["2*3+2","2+3*2"]
Explanation: Both "2*3+2" and "2+3*2" evaluate to 8.
```

### Example 3:
```
Input: num = "3456237490", target = 9191
Output: []
Explanation: There are no expressions that can be created from "3456237490" to evaluate to 9191.
```

### Constraints:
- $1 \le \text{num.length} \le 10$
- `num` consists of only digits.
- $-2^{31} \le \text{target} \le 2^{31} - 1$

---

## 💡 Intuition & Approach

### 1. Backtracking State Exploration
We can branch at each position by choosing a substring operand length and choosing among 4 choices:
1. No operator (concatenation / first operand).
2. Addition (`+`).
3. Subtraction (`-`).
4. Multiplication (`*`).

### 2. Operator Precedence Handling for Multiplication (`*`)
Standard evaluation occurs left-to-right, but `*` has higher precedence. To handle `*` in a single pass without a full expression parser/stack:
- Maintain `prevOperand`: the value of the most recently added/subtracted term.
- When multiplying by current operand $X$:
  $$\text{newVal} = (\text{currentVal} - \text{prevOperand}) + (\text{prevOperand} \times X)$$
  $$\text{newPrev} = \text{prevOperand} \times X$$

### 3. Pruning Constraints
- **Leading Zeros**: If `num[index] == '0'`, we can only take length 1 (the single digit `'0'`); multi-digit operands starting with `'0'` are prohibited.
- **64-bit Integers**: Arithmetic evaluations can exceed 32-bit signed limits before reaching the target; all accumulators must use `long long`.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(4^N)$ where $N = \text{num.length} \le 10$. At each character gap, we have 4 choices (concatenate, `+`, `-`, `*`).
- **Space Complexity:** $\mathcal{O}(N)$ recursion call stack and expression buffer.

---

## 🔍 Edge Cases Considered

- **Leading Zeros**: Handled by breaking early when `len > 1 && num[index] == '0'`.
- **Target Exceeding Range / Negative Values**: Supported via `long long`.
- **$N = 1$**: Evaluates single digit equality against `target`.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
