/**
 * Problem: 895. Maximum Frequency Stack
 * Difficulty: Hard
 * Topics: Hash Table, Stack, Design
 * LeetCode Link: https://leetcode.com/problems/maximum-frequency-stack/
 * 
 * Time Complexity:  O(1) for both push and pop operations.
 * Space Complexity: O(N) where N is the number of elements pushed into the stack.
 */

#include <iostream>
#include <unordered_map>
#include <stack>
#include <cassert>

using namespace std;

class FreqStack {
private:
    unordered_map<int, int> freq;
    unordered_map<int, stack<int>> group;
    int maxFreq;

public:
    FreqStack() {
        maxFreq = 0;
    }
    
    void push(int val) {
        int f = freq[val] + 1;
        freq[val] = f;
        if (f > maxFreq) {
            maxFreq = f;
        }
        group[f].push(val);
    }
    
    int pop() {
        int x = group[maxFreq].top();
        group[maxFreq].pop();
        
        freq[x]--;
        if (group[maxFreq].empty()) {
            maxFreq--;
        }
        
        return x;
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    FreqStack freqStack;

    freqStack.push(5);
    freqStack.push(7);
    freqStack.push(5);
    freqStack.push(7);
    freqStack.push(4);
    freqStack.push(5);
    
    assert(freqStack.pop() == 5);
    assert(freqStack.pop() == 7);
    assert(freqStack.pop() == 5);
    assert(freqStack.pop() == 4);

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
