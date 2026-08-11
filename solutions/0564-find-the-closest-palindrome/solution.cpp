/**
 * Problem: 564. Find the Closest Palindrome
 * Difficulty: Hard
 * Topics: Math, String
 * LeetCode Link: https://leetcode.com/problems/find-the-closest-palindrome/
 * 
 * Time Complexity:  O(L) where L is the number of digits in n (L <= 18)
 * Space Complexity: O(L) to store candidates and string prefixes
 */

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <climits>
#include <cassert>

using namespace std;

class Solution {
public:
    string nearestPalindromic(string n) {
        int len = n.length();
        long long originalNum = stoll(n);

        vector<long long> candidates;

        // 1. Boundary candidate: 10^(len - 1) - 1 (e.g. 99...9)
        candidates.push_back(static_cast<long long>(pow(10, len - 1)) - 1);

        // 2. Boundary candidate: 10^len + 1 (e.g. 100...001)
        candidates.push_back(static_cast<long long>(pow(10, len)) + 1);

        // 3. Mirroring Prefix - 1, Prefix, Prefix + 1
        int prefixLen = (len + 1) / 2;
        long long prefixVal = stoll(n.substr(0, prefixLen));

        for (int diff = -1; diff <= 1; ++diff) {
            string prefixStr = to_string(prefixVal + diff);
            string palindromeStr = prefixStr;

            // Reflect the prefix to construct the candidate palindrome
            int suffixStart = (len % 2 == 0) ? prefixStr.length() - 1 : prefixStr.length() - 2;
            for (int j = suffixStart; j >= 0; --j) {
                palindromeStr += prefixStr[j];
            }

            candidates.push_back(stoll(palindromeStr));
        }

        // Find the candidate closest to originalNum (excluding itself)
        long long minDiff = LLONG_MAX;
        long long closestPalindrome = -1;

        for (long long cand : candidates) {
            if (cand == originalNum) continue;

            long long currDiff = abs(cand - originalNum);
            if (currDiff < minDiff || (currDiff == minDiff && cand < closestPalindrome)) {
                minDiff = currDiff;
                closestPalindrome = cand;
            }
        }

        return to_string(closestPalindrome);
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1: Standard Example 1
    {
        string n = "123";
        string result = solver.nearestPalindromic(n);
        cout << "Test 1 - n=\"123\" -> Expected: \"121\", Got: \"" << result << "\"" << endl;
        assert(result == "121");
    }

    // Test Case 2: Single digit
    {
        string n = "1";
        string result = solver.nearestPalindromic(n);
        cout << "Test 2 - n=\"1\" -> Expected: \"0\", Got: \"" << result << "\"" << endl;
        assert(result == "0");
    }

    // Test Case 3: Boundary power of 10
    {
        string n = "1000";
        string result = solver.nearestPalindromic(n);
        cout << "Test 3 - n=\"1000\" -> Expected: \"999\", Got: \"" << result << "\"" << endl;
        assert(result == "999");
    }

    // Test Case 4: Boundary all 9s
    {
        string n = "99";
        string result = solver.nearestPalindromic(n);
        cout << "Test 4 - n=\"99\" -> Expected: \"101\", Got: \"" << result << "\"" << endl;
        assert(result == "101");
    }

    // Test Case 5: Large 18-digit number
    {
        string n = "807045053224792883";
        string result = solver.nearestPalindromic(n);
        cout << "Test 5 - n=\"807045053224792883\" -> Expected: \"807045053350540708\", Got: \"" << result << "\"" << endl;
        assert(result == "807045053350540708");
    }

    cout << "\nAll test cases passed successfully!" << endl;
    return 0;
}
#endif
