# [736. Parse Lisp Expression](https://leetcode.com/problems/parse-lisp-expression/)

**Difficulty:** `Hard`  
**Topics:** [Stack & Queue](../../topics/stack-and-queue.md), [Arrays & Hashing](../../topics/arrays-and-hashing.md)

---

## 📌 Problem Statement

You are given a string `expression` representing a Lisp-like expression. Return the integer value it evaluates to.

### Grammar:
- **Integer**: Positive or negative number.
- **Variable**: Starts with a lowercase letter, followed by zero or more lowercase letters/digits.
- **`(let v1 e1 v2 e2 ... expr)`**: Bind variables sequentially, then evaluate the tail expression.
- **`(add e1 e2)`**: Evaluate and sum two expressions.
- **`(mult e1 e2)`**: Evaluate and multiply two expressions.
- **Scoping**: Variable lookups check the innermost scope first, then outer scopes.

### Example 1:
```
Input:  "(let x 2 (mult x (let x 3 y 4 (add x y))))"
Output: 14
Explanation: Inner let shadows x=3, y=4. (add x y) = 7. Outer x=2. (mult 2 7) = 14.
```

### Example 2:
```
Input:  "(let x 3 x 2 x)"
Output: 2
Explanation: Assignments are sequential. x is first 3, then reassigned to 2.
```

### Example 3:
```
Input:  "(let x 1 y 2 x (add x y) (add x y))"
Output: 5
Explanation: x=1, y=2, then x = (add 1 2) = 3. Final: (add 3 2) = 5.
```

### Constraints:
- $1 \le \text{expression.length} \le 2000$
- No leading or trailing spaces. Tokens separated by single spaces.
- Guaranteed valid and evaluates to a 32-bit integer.

---

## 💡 Intuition & Approach

### 1. Why This Is a Parser Problem

The expression has recursive structure — expressions can contain other expressions. The `let` keyword introduces variable bindings with **lexical scoping** (inner scopes shadow outer ones). This maps directly to a **recursive descent parser** with an environment chain.

### 2. Optimal Strategy — Recursive Descent with Scope Chain

We maintain:
- A shared index `pos` that advances through the expression string
- A **scope chain**: `vector<unordered_map<string, int>>` — each `let` pushes a new scope, and pops it when done

The parser dispatches on the first character:
| First char | Action |
| :--- | :--- |
| `'('` | Parse compound: read keyword, dispatch to `let` / `add` / `mult` |
| digit or `'-'` | Parse integer literal |
| lowercase letter | Parse variable name, look up in scope chain |

### 3. The `let` Parsing Logic

This is the trickiest part. After reading `"let"`, we repeatedly:
1. Check if the next token starts with `'('` or is a number → it's the **tail expression** (evaluate and return)
2. Otherwise, parse a variable name
3. If the next character is `')'` → this variable name IS the tail expression (look it up)
4. Otherwise, evaluate the next expression, bind the variable, continue

### 4. Scope Chain Walkthrough

```
Expression: (let x 2 (mult x (let x 3 y 4 (add x y))))

Step 1: Enter let, push scope {}
Step 2: Bind x=2         → scopes: [{x:2}]
Step 3: Evaluate (mult x (let x 3 y 4 (add x y)))
  Step 3a: Evaluate x     → lookup finds x=2 in scope[0]
  Step 3b: Evaluate (let x 3 y 4 (add x y))
    Step 3b-i:   Push scope {}      → scopes: [{x:2}, {}]
    Step 3b-ii:  Bind x=3           → scopes: [{x:2}, {x:3}]
    Step 3b-iii: Bind y=4           → scopes: [{x:2}, {x:3, y:4}]
    Step 3b-iv:  Evaluate (add x y) → x=3 (inner), y=4 → 7
    Step 3b-v:   Pop scope          → scopes: [{x:2}]
  Step 3c: mult 2 × 7 = 14
Step 4: Pop scope → scopes: []
Result: 14 ✓
```

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N^2)$ worst-case
  - $\mathcal{O}(N)$ to parse through the expression.
  - Each variable lookup traverses the scope chain: $\mathcal{O}(D)$ where $D$ = nesting depth.
  - Worst case $D = \mathcal{O}(N)$ for deeply nested lets.
- **Space Complexity:** $\mathcal{O}(N)$
  - Recursion depth + scope chain storage proportional to expression length.

---

## 🔍 Edge Cases Considered

- **Bare integer** (`"42"` → 42): No parentheses, just an atom.
- **Negative numbers** (`"(let x -2 (mult x x))"` → 4): Negative sign parsed correctly.
- **Sequential reassignment** (`"(let x 3 x 2 x)"` → 2): Later binding overwrites earlier.
- **Variable used in its own reassignment** (`"(let x 1 y 2 x (add x y) (add x y))"` → 5): Sequential evaluation ensures x=3 before final expression.
- **Deep nesting**: Scope chain correctly shadows and unshadows variables.
- **Variable as tail expression** (`"(let x 5 x)"` → 5): Variable lookup, not sub-expression.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
