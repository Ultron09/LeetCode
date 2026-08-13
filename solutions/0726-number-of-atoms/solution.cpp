/**
 * Problem: 726. Number of Atoms
 * Difficulty: Hard
 * Topics: Stack, Hash Table, String, Sorting
 * LeetCode Link: https://leetcode.com/problems/number-of-atoms/
 *
 * Approach: Stack of Hash Maps — Recursive Grammar Flattening
 *
 * Key Insight:
 *   The formula is a recursively nested grammar:
 *     Formula  ::= (Group | Atom)+
 *     Group    ::= '(' Formula ')' [Number]
 *     Atom     ::= UpperCase LowerCase* [Number]
 *     Number   ::= Digit+
 *
 *   We maintain a stack of maps. The stack top is the "current scope."
 *   - On '(':  Push a new empty map (enter a new scope).
 *   - On ')':  Pop the top map, parse the multiplier, and merge all
 *              counts (multiplied) into the new top map.
 *   - On Atom: Parse the element name + count, add to the top map.
 *
 *   At the end, the single remaining map contains all atom counts.
 *   Sort by key and format the output string.
 *
 * Time Complexity:  O(N + K log K) — N = formula length, K = unique atoms
 * Space Complexity: O(N) — stack depth + map storage
 */

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <stack>
#include <cassert>

using namespace std;

class Solution {
public:
    string countOfAtoms(string formula) {
        int n = static_cast<int>(formula.size());
        int i = 0;

        // Stack of ordered maps: each map represents a nesting scope
        stack<map<string, int>> stk;
        stk.push({});

        while (i < n) {
            if (formula[i] == '(') {
                // Open new scope
                stk.push({});
                ++i;
            } else if (formula[i] == ')') {
                // Close scope: pop, multiply, and merge into parent
                ++i;
                int count = parseNumber(formula, i);

                map<string, int> top = stk.top();
                stk.pop();

                for (auto& [atom, cnt] : top) {
                    stk.top()[atom] += cnt * count;
                }
            } else {
                // Parse atom name: starts with uppercase, followed by lowercase
                string atom = parseAtom(formula, i);
                int count = parseNumber(formula, i);
                stk.top()[atom] += count;
            }
        }

        // Build result string from sorted map
        string result;
        for (auto& [atom, cnt] : stk.top()) {
            result += atom;
            if (cnt > 1) {
                result += to_string(cnt);
            }
        }

        return result;
    }

private:
    // Parse an element name: one uppercase followed by zero or more lowercase
    string parseAtom(const string& s, int& i) {
        string atom;
        atom += s[i++]; // First uppercase character
        while (i < static_cast<int>(s.size()) && islower(s[i])) {
            atom += s[i++];
        }
        return atom;
    }

    // Parse a number: one or more digits. Returns 1 if no digits present.
    int parseNumber(const string& s, int& i) {
        if (i >= static_cast<int>(s.size()) || !isdigit(s[i])) {
            return 1; // Implicit count of 1
        }
        int num = 0;
        while (i < static_cast<int>(s.size()) && isdigit(s[i])) {
            num = num * 10 + (s[i] - '0');
            ++i;
        }
        return num;
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1: Simple formula
    {
        string formula = "H2O";
        string result = solver.countOfAtoms(formula);
        assert(result == "H2O");
        cout << "Test 1 Passed! H2O → " << result << endl;
    }

    // Test Case 2: Parentheses with multiplier
    {
        string formula = "Mg(OH)2";
        string result = solver.countOfAtoms(formula);
        assert(result == "H2MgO2");
        cout << "Test 2 Passed! Mg(OH)2 → " << result << endl;
    }

    // Test Case 3: Nested parentheses
    {
        string formula = "K4(ON(SO3)2)2";
        string result = solver.countOfAtoms(formula);
        assert(result == "K4N2O14S4");
        cout << "Test 3 Passed! K4(ON(SO3)2)2 → " << result << endl;
    }

    // Test Case 4: Single atom
    {
        string formula = "O";
        string result = solver.countOfAtoms(formula);
        assert(result == "O");
        cout << "Test 4 Passed! O → " << result << endl;
    }

    // Test Case 5: Large multiplier
    {
        string formula = "(H)100";
        string result = solver.countOfAtoms(formula);
        assert(result == "H100");
        cout << "Test 5 Passed! (H)100 → " << result << endl;
    }

    // Test Case 6: Multi-character atom names
    {
        string formula = "Fe2O3";
        string result = solver.countOfAtoms(formula);
        assert(result == "Fe2O3");
        cout << "Test 6 Passed! Fe2O3 → " << result << endl;
    }

    // Test Case 7: Deeply nested
    {
        string formula = "((N42))";
        string result = solver.countOfAtoms(formula);
        assert(result == "N42");
        cout << "Test 7 Passed! ((N42)) → " << result << endl;
    }

    // Test Case 8: Concatenated groups
    {
        string formula = "H2O2He3Mg4";
        string result = solver.countOfAtoms(formula);
        assert(result == "H2He3Mg4O2");
        cout << "Test 8 Passed! H2O2He3Mg4 → " << result << endl;
    }

    cout << "\nAll test cases passed successfully!" << endl;
    return 0;
}
#endif
