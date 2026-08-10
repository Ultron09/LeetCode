# 🎯 Two Pointers

Comprehensive theory, algorithmic patterns, templates, and problem catalog for the Two Pointers technique.

---

## 📖 1. Core Theory & Fundamentals

The Two Pointers technique optimizes nested $\mathcal{O}(N^2)$ loops to $\mathcal{O}(N)$ by utilizing mathematical monotonicity or structural properties of data (such as sorted order, palindromes, or partitioning).

### Major Variations
1. **Opposite Ends (Converging Pointers)**: One pointer starts at index `0` and another at index `N - 1`. They move inward until they meet (e.g., Valid Palindrome, Two Sum II, Container With Most Water).
2. **Same Direction (Fast & Slow Pointers)**: Both move forward, but at different speeds or conditions (e.g., Remove Duplicates from Sorted Array, Move Zeroes, Floyd's Cycle Detection).
3. **Two Sequences**: One pointer in array $A$ and another in array $B$ (e.g., Merge Sorted Array, Is Subsequence).

---

## 🛠️ 2. Key Patterns & Code Templates

### Pattern A: Converging Pointers on Sorted Array (Two Sum II)
```cpp
vector<int> twoSumSorted(vector<int>& numbers, int target) {
    int left = 0;
    int right = static_cast<int>(numbers.size()) - 1;
    
    while (left < right) {
        int sum = numbers[left] + numbers[right];
        if (sum == target) {
            return {left + 1, right + 1}; // 1-indexed
        } else if (sum < target) {
            left++; // Need a larger sum
        } else {
            right--; // Need a smaller sum
        }
    }
    return {};
}
```

### Pattern B: Fast & Slow Pointer (In-Place Array Modification)
```cpp
// Remove duplicates in-place from sorted array
int removeDuplicates(vector<int>& nums) {
    if (nums.empty()) return 0;
    int slow = 0;
    for (size_t fast = 1; fast < nums.size(); ++fast) {
        if (nums[fast] != nums[slow]) {
            slow++;
            nums[slow] = nums[fast];
        }
    }
    return slow + 1; // Length of unique elements
}
```

### Pattern C: Three Pointers / 3Sum Pattern
Sort the array, fix one element `i`, and use two converging pointers for the remaining pair.
```cpp
vector<vector<int>> threeSum(vector<int>& nums) {
    vector<vector<int>> result;
    sort(nums.begin(), nums.end());
    int n = nums.size();
    
    for (int i = 0; i < n - 2; ++i) {
        if (i > 0 && nums[i] == nums[i - 1]) continue; // Skip duplicate pivots
        if (nums[i] > 0) break; // Optimization: sum cannot reach 0
        
        int left = i + 1, right = n - 1;
        while (left < right) {
            int sum = nums[i] + nums[left] + nums[right];
            if (sum == 0) {
                result.push_back({nums[i], nums[left], nums[right]});
                while (left < right && nums[left] == nums[left + 1]) left++;
                while (left < right && nums[right] == nums[right - 1]) right--;
                left++;
                right--;
            } else if (sum < 0) {
                left++;
            } else {
                right--;
            }
        }
    }
    return result;
}
```

### Pattern D: Converging Pointers with Running Min-Max Boundaries (Trapping Rain Water)
```cpp
int trap(vector<int>& height) {
    int left = 0, right = static_cast<int>(height.size()) - 1;
    int leftMax = 0, rightMax = 0, water = 0;

    while (left < right) {
        if (height[left] < height[right]) {
            if (height[left] >= leftMax) leftMax = height[left];
            else water += leftMax - height[left];
            left++;
        } else {
            if (height[right] >= rightMax) rightMax = height[right];
            else water += rightMax - height[right];
            right--;
        }
    }
    return water;
}
```

---

## ⚠️ 3. Common Pitfalls & Edge Cases

1. **Infinite Loops**: Ensure at least one pointer strictly advances/retreats in every iteration of the `while` loop.
2. **Duplicate Handling**: In multi-sum problems (3Sum, 4Sum), skipping duplicates at both the pivot level and the inner pointer level is essential to prevent duplicate triplets/quadruplets.
3. **Index Bounds**: When skipping duplicates with `while (left < right && nums[left] == nums[left + 1])`, always check `left < right` before dereferencing `left + 1`.

---

## 📋 4. Solved Problems

| # | Title | Difficulty | Time | Space | Solution Link |
| :---: | :--- | :---: | :---: | :---: | :--- |
| 42 | [Trapping Rain Water](../solutions/0042-trapping-rain-water/README.md) | `Hard` | $\mathcal{O}(N)$ | $\mathcal{O}(1)$ | [C++](../solutions/0042-trapping-rain-water/solution.cpp) |
| 3534 | [Path Existence Queries in a Graph II](../solutions/3534-path-existence-queries-in-a-graph-ii/README.md) | `Hard` | $\mathcal{O}(N \log N + Q \log N)$ | $\mathcal{O}(N \log N)$ | [C++](../solutions/3534-path-existence-queries-in-a-graph-ii/solution.cpp) |

