/**
 * Problem: 295. Find Median from Data Stream
 * Difficulty: Hard
 * Topics: Two Pointers, Design, Sorting, Heap (Priority Queue), Data Stream
 * LeetCode Link: https://leetcode.com/problems/find-median-from-data-stream/
 * 
 * Time Complexity:
 *   - addNum():    O(log N) - priority queue push/pop
 *   - findMedian(): O(1) - top elements access
 * Space Complexity: O(N) to store stream elements across both heaps
 */

#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <cassert>

using namespace std;

class MedianFinder {
private:
    priority_queue<int> maxHeap;                             // Lower half of numbers (max at top)
    priority_queue<int, vector<int>, greater<int>> minHeap;  // Upper half of numbers (min at top)

public:
    MedianFinder() {}

    void addNum(int num) {
        // Step 1: Add to maxHeap
        maxHeap.push(num);

        // Step 2: Enforce ordering invariant (all elements in maxHeap <= minHeap)
        minHeap.push(maxHeap.top());
        maxHeap.pop();

        // Step 3: Enforce size invariant (maxHeap size is either equal to minHeap or 1 greater)
        if (minHeap.size() > maxHeap.size()) {
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }
    }

    double findMedian() {
        if (maxHeap.size() > minHeap.size()) {
            return static_cast<double>(maxHeap.top());
        }
        return (static_cast<double>(maxHeap.top()) + minHeap.top()) / 2.0;
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    // Test Case 1: Example 1
    {
        MedianFinder mf;
        mf.addNum(1);
        mf.addNum(2);
        assert(fabs(mf.findMedian() - 1.5) < 1e-5);
        mf.addNum(3);
        assert(fabs(mf.findMedian() - 2.0) < 1e-5);
        cout << "Test 1 Passed: Standard stream [1, 2, 3]" << endl;
    }

    // Test Case 2: Negative Numbers
    {
        MedianFinder mf;
        mf.addNum(-1);
        assert(fabs(mf.findMedian() - (-1.0)) < 1e-5);
        mf.addNum(-2);
        assert(fabs(mf.findMedian() - (-1.5)) < 1e-5);
        mf.addNum(-3);
        assert(fabs(mf.findMedian() - (-2.0)) < 1e-5);
        mf.addNum(-4);
        assert(fabs(mf.findMedian() - (-2.5)) < 1e-5);
        mf.addNum(-5);
        assert(fabs(mf.findMedian() - (-3.0)) < 1e-5);
        cout << "Test 2 Passed: Negative numbers stream [-1, -2, -3, -4, -5]" << endl;
    }

    // Test Case 3: Duplicates
    {
        MedianFinder mf;
        mf.addNum(5);
        mf.addNum(5);
        mf.addNum(5);
        assert(fabs(mf.findMedian() - 5.0) < 1e-5);
        cout << "Test 3 Passed: Duplicates handled correctly" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
