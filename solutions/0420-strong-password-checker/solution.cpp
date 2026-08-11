/**
 * Problem: 420. Strong Password Checker
 * Difficulty: Hard
 * Topics: String, Greedy, Heap (Priority Queue)
 * LeetCode Link: https://leetcode.com/problems/strong-password-checker/
 * 
 * Time Complexity:  O(N) - Single linear pass to scan runs and O(N) greedy reduction passes
 * Space Complexity: O(N) - Storing repeating run lengths (at most N / 3 entries)
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <cassert>

using namespace std;

class Solution {
public:
    int strongPasswordChecker(string password) {
        int n = password.length();

        bool hasLower = false;
        bool hasUpper = false;
        bool hasDigit = false;

        for (char c : password) {
            if (islower(c)) hasLower = true;
            else if (isupper(c)) hasUpper = true;
            else if (isdigit(c)) hasDigit = true;
        }

        int missingTypes = (!hasLower) + (!hasUpper) + (!hasDigit);

        // Collect lengths of consecutive identical character runs >= 3
        vector<int> runs;
        for (int i = 0; i < n;) {
            int j = i;
            while (j < n && password[j] == password[i]) {
                j++;
            }
            int len = j - i;
            if (len >= 3) {
                runs.push_back(len);
            }
            i = j;
        }

        // Case 1: Length < 6 -> Inserts dominate
        if (n < 6) {
            return max(6 - n, missingTypes);
        }

        // Case 2: 6 <= Length <= 20 -> Replacements dominate
        if (n <= 20) {
            int replaceNeeded = 0;
            for (int len : runs) {
                replaceNeeded += len / 3;
            }
            return max(replaceNeeded, missingTypes);
        }

        // Case 3: Length > 20 -> Mandatory deletions must be greedily allocated
        int deletions = n - 20;

        // Priority 1: Runs where len % 3 == 0 (1 deletion saves 1 replacement)
        for (int& len : runs) {
            if (deletions >= 1 && len % 3 == 0) {
                len -= 1;
                deletions -= 1;
            }
        }

        // Priority 2: Runs where len % 3 == 1 (2 deletions save 1 replacement)
        for (int& len : runs) {
            if (deletions >= 2 && len % 3 == 1) {
                len -= 2;
                deletions -= 2;
            }
        }

        // Priority 3: Remaining deletions applied in chunks of 3 (3 deletions save 1 replacement)
        for (int& len : runs) {
            if (deletions > 0 && len >= 3) {
                int canReduce = min(len - 2, deletions);
                len -= canReduce;
                deletions -= canReduce;
            }
        }

        int remainingReplace = 0;
        for (int len : runs) {
            if (len >= 3) {
                remainingReplace += len / 3;
            }
        }

        return (n - 20) + max(remainingReplace, missingTypes);
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1: Single char (n = 1 < 6)
    {
        string s = "a";
        int result = solver.strongPasswordChecker(s);
        cout << "Test 1 - \"a\" -> Expected: 5, Got: " << result << endl;
        assert(result == 5);
    }

    // Test Case 2: Short strong characters (n = 3 < 6)
    {
        string s = "aA1";
        int result = solver.strongPasswordChecker(s);
        cout << "Test 2 - \"aA1\" -> Expected: 3, Got: " << result << endl;
        assert(result == 3);
    }

    // Test Case 3: Already strong password (n = 8)
    {
        string s = "1337C0d3";
        int result = solver.strongPasswordChecker(s);
        cout << "Test 3 - \"1337C0d3\" -> Expected: 0, Got: " << result << endl;
        assert(result == 0);
    }

    // Test Case 4: Long password with repeated dots (n = 21 > 20)
    {
        string s = "....................a";
        int result = solver.strongPasswordChecker(s);
        cout << "Test 4 - \"....................a\" -> Expected: 7, Got: " << result << endl;
        assert(result == 7);
    }

    // Test Case 5: Repeated characters within valid length (6 <= n <= 20)
    {
        string s = "aaa111";
        int result = solver.strongPasswordChecker(s);
        cout << "Test 5 - \"aaa111\" -> Expected: 2, Got: " << result << endl;
        assert(result == 2);
    }

    // Test Case 6: Mixed case requiring 1 replacement to fix repetition and missing type
    {
        string s = "aaa123";
        int result = solver.strongPasswordChecker(s);
        cout << "Test 6 - \"aaa123\" -> Expected: 1, Got: " << result << endl;
        assert(result == 1);
    }

    // Test Case 7: All identical digits (n = 10)
    {
        string s = "1111111111";
        int result = solver.strongPasswordChecker(s);
        cout << "Test 7 - \"1111111111\" -> Expected: 3, Got: " << result << endl;
        assert(result == 3);
    }

    // Test Case 8: Long repeating pattern with multi-character runs
    {
        string s = "bbaaaaaaaaaaaaaaacccccc";
        int result = solver.strongPasswordChecker(s);
        cout << "Test 8 - \"bbaaaaaaaaaaaaaaacccccc\" -> Expected: 8, Got: " << result << endl;
        assert(result == 8);
    }

    cout << "\nAll test cases passed successfully!" << endl;
    return 0;
}
#endif
