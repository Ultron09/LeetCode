/**
 * Problem: 1622. Fancy Sequence
 * Difficulty: Hard
 * Topics: Math, Design, Segment Tree / Number Theory
 * LeetCode Link: https://leetcode.com/problems/fancy-sequence/
 * 
 * Time Complexity:  O(log MOD) per append, O(1) for addAll, multAll, and getIndex
 * Space Complexity: O(N) where N is the number of appended elements (<= 10^5)
 */

#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

class Fancy {
private:
    static constexpr long long MOD = 1'000'000'007;
    vector<long long> arr;
    long long a; // global multiplication coefficient: f(x) = (a * x + b) % MOD
    long long b; // global addition coefficient

    // Modular exponentiation to compute (base^exp) % MOD
    long long power(long long base, long long exp) const {
        long long res = 1;
        base %= MOD;
        while (exp > 0) {
            if (exp & 1) res = (res * base) % MOD;
            base = (base * base) % MOD;
            exp >>= 1;
        }
        return res;
    }

    // Modular multiplicative inverse using Fermat's Little Theorem (MOD is prime)
    long long modInverse(long long n) const {
        return power(n, MOD - 2);
    }

public:
    Fancy() : a(1), b(0) {
        arr.reserve(100000);
    }
    
    void append(int val) {
        // We want: (a * x + b) = val (mod MOD)
        // => x = (val - b) * inv(a) (mod MOD)
        long long invA = modInverse(a);
        long long raw = (((val - b) % MOD + MOD) % MOD * invA) % MOD;
        arr.push_back(raw);
    }
    
    void addAll(int inc) {
        // f(x) -> (a * x + b) + inc = a * x + (b + inc)
        b = (b + inc) % MOD;
    }
    
    void multAll(int m) {
        // f(x) -> (a * x + b) * m = (a * m) * x + (b * m)
        a = (a * m) % MOD;
        b = (b * m) % MOD;
    }
    
    int getIndex(int idx) {
        if (idx >= static_cast<int>(arr.size())) {
            return -1;
        }
        return static_cast<int>((a * arr[idx] + b) % MOD);
    }
};

/**
 * Your Fancy object will be instantiated and called as such:
 * Fancy* obj = new Fancy();
 * obj->append(val);
 * obj->addAll(inc);
 * obj->multAll(m);
 * int param_4 = obj->getIndex(idx);
 */

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Fancy fancy;
    fancy.append(2);   // [2]
    fancy.addAll(3);   // [5]
    fancy.append(7);   // [5, 7]
    fancy.multAll(2);  // [10, 14]
    assert(fancy.getIndex(0) == 10);
    cout << "Test 1 Passed: getIndex(0) == 10" << endl;

    fancy.addAll(3);   // [13, 17]
    fancy.append(10);  // [13, 17, 10]
    fancy.multAll(2);  // [26, 34, 20]
    assert(fancy.getIndex(0) == 26);
    assert(fancy.getIndex(1) == 34);
    assert(fancy.getIndex(2) == 20);
    assert(fancy.getIndex(3) == -1);

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
