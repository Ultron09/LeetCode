/**
 * Problem: 736. Parse Lisp Expression
 * Difficulty: Hard
 * Topics: Stack, Recursion, String, Hash Table
 * LeetCode Link: https://leetcode.com/problems/parse-lisp-expression/
 *
 * Approach: Recursive Descent Parser with Scoped Environment Chain
 *
 * Key Insight:
 *   The Lisp grammar is recursively defined:
 *     Expr  ::= Integer | Variable | '(' Compound ')'
 *     Compound ::= 'let' (Var Expr)* Expr
 *                | 'add' Expr Expr
 *                | 'mult' Expr Expr
 *
 *   Scoping: Each 'let' creates a new scope. Variable lookups walk
 *   from innermost to outermost scope. When 'let' finishes, its scope
 *   is destroyed — classic lexical scoping.
 *
 *   Implementation: We use a vector<unordered_map> as a scope chain.
 *   The recursive evaluate() function advances a shared index `pos`
 *   through the expression string, parsing tokens as needed.
 *
 * Time Complexity:  O(N²) worst-case — N = expression length, each
 *                   variable lookup may traverse the scope chain
 * Space Complexity: O(N) — recursion depth + scope chain storage
 */

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <cassert>

using namespace std;

class Solution {
public:
    int evaluate(string expression) {
        int pos = 0;
        vector<unordered_map<string, int>> scopes;
        return eval(expression, pos, scopes);
    }

private:
    // Parse the next token (word or number, delimited by space, ')', or end)
    string parseToken(const string& expr, int& pos) {
        string token;
        while (pos < static_cast<int>(expr.size()) &&
               expr[pos] != ' ' && expr[pos] != ')') {
            token += expr[pos++];
        }
        return token;
    }

    // Look up a variable in the scope chain (innermost first)
    int lookup(const vector<unordered_map<string, int>>& scopes,
               const string& var) {
        for (int i = static_cast<int>(scopes.size()) - 1; i >= 0; --i) {
            auto it = scopes[i].find(var);
            if (it != scopes[i].end()) {
                return it->second;
            }
        }
        return 0; // Should never reach here for valid expressions
    }

    // Recursive evaluator — advances pos through the expression
    int eval(const string& expr, int& pos,
             vector<unordered_map<string, int>>& scopes) {

        if (expr[pos] == '(') {
            // Compound expression: skip '('
            ++pos;
            string keyword = parseToken(expr, pos);
            ++pos; // skip space after keyword

            int result = 0;

            if (keyword == "let") {
                // Push new scope for this let block
                scopes.push_back({});

                while (true) {
                    // Check if next token is a variable or the final expression
                    // If it starts with '(' or is a digit/negative, it's an expr
                    // If it's a variable followed by a closing ')', it's the tail expr
                    //
                    // Strategy: try to parse a variable name. If what follows
                    // is ')' then this is the final expression.

                    if (expr[pos] == '(' || isdigit(expr[pos]) ||
                        (expr[pos] == '-' && isdigit(expr[pos + 1]))) {
                        // This is the final expression (starts with '(' or number)
                        result = eval(expr, pos, scopes);
                        break;
                    }

                    // Parse variable name
                    string var = parseToken(expr, pos);

                    // If next char is ')', this variable IS the final expression
                    if (expr[pos] == ')') {
                        result = lookup(scopes, var);
                        break;
                    }

                    // Otherwise, skip space and evaluate the binding value
                    ++pos; // skip space
                    int val = eval(expr, pos, scopes);
                    scopes.back()[var] = val;

                    // Skip space before next pair or final expression
                    if (expr[pos] == ' ') ++pos;
                }

                // Pop scope
                scopes.pop_back();

            } else if (keyword == "add") {
                int e1 = eval(expr, pos, scopes);
                ++pos; // skip space
                int e2 = eval(expr, pos, scopes);
                result = e1 + e2;

            } else { // "mult"
                int e1 = eval(expr, pos, scopes);
                ++pos; // skip space
                int e2 = eval(expr, pos, scopes);
                result = e1 * e2;
            }

            ++pos; // skip ')'
            return result;

        } else {
            // Atom: either a number or a variable name
            string token = parseToken(expr, pos);

            // If starts with digit or '-' followed by digit, it's a number
            if (isdigit(token[0]) || (token[0] == '-' && token.size() > 1)) {
                return stoi(token);
            }

            // Otherwise it's a variable — look up in scope chain
            return lookup(scopes, token);
        }
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    // Test Case 1: Nested let with inner variable shadowing
    {
        string expr = "(let x 2 (mult x (let x 3 y 4 (add x y))))";
        int result = solver.evaluate(expr);
        assert(result == 14);
        cout << "Test 1 Passed! → " << result << endl;
    }

    // Test Case 2: Sequential variable reassignment
    {
        string expr = "(let x 3 x 2 x)";
        int result = solver.evaluate(expr);
        assert(result == 2);
        cout << "Test 2 Passed! → " << result << endl;
    }

    // Test Case 3: Variable used in its own reassignment
    {
        string expr = "(let x 1 y 2 x (add x y) (add x y))";
        int result = solver.evaluate(expr);
        assert(result == 5);
        cout << "Test 3 Passed! → " << result << endl;
    }

    // Test Case 4: Simple add
    {
        string expr = "(add 1 2)";
        int result = solver.evaluate(expr);
        assert(result == 3);
        cout << "Test 4 Passed! → " << result << endl;
    }

    // Test Case 5: Simple mult
    {
        string expr = "(mult 3 (add 2 3))";
        int result = solver.evaluate(expr);
        assert(result == 15);
        cout << "Test 5 Passed! → " << result << endl;
    }

    // Test Case 6: Negative numbers
    {
        string expr = "(let x -2 (mult x x))";
        int result = solver.evaluate(expr);
        assert(result == 4);
        cout << "Test 6 Passed! → " << result << endl;
    }

    // Test Case 7: Bare integer
    {
        string expr = "42";
        int result = solver.evaluate(expr);
        assert(result == 42);
        cout << "Test 7 Passed! → " << result << endl;
    }

    // Test Case 8: Scope isolation — inner let doesn't leak
    {
        string expr = "(let x 7 (let x 3 x) x)";
        // Inner let: x=3, returns 3. But final x is evaluated in outer scope where x=7... wait
        // Actually: (let x 7 <expr1> <expr2>)
        // This is: let x=7, then let bindings for (let x 3 x) and then x
        // Hmm, actually this has pairs: x=7, then (let x 3 x) is assigned to... no.
        // (let x 7 (let x 3 x) x) — this has one pair (x, 7), then the body needs to be parsed:
        // After x=7, next token is "(let x 3 x)" which starts with '(' so it's the final expression.
        // Wait, but then there's another x after that... Let me re-read.
        // Actually (let v1 e1 expr): x=7, then "(let x 3 x)" is the tail expression? But then there's "x" after.
        // Oh wait, the let form is (let v1 e1 v2 e2 ... expr). So we'd need pairs.
        // Actually I think the parser handles this: after x=7, next is "(let x 3 x)" which is an expression
        // (starts with '('). But then we need to check if it's the final expression or a binding value.
        // Since "(let x 3 x)" starts with '(', it IS the final expression.
        // But then the remaining "x)" would be problematic. Let me just use a different test.
        // Let me skip this edge case and use a cleaner test.
    }

    // Test Case 8 (corrected): Deep nesting
    {
        string expr = "(let a 5 b 10 (add (mult a b) a))";
        // a=5, b=10, body = (add (mult 5 10) 5) = (add 50 5) = 55
        int result = solver.evaluate(expr);
        assert(result == 55);
        cout << "Test 8 Passed! → " << result << endl;
    }

    cout << "\nAll test cases passed successfully!" << endl;
    return 0;
}
#endif
