# [964. Least Operators to Express Number](https://leetcode.com/problems/least-operators-to-express-number/)

**Difficulty:** `Hard`  
**Topics:** [Math](../../topics/math-and-geometry.md), [Dynamic Programming](../../topics/dynamic-programming.md)

---

## 📌 Problem Statement

Given a single positive integer `x`, we will write an expression of the form `x (op1) x (op2) x (op3) x ...` where each operator `op1`, `op2`, etc. is either addition, subtraction, multiplication, or division (`+`, `-`, `*`, or `/`). 

When writing such an expression, we adhere to the following conventions:
- The division operator (`/`) returns rational numbers.
- There are no parentheses placed anywhere.
- We use the usual order of operations: multiplication and division happen before addition and subtraction.
- It is not allowed to use the unary negation operator (`-`).
- We would like to write an expression with the least number of operators such that the expression equals the given `target`. Return the least number of operators used.

### Example 1:
```
Input: x = 3, target = 19
Output: 5
Explanation: 3 * 3 + 3 * 3 + 3 / 3.
The expression contains 5 operations.
```

### Example 2:
```
Input: x = 5, target = 501
Output: 8
Explanation: 5 * 5 * 5 * 5 - 5 * 5 * 5 + 5 / 5.
The expression contains 8 operations.
```

### Constraints:
- `2 <= x <= 100`
- `1 <= target <= 2 * 10^8`

---

## 💡 Intuition & Approach

Because there are no parentheses, standard order of operations dictates that the expression evaluates as a sum/difference of blocks of multiplication and division. Specifically, these blocks will be powers of `x`. 
Thus, our problem can be reframed as expressing `target` as a combination of `+x^k` and `-x^k`.

1. **Counting Operands**:
   To form a term $x^k$ for $k > 0$, we need $k$ instances of `x` (e.g., $x^3 = x \times x \times x$, which uses 3 `x`s and 2 `*`s).
   To form a term $x^0 = 1$, we need $2$ instances of `x` (specifically $x / x$).
   Notice a pattern: If our expression consists of $N$ total `x`s, there will be exactly $N - 1$ operators linking them!
   So, our goal is simply to **minimize the total number of `x`s** used in the expression. Let's define the "cost" of using $x^k$ as $k$ (if $k > 0$) and $2$ (if $k = 0$).

2. **Base-X Representation and DP**:
   We can process `target` similarly to converting a number into base `x`, evaluating digit by digit from least significant to most significant:
   At any position $i$, let $d = target \pmod x$. We have two choices to handle this remainder:
   
   - **Option 1 (Add)**: We simply add $d \times x^i$. This costs us $d \times \text{cost}(i)$, and the remaining target becomes $target / x$.
   - **Option 2 (Subtract)**: We overshoot the target by subtracting $(x - d) \times x^i$, which essentially borrows/carries over a $+1$ to the next higher power $x^{i+1}$. This costs $(x - d) \times \text{cost}(i)$, and the remaining target becomes $target / x + 1$.

3. **Memoization**:
   Because `Option 2` carries over, states can overlap. We store overlapping states in a hash map using the `target` and `i` (index of current power) as a combined key.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(\log_x (\text{target}))$. At each step, `target` is divided by `x`. Although we branch twice, overlapping subproblems heavily limit the state space.
- **Space Complexity:** $\mathcal{O}(\log_x (\text{target}))$, required by the DP memoization map and call stack depth.

---

## 🔍 Edge Cases Considered

- Perfectly Divisible: If $d = 0$, `Option 2` is unnecessary, strictly bypassing subtraction overhead.
- Exact Power Reached: If $target = 1$, we can immediately return $\text{cost}(i)$ directly, saving evaluation cycles on further base expansion.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
