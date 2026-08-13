# [726. Number of Atoms](https://leetcode.com/problems/number-of-atoms/)

**Difficulty:** `Hard`  
**Topics:** [Stack & Queue](../../topics/stack-and-queue.md), [Arrays & Hashing](../../topics/arrays-and-hashing.md)

---

## 📌 Problem Statement

Given a string `formula` representing a chemical formula, return the count of each atom.

- An atomic element starts with an uppercase character, then zero or more lowercase letters.
- One or more digits may follow for the count (omitted if count is 1).
- Formulas can be concatenated: `"H2O2He3Mg4"`.
- Formulas can be grouped with parentheses and an optional multiplier: `"(H2O2)3"`.

Return the count of all elements as a string: names in **sorted order**, each followed by its count (if > 1).

### Example 1:
```
Input: formula = "H2O"
Output: "H2O"
Explanation: {'H': 2, 'O': 1}
```

### Example 2:
```
Input: formula = "Mg(OH)2"
Output: "H2MgO2"
Explanation: {'H': 2, 'Mg': 1, 'O': 2}
```

### Example 3:
```
Input: formula = "K4(ON(SO3)2)2"
Output: "K4N2O14S4"
Explanation: {'K': 4, 'N': 2, 'O': 14, 'S': 4}
```

### Constraints:
- $1 \le \text{formula.length} \le 1000$
- `formula` consists of English letters, digits, `'('`, and `')'`.
- `formula` is always valid.

---

## 💡 Intuition & Approach

### 1. Brute Force Idea — Recursive Descent Parser

Write a recursive parser that mirrors the grammar:
```
Formula  ::= (Group | Atom)+
Group    ::= '(' Formula ')' [Number]
Atom     ::= UpperCase LowerCase* [Number]
```

This works but can be tricky with recursion depth and index management.

### 2. Optimal Strategy — Stack of Hash Maps

Use a **stack of ordered maps** where each map represents one nesting level:

| Event | Action |
| :--- | :--- |
| `'('` | Push a new empty `map<string, int>` onto the stack |
| `')'` | Pop the top map, parse the multiplier $m$, multiply every count by $m$, merge into the new top |
| Uppercase letter | Parse the full atom name + count, add to the current top map |

#### Why `std::map` and not `unordered_map`?
The output requires atoms in **sorted order**. Using `std::map` (red-black tree) gives us sorted keys automatically, avoiding a separate sort step.

### 3. Step-by-step Execution

Given `formula = "K4(ON(SO3)2)2"`:

```
i=0  'K'  → parse "K", count=4      stack: [{K:4}]
i=2  '('  → push new scope           stack: [{K:4}, {}]
i=3  'O'  → parse "O", count=1      stack: [{K:4}, {O:1}]
i=4  'N'  → parse "N", count=1      stack: [{K:4}, {N:1, O:1}]
i=5  '('  → push new scope           stack: [{K:4}, {N:1, O:1}, {}]
i=6  'S'  → parse "S", count=1      stack: [{K:4}, {N:1, O:1}, {S:1}]
i=7  'O'  → parse "O", count=3      stack: [{K:4}, {N:1, O:1}, {O:3, S:1}]
i=9  ')'  → pop, multiply by 2       stack: [{K:4}, {N:1, O:1+6=7, S:2}]
i=11 ')'  → pop, multiply by 2       stack: [{K:4, N:2, O:14, S:4}]

Result: "K4N2O14S4" ✓
```

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N + K \log K)$
  - $\mathcal{O}(N)$ to parse the entire formula (each character visited once).
  - $\mathcal{O}(K \log K)$ for the sorted map iteration where $K$ = number of unique atoms.
  - Pop-and-merge operations are amortized $\mathcal{O}(N)$ total across all parentheses.
- **Space Complexity:** $\mathcal{O}(N)$
  - Stack depth proportional to nesting depth (at most $\mathcal{O}(N/2)$).
  - Map entries proportional to unique atoms across all scopes.

---

## 🔍 Edge Cases Considered

- **Single atom with no count** (`"O"` → `"O"`): Implicit count of 1.
- **Deeply nested parentheses** (`"((N42))"` → `"N42"`): Multiple pops with multiplier 1.
- **Large multipliers** (`"(H)100"` → `"H100"`): Multi-digit number parsing.
- **Multi-character atom names** (`"Fe2O3"` → `"Fe2O3"`): Correct uppercase+lowercase parsing.
- **No parentheses** (`"H2O2He3Mg4"`): Flat concatenation handled by the base case.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
