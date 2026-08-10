# [68. Text Justification](https://leetcode.com/problems/text-justification/)

**Difficulty:** `Hard`  
**Topics:** [Greedy](../../topics/greedy.md), [Arrays & Hashing](../../topics/arrays-and-hashing.md), [Simulation](../../topics/greedy.md)

---

## 📌 Problem Statement

Given an array of strings `words` and a width `maxWidth`, format the text such that each line has exactly `maxWidth` characters and is fully (left and right) justified.

You should pack your words in a greedy approach; that is, pack as many words as you can in each line. Pad extra spaces `' '` when necessary so that each line has exactly `maxWidth` characters.

Extra spaces between words should be distributed as evenly as possible. If the number of spaces on a line does not divide evenly between words, the empty slots on the left will be assigned more spaces than the slots on the right.

For the last line of text, it should be left-justified, and no extra space is inserted between words.

### Example 1:
```
Input: words = ["This", "is", "an", "example", "of", "text", "justification."], maxWidth = 16
Output:
[
   "This    is    an",
   "example  of text",
   "justification.  "
]
```

### Example 2:
```
Input: words = ["What","must","be","acknowledgment","shall","be"], maxWidth = 16
Output:
[
  "What   must   be",
  "acknowledgment  ",
  "shall be        "
]
```

### Example 3:
```
Input: words = ["Science","is","what","we","understand","well","enough","to","explain","to","a","computer.","Art","is","everything","else","we","do"], maxWidth = 20
Output:
[
  "Science  is  what we",
  "understand      well",
  "enough to explain to",
  "a  computer.  Art is",
  "everything  else  we",
  "do                  "
]
```

### Constraints:
- $1 \le \text{words.length} \le 300$
- $1 \le \text{words}[i]\text{.length} \le 20$
- $1 \le \text{maxWidth} \le 100$
- $\text{words}[i]\text{.length} \le \text{maxWidth}$

---

## 💡 Intuition & Approach

### 1. Greedy Line Partitioning
Scan through `words` and greedily pack as many words as possible on the current line by ensuring:
$$\sum \text{len}(\text{word}) + (\text{numWords} - 1) \le \text{maxWidth}$$

### 2. Space Distribution Cases
Let `totalSpaces = maxWidth - sum(len(word))` and `numGaps = numWords - 1`.
- **Case 1: Left-Justified (Last line OR Single-word line, i.e., $j == n$ or $\text{numGaps} == 0$)**:
  - Separate consecutive words with exactly 1 space.
  - Pad the remaining $\text{maxWidth} - \text{line.length()}$ spaces at the end.
- **Case 2: Fully-Justified ($\text{numGaps} > 0$ and not last line)**:
  - Base spaces per gap: $\text{baseSpaces} = \lfloor \text{totalSpaces} / \text{numGaps} \rfloor$.
  - Extra remainder spaces: $\text{extraSpaces} = \text{totalSpaces} \bmod \text{numGaps}$.
  - The first $\text{extraSpaces}$ slots receive $\text{baseSpaces} + 1$ spaces; the remaining receive $\text{baseSpaces}$.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(\text{Total Characters})$ — Linear traversal through words and string constructions.
- **Space Complexity:** $\mathcal{O}(\text{maxWidth})$ auxiliary space per line formatted.

---

## 🔍 Edge Cases Considered

- **Single word line**: Left-aligned with trailing spaces.
- **Last line with multiple words**: Normal single-space gaps followed by right padding.
- **Full line packing**: Where words perfectly fill `maxWidth` with single spaces.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
