# [403. Frog Jump](https://leetcode.com/problems/frog-jump/)

**Difficulty:** `Hard`  
**Topics:** [Dynamic Programming](../../topics/dynamic-programming.md), [Arrays & Hashing](../../topics/arrays-and-hashing.md), [Binary Search](../../topics/binary-search.md)

---

## 📌 Problem Statement

A frog is crossing a river. The river is divided into some number of units, and at each unit, there may or may not exist a stone. The frog can jump on a stone, but it must not jump into the water.

Given a list of `stones` positions (in units) in sorted ascending order, determine if the frog can cross the river by landing on the last stone. Initially, the frog is on the first stone and assumes the first jump must be $1$ unit.

If the frog's last jump was $k$ units, its next jump must be either $k - 1$, $k$, or $k + 1$ units. The frog can only jump in the forward direction.

### Example 1:
```
Input: stones = [0,1,3,5,6,8,12,17]
Output: true
Explanation: The frog can jump to the last stone by jumping 1 unit to the 2nd stone, then 2 units to the 3rd stone, then 2 units to the 4th stone, then 3 units to the 6th stone, 4 units to the 7th stone, and 5 units to the 8th stone.
```

### Example 2:
```
Input: stones = [0,1,2,3,4,8,9,11]
Output: false
Explanation: There is no way to jump to the last stone as the gap between the 5th and 6th stone is too large.
```

### Constraints:
- $2 \le \text{stones.length} \le 2000$
- $0 \le \text{stones}[i] \le 2^{31} - 1$
- $\text{stones}[0] == 0$
- `stones` is sorted in a **strictly increasing** order.

---

## 💡 Intuition & Approach

### 1. Mathematical Upper Bound on Jump Sizes
A crucial mathematical observation is that at stone index $i$ ($0$-indexed), the incoming jump size $k$ cannot exceed $i$:
- Stone $0 \to$ jump $1 \to$ stone $1$ ($k = 1 \le 1$).
- From stone $1$, the next jump is at most $1 + 1 = 2 \le 2$.
- By mathematical induction, after $m$ jumps the jump size is at most $m$. Since reaching index $i$ requires at least $i$ jumps if every consecutive stone is stepped on (or fewer jumps if stones are skipped), the incoming jump $k$ satisfies:
  $$k \le i < N$$

Therefore, the maximum possible jump size at any stone is strictly bounded by $N - 1 \le 2000$.

### 2. State Formulation & Transition
Define the 2D dynamic programming state:
- $\text{dp}[i][k] =$ `true` if stone $i$ can be reached with an incoming jump of size $k$.

#### Base Case:
- If $\text{stones}[1] \ne 1$, the frog cannot even make the mandatory initial jump of $1$ unit $\to$ return `false`.
- $\text{dp}[1][1] = \text{true}$ (at stone index $1$ with incoming jump $k=1$).

#### Transitions:
For each stone $i \in [1, N-2]$ and each valid incoming jump $k \in [1, i]$ where $\text{dp}[i][k] = \text{true}$:
- Consider next jump $d \in \{k - 1, k, k + 1\}$ where $d > 0$.
- The landing coordinate is $\text{target} = \text{stones}[i] + d$.
- If $\text{target}$ exists in the stone list at index $j$:
  - If $j == N - 1$, the frog has successfully reached the destination $\to$ **early return `true`**.
  - Set $\text{dp}[j][d] = \text{true}$.

### 3. Space & Lookup Optimization
- Instead of dynamically allocating nested containers, we use a single flat contiguous 1D array of size $N \times N$ bytes ($\sim 4\text{ MB}$ for $N = 2000$), ensuring maximum cache locality and $\mathcal{O}(1)$ indexing.
- We map stone positions to their indices using `unordered_map<int, int>` with pre-reserved bucket capacity for $\mathcal{O}(1)$ average position lookups.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N^2)$
  - There are at most $\sum_{i=1}^{N-1} i = \frac{N(N-1)}{2} \approx 2 \times 10^6$ reachable states $(i, k)$.
  - From each valid state, we inspect at most $3$ next jump sizes with $\mathcal{O}(1)$ hash map lookup.
  - In practice, only a tiny fraction of the state space is reachable, allowing the algorithm to execute in $< 15\text{ ms}$.
- **Space Complexity:** $\mathcal{O}(N^2)$
  - A flat boolean array of size $N \times N$ consumes $2000 \times 2000 \times 1\text{ byte} \approx 4\text{ MB}$.
  - The position-to-index hash map stores $N$ entries ($\mathcal{O}(N)$ space).

---

## 🔍 Edge Cases Considered

- **Mandatory First Jump Check**: If $\text{stones}[1] \ne 1$, immediately returns `false`.
- **Minimal Input ($N = 2$)**: If $\text{stones} = [0, 1]$, correctly evaluates to `true`.
- **Large Intermediate Gaps**: If any jump required exceeds $k + 1$, the target stone is unreachable and skipped.
- **Triangular Jump Growth**: Jumps strictly incrementing by $+1$ ($1, 2, 3, 4, \dots$) correctly cross quadratic coordinate distances $\frac{k(k+1)}{2}$.
- **Decelerating Jumps**: Jumps that decrease by $-1$ down to $1$ unit are fully handled without infinite loops or reverse jumping (since $d > 0$).

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
