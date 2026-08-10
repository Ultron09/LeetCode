/**
 * Problem: 23. Merge k Sorted Lists
 * Difficulty: Hard
 * Topics: Linked List, Divide and Conquer, Heap (Priority Queue)
 * LeetCode Link: https://leetcode.com/problems/merge-k-sorted-lists/
 * 
 * Time Complexity:  O(N log K) where N is the total number of nodes, K is the number of linked lists
 * Space Complexity: O(K) for the priority queue min-heap
 */

#include <iostream>
#include <vector>
#include <queue>
#include <cassert>

using namespace std;

#ifdef LOCAL_TEST
// Definition for singly-linked list node (guarded for local testing)
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
#endif

class Solution {
private:
    struct Compare {
        bool operator()(const ListNode* a, const ListNode* b) const {
            return a->val > b->val; // Min-heap based on node values
        }
    };

public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        priority_queue<ListNode*, vector<ListNode*>, Compare> minHeap;

        // 1. Initialize heap with head of each non-empty list
        for (ListNode* head : lists) {
            if (head != nullptr) {
                minHeap.push(head);
            }
        }

        ListNode dummy(0);
        ListNode* tail = &dummy;

        // 2. Extract smallest node and push its successor
        while (!minHeap.empty()) {
            ListNode* node = minHeap.top();
            minHeap.pop();

            tail->next = node;
            tail = tail->next;

            if (node->next != nullptr) {
                minHeap.push(node->next);
            }
        }

        return dummy.next;
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
ListNode* createList(const vector<int>& values) {
    ListNode dummy(0);
    ListNode* curr = &dummy;
    for (int val : values) {
        curr->next = new ListNode(val);
        curr = curr->next;
    }
    return dummy.next;
}

vector<int> toVector(ListNode* head) {
    vector<int> res;
    while (head != nullptr) {
        res.push_back(head->val);
        head = head->next;
    }
    return res;
}

void freeList(ListNode* head) {
    while (head != nullptr) {
        ListNode* next = head->next;
        delete head;
        head = next;
    }
}

int main() {
    Solution solver;

    // Test Case 1: Standard multi-list merge
    {
        vector<ListNode*> lists = {
            createList({1, 4, 5}),
            createList({1, 3, 4}),
            createList({2, 6})
        };
        ListNode* merged = solver.mergeKLists(lists);
        vector<int> expected = {1, 1, 2, 3, 4, 4, 5, 6};
        assert(toVector(merged) == expected);
        cout << "Test 1 Passed: [1,1,2,3,4,4,5,6]" << endl;
        freeList(merged);
    }

    // Test Case 2: Empty list array
    {
        vector<ListNode*> lists = {};
        ListNode* merged = solver.mergeKLists(lists);
        assert(merged == nullptr);
        cout << "Test 2 Passed: empty array" << endl;
    }

    // Test Case 3: Array of empty lists
    {
        vector<ListNode*> lists = {nullptr};
        ListNode* merged = solver.mergeKLists(lists);
        assert(merged == nullptr);
        cout << "Test 3 Passed: [[]]" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
