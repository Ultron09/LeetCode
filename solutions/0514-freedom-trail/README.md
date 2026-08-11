# [514. Freedom Trail](https://leetcode.com/problems/freedom-trail/)

**Difficulty:** `Hard`  
**Topics:** [Dynamic Programming](../../topics/dynamic-programming.md), [String](../../topics/dynamic-programming.md)

---

## 📌 Problem Statement

In the video game Fallout 4, the quest "Road to Freedom" requires players to reach a metal dial called the "Freedom Trail Ring" and use the dial to spell a specific keyword to open the door.

Given a string `ring` that represents the code engraved on the outer ring and another string `key` that represents the keyword that needs to be spelled, return the **minimum number of steps** to spell all the characters in the keyword.

Initially, the first character of the ring is aligned at the "12:00" direction. You should spell all the characters in key one by one by rotating `ring` clockwise or anticlockwise to make each character of the string `key` aligned at the "12:00" direction and then by pressing the center button.

At the stage of rotating the ring to spell the key character `key[i]`:
1. You can rotate the ring clockwise or anticlockwise by one place, which counts as one step. The final purpose of the rotation is to align one of `ring`'s characters at the "12:00" direction, where this character must equal `key[i]`.
2. If the character `key[i]` has been aligned at the "12:00" direction, press the center button to spell, which also counts as one step. After pressing, you begin spelling the next character in the key.

### Example 1:
```
Input: ring = "godding", key = "gd"
Output: 4
Explanation:
For the first key character 'g', since it is already in place, we just need 1 step to spell this character. 
For the second key character 'd', we rotate anticlockwise by two steps ("godding" -> "ddinggo").
Pressing the button adds 1 step.
Total output = 1 + 2 + 1 = 4.
```

### Example 2:
```
Input: ring = "godding", key = "godding"
Output: 13
```

### Constraints:
- $1 \le \text{ring.length}, \text{key.length} \le 100$
- `ring` and `key` consist of only lowercase English letters.
- It is guaranteed that `key` can always be spelled by rotating `ring`.

---

## 💡 Intuition & Approach

### 1. Circular Ring Metric
In a circular string of length $R$, the minimum rotation steps between dial positions $i$ and $j$ in either direction (clockwise or counter-clockwise) is:
$$\text{dist}(i, j) = \min(|i - j|, R - |i - j|)$$

### 2. Multi-Stage Dynamic Programming
Because a character may appear multiple times in `ring`, a greedy choice (nearest occurrence) may lead to a suboptimal future position. We must evaluate all reachable occurrences using Dynamic Programming:
- **State Definition**: Let $\text{dp}[\text{pos}]$ be the minimum accumulated cost (rotations + button presses) to spell the prefix of `key` spelled so far, ending with the dial at ring index $\text{pos}$.
- **Base Case**: At step 0, dial starts at position 0: $\text{dp}[0] = 0$, all other $\text{dp}[\text{pos}] = \infty$.
- **State Transition**: For each character $c = \text{key}[\text{step}]$:
  $$\text{next\_dp}[\text{nxt}] = \min_{\text{prev}} \Big( \text{dp}[\text{prev}] + \text{dist}(\text{prev}, \text{nxt}) + 1 \Big) \quad \forall \text{nxt} \in \text{positions}(c)$$
- **Result**: $\min_{\text{pos}} \text{dp}[\text{pos}]$ after processing all characters in `key`.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(K \cdot R^2)$
  - Outer loop runs $K = |\text{key}|$ times.
  - For each character, there are at most $R = |\text{ring}|$ candidate destinations, each evaluating at most $R$ previous active states.
  - Total operations $\le 100 \times 100 \times 100 = 10^6$ operations (executes in $< 4\text{ ms}$).
- **Space Complexity:** $\mathcal{O}(R)$
  - Rolling 1D array of size $R$ storing state costs between successive key character stages.

---

## 🔍 Edge Cases Considered

- **Single Character Strings ($R=1, K=1$)**: Returns 1 (single button press).
- **All Identical Characters**: Transitions maintain minimum step counts seamlessly.
- **Multiple Identical Target Characters in Ring**: Evaluates both clockwise and counterclockwise branches to find global minimum.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
