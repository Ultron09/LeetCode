# [972. Equal Rational Numbers](https://leetcode.com/problems/equal-rational-numbers/)

**Difficulty:** `Hard`  
**Topics:** [Math](../../topics/math-and-geometry.md), [String](../../topics/arrays-and-hashing.md)

---

## 📌 Problem Statement

Given two strings `s` and `t`, each of which represents a non-negative rational number, return `true` if and only if they represent the same number. The strings may use parentheses to denote the repeating part of the rational number.

A rational number can be represented using up to three parts: `<IntegerPart>`, `<NonRepeatingPart>`, and a `<RepeatingPart>`. The number will be represented in one of the following three ways:
1. `<IntegerPart>` (For example, `12`, `0`, and `123`)
2. `<IntegerPart><.><NonRepeatingPart>` (For example, `0.5`, `1.`, `2.12`, and `123.0001`)
3. `<IntegerPart><.><NonRepeatingPart><(><RepeatingPart><)>` (For example, `0.1(6)`, `1.(9)`, `123.00(1212)`)

### Example 1:
```
Input: s = "0.(52)", t = "0.5(25)"
Output: true
Explanation: 
Because "0.(52)" represents 0.52525252..., and "0.5(25)" represents 0.52525252525..... , the strings represent the same number.
```

### Example 2:
```
Input: s = "0.1666(6)", t = "0.166(66)"
Output: true
```

### Example 3:
```
Input: s = "0.9(9)", t = "1."
Output: true
Explanation: 
"0.9(9)" represents 0.999999999... repeated forever, which mathematically equals 1.
```

### Constraints:
- Each part consists only of digits.
- The `<IntegerPart>` does not have leading zeros (except for the zero itself).
- `1 <= <IntegerPart>.length <= 4`
- `0 <= <NonRepeatingPart>.length <= 4`
- `1 <= <RepeatingPart>.length <= 4`

---

## 💡 Intuition & Approach

Because the repeating representations of decimals are inherently rational, we can perfectly evaluate and store them using **exact fractional representations (Numerator / Denominator)** instead of dealing with lossy floating-point errors.

A number given as `Int.NonRep(Rep)` can be decomposed into two distinct fractions:
1. The non-repeating part: `Int + NonRep / (10 ^ len(NonRep))`
   (e.g. `0.16` becomes `16 / 100`)
2. The repeating part: `Rep / ( (10 ^ len(Rep) - 1) * 10 ^ len(NonRep) )`
   (e.g. `0.0(66)` becomes `66 / 9900`)

By converting `s` and `t` into exact fractions and reducing them by dividing their numerators and denominators by their Greatest Common Divisor (GCD), any two representations of the same rational number will perfectly collapse down to identical numerator and denominator pairs. 

1. **Fraction Normalization**: Whenever a `Fraction` struct is constructed, it immediately divides its components by `gcd(numerator, denominator)` to strictly maintain simplest form.
2. **String Parsing**: Extract `IntegerPart`, `NonRepeatingPart`, and `RepeatingPart` using string methods. Calculate their fractional contributions.
3. **Combination**: Add the two partial fractions together using Least Common Multiple (LCM) denominator alignment.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(L)$ where $L$ is the length of the string representation. Finding periods, substrings, and generating fractions occurs inside bounds $\le 16$ characters, resulting in essentially $\mathcal{O}(1)$ performance.
- **Space Complexity:** $\mathcal{O}(1)$. Memory usage is bounded by small fixed string manipulations and a few `long long` variables.

---

## 🔍 Edge Cases Considered

- **"1." format**: `1.` has an empty `NonRepeatingPart` and evaluates perfectly to `1 / 1`.
- **0.9(9) equals 1**: By formula: `9 / 9 = 1`. Adds exactly to evaluate to `1 / 1`.
- **Leading Zeros in parts**: Extracted properly using substring integer conversions without issue.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
