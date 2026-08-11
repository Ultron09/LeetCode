# [301. Remove Invalid Parentheses](https://leetcode.com/problems/remove-invalid-parentheses/)

**Difficulty:** `Hard`  
**Topics:** [Backtracking](../../topics/backtracking.md), [Breadth-First Search](../../topics/graphs.md), [String](../../topics/arrays-and-hashing.md), [Stack & Queue](../../topics/stack-and-queue.md)

---

## 📌 Problem Statement

Given a string `s` that contains parentheses and letters, remove the minimum number of invalid parentheses to make the input string valid.

Return **a list of unique strings that are valid with the minimum number of removals**. You may return the answer in any order.

### Example 1:
```
Input: s = "()())()"
Output: ["(())()","()()()"]
```

### Example 2:
```
Input: s = "(a)())()"
Output: ["(a())()","(a)()()"]
```

### Example 3:
```
Input: s = ")("
Output: [""]
```

### Constraints:
- $1 \le \text{s.length} \le 25$
- `s` consists of lowercase English letters and parentheses `'('` and `')'`.
- There will be at most $20$ parentheses in `s`.

---

## 💡 Intuition & Approach

### 1. Precomputing Minimum Removals
In a single linear scan of $s$, we can determine the exact count of misplaced `'('` (`remL`) and misplaced `')'` (`remR`) that must be removed:
- Increment `remL` on `'('`.
- On `')'`: if `remL > 0`, pair it by decrementing `remL`; otherwise increment `remR`.

### 2. Pruned Backtracking DFS
With exact target removal counts `remL` and `remR`, explore decisions at each index:
1. **Option 1: Remove**:
   - If `s[index] == '('` and `remL > 0`: recurse with `remL - 1`.
   - If `s[index] == ')'` and `remR > 0`: recurse with `remR - 1`.
2. **Option 2: Keep**:
   - For letters: append to buffer and recurse.
   - For `'('`: append, increment `leftCount`, and recurse.
   - For `')'`: append only if `rightCount < leftCount` (guarantees valid prefix balance), increment `rightCount`, and recurse.
3. **Deduplication**: Collect valid outcomes at `index == n` into a `std::unordered_set<string>`.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(2^N)$ with heavy pruning where $N = \text{s.length} \le 25$. Branching only occurs on parentheses and invalid prefixes are pruned in $\mathcal{O}(1)$.
- **Space Complexity:** $\mathcal{O}(N)$ recursion call stack and current string buffer.

---

## 🔍 Edge Cases Considered

- **String with No Parentheses (e.g. `"abc"`)**: Returns `["abc"]`.
- **Completely Invalid Parentheses (e.g. `")("`)**: Returns `[""]`.
- **Nested / Duplicate Removals**: Deduplicated via hash set.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
