/**
 * Problem: 460. LFU Cache
 * Difficulty: Hard
 * Topics: Hash Table, Linked List, Design, Doubly-Linked List
 * LeetCode Link: https://leetcode.com/problems/lfu-cache/
 * 
 * Time Complexity:  O(1) average for both get() and put()
 * Space Complexity: O(capacity) - Hash maps and doubly linked lists storing cache items
 */

#include <iostream>
#include <unordered_map>
#include <list>
#include <cassert>

using namespace std;

class LFUCache {
private:
    int capacity;
    int minFreq;

    // Maps key -> {value, frequency}
    unordered_map<int, pair<int, int>> keyToValFreq;

    // Maps frequency -> Doubly-linked list of keys with that frequency
    // Most recently used keys with this frequency are at front(); LRU is at back()
    unordered_map<int, list<int>> freqToList;

    // Maps key -> iterator to its position in freqToList[freq]
    unordered_map<int, list<int>::iterator> keyToIter;

    /**
     * Increments the frequency of a key by 1 and moves it to the front
     * of the corresponding frequency list.
     */
    void touch(int key) {
        int freq = keyToValFreq[key].second;
        
        // Remove key from its current frequency list
        freqToList[freq].erase(keyToIter[key]);
        if (freqToList[freq].empty()) {
            freqToList.erase(freq);
            // If the deleted frequency was minFreq, advance minFreq
            if (minFreq == freq) {
                minFreq++;
            }
        }

        // Increment frequency and place at the front of the new frequency list
        int newFreq = freq + 1;
        keyToValFreq[key].second = newFreq;
        freqToList[newFreq].push_front(key);
        keyToIter[key] = freqToList[newFreq].begin();
    }

public:
    LFUCache(int capacity) : capacity(capacity), minFreq(0) {}

    int get(int key) {
        auto it = keyToValFreq.find(key);
        if (it == keyToValFreq.end()) {
            return -1;
        }

        touch(key);
        return it->second.first;
    }

    void put(int key, int value) {
        if (capacity <= 0) return;

        auto it = keyToValFreq.find(key);
        if (it != keyToValFreq.end()) {
            it->second.first = value;
            touch(key);
            return;
        }

        // If at full capacity, evict the least recently used key among those with minFreq
        if (static_cast<int>(keyToValFreq.size()) >= capacity) {
            int evictKey = freqToList[minFreq].back();
            freqToList[minFreq].pop_back();
            if (freqToList[minFreq].empty()) {
                freqToList.erase(minFreq);
            }
            keyToIter.erase(evictKey);
            keyToValFreq.erase(evictKey);
        }

        // Insert new element with frequency 1
        keyToValFreq[key] = {value, 1};
        freqToList[1].push_front(key);
        keyToIter[key] = freqToList[1].begin();
        minFreq = 1;
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    LFUCache lfu(2);

    // Test Case 1: Standard example sequence
    lfu.put(1, 1);
    lfu.put(2, 2);
    assert(lfu.get(1) == 1);
    cout << "get(1) -> 1 - PASSED" << endl;

    lfu.put(3, 3); // Evicts key 2 (cnt=1)
    assert(lfu.get(2) == -1);
    assert(lfu.get(3) == 3);
    cout << "get(2) -> -1, get(3) -> 3 - PASSED" << endl;

    lfu.put(4, 4); // Both 1 and 3 have cnt=2, evicts LRU key 1
    assert(lfu.get(1) == -1);
    assert(lfu.get(3) == 3);
    assert(lfu.get(4) == 4);
    cout << "get(1) -> -1, get(3) -> 3, get(4) -> 4 - PASSED" << endl;

    // Test Case 2: Capacity 1 cache
    {
        LFUCache lfu1(1);
        lfu1.put(2, 1);
        assert(lfu1.get(2) == 1);
        lfu1.put(3, 2);
        assert(lfu1.get(2) == -1);
        assert(lfu1.get(3) == 2);
        cout << "Capacity 1 tests - PASSED" << endl;
    }

    cout << "\nAll test cases passed successfully!" << endl;
    return 0;
}
#endif
