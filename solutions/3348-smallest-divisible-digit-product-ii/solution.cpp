/**
 * Problem: 3348. Smallest Divisible Digit Product II
 * Difficulty: Hard
 * Topics: Greedy, Dynamic Programming, Math, String
 * LeetCode Link: https://leetcode.com/problems/smallest-divisible-digit-product-ii/
 * 
 * Time Complexity:  O(N + max(a, b) * max(c, d)) where N = num.length() and prime powers <= 50.
 * Space Complexity: O(N) for prefix powers and resulting string.
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution {
private:
    static constexpr int MAX_A = 60;
    static constexpr int MAX_B = 40;
    int dp[MAX_A + 1][MAX_B + 1];
    bool dp_initialized = false;

    void initDP() {
        if (dp_initialized) return;
        
        for (int i = 0; i <= MAX_A; ++i) {
            for (int j = 0; j <= MAX_B; ++j) {
                dp[i][j] = 1e9;
            }
        }
        dp[0][0] = 0;

        for (int i = 0; i <= MAX_A; ++i) {
            for (int j = 0; j <= MAX_B; ++j) {
                if (i == 0 && j == 0) continue;
                // Digit 2: (1, 0)
                dp[i][j] = min(dp[i][j], 1 + dp[max(0, i - 1)][j]);
                // Digit 3: (0, 1)
                dp[i][j] = min(dp[i][j], 1 + dp[i][max(0, j - 1)]);
                // Digit 4: (2, 0)
                dp[i][j] = min(dp[i][j], 1 + dp[max(0, i - 2)][j]);
                // Digit 6: (1, 1)
                dp[i][j] = min(dp[i][j], 1 + dp[max(0, i - 1)][max(0, j - 1)]);
                // Digit 8: (3, 0)
                dp[i][j] = min(dp[i][j], 1 + dp[max(0, i - 3)][j]);
                // Digit 9: (0, 2)
                dp[i][j] = min(dp[i][j], 1 + dp[i][max(0, j - 2)]);
            }
        }
        dp_initialized = true;
    }

    int minDigits(int a, int b, int c, int d) {
        a = max(0, a);
        b = max(0, b);
        c = max(0, c);
        d = max(0, d);
        if (a > MAX_A || b > MAX_B) return 1e9;
        return dp[a][b] + c + d;
    }

    void getDigitPowers(int digit, int& da, int& db, int& dc, int& dd) {
        da = db = dc = dd = 0;
        if (digit == 2) da = 1;
        else if (digit == 3) db = 1;
        else if (digit == 4) da = 2;
        else if (digit == 5) dc = 1;
        else if (digit == 6) { da = 1; db = 1; }
        else if (digit == 7) dd = 1;
        else if (digit == 8) da = 3;
        else if (digit == 9) db = 2;
    }

    string buildSuffix(int a, int b, int c, int d, int len) {
        string res = "";
        int min_len = minDigits(a, b, c, d);
        if (len > min_len) {
            res.append(len - min_len, '1');
            len = min_len;
        }

        while (len > 0) {
            for (int digit = 1; digit <= 9; ++digit) {
                int da, db, dc, dd;
                getDigitPowers(digit, da, db, dc, dd);

                int na = max(0, a - da);
                int nb = max(0, b - db);
                int nc = max(0, c - dc);
                int nd = max(0, d - dd);

                if (minDigits(na, nb, nc, nd) <= len - 1) {
                    res.push_back('0' + digit);
                    a = na;
                    b = nb;
                    c = nc;
                    d = nd;
                    len--;
                    break;
                }
            }
        }
        return res;
    }

public:
    string smallestNumber(string num, long long t) {
        initDP();

        // 1. Factorize t into prime powers of 2, 3, 5, 7
        int req_a = 0, req_b = 0, req_c = 0, req_d = 0;
        while (t % 2 == 0) { req_a++; t /= 2; }
        while (t % 3 == 0) { req_b++; t /= 3; }
        while (t % 5 == 0) { req_c++; t /= 5; }
        while (t % 7 == 0) { req_d++; t /= 7; }

        // If t contains prime factors > 7, no zero-free digit product can be divisible by t
        if (t > 1) return "-1";

        int n = num.size();

        // 2. Find first zero in num
        int first_zero = n;
        for (int i = 0; i < n; ++i) {
            if (num[i] == '0') {
                first_zero = i;
                break;
            }
        }

        // 3. Compute prefix prime power counts for num (up to first_zero)
        vector<int> pref_a(first_zero + 1, 0);
        vector<int> pref_b(first_zero + 1, 0);
        vector<int> pref_c(first_zero + 1, 0);
        vector<int> pref_d(first_zero + 1, 0);

        for (int i = 0; i < first_zero; ++i) {
            int d = num[i] - '0';
            int da, db, dc, dd;
            getDigitPowers(d, da, db, dc, dd);
            pref_a[i + 1] = pref_a[i] + da;
            pref_b[i + 1] = pref_b[i] + db;
            pref_c[i + 1] = pref_c[i] + dc;
            pref_d[i + 1] = pref_d[i] + dd;
        }

        // 4. Check if num itself is valid (zero-free and divisible)
        if (first_zero == n) {
            if (pref_a[n] >= req_a && pref_b[n] >= req_b && 
                pref_c[n] >= req_c && pref_d[n] >= req_d) {
                return num;
            }
        }

        // 5. Try to match prefix of length i (from first_zero down to 0)
        for (int i = first_zero; i >= 0; --i) {
            int start_digit = 1;
            if (i < n) {
                if (num[i] == '0') {
                    start_digit = 1;
                } else {
                    start_digit = (num[i] - '0') + 1;
                }
            }

            int cur_a = pref_a[i];
            int cur_b = pref_b[i];
            int cur_c = pref_c[i];
            int cur_d = pref_d[i];

            for (int D = start_digit; D <= 9; ++D) {
                int da, db, dc, dd;
                getDigitPowers(D, da, db, dc, dd);

                int rem_a = max(0, req_a - (cur_a + da));
                int rem_b = max(0, req_b - (cur_b + db));
                int rem_c = max(0, req_c - (cur_c + dc));
                int rem_d = max(0, req_d - (cur_d + dd));

                int rem_len = n - 1 - i;
                if (minDigits(rem_a, rem_b, rem_c, rem_d) <= rem_len) {
                    string ans = num.substr(0, i);
                    ans.push_back('0' + D);
                    ans += buildSuffix(rem_a, rem_b, rem_c, rem_d, rem_len);
                    return ans;
                }
            }
        }

        // 6. If no number of length n exists, construct smallest number of length > n
        int ans_len = max(n + 1, minDigits(req_a, req_b, req_c, req_d));
        return buildSuffix(req_a, req_b, req_c, req_d, ans_len);
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1: Example 1
    {
        string num = "1234";
        long long t = 256;
        string expected = "1488";
        string result = solver.smallestNumber(num, t);
        assert(result == expected);
        cout << "Test 1 Passed! Result: " << result << endl;
    }

    // Test Case 2: Example 2
    {
        string num = "12355";
        long long t = 50;
        string expected = "12355";
        string result = solver.smallestNumber(num, t);
        assert(result == expected);
        cout << "Test 2 Passed! Result: " << result << endl;
    }

    // Test Case 3: Example 3 (Prime factor > 7 -> impossible)
    {
        string num = "11111";
        long long t = 26;
        string expected = "-1";
        string result = solver.smallestNumber(num, t);
        assert(result == expected);
        cout << "Test 3 Passed! Result: " << result << endl;
    }

    // Test Case 4: Zero in num
    {
        string num = "102";
        long long t = 1;
        string expected = "111";
        string result = solver.smallestNumber(num, t);
        assert(result == expected);
        cout << "Test 4 Passed! Result: " << result << endl;
    }

    // Test Case 5: Length expansion
    {
        string num = "999";
        long long t = 256;
        string expected = "1488";
        string result = solver.smallestNumber(num, t);
        assert(result == expected);
        cout << "Test 5 Passed! Result: " << result << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
