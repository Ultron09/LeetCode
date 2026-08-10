/**
 * Problem: 25. Reverse Nodes in k-Group
 * Difficulty: Hard
 * Topics: Linked List, Recursion
 * LeetCode Link: https://leetcode.com/problems/reverse-nodes-in-k-group/
 * 
 * Time Complexity:  O(N) where N is the total number of nodes in the linked list
 * Space Complexity: O(1) auxiliary space (in-place pointer manipulation)
 */

#include <iostream>
#include <vector>
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
    ListNode* getKth(ListNode* curr, int k) {
        while (curr != nullptr && k > 0) {
            curr = curr->next;
            k--;
        }
        return curr;
    }

public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if (head == nullptr || k <= 1) return head;

        ListNode dummy(0);
        dummy.next = head;
        ListNode* groupPrev = &dummy;

        while (true) {
            // 1. Locate the k-th node of the current group
            ListNode* kth = getKth(groupPrev, k);
            if (kth == nullptr) {
                // Fewer than k nodes remain; leave as-is
                break;
            }
            ListNode* groupNext = kth->next;

            // 2. Reverse nodes in the current k-group
            ListNode* prev = groupNext;
            ListNode* curr = groupPrev->next;
            while (curr != groupNext) {
                ListNode* nextTemp = curr->next;
                curr->next = prev;
                prev = curr;
                curr = nextTemp;
            }

            // 3. Reconnect the previous group's tail to the new group head (kth)
            ListNode* newGroupEnd = groupPrev->next;
            groupPrev->next = kth;
            groupPrev = newGroupEnd;
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

    // Test Case 1: [1,2,3,4,5], k = 2 -> [2,1,4,3,5]
    {
        ListNode* head = createList({1, 2, 3, 4, 5});
        ListNode* res = solver.reverseKGroup(head, 2);
        vector<int> expected = {2, 1, 4, 3, 5};
        assert(toVector(res) == expected);
        cout << "Test 1 Passed: [2,1,4,3,5]" << endl;
        freeList(res);
    }

    // Test Case 2: [1,2,3,4,5], k = 3 -> [3,2,1,4,5]
    {
        ListNode* head = createList({1, 2, 3, 4, 5});
        ListNode* res = solver.reverseKGroup(head, 3);
        vector<int> expected = {3, 2, 1, 4, 5};
        assert(toVector(res) == expected);
        cout << "Test 2 Passed: [3,2,1,4,5]" << endl;
        freeList(res);
    }

    // Test Case 3: Single element, k = 1
    {
        ListNode* head = createList({1});
        ListNode* res = solver.reverseKGroup(head, 1);
        vector<int> expected = {1};
        assert(toVector(res) == expected);
        cout << "Test 3 Passed: [1]" << endl;
        freeList(res);
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
