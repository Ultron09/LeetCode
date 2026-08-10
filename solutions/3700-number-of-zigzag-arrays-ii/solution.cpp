/**
 * Problem: 3700. Number of ZigZag Arrays II
 * Difficulty: Hard
 * Topics: Dynamic Programming, Matrix Exponentiation, Combinatorics, Math
 * LeetCode Link: https://leetcode.com/problems/number-of-zigzag-arrays-ii/
 * 
 * Time Complexity:  O((2M)^3 * log N) where M = r - l + 1 <= 75, (2M <= 150)
 * Space Complexity: O((2M)^2) for transition matrices
 */

#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

class Solution {
private:
    static constexpr int MOD = 1'000'000'007;

    // Cache-friendly matrix multiplication with zero-skipping optimization
    vector<vector<long long>> multiply(const vector<vector<long long>>& A, const vector<vector<long long>>& B, int size) {
        vector<vector<long long>> C(size, vector<long long>(size, 0));
        for (int i = 0; i < size; ++i) {
            for (int k = 0; k < size; ++k) {
                if (A[i][k] == 0) continue;
                for (int j = 0; j < size; ++j) {
                    C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
                }
            }
        }
        return C;
    }

    // Binary matrix exponentiation: A^p
    vector<vector<long long>> power(vector<vector<long long>> A, long long p, int size) {
        vector<vector<long long>> res(size, vector<long long>(size, 0));
        for (int i = 0; i < size; ++i) {
            res[i][i] = 1; // Identity matrix
        }

        while (p > 0) {
            if (p & 1) {
                res = multiply(res, A, size);
            }
            A = multiply(A, A, size);
            p >>= 1;
        }
        return res;
    }

public:
    int zigZagArrays(int n, int l, int r) {
        int m = r - l + 1;
        if (m <= 1) return 0;

        int size = 2 * m;

        // State Encoding:
        // [0, m - 1]:     Up(v)   -> Last transition was increasing to value v
        // [m, 2*m - 1]:   Down(v) -> Last transition was decreasing to value v
        vector<vector<long long>> T(size, vector<long long>(size, 0));

        for (int v = 0; v < m; ++v) {
            // From Up(v), next step must be Down(w) with w < v
            for (int w = 0; w < v; ++w) {
                T[m + w][v] = 1;
            }
            // From Down(v), next step must be Up(w) with w > v
            for (int w = v + 1; w < m; ++w) {
                T[w][m + v] = 1;
            }
        }

        // Base Vector V_2 for length n = 2:
        // Up(v): number of preceding elements u < v is v
        // Down(v): number of preceding elements u > v is m - 1 - v
        vector<long long> V(size, 0);
        for (int v = 0; v < m; ++v) {
            V[v] = v;
            V[m + v] = m - 1 - v;
        }

        // Compute T^(n - 2) via Matrix Exponentiation
        vector<vector<long long>> Tn = power(T, n - 2, size);

        // Result vector V_n = T^(n - 2) * V_2
        long long totalArrays = 0;
        for (int i = 0; i < size; ++i) {
            long long stateCount = 0;
            for (int j = 0; j < size; ++j) {
                stateCount = (stateCount + Tn[i][j] * V[j]) % MOD;
            }
            totalArrays = (totalArrays + stateCount) % MOD;
        }

        return static_cast<int>(totalArrays);
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
        int n = 3, l = 4, r = 5;
        int expected = 2;
        assert(solver.zigZagArrays(n, l, r) == expected);
        cout << "Test 1 Passed!" << endl;
    }

    // Test Case 2: Example 2
    {
        int n = 3, l = 1, r = 3;
        int expected = 10;
        assert(solver.zigZagArrays(n, l, r) == expected);
        cout << "Test 2 Passed!" << endl;
    }

    // Test Case 3: Larger n
    {
        int n = 4, l = 1, r = 3;
        // Total valid zigzag arrays of length 4 for [1, 3]
        int res = solver.zigZagArrays(n, l, r);
        assert(res > 0);
        cout << "Test 3 Passed (Result = " << res << ")!" << endl;
    }

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
