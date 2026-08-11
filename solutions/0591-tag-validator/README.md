# [591. Tag Validator](https://leetcode.com/problems/tag-validator/)

**Difficulty:** `Hard`  
**Topics:** [Stack](../../topics/stack-and-queue.md), [String](../../topics/dynamic-programming.md)

---

## 📌 Problem Statement

Given a string representing a code snippet, implement a tag validator to parse the code and return whether it is valid.

A code snippet is valid if all the following rules hold:
1. The code must be wrapped in a **valid closed tag**. Otherwise, the code is invalid.
2. A closed tag has the format `<TAG_NAME>TAG_CONTENT</TAG_NAME>`. The `TAG_NAME` in start and end tags must match.
3. A valid `TAG_NAME` contains **only upper-case letters**, and has length in range $[1, 9]$.
4. A valid `TAG_CONTENT` may contain other valid closed tags, CDATA sections, and any characters EXCEPT unmatched `<`, unmatched start/end tags, or closed tags with invalid `TAG_NAME`.
5. A start tag is unmatched if no corresponding end tag exists with the same `TAG_NAME`, considering balanced nesting.
6. A `<` is unmatched if you cannot find a subsequent `>`. When encountering `<` or `</`, all subsequent characters until the next `>` are parsed as `TAG_NAME`.
7. CDATA has the format `<![CDATA[CDATA_CONTENT]]>`. The range of `CDATA_CONTENT` is defined as characters between `<![CDATA[` and the **first subsequent** `]]>`.
8. `CDATA_CONTENT` is treated as literal plain text; no tags are parsed inside it.

### Example 1:
```
Input: code = "<DIV>This is the first line <![CDATA[<div>]]></DIV>"
Output: true
Explanation: 
The code is wrapped in a closed tag : <DIV> and </DIV>. 
The TAG_NAME is valid, the TAG_CONTENT consists of some characters and cdata. 
Although CDATA_CONTENT has an unmatched start tag with invalid TAG_NAME, it should be considered as plain text, not parsed as a tag.
So TAG_CONTENT is valid, and then the code is valid. Thus return true.
```

### Example 2:
```
Input: code = "<DIV>>>  ![cdata[]] <![CDATA[<div>]>]]>]]>>]</DIV>"
Output: true
```

### Example 3:
```
Input: code = "<A>  <B> </A>   </B>"
Output: false
Explanation: Unbalanced. If "<A>" is closed, then "<B>" must be unmatched, and vice versa.
```

### Constraints:
- $1 \le \text{code.length} \le 500$
- `code` consists of English letters, digits, `'<'`, `'>'`, `'/'`, `'!'`, `'['`, `']'`, `'.'`, and `' '`.

---

## 💡 Intuition & Approach

### 1. Token Dispatching & Grammar Rules
A stack-based deterministic parser can consume the string linearly by examining the character at index $i$:
1. **Single Root Tag Invariant**:
   - If $i > 0$ and `stack.empty()`, any further character implies multiple root tags or trailing data outside the outermost closed tag $\implies$ `false`.
   - Characters outside any tag (`stack.empty()`) are strictly illegal.
2. **CDATA Detection (`<![CDATA[`)**:
   - Must appear inside an open tag (`!stack.empty()`).
   - Advance $i$ directly to the position immediately following the first `]]>`.
3. **Closing Tag (`</`)**:
   - Locate the next `>`.
   - Extract `TAG_NAME` and verify: length $\in [1, 9]$ and all characters are uppercase `A-Z`.
   - Verify `!stack.empty()` and `stack.top() == TAG_NAME`.
   - Pop `TAG_NAME` from stack.
4. **Opening Tag (`<`)**:
   - Locate the next `>`.
   - Extract `TAG_NAME` and verify length and uppercase validity.
   - Push `TAG_NAME` onto stack.
5. **Plain Characters**:
   - Valid only if `!stack.empty()`.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N)$ where $N$ is the length of `code`.
  - Each character is scanned and parsed at most a constant number of times (string searches advance the parser index past the matched tokens).
- **Space Complexity:** $\mathcal{O}(N)$
  - Auxiliary space for the tag stack and extracted tag substrings.

---

## 🔍 Edge Cases Considered

- **Multiple Root Elements (`"<A></A><B></B>"`)**: Detected because the stack becomes empty after `</A>` while $i < N$.
- **Standalone CDATA / Plain text outside root tag (`"<![CDATA[abc]]>"`)**: Detected via `stack.empty()` check before parsing content.
- **Unclosed CDATA / Tag**: `find()` returns `string::npos` $\implies$ returns `false`.
- **Invalid Tag Names (`"123"`, `"tag"`, `"VERYLONGTAGNAME"`)**: Length outside $[1, 9]$ or non-uppercase letters $\implies$ returns `false`.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
