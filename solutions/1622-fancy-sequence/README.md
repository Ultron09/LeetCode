# [1622. Fancy Sequence](https://leetcode.com/problems/fancy-sequence/)

**Difficulty:** `Hard`  
**Topics:** [Math & Geometry](../../topics/math-and-geometry.md), [Design](../../topics/arrays-and-hashing.md), [Number Theory](../../topics/math-and-geometry.md)

---

## 📌 Problem Statement

Write an API that generates fancy sequences using the `append`, `addAll`, and `multAll` operations.

Implement the `Fancy` class:
- `Fancy()`: Initializes the object with an empty sequence.
- `void append(val)`: Appends an integer `val` to the end of the sequence.
- `void addAll(inc)`: Increments all existing values in the sequence by an integer `inc`.
- `void multAll(m)`: Multiplies all existing values in the sequence by an integer `m`.
- `int getIndex(idx)`: Gets the current value at index `idx` (0-indexed) of the sequence modulo $10^9 + 7$. If `idx >= length`, return `-1`.

### Example 1:
```
Input:
["Fancy", "append", "addAll", "append", "multAll", "getIndex", "addAll", "append", "multAll", "getIndex", "getIndex", "getIndex"]
[[], [2], [3], [7], [2], [0], [3], [10], [2], [0], [1], [2]]

Output:
[null, null, null, null, null, 10, null, null, null, 26, 34, 20]

Explanation:
Fancy fancy = new Fancy();
fancy.append(2);   // fancy sequence: [2]
fancy.addAll(3);   // fancy sequence: [2+3] -> [5]
fancy.append(7);   // fancy sequence: [5, 7]
fancy.multAll(2);  // fancy sequence: [5*2, 7*2] -> [10, 14]
fancy.getIndex(0); // return 10
fancy.addAll(3);   // fancy sequence: [10+3, 14+3] -> [13, 17]
fancy.append(10);  // fancy sequence: [13, 17, 10]
fancy.multAll(2);  // fancy sequence: [13*2, 17*2, 10*2] -> [26, 34, 20]
fancy.getIndex(0); // return 26
fancy.getIndex(1); // return 34
fancy.getIndex(2); // return 20
```

### Constraints:
- $1 \le \text{val}, \text{inc}, m \le 100$
- $0 \le \text{idx} \le 10^5$
- At most $10^5$ calls total will be made to `append`, `addAll`, `multAll`, and `getIndex`.

---

## 💡 Intuition & Approach

### 1. Global Affine / Linear Transformation
Instead of modifying all elements in $\mathcal{O}(N)$ on each `addAll` or `multAll`, maintain a global linear transformation applied to all elements:
$$f(x) = (a \cdot x + b) \pmod M$$
where $M = 10^9 + 7$ (a prime number), initialized to $a = 1, b = 0$.

### 2. Updating Global Coefficients
- `addAll(inc)`:
  $$(a \cdot x + b) + \text{inc} = a \cdot x + (b + \text{inc}) \implies b \gets (b + \text{inc}) \bmod M$$
- `multAll(m)`:
  $$(a \cdot x + b) \cdot m = (a \cdot m) \cdot x + (b \cdot m) \implies a \gets (a \cdot m) \bmod M, \quad b \gets (b \cdot m) \bmod M$$

### 3. Inverting Values on `append(val)`
When adding a new element `val`, we must find a raw value $x$ such that applying the current $(a, b)$ yields `val`:
$$a \cdot x + b \equiv \text{val} \pmod M \implies x \equiv (\text{val} - b) \cdot a^{-1} \pmod M$$
Since $M = 10^9 + 7$ is prime and $a \not\equiv 0 \pmod M$, Fermat's Little Theorem gives:
$$a^{-1} \equiv a^{M - 2} \pmod M$$

### 4. Querying `getIndex(idx)`
Simply return:
$$(a \cdot \text{arr}[\text{idx}] + b) \pmod M$$

---

## ⚡ Complexity Analysis

- **Time Complexity:**
  - `append(val)`: $\mathcal{O}(\log M) \approx 30$ multiplications via binary modular exponentiation.
  - `addAll(inc)`: $\mathcal{O}(1)$.
  - `multAll(m)`: $\mathcal{O}(1)$.
  - `getIndex(idx)`: $\mathcal{O}(1)$.
  - Total time for $10^5$ operations $\approx 3$ ms in C++.
- **Space Complexity:** $\mathcal{O}(N)$ where $N \le 10^5$ is the total number of appended elements.

---

## 🔍 Edge Cases Considered

- **`getIndex` out of bounds**: Returns `-1` for invalid indices.
- **Negative Modulo wrap**: `(val - b) % MOD + MOD` prevents negative intermediate remainders in C++.
- **Consecutive multiplications**: Handled with 64-bit integer arithmetic (`long long`) to prevent overflow before taking modulo.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
