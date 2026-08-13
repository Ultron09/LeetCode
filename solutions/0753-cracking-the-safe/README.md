# [753. Cracking the Safe](https://leetcode.com/problems/cracking-the-safe/)

**Difficulty:** `Hard`  
**Topics:** [Graphs](../../topics/graphs.md), DFS, Eulerian Circuit, Math

---

## 📌 Problem Statement

There is a safe protected by a password. The password is a sequence of `n` digits where each digit can be in the range `[0, k - 1]`.

The safe has a peculiar way of checking the password. When you enter in a sequence, it checks the most recent `n` digits that were entered each time you type a digit.

Return any string of minimum length that will unlock the safe at some point of entering it.

### Example 1:
```
Input: n = 1, k = 2
Output: "10"
Explanation: The password is a single digit, so enter each digit. "01" would also unlock the safe.
```

### Example 2:
```
Input: n = 2, k = 2
Output: "01100"
Explanation: For each possible password:
- "00" is typed in starting from the 4th digit.
- "01" is typed in starting from the 1st digit.
- "10" is typed in starting from the 3rd digit.
- "11" is typed in starting from the 2nd digit.
Thus "01100" will unlock the safe. "10011", and "11001" would also unlock the safe.
```

### Constraints:
- `1 <= n <= 4`
- `1 <= k <= 10`
- `1 <= k^n <= 4096`

---

## 💡 Intuition & Approach

This problem is equivalent to finding a **De Bruijn Sequence**. A De Bruijn sequence of order $n$ on an alphabet of size $k$ is a cyclic sequence in which every possible length-$n$ string on the alphabet occurs exactly once as a contiguous substring.

We can model this as a graph:
- **Vertices**: All possible strings of length $n-1$. (There are $k^{n-1}$ such vertices).
- **Edges**: Directed edges representing the addition of a new digit (0 to $k-1$). Each edge corresponds to a string of length $n$. (There are $k^n$ edges).

Because every vertex has exactly $k$ incoming edges and $k$ outgoing edges, the graph is strongly connected and balanced. By Euler's theorem, an **Eulerian circuit** (a path that visits every edge exactly once) is guaranteed to exist.

We can find an Eulerian path using **Hierholzer's Algorithm**:
1. Start at any vertex, such as the string of $n-1$ zeros.
2. Traverse unvisited outgoing edges recursively (DFS).
3. Post-order append the appended character to the answer string.
4. Finally, append the starting node string of $n-1$ zeros to the answer.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(k^n)$ — There are $k^n$ combinations/edges. Our DFS explores each edge exactly once. Checking and inserting into a hash set takes average $\mathcal{O}(n)$ time, so strictly it's $\mathcal{O}(n \cdot k^n)$, but since $n \le 4$, this is effectively $\mathcal{O}(k^n)$.
- **Space Complexity:** $\mathcal{O}(k^n)$ — The set `visited` stores $k^n$ strings of length $n$. The recursion stack depth is at most $k^n$.

---

## 🔍 Edge Cases Considered

- `n = 1` and `k = 1`: The graph has a single node of length 0 (empty string). Handled cleanly by starting with an empty string and appending.
- Small limits where `n=1`: The starting node is the empty string `""`, and edges are just single digits `0` to `k-1`.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
