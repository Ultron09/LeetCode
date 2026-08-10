# [2751. Robot Collisions](https://leetcode.com/problems/robot-collisions/)

**Difficulty:** `Hard`  
**Topics:** [Stack & Queue](../../topics/stack-and-queue.md), [Arrays & Hashing](../../topics/arrays-and-hashing.md), [Sorting](../../topics/arrays-and-hashing.md)

---

## 📌 Problem Statement

There are $n$ 1-indexed robots positioned on a line, each with an initial position, health, and movement direction (`'L'` or `'R'`).

All robots start moving simultaneously at the same speed:
- If two robots collide:
  - The robot with **lower health is removed** from the line.
  - The survivor's health **decreases by 1** and it continues in its original direction.
  - If both have **equal health, both are removed**.
- Return an array containing the remaining healths of the surviving robots in their **original input order**.

### Example 1:
```
Input: positions = [5,4,3,2,1], healths = [2,17,9,15,10], directions = "RRRRR"
Output: [2,17,9,15,10]
Explanation: All robots move right in the same direction, so no collisions occur.
```

### Example 2:
```
Input: positions = [3,5,2,6], healths = [10,10,15,12], directions = "RLRL"
Output: [14]
Explanation:
- Robot at 3 ('R', 10) and Robot at 5 ('L', 10) collide; both destroyed.
- Robot at 2 ('R', 15) and Robot at 6 ('L', 12) collide; Robot at 6 destroyed, Robot at 2 health becomes 15 - 1 = 14.
- Return [14].
```

### Example 3:
```
Input: positions = [1,2,5,6], healths = [10,10,11,11], directions = "RLRL"
Output: []
```

### Constraints:
- $1 \le n == \text{positions.length} == \text{healths.length} == \text{directions.length} \le 10^5$
- $1 \le \text{positions}[i], \text{healths}[i] \le 10^9$
- $\text{directions}[i] \in \{'L', 'R'\}$
- All values in `positions` are distinct.

---

## 💡 Intuition & Approach

### 1. Spatial Ordering
Since collisions can only happen when a right-moving robot `'R'` is to the left of a left-moving robot `'L'`, we must process robots in increasing order of their spatial positions.
- Store original indices `0..n-1` and sort them using a custom comparator on `positions[i]`.

### 2. Stack-Based Collision Resolution
As we iterate left-to-right through sorted robots:
- **Direction `'R'`**: Push robot index onto stack (it travels rightwards, awaiting potential collisions with future `'L'` robots).
- **Direction `'L'`**: Resolve collisions against the stack of active `'R'` robots:
  - While stack is not empty and current robot has $\text{health} > 0$:
    - If `healths[top] < healths[curr]`: Top is destroyed (`healths[top] = 0`), stack pops, and `healths[curr] -= 1`.
    - If `healths[top] > healths[curr]`: Current is destroyed (`healths[curr] = 0`), `healths[top] -= 1`, break.
    - If `healths[top] == healths[curr]`: Both are destroyed (`healths[top] = 0, healths[curr] = 0`), stack pops, break.

### 3. Preserving Original Input Order
Iterate through the original `0..n-1` indices and collect `healths[i]` for all $i$ where $\text{healths}[i] > 0$.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N \log N)$
  - Sorting indices: $\mathcal{O}(N \log N)$.
  - Stack operations: Each robot index is pushed onto the stack at most once and popped at most once $\implies \mathcal{O}(N)$.
  - Output collection: $\mathcal{O}(N)$.
  - Total time $< 15$ ms in C++.
- **Space Complexity:** $\mathcal{O}(N)$ auxiliary space for indices array and collision stack.

---

## 🔍 Edge Cases Considered

- **All same direction (`"RRR..."` or `"LLL..."`)**: Zero collisions occur; all survive in original order.
- **Equal health simultaneous elimination**: Both robots marked as health $0$ and popped cleanly.
- **Cascade of multiple collisions**: A strong `'L'` robot eliminates multiple `'R'` robots in sequence until either depleted or surviving.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
