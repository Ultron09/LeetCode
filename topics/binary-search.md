# 🔍 Binary Search

Comprehensive theory, algorithmic patterns, templates, and problem catalog for Binary Search and Search on Answer space.

---

## 📖 1. Core Theory & Fundamentals

Binary Search reduces the search space by half at each step, yielding logarithmic $\mathcal{O}(\log N)$ time complexity.
- **Prerequisite**: Monotonicity (the search space or a predicate function evaluates to `[true, true, ..., false, false]` or monotonic increasing values).
- **Core Principle**: Find the boundary or target by querying the midpoint $M = L + \frac{R - L}{2}$.

### Search Space Types
1. **Index Space**: Direct lookup in a sorted/rotated array or matrix.
2. **Value / Answer Space**: When minimizing the maximum (or maximizing the minimum) feasible answer (e.g. Koko Eating Bananas, Capacity To Ship Packages).

---

## 🛠️ 2. Key Patterns & Code Templates

### Pattern A: Standard Binary Search / Leftmost & Rightmost Bound
```cpp
// Lower Bound (First index where nums[i] >= target)
int lowerBound(const vector<int>& nums, int target) {
    int left = 0, right = nums.size(); // [left, right)
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] >= target) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    return left;
}
```

### Pattern B: Search in Rotated Sorted Array
```cpp
int searchRotated(vector<int>& nums, int target) {
    int left = 0, right = static_cast<int>(nums.size()) - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] == target) return mid;

        // Check if left half is sorted
        if (nums[left] <= nums[mid]) {
            if (nums[left] <= target && target < nums[mid]) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        } 
        // Right half must be sorted
        else {
            if (nums[mid] < target && target <= nums[right]) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
    }
    return -1;
}
```

### Pattern C: Binary Search on Answer Space (Feasibility / Predicate Template)
```cpp
// Example: Koko Eating Bananas
bool isPossible(const vector<int>& piles, int speed, int h) {
    long long hours = 0;
    for (int pile : piles) {
        hours += (pile + speed - 1) / speed; // Ceiling division
    }
    return hours <= h;
}

int minEatingSpeed(vector<int>& piles, int h) {
    int low = 1, high = *max_element(piles.begin(), piles.end());
    int result = high;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (isPossible(piles, mid, h)) {
            result = mid;       // Try finding a smaller feasible speed
            high = mid - 1;
        } else {
            low = mid + 1;      // Speed too slow, increase speed
        }
    }
    return result;
}
```

### Pattern D: Range Query over Compressed Block Boundaries (Binary Search + RMQ)
When range queries $[L, R]$ operate on run-length encoded or grouped blocks (e.g. contiguous runs of 0s or intervals), we can binary search the boundary blocks in $\mathcal{O}(\log M)$ time:
- `first = lower_bound(blockEnds.begin(), blockEnds.end(), L) - blockEnds.begin()`
- `last = upper_bound(blockStarts.begin(), blockStarts.end(), R) - blockStarts.begin() - 1`
Boundary blocks $[first]$ and $[last]$ are clamped to $[L, R]$, while fully contained interior blocks $[first+1, last-2]$ are queried in $\mathcal{O}(1)$ via a precomputed Sparse Table or Segment Tree.

---

## ⚠️ 3. Common Pitfalls & Edge Cases

1. **Integer Overflow in Midpoint Calculation**: Always use `mid = low + (high - low) / 2` instead of `(low + high) / 2`.
2. **Off-by-One in Boundary Conditions**:
   - `while (low <= high)` requires `low = mid + 1` and `high = mid - 1`.
   - `while (low < high)` requires `right = mid` or `left = mid + 1`.
3. **Duplicates in Rotated Array**: If `nums[left] == nums[mid] == nums[right]`, we cannot determine which half is sorted; we must shrink bounds with `left++` and `right--` ($\mathcal{O}(N)$ worst-case).

---

## 📋 4. Solved Problems

| # | Title | Difficulty | Time | Space | Solution Link |
| :---: | :--- | :---: | :---: | :---: | :--- |
| 3312 | [Sorted GCD Pair Queries](../solutions/3312-sorted-gcd-pair-queries/README.md) | `Hard` | $\mathcal{O}(N + M \log M + Q \log M)$ | $\mathcal{O}(M)$ | [C++](../solutions/3312-sorted-gcd-pair-queries/solution.cpp) |
| 3501 | [Maximize Active Section with Trade II](../solutions/3501-maximize-active-section-with-trade-ii/README.md) | `Hard` | $\mathcal{O}(N \log N + Q \log N)$ | $\mathcal{O}(N \log N)$ | [C++](../solutions/3501-maximize-active-section-with-trade-ii/solution.cpp) |
| 3620 | [Network Recovery Pathways](../solutions/3620-network-recovery-pathways/README.md) | `Hard` | $\mathcal{O}((N + M) \log N \log M)$ | $\mathcal{O}(N + M)$ | [C++](../solutions/3620-network-recovery-pathways/solution.cpp) |

