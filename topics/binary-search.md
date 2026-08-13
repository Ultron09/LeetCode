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

### Pattern E: Binary Search in Rotated Sorted Array with Duplicates
When finding the minimum element in a rotated sorted array with duplicates:
1. Compare `nums[mid]` against `nums[right]`.
2. If `nums[mid] > nums[right]`: pivot is to the right $\to$ `left = mid + 1`.
3. If `nums[mid] < nums[right]`: right half is sorted $\to$ `right = mid`.
4. If `nums[mid] == nums[right]`: ambiguous inflection point $\to$ safely decrement `right--` ($\mathcal{O}(\log N)$ average, $\mathcal{O}(N)$ worst).

### Pattern F: Search on Answer with Circular Perimeter Linearization & Greedy Selection
When maximizing the minimum distance among $k$ points on a circular boundary (e.g. square perimeter):
1. **Linearize 2D Boundary to 1D**: Map $(x, y) \to pos \in [0, 4 \times side)$.
2. **Binary Search on Feasible Distance**: Search for optimal minimum distance $D \in [1, side]$.
3. **Pigeonhole Pruning**: Test candidate starting points within $[pos[0], pos[0] + P/k]$.
4. **Greedy Jumps with `std::lower_bound`**: Select $k - 1$ subsequent points on the doubled array $pos + P$ in $\mathcal{O}(k \log N)$ time.

### Pattern G: Median / k-th Element Partitioning of Two Sorted Arrays
To find the median or $k$-th element of two sorted arrays in $\mathcal{O}(\log(\min(M, N)))$ time:
1. **Partition Search Space**: Ensure $M \le N$. Binary search $i \in [0, M]$ elements taken from array 1, fixing $j = \lfloor \frac{M + N + 1}{2} \rfloor - i$ elements from array 2.
2. **Boundary Sentinels**: Define $\text{maxLeft1} = (i == 0) \, ? \, -\infty : A[i-1]$, $\text{minRight1} = (i == M) \, ? \, +\infty : A[i]$, and similarly for $B$.
### Pattern H: Rotated Array Pivot Search with Duplicates
To find the minimum element or rotation pivot when the array contains duplicate elements:
1. Maintain search window `[left, right]` with `mid = left + (right - left) / 2`.
2. Compare `nums[mid]` against `nums[right]`:
   - If `nums[mid] > nums[right]`: The inflection pivot must lie strictly in the right half $\implies \text{left} = \text{mid} + 1$.
   - If `nums[mid] < nums[right]`: The right half is strictly sorted; minimum lies in the left half or at `mid` $\implies \text{right} = \text{mid}$.
   - If `nums[mid] == nums[right]`: Ambiguity exists due to duplicates; safely eliminate the redundant boundary element without missing the minimum $\implies \text{right} = \text{right} - 1$.
3. Average time complexity is $\mathcal{O}(\log N)$, degrading to $\mathcal{O}(N)$ in the worst case when all elements are identical.

### Pattern I: Divide-and-Conquer Range Sum Counting with Monotonic Two-Pointer Windowing
When counting index pairs $(i, j)$ with $i < j$ satisfying range bounds on prefix sums ($\text{lower} \le P[j] - P[i] \le \text{upper} \iff P[j] - \text{upper} \le P[i] \le P[j] - \text{lower}$):
1. **Divide & Conquer on Prefix Sums**: Recursively divide the prefix array into $[ \text{left}, \text{mid} ]$ and $[ \text{mid} + 1, \text{right} ]$, sorting each half during the merge step.
2. **Monotonic Window Traversal**: For each $j \in [\text{mid} + 1, \text{right}]$, both target bounds $[P[j] - \text{upper}, P[j] - \text{lower}]$ increase monotonically.
3. **Linear Cross-Counting**: Advance two non-resetting pointers `low_ptr` and `high_ptr` through the sorted left half in $\mathcal{O}(\text{right} - \text{left} + 1)$ time.
4. **Merge**: In-place / buffer merge maintains sorted order for the parent recursion frame, achieving optimal $\mathcal{O}(N \log N)$ total time without coordinate compression overhead.

### Pattern J: 2D Column Compression with Ordered Set BST Prefix Lookup
When finding the max rectangle sum $\le k$ in an $m \times n$ matrix:
1. **Column Compression**: Fix left column $l$ and right column $r$. Maintain `rowSum[i]` = sum of `matrix[i][l..r]`, reducing the 2D problem to a 1D constrained max subarray sum.
2. **Ordered Set for Constrained Prefix Sum**: For prefix sum `currSum`, find the smallest `prevSum` $\ge$ `currSum - k` using `std::set::lower_bound(currSum - k)` in $\mathcal{O}(\log m)$.
3. **Dimension Optimization**: Always iterate over $\min(m, n)^2$ pairs in the outer loop. Transpose the matrix if $m < n$.
4. **Total Complexity**: $\mathcal{O}(\min(m,n)^2 \cdot \max(m,n) \cdot \log(\max(m,n)))$.

### Pattern K: Minimax Partitioning on Answer Space (Greedy Capacity Packing)
When partitioning a contiguous array into $k$ non-empty subarrays to minimize the largest subarray sum:
1. **Monotonicity Identification**: Feasibility predicate $P(S)$ = "Can `nums` be split into $\le k$ subarrays with sum $\le S$?" evaluates monotonically as `[false, ..., false, true, ..., true]`.
2. **Search Range Bounds**:
   - $\text{low} = \max(\text{nums})$ (the single largest element cannot be subdivided).
   - $\text{high} = \sum \text{nums}$ (all elements in a single partition).
3. **Linear Greedy Verification**: Greedily accumulate elements into the current subarray; as soon as adding the next element exceeds $S$, start a new subarray. If total subarrays exceed $k$, return `false`.
4. **Logarithmic Convergence**: Achieves $\mathcal{O}(N \log(\sum \text{nums}))$ time with $\mathcal{O}(1)$ space, drastically outperforming $\mathcal{O}(k N^2)$ DP.

### Pattern L: Merge Sort Inversion Counting with Scaling Factors (Reverse Pairs)
When counting index pairs $(i, j)$ with $i < j$ satisfying non-unit multiplicative thresholds $\text{nums}[i] > c \times \text{nums}[j]$ (e.g. $c = 2$):
1. **Divide & Conquer**: Recursively sort $[l, mid]$ and $[mid+1, r]$.
2. **Two-Pointer Monotonic Cross Counting**: For each $i \in [l, mid]$, advance right pointer $j \in [mid+1, r]$ while $\text{nums}[i] > c \times \text{nums}[j]$. Add $(j - (mid + 1))$ to the inversion count in $\mathcal{O}(r - l + 1)$ amortized time.
3. **64-bit Overflow Protection**: Evaluate $c \times \text{nums}[j]$ using `2LL * nums[j]` to avoid signed 32-bit integer overflow.
4. **Complexity**: $\mathcal{O}(N \log N)$ time and $\mathcal{O}(N)$ space.

### Pattern M: Search on Answer in Implicit Monotonic 2D Matrices (Kth Smallest Number in Multiplication Table)
When finding the $k$-th smallest element in an implicit monotonic 2D grid (e.g. $A[i][j] = i \times j$):
1. **Search Domain**: Low bound $1$, high bound $M \times N$.
2. **Row-Wise Counting Predicate**: For candidate $X$, row $i$ values are $i \times 1, i \times 2, \dots, i \times N$. The number of elements $\le X$ in row $i$ is $\min(N, \lfloor X / i \rfloor)$.
3. **Dimension Optimization**: Summing over $\min(M, N)$ rows evaluates $f(X)$ in $\mathcal{O}(\min(M, N))$ time.
4. **Complexity**: $\mathcal{O}(\min(M, N) \cdot \log(M \cdot N))$ time and $\mathcal{O}(1)$ space.

---

## ⚠️ 3. Common Pitfalls & Edge Cases

1. **Integer Overflow in Midpoint Calculation**: Always use `mid = low + (high - low) / 2` instead of `(low + high) / 2`.
2. **Off-by-One in Boundary Conditions**:
   - `while (low <= high)` requires `low = mid + 1` and `high = mid - 1`.
   - `while (low < high)` requires `right = mid` or `left = mid + 1`.
3. **Duplicates in Rotated Array**: If `nums[left] == nums[mid] == nums[right]`, we cannot determine which half is sorted; we must shrink bounds with `right--` ($\mathcal{O}(N)$ worst-case).
4. **64-bit Range Queries on Prefix Sums**: When calculating $P[j] - \text{upper}$, 32-bit values can overflow; always use `long long` for prefix sums and interval checks.

---

## 📋 4. Solved Problems

| # | Title | Difficulty | Time | Space | Solution Link |
| :---: | :--- | :---: | :---: | :---: | :--- |
| 4 | [Median of Two Sorted Arrays](../solutions/0004-median-of-two-sorted-arrays/README.md) | `Hard` | $\mathcal{O}(\log(\min(M, N)))$ | $\mathcal{O}(1)$ | [C++](../solutions/0004-median-of-two-sorted-arrays/solution.cpp) |
| 154 | [Find Minimum in Rotated Sorted Array II](../solutions/0154-find-minimum-in-rotated-sorted-array-ii/README.md) | `Hard` | $\mathcal{O}(\log N)$ avg / $\mathcal{O}(N)$ | $\mathcal{O}(1)$ | [C++](../solutions/0154-find-minimum-in-rotated-sorted-array-ii/solution.cpp) |
| 315 | [Count of Smaller Numbers After Self](../solutions/0315-count-of-smaller-numbers-after-self/README.md) | `Hard` | $\mathcal{O}(N \log N)$ | $\mathcal{O}(N)$ | [C++](../solutions/0315-count-of-smaller-numbers-after-self/solution.cpp) |
| 327 | [Count of Range Sum](../solutions/0327-count-of-range-sum/README.md) | `Hard` | $\mathcal{O}(N \log N)$ | $\mathcal{O}(N)$ | [C++](../solutions/0327-count-of-range-sum/solution.cpp) |
| 363 | [Max Sum of Rectangle No Larger Than K](../solutions/0363-max-sum-of-rectangle-no-larger-than-k/README.md) | `Hard` | $\mathcal{O}(\min(m,n)^2 \cdot \max(m,n) \cdot \log(\max(m,n)))$ | $\mathcal{O}(\max(m,n))$ | [C++](../solutions/0363-max-sum-of-rectangle-no-larger-than-k/solution.cpp) |
| 410 | [Split Array Largest Sum](../solutions/0410-split-array-largest-sum/README.md) | `Hard` | $\mathcal{O}(N \log(\sum \text{nums}))$ | $\mathcal{O}(1)$ | [C++](../solutions/0410-split-array-largest-sum/solution.cpp) |
| 493 | [Reverse Pairs](../solutions/0493-reverse-pairs/README.md) | `Hard` | $\mathcal{O}(N \log N)$ | $\mathcal{O}(N)$ | [C++](../solutions/0493-reverse-pairs/solution.cpp) |
| 668 | [Kth Smallest Number in Multiplication Table](../solutions/0668-kth-smallest-number-in-multiplication-table/README.md) | `Hard` | $\mathcal{O}(\min(M, N) \cdot \log(M \cdot N))$ | $\mathcal{O}(1)$ | [C++](../solutions/0668-kth-smallest-number-in-multiplication-table/solution.cpp) |
| 719 | [Find K-th Smallest Pair Distance](../solutions/0719-find-k-th-smallest-pair-distance/README.md) | `Hard` | $\mathcal{O}(N \log N + N \log W)$ | $\mathcal{O}(1)$ | [C++](../solutions/0719-find-k-th-smallest-pair-distance/solution.cpp) |
| 3312 | [Sorted GCD Pair Queries](../solutions/3312-sorted-gcd-pair-queries/README.md) | `Hard` | $\mathcal{O}(N + M \log M + Q \log M)$ | $\mathcal{O}(M)$ | [C++](../solutions/3312-sorted-gcd-pair-queries/solution.cpp) |
| 3464 | [Maximize the Distance Between Points on a Square](../solutions/3464-maximize-the-distance-between-points-on-a-square/README.md) | `Hard` | $\mathcal{O}(N \log N \log(\text{side}))$ | $\mathcal{O}(N)$ | [C++](../solutions/3464-maximize-the-distance-between-points-on-a-square/solution.cpp) |
| 3501 | [Maximize Active Section with Trade II](../solutions/3501-maximize-active-section-with-trade-ii/README.md) | `Hard` | $\mathcal{O}(N \log N + Q \log N)$ | $\mathcal{O}(N \log N)$ | [C++](../solutions/3501-maximize-active-section-with-trade-ii/solution.cpp) |
| 3620 | [Network Recovery Pathways](../solutions/3620-network-recovery-pathways/README.md) | `Hard` | $\mathcal{O}((N + M) \log N \log M)$ | $\mathcal{O}(N + M)$ | [C++](../solutions/3620-network-recovery-pathways/solution.cpp) |
