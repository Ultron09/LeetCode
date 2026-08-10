# [1320. Minimum Distance to Type a Word Using Two Fingers](https://leetcode.com/problems/minimum-distance-to-type-a-word-using-two-fingers/)

**Difficulty:** `Hard`  
**Topics:** [Dynamic Programming](../../topics/dynamic-programming.md), [Arrays & Hashing](../../topics/arrays-and-hashing.md)

---

## 📌 Problem Statement

You have a 6-column keyboard layout in the X-Y plane where each uppercase English letter is placed sequentially:
- `row = (c - 'A') / 6`
- `col = (c - 'A') % 6`

Given a string `word`, return the **minimum total distance** to type the string using **only two fingers**.
- The distance between $(x_1, y_1)$ and $(x_2, y_2)$ is $|x_1 - x_2| + |y_1 - y_2|$.
- Initial positions of both fingers are **free** (cost 0) and do not have to start at the first letters.

### Example 1:
```
Input: word = "CAKE"
Output: 3
Explanation:
- Finger 1 on 'C' (cost 0) -> 'A' (dist = 2).
- Finger 2 on 'K' (cost 0) -> 'E' (dist = 1).
Total distance = 3.
```

### Example 2:
```
Input: word = "HAPPY"
Output: 6
Explanation:
- Finger 1: 'H' (cost 0) -> 'A' (dist = 2) -> 'Y' (dist = 4).
- Finger 2: 'P' (cost 0) -> 'P' (dist = 0).
Total distance = 2 + 4 = 6.
```

### Constraints:
- $2 \le \text{word.length} \le 300$
- `word` consists of uppercase English letters.

---

## 💡 Intuition & Approach

### 1. Implicit Position Reduction
At any step $i$ after typing `word[i - 1]`, **one finger is guaranteed to reside at position `word[i - 1]`**.
Therefore, we only need to track the position of the **other finger** $\in [0, 25] \cup \{\text{UNPLACED}\}$!

### 2. State & Transitions
Let `dp[other]` be the minimum distance after typing up to `word[i - 1]`, where the other finger is at character index `other` ($26$ represents unplaced/free).

To type the next character `curr = word[i]`:
1. **Option 1 (Move primary finger)**:
   - Move from `prev = word[i - 1]` to `curr`.
   - The other finger remains at `other`.
   $$\text{next\_dp}[other] = \min(\text{next\_dp}[other], \, dp[other] + \text{dist}(prev, curr))$$
2. **Option 2 (Move other finger)**:
   - Move from `other` to `curr`.
   - The primary finger at `prev` now becomes the *other* finger!
   $$\text{next\_dp}[prev] = \min(\text{next\_dp}[prev], \, dp[other] + \text{dist}(other, curr))$$

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N \cdot \Sigma)$ where $N = \text{word.length} \le 300$ and $\Sigma = 26$
  - Number of transitions per character: $27$.
  - Total operations: $300 \times 27 \approx 8100$ ($< 1$ ms in C++).
- **Space Complexity:** $\mathcal{O}(\Sigma) = \mathcal{O}(1)$
  - Fixed 27-element vector.

---

## 🔍 Edge Cases Considered

- **Initial Free Moves**: Represented by state index $26$ (`UNPLACED`), with distance function returning 0 whenever an unplaced finger moves.
- **Single-finger typing**: Trivially covered as one of the DP paths.
- **Repeated letters**: Distance is 0.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
