# [1406. Stone Game III](https://leetcode.com/problems/stone-game-iii/)

**Difficulty:** `Hard`  
**Topics:** [Dynamic Programming](../../topics/dynamic-programming.md), [Math & Geometry](../../topics/math-and-geometry.md)

---

## 📌 Problem Statement

Alice and Bob continue their games with piles of stones. There are several stones arranged in a row, and each stone has an associated value which is an integer given in the array `stoneValue`.

Alice and Bob take turns, with Alice starting first. On each player's turn, that player can take $1, 2,$ or $3$ stones from the first remaining stones in the row.

The score of each player is the sum of the values of the stones taken. The score of each player is $0$ initially.

The objective of the game is to end with the highest score, and the winner is the player with the highest score and there could be a tie. The game continues until all the stones have been taken.

Assume Alice and Bob play optimally.

Return `"Alice"` if Alice will win, `"Bob"` if Bob will win, or `"Tie"` if they will end the game with the same score.

### Example 1:
```
Input: stoneValue = [1,2,3,7]
Output: "Bob"
Explanation: Alice will always lose. Her best move will be to take three piles and the score become 6. Now the score of Bob is 7 and Bob wins.
```

### Example 2:
```
Input: stoneValue = [1,2,3,-9]
Output: "Alice"
Explanation: Alice must choose all the three piles at the first move to win and leave Bob with negative score.
If Alice chooses one pile her score will be 1 and the next move Bob's score becomes 5. In the next move, Alice will take the pile with value = -9 and lose.
If Alice chooses two piles her score will be 3 and the next move Bob's score becomes 3. In the next move, Alice will take the pile with value = -9 and also lose.
Remember that both play optimally so here Alice will choose the scenario that makes her win.
```

### Example 3:
```
Input: stoneValue = [1,2,3,6]
Output: "Tie"
Explanation: Alice cannot win this game. She can end the game in a draw if she decided to choose all the first three piles, otherwise she will lose.
```

### Constraints:
- $1 \le \text{stoneValue.length} \le 5 \times 10^4$
- $-1000 \le \text{stoneValue}[i] \le 1000$

---

## 💡 Intuition & Approach

### 1. Game Theory / Minimax Relative Score Formulation
In a two-player zero-sum sequential game with full information, both players aim to maximize their score and minimize their opponent's score. Instead of tracking two separate running scores, we define a single state:
$$\text{dp}[i] = \text{Maximum relative score difference } (\text{Current Player's Score} - \text{Opponent's Score}) \text{ achievable from index } i \text{ to } n-1.$$

### 2. State Transition
From index $i$, the current player can choose to pick $k \in \{1, 2, 3\}$ stones (as long as $i + k \le n$):
- Sum of stones taken: $S_k = \sum_{j=i}^{i+k-1} \text{stoneValue}[j]$
- The remaining stones from index $i + k$ are now played by the opponent, whose best relative advantage will be $\text{dp}[i+k]$.
- Therefore, the current player's relative score difference for choice $k$ is:
$$\text{Score Diff} = S_k - \text{dp}[i+k]$$
- The optimal player chooses $k$ to maximize this difference:
$$\text{dp}[i] = \max_{k \in \{1, 2, 3\}, i+k \le n} \left( \sum_{j=i}^{i+k-1} \text{stoneValue}[j] - \text{dp}[i+k] \right)$$

### 3. Base Case & Space Optimization
- Base Case: $\text{dp}[n] = 0$ (no stones left means $0$ score difference).
- Because $\text{dp}[i]$ only depends on the subsequent 3 states ($\text{dp}[i+1], \text{dp}[i+2], \text{dp}[i+3]$), we only need 3 variables, optimizing auxiliary space from $\mathcal{O}(N)$ to $\mathcal{O}(1)$.

### 4. Final Result Evaluation
After computing $\text{dp}[0]$:
- If $\text{dp}[0] > 0 \implies \text{Alice's score} > \text{Bob's score} \implies \text{"Alice"}$
- If $\text{dp}[0] < 0 \implies \text{Alice's score} < \text{Bob's score} \implies \text{"Bob"}$
- If $\text{dp}[0] = 0 \implies \text{"Tie"}$

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N)$ — A single reverse loop from $N-1$ down to $0$ with at most $3$ constant-time transitions per index.
- **Space Complexity:** $\mathcal{O}(1)$ — Only $3$ integer variables (`dp1`, `dp2`, `dp3`) to store previous DP states.

---

## 🔍 Edge Cases Considered

- **Negative Values**: Stone values can be negative ($-1000 \le \text{stoneValue}[i] \le 1000$), so taking more stones can sometimes decrease score unless it forces the opponent into a worse deficit.
- **Array Length $< 3$**: Safely handles $N = 1$ and $N = 2$ without out-of-bounds access.
- **Tie Situations**: Handled when $\text{dp}[0] = 0$.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
