/**
 * Problem: 770. Basic Calculator IV
 * Difficulty: Hard
 * Topics: Stack & Queue, Math, String
 * LeetCode Link: https://leetcode.com/problems/basic-calculator-iv/
 *
 * Approach: Recursive Descent Parser & Polynomial Algebra
 *
 * Key Insight:
 *   The problem asks us to evaluate an expression with variables and return the 
 *   simplified polynomial. The operations are +, -, *.
 *   We can represent a polynomial as a hash map from a term (represented as a 
 *   sorted list of strings) to its integer coefficient.
 *   
 *   1. Polynomial representation: `map<vector<string>, int>`. We use a vector of 
 *      strings because a term can have multiple variables, e.g., "a*a*b".
 *      We keep the vector sorted to easily combine like terms.
 *   2. Operations:
 *      - Addition: Combine the maps.
 *      - Subtraction: Negate the second map and combine.
 *      - Multiplication: Cartesian product of terms. Add their vectors (and sort), 
 *        multiply coefficients.
 *   3. Parsing: A standard recursive descent parser or shunting yard algorithm.
 *      Expression grammar:
 *      Expr   -> Term (('+' | '-') Term)*
 *      Term   -> Factor ('*' Factor)*
 *      Factor -> '(' Expr ')' | Variable | Integer
 *
 * Time Complexity:  O(2^N) in the worst-case for polynomial expansion (e.g., (a+b)*(c+d)...)
 * Space Complexity: O(2^N) to store the expanded polynomial terms.
 */

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <cassert>
#include <cctype>

using namespace std;

class Poly {
public:
    // Represents a polynomial: Term (sorted vars) -> Coefficient
    map<vector<string>, int> terms;

    Poly() {}

    Poly(int val) {
        if (val != 0) {
            terms[{}] = val;
        }
    }

    Poly(string var) {
        terms[{var}] = 1;
    }

    Poly add(const Poly& other) const {
        Poly res = *this;
        for (const auto& [term, coef] : other.terms) {
            res.terms[term] += coef;
            if (res.terms[term] == 0) {
                res.terms.erase(term);
            }
        }
        return res;
    }

    Poly sub(const Poly& other) const {
        Poly res = *this;
        for (const auto& [term, coef] : other.terms) {
            res.terms[term] -= coef;
            if (res.terms[term] == 0) {
                res.terms.erase(term);
            }
        }
        return res;
    }

    Poly mul(const Poly& other) const {
        Poly res;
        for (const auto& [t1, c1] : terms) {
            for (const auto& [t2, c2] : other.terms) {
                vector<string> combined = t1;
                combined.insert(combined.end(), t2.begin(), t2.end());
                sort(combined.begin(), combined.end());
                res.terms[combined] += c1 * c2;
                if (res.terms[combined] == 0) {
                    res.terms.erase(combined);
                }
            }
        }
        return res;
    }

    vector<string> format() const {
        // Sort terms by degree (descending), then lexicographically
        vector<pair<vector<string>, int>> sorted_terms(terms.begin(), terms.end());
        sort(sorted_terms.begin(), sorted_terms.end(), [](const pair<vector<string>, int>& a, const pair<vector<string>, int>& b) {
            if (a.first.size() != b.first.size()) {
                return a.first.size() > b.first.size();
            }
            return a.first < b.first;
        });

        vector<string> res;
        for (const auto& [term, coef] : sorted_terms) {
            if (coef == 0) continue;
            string s = to_string(coef);
            for (const string& var : term) {
                s += "*" + var;
            }
            res.push_back(s);
        }
        return res;
    }
};

class Solution {
    unordered_map<string, int> evalMap;

    Poly parseExpr(const string& s, int& i) {
        Poly res = parseTerm(s, i);
        while (i < s.length() && (s[i] == '+' || s[i] == '-')) {
            char op = s[i];
            i++; // skip op
            Poly nextTerm = parseTerm(s, i);
            if (op == '+') res = res.add(nextTerm);
            else res = res.sub(nextTerm);
        }
        return res;
    }

    Poly parseTerm(const string& s, int& i) {
        Poly res = parseFactor(s, i);
        while (i < s.length() && s[i] == '*') {
            i++; // skip '*'
            Poly nextFactor = parseFactor(s, i);
            res = res.mul(nextFactor);
        }
        return res;
    }

    Poly parseFactor(const string& s, int& i) {
        if (s[i] == '(') {
            i++; // skip '('
            Poly res = parseExpr(s, i);
            i++; // skip ')'
            return res;
        }

        string token;
        while (i < s.length() && isalnum(s[i])) {
            token += s[i];
            i++;
        }

        if (isdigit(token[0])) {
            return Poly(stoi(token));
        } else {
            if (evalMap.count(token)) {
                return Poly(evalMap[token]);
            }
            return Poly(token);
        }
    }

public:
    vector<string> basicCalculatorIV(string expression, vector<string>& evalvars, vector<int>& evalints) {
        for (int i = 0; i < evalvars.size(); ++i) {
            evalMap[evalvars[i]] = evalints[i];
        }

        // Clean spaces from expression to simplify parsing
        string cleanExpr;
        for (char c : expression) {
            if (c != ' ') cleanExpr += c;
        }

        int idx = 0;
        Poly result = parseExpr(cleanExpr, idx);
        return result.format();
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1
    {
        string expr = "e + 8 - a + 5";
        vector<string> vars = {"e"};
        vector<int> ints = {1};
        vector<string> expected = {"-1*a", "14"};
        auto res = solver.basicCalculatorIV(expr, vars, ints);
        assert(res == expected);
        cout << "Test 1 Passed!" << endl;
    }

    // Test Case 2
    {
        string expr = "e - 8 + temperature - pressure";
        vector<string> vars = {"e", "temperature"};
        vector<int> ints = {1, 12};
        vector<string> expected = {"-1*pressure", "5"};
        auto res = solver.basicCalculatorIV(expr, vars, ints);
        assert(res == expected);
        cout << "Test 2 Passed!" << endl;
    }

    // Test Case 3
    {
        string expr = "(e + 8) * (e - 8)";
        vector<string> vars = {};
        vector<int> ints = {};
        vector<string> expected = {"1*e*e", "-64"};
        auto res = solver.basicCalculatorIV(expr, vars, ints);
        assert(res == expected);
        cout << "Test 3 Passed!" << endl;
    }

    cout << "\nAll test cases passed successfully!" << endl;
    return 0;
}
#endif
