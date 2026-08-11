# [552. Student Attendance Record II](https://leetcode.com/problems/student-attendance-record-ii/)

**Difficulty:** `Hard`  
**Topics:** [Dynamic Programming](../../topics/dynamic-programming.md), [Math & Geometry](../../topics/math-and-geometry.md)

---

## 📌 Problem Statement

An attendance record for a student can be represented as a string where each character signifies whether the student was absent, late, or present on that day. The record only contains the following three characters:
- `'A'`: Absent.
- `'L'`: Late.
- `'P'`: Present.

Any student is eligible for an attendance award if they meet **both** of the following criteria:
1. The student was absent (`'A'`) for **strictly fewer than 2 days total**.
2. The student was **never late (`'L'`) for 3 or more consecutive days**.

Given an integer `n`, return the number of possible attendance records of length `n` that make a student eligible for an attendance award. The answer may be very large, so return it **modulo $10^9 + 7$**.

### Example 1:
```
Input: n = 2
Output: 8
Explanation: There are 8 records with length 2 that are eligible for an award:
"PP", "AP", "PA", "LP", "PL", "AL", "LA", "LL"
Only "AA" is not eligible because there are 2 absences (there need to be fewer than 2).
```

### Example 2:
```
Input: n = 1
Output: 3
```

### Example 3:
```
Input: n = 10101
Output: 183236316
```

### Constraints:
- $1 \le n \le 10^5$

---

## 💡 Intuition & Approach

### 1. Finite State Machine Representation
To determine eligibility, we only need to track two discrete properties at any prefix of length $i$:
1. Total absences so far: $a \in \{0, 1\}$.
2. Consecutive late days ending at current day: $l \in \{0, 1, 2\}$.

This defines a finite state space of exactly $2 \times 3 = 6$ states:
- $(a=0, l=0), (a=0, l=1), (a=0, l=2)$
- $(a=1, l=0), (a=1, l=1), (a=1, l=2)$

### 2. State Transitions
Let $\text{dp}[a][l]$ denote the number of valid sequences of length $i$ ending in state $(a, l)$:

1. **Append `'P'`**:
   - Resets consecutive late streak to $0$, leaves absence count unchanged.
   $$\text{next\_dp}[a][0] \gets \text{next\_dp}[a][0] + \text{dp}[a][l] \quad (\forall l \in \{0, 1, 2\})$$

2. **Append `'A'`**:
   - Permissible only if $a = 0$. Increments absence count to $1$ and resets late streak to $0$.
   $$\text{next\_dp}[1][0] \gets \text{next\_dp}[1][0] + \text{dp}[0][l] \quad (\forall l \in \{0, 1, 2\})$$

3. **Append `'L'`**:
   - Permissible only if $l < 2$. Increments consecutive late streak by $1$.
   $$\text{next\_dp}[a][l+1] \gets \text{next\_dp}[a][l+1] + \text{dp}[a][l] \quad (\forall l \in \{0, 1\})$$

### 3. Matrix Exponentiation Generalization
The above transitions can also be encoded as a $6 \times 6$ linear recurrence matrix $M$:
$$V_{n} = M^n \cdot V_0$$
Using binary exponentiation, this can compute results for $N$ up to $10^{18}$ in $\mathcal{O}(6^3 \log N)$ time. For $N \le 10^5$, linear $\mathcal{O}(N)$ DP with $\mathcal{O}(1)$ space is exceptionally fast ($< 2\text{ ms}$).

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N)$
  - Scanning from length $1$ to $N$ with $6$ constant-time state updates per step.
  - Runtime: $< 2\text{ ms}$ for $N = 10^5$.
- **Space Complexity:** $\mathcal{O}(1)$
  - Constant $2 \times 3$ matrix for rolling state accumulation.

---

## 🔍 Edge Cases Considered

- **$N = 1$**: Handled natively, returns $3$ (`"P"`, `"A"`, `"L"`).
- **Modulo Arithmetic**: Intermediate accumulations cast to `long long` before modulo to prevent 32-bit integer overflow.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
