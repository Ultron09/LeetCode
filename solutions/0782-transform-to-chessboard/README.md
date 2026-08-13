# [782. Transform to Chessboard](https://leetcode.com/problems/transform-to-chessboard/)

**Difficulty:** `Hard`  
**Topics:** [Arrays & Hashing](../../topics/arrays-and-hashing.md), [Math & Geometry](../../topics/math-and-geometry.md)

---

## 📌 Problem Statement

You are given an `n x n` binary grid `board`. In each move, you can swap any two rows with each other, or any two columns with each other.

Return the minimum number of moves to transform the board into a chessboard board. If the task is impossible, return `-1`.

A chessboard board is a board where no `0`'s and no `1`'s are 4-directionally adjacent.

### Example 1:
```
Input: board = [[0,1,1,0],[0,1,1,0],[1,0,0,1],[1,0,0,1]]
Output: 2
Explanation: One potential sequence of moves is shown.
The first move swaps the first and second column.
The second move swaps the second and third row.
```

### Constraints:
- `n == board.length`
- `n == board[i].length`
- `2 <= n <= 30`
- `board[i][j]` is either `0` or `1`.

---

## 💡 Intuition & Approach

This problem can be heavily simplified by noticing two mathematical properties of row/column swaps on a matrix:

1. **Invariance of Relative Structure**: Swapping rows never changes the contents of a row, only its vertical position. The same applies to columns. Thus, in a valid chessboard, there can only be **two unique types of rows**, and they must be bitwise inverses of each other (e.g., `0101` and `1010`). The exact same logic applies to columns.
2. **Independence of Swaps**: Swapping two rows does not change the parity (even/odd sequence) of the columns, and vice versa. Therefore, we can calculate the minimum row swaps and minimum column swaps **independently** and simply sum them.

### Step-by-Step Algorithm:

1. **Validity Check (Rectangle Property)**:
   For any rectangle defined by corners `(0, 0)`, `(r, 0)`, `(0, c)`, and `(r, c)`, the XOR sum of the four corners must be `0`.
   `board[0][0] ^ board[r][0] ^ board[0][c] ^ board[r][c] == 0`
   If this is ever `1`, the board cannot be transformed into a chessboard.

2. **Count 1s and Misplaced Elements**:
   We only need to look at the first row and the first column (due to the invariance property, fixing the first row/col forces the rest of the valid board into place).
   Count the total `1`s in the first row and first column. 
   Also, count how many elements are out of place compared to an ideal alternating pattern starting with `1` (i.e., `1, 0, 1, 0...`).

3. **Check Frequency Constraints**:
   For a line of length `N` to alternate, the count of `1`s and `0`s must either be equal (if `N` is even) or differ by exactly 1 (if `N` is odd). If the counts are off, return `-1`.

4. **Calculate Minimum Swaps**:
   Each swap corrects exactly 2 misplaced elements, so `swaps = misplaced / 2`.
   - **If N is even**: We can target either pattern (`1010...` or `0101...`). We take the minimum of `misplaced` and `N - misplaced`.
   - **If N is odd**: We can only target the pattern that aligns with the majority element. This means the number of misplaced elements must be an **even** number (because each swap moves 2 elements). If `misplaced` is odd, we MUST use the other pattern `N - misplaced`.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N^2)$ — We iterate through all cells once to validate the rectangle property. The rest of the checks take $\mathcal{O}(N)$ time.
- **Space Complexity:** $\mathcal{O}(1)$ — We only maintain a few integer counters.

---

## 🔍 Edge Cases Considered

- **Odd vs. Even Grid Dimensions**: Handled cleanly by the parity check in step 4. Odd dimensions force a specific start bit.
- **Already a Chessboard**: Calculates `0` misplaced elements, dividing by `2` yields `0` swaps.
- **Unsolvable Configurations**: Fails gracefully either at the rectangle XOR property check or the 1s/0s frequency check.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
