# [1. Two Sum](https://leetcode.com/problems/two-sum/)

**Difficulty:** `Easy`  
**Topics:** [Arrays & Hashing](../../topics/arrays-and-hashing.md)

---

## 📌 Problem Statement

Given an array of integers `nums` and an integer `target`, return indices of the two numbers such that they add up to `target`.

You may assume that each input would have **exactly one solution**, and you may not use the same element twice.

You can return the answer in any order.

### Example 1:
```
Input: nums = [2,7,11,15], target = 9
Output: [0,1]
Explanation: Because nums[0] + nums[1] == 9, we return [0, 1].
```

### Example 2:
```
Input: nums = [3,2,4], target = 6
Output: [1,2]
```

### Example 3:
```
Input: nums = [3,3], target = 6
Output: [0,1]
```

### Constraints:
- `2 <= nums.length <= 10^4`
- `-10^9 <= nums[i] <= 10^9`
- `-10^9 <= target <= 10^9`
- **Only one valid answer exists.**

---

## 💡 Intuition & Approach

1. **Brute Force Idea**: We could check every pair of elements by using two nested loops. This takes $\mathcal{O}(N^2)$ time and is too slow for large inputs.
2. **Optimal Strategy**: A hash map allows us to look up if we've already seen the needed complement (`target - current_value`) in $\mathcal{O}(1)$ average time.
3. **Step-by-step Execution**: We iterate through the array once. For each element, we check if its complement exists in our hash map. If it does, we immediately return the indices. If not, we add the current element and its index to the hash map and move on.

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N)$ — We traverse the list containing $N$ elements exactly once. Each look up in the hash map costs $\mathcal{O}(1)$ time.
- **Space Complexity:** $\mathcal{O}(N)$ — The extra space required depends on the number of items stored in the hash map, which stores at most $N$ elements.

---

## 🔍 Edge Cases Considered

- Array containing negative numbers.
- The target is $0$.
- The two numbers that add up to the target are identical (e.g., `[3, 3]`, target `6`). The logic handles this because we check the map *before* adding the current number, meaning a number cannot match with itself at the same index.

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
