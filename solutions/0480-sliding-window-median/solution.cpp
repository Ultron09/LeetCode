/**
 * Problem: 480. Sliding Window Median
 * Difficulty: Hard
 * Topics: Array, Sliding Window, Heap (Priority Queue), Two Pointers
 * LeetCode Link: https://leetcode.com/problems/sliding-window-median/
 * 
 * Time Complexity:  O(N log k) - Each insertion and lazy deletion takes logarithmic heap time
 * Space Complexity: O(N) worst case (O(k) typical) - Auxiliary storage for dual heaps and delayed hash map
 */

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <cmath>
#include <cassert>

using namespace std;

class DualHeap {
private:
    priority_queue<long long> small;                                       // Max-heap: holds smaller half
    priority_queue<long long, vector<long long>, greater<long long>> large; // Min-heap: holds larger half
    unordered_map<long long, int> delayed;                                  // Tracks pending lazy deletions
    int k;
    int smallSize;
    int largeSize;

    // Prune invalid elements from the top of the given heap
    template <typename T>
    void prune(T& heap) {
        while (!heap.empty()) {
            long long num = heap.top();
            if (delayed.count(num)) {
                delayed[num]--;
                if (delayed[num] == 0) {
                    delayed.erase(num);
                }
                heap.pop();
            } else {
                break;
            }
        }
    }

    // Maintain size invariant: smallSize == (k + 1) / 2, largeSize == k / 2
    void makeBalance() {
        if (smallSize > largeSize + 1) {
            large.push(small.top());
            small.pop();
            smallSize--;
            largeSize++;
            prune(small);
        } else if (smallSize < largeSize) {
            small.push(large.top());
            large.pop();
            smallSize++;
            largeSize--;
            prune(large);
        }
    }

public:
    DualHeap(int k) : k(k), smallSize(0), largeSize(0) {}

    void insert(long long num) {
        if (small.empty() || num <= small.top()) {
            small.push(num);
            smallSize++;
        } else {
            large.push(num);
            largeSize++;
        }
        makeBalance();
    }

    void erase(long long num) {
        delayed[num]++;
        if (num <= small.top()) {
            smallSize--;
            if (num == small.top()) {
                prune(small);
            }
        } else {
            largeSize--;
            if (!large.empty() && num == large.top()) {
                prune(large);
            }
        }
        makeBalance();
    }

    double getMedian() {
        if (k % 2 == 1) {
            return static_cast<double>(small.top());
        } else {
            return (static_cast<double>(small.top()) + static_cast<double>(large.top())) / 2.0;
        }
    }
};

class Solution {
public:
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {
        DualHeap dh(k);
        for (int i = 0; i < k; ++i) {
            dh.insert(nums[i]);
        }

        vector<double> medians;
        medians.push_back(dh.getMedian());

        for (int i = k; i < (int)nums.size(); ++i) {
            dh.insert(nums[i]);
            dh.erase(nums[i - k]);
            medians.push_back(dh.getMedian());
        }

        return medians;
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Helper for floating point comparison
    auto match = [](const vector<double>& a, const vector<double>& b) {
        if (a.size() != b.size()) return false;
        for (size_t i = 0; i < a.size(); ++i) {
            if (abs(a[i] - b[i]) > 1e-5) return false;
        }
        return true;
    };

    // Test Case 1: Standard Odd Window Size
    {
        vector<int> nums = {1, 3, -1, -3, 5, 3, 6, 7};
        int k = 3;
        vector<double> expected = {1.00000, -1.00000, -1.00000, 3.00000, 5.00000, 6.00000};
        auto result = solver.medianSlidingWindow(nums, k);
        cout << "Test 1 Passed: " << match(result, expected) << endl;
        assert(match(result, expected));
    }

    // Test Case 2: Repeating Values
    {
        vector<int> nums = {1, 2, 3, 4, 2, 3, 1, 4, 2};
        int k = 3;
        vector<double> expected = {2.00000, 3.00000, 3.00000, 3.00000, 2.00000, 3.00000, 2.00000};
        auto result = solver.medianSlidingWindow(nums, k);
        cout << "Test 2 Passed: " << match(result, expected) << endl;
        assert(match(result, expected));
    }

    // Test Case 3: Even Window Size with Potential 32-bit Integer Overflow
    {
        vector<int> nums = {2147483647, 2147483647};
        int k = 2;
        vector<double> expected = {2147483647.00000};
        auto result = solver.medianSlidingWindow(nums, k);
        cout << "Test 3 Passed: " << match(result, expected) << endl;
        assert(match(result, expected));
    }

    cout << "\nAll test cases passed successfully!" << endl;
    return 0;
}
#endif
