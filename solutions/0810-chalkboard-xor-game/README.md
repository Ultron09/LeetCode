# [810. Chalkboard XOR Game](https://leetcode.com/problems/chalkboard-xor-game/)

**Difficulty:** `Hard`  
**Topics:** [Math](../../topics/math-and-geometry.md), [Bit Manipulation](../../topics/bit-manipulation.md), Game Theory

---

## 📌 Problem Statement

You are given an array of integers `nums` represents the numbers written on a chalkboard.

Alice and Bob take turns erasing exactly one number from the chalkboard, with Alice starting first. If erasing a number causes the bitwise XOR of all the elements of the chalkboard to become `0`, then that player loses. The bitwise XOR of one element is that element itself, and the bitwise XOR of no elements is `0`.

Also, if any player starts their turn with the bitwise XOR of all the elements of the chalkboard equal to `0`, then that player wins.

Return `true` if and only if Alice wins the game, assuming both players play optimally.

### Example 1:
```
Input: nums = [1,1,2]
Output: false
Explanation: 
Alice has two choices: erase 1 or erase 2. 
If she erases 1, the nums array becomes [1, 2]. The bitwise XOR of all the elements is 1 XOR 2 = 3. Now Bob can remove any element he wants, because Alice will be the one to erase the last element and she will lose. 
If Alice erases 2 first, now nums become [1, 1]. The bitwise XOR of all the elements is 1 XOR 1 = 0. Alice will lose.
```

### Example 2:
```
Input: nums = [0,1]
Output: true
```

### Example 3:
```
Input: nums = [1,2,3]
Output: true
```

### Constraints:
- `1 <= nums.length <= 1000`
- `0 <= nums[i] < 2^16`

---

## 💡 Intuition & Approach

This is a beautiful Game Theory problem that reduces to a simple mathematical invariant.

Let `X` be the initial XOR sum of all elements.
According to the rules, if `X == 0`, Alice wins immediately.

What happens if `X != 0`?
Alice must make a move. She loses if *every* possible move she makes results in the new XOR sum becoming `0`.
Removing an element `x` changes the XOR sum to `X ^ x`.
For this to be `0` for *all* choices of `x`, it must be that `X ^ x = 0 \implies x = X` for every element in the array.

This implies all elements on the chalkboard are identical and equal to `X`.
If all elements are identical to `X`, what is their total XOR sum?
- If the number of elements `N` is **even**, `X ^ X ^ ... ^ X (even times) = 0`.
- But we initially established that `X != 0`! This is a contradiction.

Therefore, **if the array size `N` is EVEN, it is impossible for all elements to be `X`.**
This guarantees that when `N` is even and `X != 0`, the current player can *always* find at least one element to erase that does *not* make the XOR sum `0`.

### The Winning Strategy
Because Alice always starts when `N` is even (assuming `N % 2 == 0`), she can ALWAYS make a safe move. 
She then hands the board to Bob with an odd number of elements. Bob might have a safe move, or he might not (e.g., all remaining elements are equal to the current XOR sum). 
Even if Bob survives, he passes the board back to Alice with an **even** number of elements. Because Alice only plays on turns where the remaining elements are even, she will *never* be forced to make a losing move. Since the game is finite (elements are removed one by one), Bob is mathematically guaranteed to be the one trapped with no safe moves, forcing him to lose.

**Conclusion:** Alice wins if and only if the initial XOR sum is `0` OR the array size `N` is even.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N)$ — We iterate through the array once to compute the XOR sum.
- **Space Complexity:** $\mathcal{O}(1)$ — Only a single integer is needed to store the XOR sum.

---

## 🔍 Edge Cases Considered

- **Initial XOR is 0:** Caught perfectly by the condition `X == 0`.
- **All elements identical, odd length:** E.g. `[2, 2, 2]`. XOR is `2`. Size is odd. Alice has no safe move, returns `false`.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
