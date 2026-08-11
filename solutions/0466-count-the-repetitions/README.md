# [466. Count The Repetitions](https://leetcode.com/problems/count-the-repetitions/)

**Difficulty:** `Hard`  
**Topics:** [Dynamic Programming](../../topics/dynamic-programming.md), [Two Pointers](../../topics/two-pointers.md)

---

## 📌 Problem Statement

We define `str = [s, n]` as the string `str` which consists of the string `s` concatenated `n` times.

- For example, `str == ["abc", 3] == "abcabcabc"`.

We define that string `s1` can be obtained from string `s2` if we can remove some characters from `s2` such that it becomes `s1`.

You are given two strings `s1` and `s2` and two integers `n1` and `n2`. You have the two strings `str1 = [s1, n1]` and `str2 = [s2, n2]`.

Return the maximum integer `m` such that `str = [str2, m]` can be obtained from `str1`.

### Example 1:
```
Input: s1 = "acb", n1 = 4, s2 = "ab", n2 = 2
Output: 2
```

### Example 2:
```
Input: s1 = "acb", n1 = 1, s2 = "acb", n2 = 1
Output: 1
```

### Constraints:
- $1 \le \text{s1.length}, \text{s2.length} \le 100$
- `s1` and `s2` consist of lowercase English letters.
- $1 \le n1, n2 \le 10^6$

---

## 💡 Intuition & Approach

### 1. Problem Reduction
The condition $[str_2, m]$ is a subsequence of $str_1$ is equivalent to asking:
$$\text{How many times can } s_2 \text{ be matched as a subsequence inside } [s_1, n1]?$$
If $s_2$ appears as a subsequence $K$ times, then the maximum repetitions $m = \lfloor \frac{K}{n_2} \rfloor$.

### 2. Cycle Detection via Pigeonhole Principle
Since $n_1$ can be up to $10^6$, iterating through all $n_1$ blocks of $s_1$ naively would be slow if $|s_1|$ was large, but more importantly, the matching process is **periodic**:
- When traversing an $s_1$ block character by character, we advance a pointer `s2Idx` $\in [0, |s_2| - 1]$.
- At the end of each $s_1$ block, `s2Idx` uniquely represents the matching progress into $s_2$.
- By the **Pigeonhole Principle**, because `s2Idx` can only take $|s_2|$ distinct values, within at most $|s_2| + 1$ iterations of $s_1$, the same `s2Idx` must repeat!

### 3. Fast-Forwarding the Cycle
When `s2Idx` repeats:
- A cycle is detected from $s_1$ block `prevS1` to current block `currS1`.
- Cycle length in $s_1$ blocks: $\Delta s_1 = \text{currS1} - \text{prevS1}$.
- Matching gain in $s_2$ count: $\Delta s_2 = \text{currS2} - \text{prevS2}$.
- Number of full cycles skipped:
  $$\text{numCycles} = \lfloor \frac{n_1 - \text{currS1}}{\Delta s_1} \rfloor$$
- Fast-forward the counts:
  $$\text{currS1} \gets \text{currS1} + \text{numCycles} \cdot \Delta s_1$$
  $$\text{currS2} \gets \text{currS2} + \text{numCycles} \cdot \Delta s_2$$
- Continue matching linearly for the remaining tail (at most $|s_2|$ blocks).

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(|s_1| \cdot |s_2|)$
  - A cycle is guaranteed to be detected within $|s_2| + 1$ blocks of $s_1$.
  - Matching an $s_1$ block takes $|s_1|$ operations.
  - The remaining tail after fast-forwarding takes at most $|s_2|$ blocks.
  - Total operations $\le 2 \times |s_1| \cdot |s_2| \le 2 \times 100 \times 100 = 2 \times 10^4$ operations (runs in $< 1\text{ ms}$).
- **Space Complexity:** $\mathcal{O}(|s_2|)$
  - Stores at most $|s_2|$ distinct states in the `seen` hash map.

---

## 🔍 Edge Cases Considered

- **$n_1$ smaller than cycle length**: Loop terminates naturally before cycle detection triggers.
- **$s_2$ cannot be formed**: Returns $0$ correctly.
- **$n_2 >$ total $s_2$ count**: Returns $0$ since $\lfloor \text{s2Count} / n_2 \rfloor = 0$.
- **Exact Multiple Cycle Boundaries**: Clamps `remainingS1 / cycleS1` accurately.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
