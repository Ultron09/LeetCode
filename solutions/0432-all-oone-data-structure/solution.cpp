/**
 * Problem: 432. All O`one Data Structure
 * Difficulty: Hard
 * Topics: Hash Table, Linked List, Design, Doubly-Linked List
 * LeetCode Link: https://leetcode.com/problems/all-oone-data-structure/
 * 
 * Time Complexity:  O(1) average for all operations (inc, dec, getMaxKey, getMinKey)
 * Space Complexity: O(N) where N is the number of distinct keys stored
 */

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <cassert>

using namespace std;

class AllOne {
private:
    struct Bucket {
        int count;
        unordered_set<string> keys;
    };

    // Doubly linked list of frequency buckets maintained in strictly increasing order
    list<Bucket> buckets;
    // Maps each key to the iterator of its containing bucket in the doubly linked list
    unordered_map<string, list<Bucket>::iterator> keyToBucket;

public:
    AllOne() {
        // Default constructor
    }

    void inc(string key) {
        auto it = keyToBucket.find(key);

        if (it == keyToBucket.end()) {
            // Key not present: must insert into bucket with count 1
            if (buckets.empty() || buckets.front().count != 1) {
                buckets.push_front({1, {}});
            }
            buckets.front().keys.insert(key);
            keyToBucket[key] = buckets.begin();
        } else {
            // Key exists in bucket with count C: move to bucket with count C + 1
            auto currBucket = it->second;
            int nextCount = currBucket->count + 1;
            auto nextBucket = next(currBucket);

            if (nextBucket == buckets.end() || nextBucket->count != nextCount) {
                nextBucket = buckets.insert(nextBucket, {nextCount, {}});
            }

            nextBucket->keys.insert(key);
            keyToBucket[key] = nextBucket;

            currBucket->keys.erase(key);
            if (currBucket->keys.empty()) {
                buckets.erase(currBucket);
            }
        }
    }

    void dec(string key) {
        auto it = keyToBucket.find(key);
        if (it == keyToBucket.end()) return;

        auto currBucket = it->second;

        if (currBucket->count == 1) {
            // Decrement to 0: remove key completely
            currBucket->keys.erase(key);
            keyToBucket.erase(it);
            if (currBucket->keys.empty()) {
                buckets.erase(currBucket);
            }
        } else {
            // Decrement to C - 1: move to preceding bucket
            int prevCount = currBucket->count - 1;
            auto prevBucket = (currBucket == buckets.begin()) ? buckets.end() : prev(currBucket);

            if (prevBucket == buckets.end() || prevBucket->count != prevCount) {
                prevBucket = buckets.insert(currBucket, {prevCount, {}});
            }

            prevBucket->keys.insert(key);
            keyToBucket[key] = prevBucket;

            currBucket->keys.erase(key);
            if (currBucket->keys.empty()) {
                buckets.erase(currBucket);
            }
        }
    }

    string getMaxKey() {
        if (buckets.empty()) return "";
        return *(buckets.back().keys.begin());
    }

    string getMinKey() {
        if (buckets.empty()) return "";
        return *(buckets.front().keys.begin());
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    AllOne allOne;

    // Test Case 1: Standard Example
    allOne.inc("hello");
    allOne.inc("hello");
    assert(allOne.getMaxKey() == "hello");
    assert(allOne.getMinKey() == "hello");
    cout << "Step 1: getMaxKey='hello', getMinKey='hello' - PASSED" << endl;

    allOne.inc("leet");
    assert(allOne.getMaxKey() == "hello");
    assert(allOne.getMinKey() == "leet");
    cout << "Step 2: getMaxKey='hello', getMinKey='leet' - PASSED" << endl;

    // Test Case 2: Decrements
    allOne.dec("hello");
    allOne.dec("hello");
    assert(allOne.getMaxKey() == "leet");
    assert(allOne.getMinKey() == "leet");
    cout << "Step 3: after dec('hello') x2 -> getMaxKey='leet', getMinKey='leet' - PASSED" << endl;

    allOne.dec("leet");
    assert(allOne.getMaxKey() == "");
    assert(allOne.getMinKey() == "");
    cout << "Step 4: after dec('leet') -> empty -> getMaxKey='', getMinKey='' - PASSED" << endl;

    // Test Case 3: Multiple keys sharing frequency buckets
    allOne.inc("a");
    allOne.inc("b");
    allOne.inc("c");
    allOne.inc("a");
    assert(allOne.getMaxKey() == "a");
    string minKey = allOne.getMinKey();
    assert(minKey == "b" || minKey == "c");
    cout << "Step 5: Shared buckets - PASSED" << endl;

    cout << "\nAll test cases passed successfully!" << endl;
    return 0;
}
#endif
