# [420. Strong Password Checker](https://leetcode.com/problems/strong-password-checker/)

**Difficulty:** `Hard`  
**Topics:** [Greedy](../../topics/greedy.md), [Arrays & Hashing](../../topics/arrays-and-hashing.md)

---

## 📌 Problem Statement

A password is considered strong if the below conditions are all met:
1. It has at least $6$ characters and at most $20$ characters.
2. It contains at least one lowercase letter, at least one uppercase letter, and at least one digit.
3. It does not contain three repeating characters in a row (i.e., `"Baaabb0"` is weak, but `"Baaba0"` is strong).

Given a string `password`, return the minimum number of steps required to make `password` strong. If `password` is already strong, return $0$.

In one step, you can:
- **Insert** one character to `password`,
- **Delete** one character from `password`, or
- **Replace** one character of `password` with another character.

### Example 1:
```
Input: password = "a"
Output: 5
Explanation: Insert 5 characters to reach length 6, ensuring at least one uppercase and one digit are added.
```

### Example 2:
```
Input: password = "aA1"
Output: 3
Explanation: Insert 3 characters to reach length 6.
```

### Example 3:
```
Input: password = "1337C0d3"
Output: 0
Explanation: Password satisfies all criteria.
```

### Constraints:
- $1 \le \text{password.length} \le 50$
- `password` consists of letters, digits, dot `'.'` or exclamation mark `'!'`.

---

## 💡 Intuition & Approach

The challenge lies in resolving interactions between three distinct constraints: length bounds $[6, 20]$, required character types (lowercase, uppercase, digit), and repeating runs of length $L \ge 3$. We decompose the problem into three mutually exclusive length regimes:

### 1. Case 1: Length $N < 6$
- We must perform at least $6 - N$ insertions.
- Any insertion can be chosen to supply a missing character type and simultaneously break any repeating run.
- For $N \le 5$, the maximum run is 5 (`aaaaa`), requiring $\lfloor 5/3 \rfloor = 1$ fix, which is easily broken by any insertion (`aaXaa`).
- Formula:
  $$\text{ans} = \max(6 - N, \text{missingTypes})$$

### 2. Case 2: Length $6 \le N \le 20$
- The length is already valid; no insertions or deletions are necessary.
- Each repeating run of length $L$ requires $\lfloor L / 3 \rfloor$ replacements.
- Each replacement can simultaneously eliminate a run violation and supply a missing character type.
- Formula:
  $$\text{ans} = \max\left(\sum \lfloor L_i / 3 \rfloor, \text{missingTypes}\right)$$

### 3. Case 3: Length $N > 20$ (Greedy Deletion Allocation)
- We are forced to perform $D = N - 20$ deletions.
- Deleting characters reduces the length of repeating runs, thereby reducing the number of replacements needed:
  - **$L_i \pmod 3 == 0$ (e.g. $L = 3 \to 2$):** **1 deletion** saves **1 replacement**. (Highest priority).
  - **$L_i \pmod 3 == 1$ (e.g. $L = 4 \to 2$):** **2 deletions** save **1 replacement**. (Second priority).
  - **$L_i \pmod 3 == 2$ (e.g. $L = 5 \to 2$):** **3 deletions** save **1 replacement**. (Lowest priority).
- **Greedy Deletion Algorithm**:
  1. Allocate 1 deletion to each run with $L_i \pmod 3 == 0$.
  2. Allocate 2 deletions to each run with $L_i \pmod 3 == 1$.
  3. Allocate remaining deletions in chunks of 3 to any run with $L_i \ge 3$.
  4. Sum remaining replacements: $\text{rem} = \sum \lfloor L_i / 3 \rfloor$.
- Formula:
  $$\text{ans} = (N - 20) + \max(\text{rem}, \text{missingTypes})$$

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N)$
  - Scanning character categories and collecting run lengths takes $\mathcal{O}(N)$ time.
  - The greedy deletion passes iterate over at most $N / 3$ runs, taking $\mathcal{O}(N)$ time.
  - Overall time complexity is linear $\mathcal{O}(N)$.
- **Space Complexity:** $\mathcal{O}(N)$
  - Stores at most $\lfloor N / 3 \rfloor \le 17$ run lengths in a dynamic array.

---

## 🔍 Edge Cases Considered

- **Single Character**: $N = 1 \implies$ requires 5 insertions to reach 6.
- **Already Strong**: Returns 0 immediately without modifying characters.
- **Monotonous Long Password**: e.g., 20 dots $\to 1$ deletion $+ 6$ replacements $= 7$.
- **Short Repeating Characters**: e.g. `"aaa"` $\implies N = 3$, requires $\max(3, 2) = 3$ insertions.
- **Deletions Exhausted Early**: Handles cases where available deletions $D <$ deletions needed to break all runs.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
