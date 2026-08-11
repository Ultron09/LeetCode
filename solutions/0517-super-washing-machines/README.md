# [517. Super Washing Machines](https://leetcode.com/problems/super-washing-machines/)

**Difficulty:** `Hard`  
**Topics:** [Greedy](../../topics/greedy.md), [Prefix Sum](../../topics/arrays-and-hashing.md), [Math & Geometry](../../topics/math-and-geometry.md)

---

## 📌 Problem Statement

You have `n` super washing machines on a line. Initially, each washing machine has some dresses or is empty.

For each move, you could choose any `m` ($1 \le m \le n$) washing machines, and pass **one dress** of each washing machine to one of its adjacent washing machines at the same time.

Given an integer array `machines` representing the number of dresses in each washing machine from left to right on the line, return the **minimum number of moves** to make all the washing machines have the same number of dresses. If it is not possible to do it, return `-1`.

### Example 1:
```
Input: machines = [1,0,5]
Output: 3
Explanation:
1st move:    1     0 <-- 5    =>    1     1     4
2nd move:    1 <-- 1 <-- 4    =>    2     1     3
3rd move:    2     1 <-- 3    =>    2     2     2
```

### Example 2:
```
Input: machines = [0,3,0]
Output: 2
Explanation:
1st move:    0 <-- 3     0    =>    1     2     0
2nd move:    1     2 --> 0    =>    1     1     1
```

### Example 3:
```
Input: machines = [0,2,0]
Output: -1
Explanation:
It's impossible to make all three washing machines have the same number of dresses.
```

### Constraints:
- $n == \text{machines.length}$
- $1 \le n \le 10^4$
- $0 \le \text{machines}[i] \le 10^5$

---

## 💡 Intuition & Approach

### 1. Parity & Feasibility Check
Let $S = \sum \text{machines}[i]$. If $S \pmod n \ne 0$, dresses cannot be distributed evenly; return `-1` immediately.  
The target number of dresses for each machine is $\text{target} = S / n$.

### 2. Flow Bottleneck Analysis
In each step, any dress can move across any adjacent machine boundary simultaneously. Two distinct physical bottlenecks dictate the lower bound:

1. **Cut Bottleneck (Cross-Boundary Flow)**:
   - For any partition between machine $i$ and $i+1$, the net excess dresses in the left partition $[0 \dots i]$ is:
     $$\text{balance}[i] = \sum_{k=0}^{i} (\text{machines}[k] - \text{target})$$
   - Since at most 1 dress can cross the boundary between $i$ and $i+1$ in a single move, this cut requires at least $|\text{balance}[i]|$ moves.
   
2. **Single Machine Outflow Rate Bottleneck**:
   - A single machine with excess dresses $(\text{machines}[i] - \text{target} > 0)$ can only emit **at most 1 dress per turn** (it cannot simultaneously send a dress to the left and to the right in the same turn).
   - Hence, this individual machine alone requires at least $\text{machines}[i] - \text{target}$ moves.

### 3. Tightness of Lower Bound
Because all non-conflicting flows can occur simultaneously across independent edges, the global minimum number of moves is precisely the maximum over all local bottlenecks:
$$\text{moves} = \max_{0 \le i < n} \Big( \max\big(|\text{balance}[i]|, \text{machines}[i] - \text{target}\big) \Big)$$

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N)$
  - A single linear pass computes the total sum and evaluates running balances.
  - With $N \le 10^4$, execution completes in $< 1\text{ ms}$.
- **Space Complexity:** $\mathcal{O}(1)$
  - Only scalar counters for total sum, target, and running balance are maintained.

---

## 🔍 Edge Cases Considered

- **Non-divisible Total Sum**: Returns `-1`.
- **Already Equal ($N$ identical elements)**: Returns `0` immediately.
- **Large Peak Values ($10^5$)**: Accurately tracks heavy outflow constraints without overflow.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
