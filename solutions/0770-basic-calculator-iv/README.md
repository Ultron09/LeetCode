# [770. Basic Calculator IV](https://leetcode.com/problems/basic-calculator-iv/)

**Difficulty:** `Hard`  
**Topics:** [Stack & Queue](../../topics/stack-and-queue.md), Math, String

---

## 📌 Problem Statement

Given an expression such as `expression = "e + 8 - a + 5"` and an evaluation map such as `{"e": 1}` (given in terms of `evalvars = ["e"]` and `evalints = [1]`), return a list of tokens representing the simplified expression, such as `["-1*a","14"]`.

An expression alternates chunks and symbols, with a space separating each chunk and symbol.
A chunk is either an expression in parentheses, a variable, or a non-negative integer.
A variable is a string of lowercase letters (not including digits).

Expressions are evaluated in the usual order: brackets first, then multiplication, then addition and subtraction.

The format of the output is as follows:
- Free variables within a term in sorted order lexicographically.
- Terms are sorted by degree (descending), then lexicographically by free variables.
- The leading coefficient of the term is placed directly to the left with an asterisk separating it from the variables.
- Terms with coefficient 0 are not included.

### Example 1:
```
Input: expression = "e + 8 - a + 5", evalvars = ["e"], evalints = [1]
Output: ["-1*a","14"]
```

### Example 2:
```
Input: expression = "(e + 8) * (e - 8)", evalvars = [], evalints = []
Output: ["1*e*e","-64"]
```

### Constraints:
- `1 <= expression.length <= 250`
- `expression` consists of lowercase English letters, digits, `'+'`, `'-'`, `'*'`, `'('`, `')'`, `' '`.
- `0 <= evalvars.length <= 100`

---

## 💡 Intuition & Approach

This problem is a fusion of a **String Parser** and **Symbolic Mathematics (Polynomial Algebra)**.

1. **Polynomial Representation**: 
   - A single mathematical term can be represented by a combination of a coefficient and a list of variables (e.g., $-2 a^2 b$ -> `-2`, `["a", "a", "b"]`).
   - An entire polynomial expression is just a sum of such terms. We can represent a polynomial using a Hash Map where the key is a sorted list of variable strings, and the value is the integer coefficient. `map<vector<string>, int>`

2. **Polynomial Operations**:
   - **Addition**: Simply iterate through the terms of the second polynomial and add their coefficients to the corresponding terms in the first polynomial. Remove terms with a coefficient of $0$.
   - **Subtraction**: Same as addition, but subtract the coefficients.
   - **Multiplication**: Use a nested loop (Cartesian product) to multiply every term in polynomial A with every term in polynomial B. The resulting coefficient is the product of coefficients, and the resulting variable list is the sorted concatenation of variables.

3. **Recursive Descent Parsing**:
   - We remove all spaces to make tokenization easier.
   - We parse using standard operator precedence grammar:
     - `Expression` -> `Term` combined by `+` or `-`
     - `Term` -> `Factor` combined by `*`
     - `Factor` -> `( Expression )`, a variable, or a constant.
   - When hitting a variable, we check if it is provided in `evalvars`. If so, it is evaluated as a constant. If not, it becomes a free variable in our polynomial representation.

4. **Formatting**:
   - Extract the terms, sort them according to the rules (Degree descending, then Lexicographical). 
   - Format them into strings like `"3*a*a*b"`.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(2^N)$ in the absolute worst-case because polynomials can expand exponentially (e.g., $(a+b)*(c+d)*(e+f)...$ creates $2^K$ terms). For standard expressions in the bounds, the parsing is proportional to the number of output terms multiplied by string parsing time.
- **Space Complexity:** $\mathcal{O}(2^N)$ to store the expanded terms of the polynomial. 

---

## 🔍 Edge Cases Considered

- **Variable Evaluation**: Directly substituting known variables at the `Factor` level simplifies the polynomial logic enormously by preventing their combinations early.
- **Degree Sorting**: Empty variable vectors have length 0 and correctly sort to the back (constants).
- **Coefficient 0**: During addition, subtraction, and multiplication, we must proactively check if a coefficient drops to 0 and erase the term to prevent it from showing up in the output.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
