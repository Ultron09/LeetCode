# 🔢 Bit Manipulation

Comprehensive theory, algorithmic patterns, templates, and problem catalog for Bitwise Operations and Bitmasks.

---

## 📖 1. Core Theory & Fundamentals

Bit manipulation operates directly on the binary representation of integers at hardware speed.

### Bitwise Operators
- `&` (AND): 1 only if both bits are 1.
- `|` (OR): 1 if either bit is 1.
- `^` (XOR): 1 if bits differ (`x ^ x = 0`, `x ^ 0 = x`).
- `~` (NOT): Inverts all bits.
- `<<` (Left Shift): Multiplies by $2^k$.
- `>>` (Right Shift): Divides by $2^k$.

### Fundamental Bit Hacks
| Operation | Expression |
| :--- | :--- |
| Check if $k$-th bit is set | `(n & (1 << k)) != 0` |
| Set $k$-th bit | `n | (1 << k)` |
| Clear $k$-th bit | `n & ~(1 << k)` |
| Toggle $k$-th bit | `n ^ (1 << k)` |
| Clear lowest set bit | `n & (n - 1)` (Brian Kernighan's) |
| Isolate lowest set bit | `n & (-n)` |
| Check if power of 2 | `n > 0 && (n & (n - 1)) == 0` |

---

## 🛠️ 2. Key Patterns & Code Templates

### Pattern A: Single Number (XOR Property)
Find the element appearing once when every other element appears twice.
```cpp
int singleNumber(vector<int>& nums) {
    int unique = 0;
    for (int num : nums) {
        unique ^= num;
    }
    return unique;
}
```

### Pattern B: Counting Set Bits (Brian Kernighan's Algorithm)
```cpp
int countSetBits(int n) {
    int count = 0;
    while (n) {
        n &= (n - 1); // Clears the lowest set bit
        count++;
    }
    return count;
}
// Or use compiler built-in: __builtin_popcount(n)
```

### Pattern C: Bitmask Dynamic Programming / Subsets
Iterate over all subsets of a set of size $N$ in $\mathcal{O}(2^N)$.
```cpp
void iterateSubsets(int n) {
    for (int mask = 0; mask < (1 << n); ++mask) {
        for (int i = 0; i < n; ++i) {
            if (mask & (1 << i)) {
                // Element i is included in this subset
            }
        }
    }
}
```

### Pattern D: Binary Digit DP with Fibonacci State Space (Non-negative Integers without Consecutive Ones)
When counting binary configurations $\le N$ satisfying local bit transitions (such as no consecutive ones `"11"`):
1. **Fibonacci Recurrence**: Number of valid $k$-bit strings satisfies $f[k] = f[k-1] + f[k-2]$ with $f[0] = 1, f[1] = 2$.
2. **MSB-to-LSB Prefix Branching**:
   - On bit $k$ where $(n \& (1 \ll k)) \ne 0$, taking branch $0$ allows any valid $k$-bit suffix $\implies \text{ans} += f[k]$.
   - Taking branch $1$ matches the prefix. If `prevBit == 1`, break immediately (illegal prefix extension).
3. **Complexity**: $\mathcal{O}(\log N)$ time and $\mathcal{O}(1)$ space.

---

## ⚠️ 3. Common Pitfalls & Edge Cases

1. **Operator Precedence**: Bitwise operators have lower precedence than arithmetic/comparison operators! Always use parentheses: `(n & 1) == 0` not `n & 1 == 0`.
2. **Shifting Beyond Bit Width**: Shifting by $\ge 32$ on 32-bit `int` is undefined behavior in C++. Use `1LL << k` for 64-bit shifts.
3. **Signed Integer Negative Shifts**: Bitwise operations on negative numbers can trigger implementation-defined sign extension. Prefer `unsigned int` or `uint64_t` when doing heavy bit manipulations.

---

## 📋 4. Solved Problems

| # | Title | Difficulty | Time | Space | Solution Link |
| :---: | :--- | :---: | :---: | :--- | :--- |
| 600 | [Non-negative Integers without Consecutive Ones](../solutions/0600-non-negative-integers-without-consecutive-ones/README.md) | `Hard` | $\mathcal{O}(\log N)$ | $\mathcal{O}(1)$ | [C++](../solutions/0600-non-negative-integers-without-consecutive-ones/solution.cpp) |
