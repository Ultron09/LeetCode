# [65. Valid Number](https://leetcode.com/problems/valid-number/)

**Difficulty:** `Hard`  
**Topics:** [Math & Geometry](../../topics/math-and-geometry.md), [String](../../topics/sliding-window.md)

---

## 📌 Problem Statement

Given a string `s`, return whether `s` is a **valid number**.

For example, all the following are valid numbers:
- `"2"`, `"0089"`, `"-0.1"`, `"+3.14"`, `"4."`, `"-."`, `"2e10"`, `"-90E3"`, `"3e+7"`, `"+6e-1"`, `"53.5e93"`, `"-123.456e789"`

While the following are not valid numbers:
- `"abc"`, `"1a"`, `"1e"`, `"e3"`, `"99e2.5"`, `"--6"`, `"-+3"`, `"95a54e53"`

Formally, a valid number consists of:
1. An integer or decimal number.
2. Followed by an optional exponent notation (`'e'` or `'E'`) followed by an integer.

### Constraints:
- $1 \le \text{s.length} \le 20$
- `s` consists of only English letters, digits (`0-9`), `'+'`, `'-'`, or `'.'`.

---

## 💡 Intuition & Approach

### 1. Deterministic State & Flag Parsing ($\mathcal{O}(N)$ Time, $\mathcal{O}(1)$ Space)
We maintain three boolean state flags throughout a single pass:
- `seenDigit`: Tracks whether at least one digit has been parsed in the current number segment.
- `seenDot`: Tracks whether a decimal point `'.'` has already been encountered.
- `seenExponent`: Tracks whether an exponent marker `'e'` / `'E'` has already been parsed.

### 2. Transition Rules
1. **Digit (`0-9`)**: Set `seenDigit = true`.
2. **Sign (`'+'`, `'-'`)**: Must only occur at index `0` or immediately after an exponent (`s[i-1] == 'e' || s[i-1] == 'E'`).
3. **Dot (`'.'`)**: Valid only if no previous dot was seen (`!seenDot`) AND no exponent has occurred (`!seenExponent`). Set `seenDot = true`.
4. **Exponent (`'e'`, `'E'`)**: Valid only if no previous exponent was seen (`!seenExponent`) AND at least one digit was parsed earlier (`seenDigit`).
   - Reset `seenDigit = false` because the exponent **must** be followed by at least one digit.
5. **Other characters**: Immediately invalid $\implies \text{return false}$.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N)$ where $N \le 20$ (single linear scan, 0 ms in C++).
- **Space Complexity:** $\mathcal{O}(1)$ auxiliary space.

---

## 🔍 Edge Cases Considered

- **Standalone signs or dots** (`"+"`, `"."`, `"-."`): Handled, returns `false` (since `seenDigit == false`).
- **Trailing dot** (`"4."`): Valid decimal number without fraction part.
- **Leading dot** (`"-.9"`): Valid decimal number without integer part.
- **Exponent without integer** (`"1e"` or `"1e+"`): Properly fails because `seenDigit` was reset upon seeing `'e'`.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
