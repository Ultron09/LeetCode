/**
 * Problem: 972. Equal Rational Numbers
 * Difficulty: Hard
 * Topics: Math, String
 * LeetCode Link: https://leetcode.com/problems/equal-rational-numbers/
 * 
 * Time Complexity:  O(L) where L is the length of the string, which is bounded by a very small constant (max 16).
 * Space Complexity: O(1) auxiliary space.
 */

#include <iostream>
#include <string>
#include <numeric>
#include <cmath>
#include <cassert>

using namespace std;

class Solution {
private:
    struct Fraction {
        long long n, d;
        Fraction(long long n = 0, long long d = 1) : n(n), d(d) {
            long long g = std::gcd(n, d);
            this->n /= g;
            this->d /= g;
        }
        bool operator==(const Fraction& other) const {
            return n == other.n && d == other.d;
        }
    };

    long long pow10(int exp) {
        long long res = 1;
        while (exp--) res *= 10;
        return res;
    }

    Fraction parse(string s) {
        auto i = s.find('.');
        // If there's no decimal point, it's a pure integer
        if (i == string::npos) {
            return Fraction(stoll(s), 1);
        }
        
        long long intPart = stoll(s.substr(0, i));
        s = s.substr(i + 1);
        
        auto j = s.find('(');
        // If there's a decimal but no repeating part
        if (j == string::npos) {
            if (s.empty()) return Fraction(intPart, 1);
            long long nonRep = stoll(s);
            long long den = pow10(s.length());
            return Fraction(intPart * den + nonRep, den);
        }
        
        // Both non-repeating and repeating parts exist
        string nonRepStr = s.substr(0, j);
        string repStr = s.substr(j + 1, s.length() - j - 2);
        
        long long nonRep = nonRepStr.empty() ? 0 : stoll(nonRepStr);
        long long nonRepDen = pow10(nonRepStr.length());
        
        long long rep = stoll(repStr);
        long long repDen = (pow10(repStr.length()) - 1) * nonRepDen;
        
        Fraction f1(intPart * nonRepDen + nonRep, nonRepDen);
        Fraction f2(rep, repDen);
        
        long long lcm = std::lcm(f1.d, f2.d);
        long long num = f1.n * (lcm / f1.d) + f2.n * (lcm / f2.d);
        
        return Fraction(num, lcm);
    }

public:
    bool isRationalEqual(string s, string t) {
        return parse(s) == parse(t);
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1
    assert(solver.isRationalEqual("0.(52)", "0.5(25)") == true);
    cout << "Test 1 Passed!" << endl;

    // Test Case 2
    assert(solver.isRationalEqual("0.1666(6)", "0.166(66)") == true);
    cout << "Test 2 Passed!" << endl;

    // Test Case 3
    assert(solver.isRationalEqual("0.9(9)", "1.") == true);
    cout << "Test 3 Passed!" << endl;
    
    // Test Case 4
    assert(solver.isRationalEqual("123", "123.000(0)") == true);
    cout << "Test 4 Passed!" << endl;

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
