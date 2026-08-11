# [273. Integer to English Words](https://leetcode.com/problems/integer-to-english-words/)

**Difficulty:** `Hard`  
**Topics:** [Math](../../topics/math-and-geometry.md), [String](../../topics/arrays-and-hashing.md), [Recursion](../../topics/backtracking.md)

---

## 📌 Problem Statement

Convert a non-negative integer `num` to its English words representation.

### Example 1:
```
Input: num = 123
Output: "One Hundred Twenty Three"
```

### Example 2:
```
Input: num = 12345
Output: "Twelve Thousand Three Hundred Forty Five"
```

### Example 3:
```
Input: num = 1234567
Output: "One Million Two Hundred Thirty Four Thousand Five Hundred Sixty Seven"
```

### Constraints:
- $0 \le \text{num} \le 2^{31} - 1$

---

## 💡 Intuition & Approach

### 1. 3-Digit Chunking Strategy
English numbers are naturally structured in groups of 3 decimal digits (thousands periods):
- Group 0: Units (e.g. $[1, 999]$)
- Group 1: `Thousand` ($10^3$)
- Group 2: `Million` ($10^6$)
- Group 3: `Billion` ($10^9$)

Since $num \le 2^{31} - 1 \approx 2.14 \times 10^9$, there are at most 4 three-digit chunks.

### 2. Processing a 3-Digit Subproblem ($\le 999$)
A helper function recursively resolves values $< 1000$:
- **$n < 20$**: Direct lookup in `belowTwenty = ["", "One", ..., "Nineteen"]`.
- **$20 \le n < 100$**: `tens[n / 10] + " " + helper(n % 10)`.
- **$100 \le n < 1000$**: `belowTwenty[n / 100] + " Hundred" + " " + helper(n % 100)`.

### 3. Assembling the Full Representation
- Process from lowest chunk (`num % 1000`) to highest (`num /= 1000`), attaching the period suffix (`"Thousand"`, `"Million"`, `"Billion"`) to non-zero chunks.
- Prepend non-empty chunk strings separated by spaces.
- Edge Case: If $num = 0$, explicitly return `"Zero"`.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(1)$ (bounded by at most $\approx 4$ chunks for any 32-bit signed integer).
- **Space Complexity:** $\mathcal{O}(1)$ auxiliary space (fixed-size string tables).

---

## 🔍 Edge Cases Considered

- **`num = 0`**: Returns `"Zero"`.
- **Exact Powers of 1000** (e.g., `1,000,000`): Omits empty sub-chunks and returns `"One Million"`.
- **Maximum 32-bit Integer** (`2,147,483,647`): Handled seamlessly without arithmetic overflow.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
