# [818. Race Car](https://leetcode.com/problems/race-car/)

**Difficulty:** `Hard`  
**Topics:** [Dynamic Programming](../../topics/dynamic-programming.md)

---

## 📌 Problem Statement

Your car starts at position `0` and speed `+1` on an infinite number line. Your car can go into negative positions. Your car drives automatically according to a sequence of instructions `'A'` (accelerate) and `'R'` (reverse):

When you get an instruction `'A'`, your car does the following:
- `position += speed`
- `speed *= 2`

When you get an instruction `'R'`, your car does the following:
- If your speed is positive then `speed = -1`
- otherwise `speed = 1`
- Your position stays the same.

For example, after commands `"AAR"`, your car goes to positions `0 --> 1 --> 3 --> 3`, and your speed goes to `1 --> 2 --> 4 --> -1`.

Given a target position `target`, return the length of the shortest sequence of instructions to get there.

### Example 1:
```
Input: target = 3
Output: 2
Explanation: 
The shortest instruction sequence is "AA".
Your position goes from 0 --> 1 --> 3.
```

### Example 2:
```
Input: target = 6
Output: 5
Explanation: 
The shortest instruction sequence is "AAARA".
Your position goes from 0 --> 1 --> 3 --> 7 --> 7 --> 6.
```

### Constraints:
- `1 <= target <= 10^4`

---

## 💡 Intuition & Approach

Because our speed doubles with every `'A'` instruction, the distance covered is $2^n - 1$ after $n$ `'A'`s. To reach a target $t$, we face two logical choices:

1. **Overshoot the Target:**
   We accelerate $n$ times until we *just* pass or hit the target ($2^n - 1 \ge t$). 
   If we hit it exactly, the cost is $n$.
   If we pass it, we must reverse (`'R'`) and travel backward to the target. The remaining distance is $(2^n - 1) - t$.
   Since we just reversed, our speed is reset to $-1$, which is functionally identical to starting a brand new race at distance $(2^n - 1) - t$.
   **Cost:** $n \text{ (forward)} + 1 \text{ (reverse)} + \text{dp}[(2^n - 1) - t]$.

2. **Undershoot the Target:**
   We accelerate $k$ times ($k < n$) and stop before the target at $2^k - 1$. 
   If we continue accelerating, we might overshoot terribly. Instead, we can reverse (`'R'`), accelerate backward $j$ times ($j < k$) to burn off speed or adjust our positioning, and then reverse *again* (`'R'`) to face the target.
   Our net position becomes $(2^k - 1) - (2^j - 1)$. 
   The remaining distance to the target is $t - (2^k - 1) + (2^j - 1)$. We are now facing forward with speed $+1$, creating another perfect subproblem.
   **Cost:** $k \text{ (forward)} + 1 \text{ (reverse)} + j \text{ (backward)} + 1 \text{ (reverse)} + \text{dp}[\text{remaining\_distance}]$.

Because both the *overshoot* and *undershoot* subproblem distances are strictly less than $t$, this guarantees a cycle-free optimal substructure. We can use a 1D DP array built bottom-up from $1$ to `target`.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(T \log^2 T)$ where $T$ is the `target`. 
  - The outer loop runs $T$ times.
  - The first inner loop $k$ runs up to $\approx \log_2(T)$.
  - The nested inner loop $j$ runs up to $k \approx \log_2(T)$.
  - Total iterations per target are bounded by $\approx \frac{1}{2} \log_2^2(T)$. For $T = 10,000$, this is incredibly fast ($\approx 10^6$ operations).
- **Space Complexity:** $\mathcal{O}(T)$ to store the memoization/DP array.

---

## 🔍 Edge Cases Considered

- `target` is exactly $2^n - 1$ (e.g., $1, 3, 7, 15$): Caught instantly by checking `(1 << n) - 1 == t` and yields exactly $n$ without branching.
- Reversing immediately without moving backward: Handled by evaluating $j = 0$ (doing an `"RR"` to reset speed back to $1$ without losing position).

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
