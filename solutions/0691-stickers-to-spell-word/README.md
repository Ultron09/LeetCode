# [691. Stickers to Spell Word](https://leetcode.com/problems/stickers-to-spell-word/)

**Difficulty:** `Hard`  
**Topics:** [Dynamic Programming](../../topics/dynamic-programming.md), [Bit Manipulation](../../topics/bit-manipulation.md)

---

## 📌 Problem Statement

We are given `n` different types of stickers. Each sticker has a lowercase English word on it.

You would like to spell out the given string `target` by cutting individual letters from your collection of stickers and rearranging them. You can use each sticker more than once if you want, and you have infinite quantities of each sticker.

Return the **minimum number of stickers** that you need to spell out `target`. If the task is impossible, return `-1`.

### Example 1:
```
Input: stickers = ["with","example","science"], target = "thehat"
Output: 3
Explanation: We can use 2 "with" stickers, and 1 "example" sticker.
After cutting and rearranging the letters of those stickers, we can form the target "thehat".
```

### Example 2:
```
Input: stickers = ["notice","possible"], target = "basicbasic"
Output: -1
Explanation: We cannot form the target "basicbasic" from cutting letters from the given stickers.
```

### Constraints:
- `n == stickers.length`
- `1 <= n <= 50`
- `1 <= stickers[i].length <= 10`
- `1 <= target.length <= 15`
- `stickers[i]` and `target` consist of lowercase English letters.

---

## 💡 Intuition & Approach

### 1. Why Bitmask DP?

The target string has at most **15 characters**. This means we can represent any subset of target positions as a bitmask of at most 15 bits ($2^{15} = 32768$ states). Each bit `b` being set means "the character at position `b` in target has been successfully matched by some sticker."

This transforms the problem from a hard combinatorial optimization into a straightforward shortest-path / BFS-style DP over subsets.

### 2. State Definition

$$dp[\text{mask}] = \text{minimum number of stickers to cover all target positions indicated by set bits in mask}$$

- **Base case:** $dp[0] = 0$ — no positions covered requires zero stickers.
- **Goal:** $dp[2^T - 1]$ — all positions covered.

### 3. Transition (The Key Insight)

For each reachable state `mask`:

1. **Find the lowest uncovered position** — the smallest index `b` where bit `b` is 0 in `mask`. This is the "anchor" character we must cover next.

2. **Only try stickers that contain this anchor character.** Any valid solution must eventually cover this position, and we lose nothing by insisting it gets covered *now*. This is a critical pruning that avoids redundant orderings (if sticker A covers positions {1,3} and sticker B covers {2,4}, we don't explore both orders A→B and B→A — we always cover the lowest uncovered first).

3. **Greedily match sticker letters.** For each qualifying sticker, iterate through all target positions (left to right). For each uncovered position, if the sticker still has a copy of that letter available, mark it as covered and decrement the sticker's available count.

4. **Update:** $dp[\text{newMask}] = \min(dp[\text{newMask}],\; dp[\text{mask}] + 1)$.

### 4. Impossibility Detection

If after processing all states, $dp[2^T - 1]$ remains `INT_MAX`, return `-1`. This happens when some letter in target doesn't appear in any sticker.

### 5. Step-by-Step Trace (Example 1)

```
target = "thehat"  (T=6, positions: t=0, h=1, e=2, h=3, a=4, t=5)
stickers = ["with", "example", "science"]

State 000000 (dp=0): lowest uncovered = 0 ('t')
  Try "with" (has 't'): covers t,h → match pos 0('t'),1('h') → mask=000011, dp=1
  Try "example": no 't' → skip
  Try "science": no 't' → skip

State 000011 (dp=1): lowest uncovered = 2 ('e')
  Try "example" (has 'e'): covers e,a → mask=010111, dp=2
  Try "science" (has 'e'): covers e → mask=000111, dp=2
  ...

State 010111 (dp=2): lowest uncovered = 3 ('h')
  Try "with" (has 'h'): covers h,t → mask=111111, dp=3 ✓

Answer: dp[111111] = 3
```

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(2^T \cdot N \cdot T)$  
  - $2^T$ states (up to $32768$).
  - For each state, try up to $N$ stickers (≤50).
  - For each sticker, scan $T$ target positions (≤15).
  - Total: $\approx 32768 \times 50 \times 15 \approx 24.6M$ — comfortably fast.

- **Space Complexity:** $\mathcal{O}(2^T)$ — for the dp array ($32768$ ints = ~128 KB).

---

## 🔍 Edge Cases Considered

- **Impossible target:** A letter in target doesn't appear in any sticker → returns `-1`.
- **Single character target:** A single sticker with that letter suffices → returns `1`.
- **Repeated characters:** Multiple copies of a letter in target require enough copies across (possibly repeated) stickers.
- **Sticker is exact target:** Covered in one use → returns `1`.
- **All stickers identical:** Degenerates to checking if the sticker alphabet covers target.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
