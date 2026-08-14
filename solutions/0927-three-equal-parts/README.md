# [927. Three Equal Parts](https://leetcode.com/problems/three-equal-parts/)

**Difficulty:** `Hard`  
**Topics:** [Math](../../topics/math-and-geometry.md), [Array](../../topics/arrays-and-hashing.md)

---

## 📌 Problem Statement

You are given an array `arr` which consists of only zeros and ones, divide the array into three non-empty parts such that all of these parts represent the same binary value.

If it is possible, return any `[i, j]` with `i + 1 < j`, such that:
- `arr[0], arr[1], ..., arr[i]` is the first part,
- `arr[i + 1], arr[i + 2], ..., arr[j - 1]` is the second part, and
- `arr[j], arr[j + 1], ..., arr[arr.length - 1]` is the third part.
- All three parts have equal binary values.

If it is not possible, return `[-1, -1]`.

Note that the entire part is used when considering what binary value it represents. For example, `[1,1,0]` represents `6` in decimal, not `3`. Also, leading zeros are allowed, so `[0,1,1]` and `[1,1]` represent the same value.

### Example 1:
```
Input: arr = [1,0,1,0,1]
Output: [0,3]
```

### Example 2:
```
Input: arr = [1,1,0,1,1]
Output: [-1,-1]
```

### Constraints:
- `3 <= arr.length <= 3 * 10^4`
- `arr[i]` is `0` or `1`

---

## 💡 Intuition & Approach

To divide the array into three parts with the same binary value, they must contain exactly the same number of `1`s. This gives us a strong constraint to identify the target boundaries.

1. **Count `1`s:** 
   Calculate the total number of `1`s in the array. If the total number of `1`s is not divisible by `3`, it's impossible to form three equal parts, so we return `[-1, -1]`.
   - If the total number of `1`s is `0`, any valid partition works. We can just return `[0, 2]`.

2. **Locate the bounds:** 
   Let `target = total_ones / 3`. We can identify the indices of the first `1` of the first part, the first `1` of the second part, and the first `1` of the third part. Let's call these indices `p1`, `p2`, and `p3`.

3. **Match the sequences:** 
   Since the third part must go all the way to the end of the array, the length of the matching non-leading-zero segment must be exactly `match_len = arr.length - p3`. 
   We just need to verify that:
   `arr[p1...p1 + match_len - 1] == arr[p2...p2 + match_len - 1] == arr[p3...arr.length - 1]`.

   If they match perfectly, we have our valid parts! The first part ends at `i = p1 + match_len - 1`, and the third part starts at `j = p2 + match_len`. (Any zeroes between the end of part 1 and the first `1` of part 2 simply act as leading zeroes for part 2, which does not affect its binary value).

---

## ⚡ Complexity Analysis

- **Time Complexity:** $\mathcal{O}(N)$ — We make a few linear passes over the array to count the `1`s, find `p1`, `p2`, `p3`, and match the subarrays.
- **Space Complexity:** $\mathcal{O}(1)$ — Only a few integer variables are used.

---

## 🔍 Edge Cases Considered

- Arrays entirely filled with `0`s (handles correctly by immediately returning `[0, 2]`).
- Arrays where `1`s cannot be split equally.
- Arrays where the matching segment extends beyond the available bounds (i.e., not enough zeroes between `1` chunks to satisfy the trailing zeroes required by the third part).

---

## 💻 Source Code

- [C++ Solution](solution.cpp)
