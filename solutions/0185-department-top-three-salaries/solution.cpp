/**
 * Problem: 185. Department Top Three Salaries
 * Difficulty: Hard
 * Topics: Database, SQL, Arrays & Hashing
 * LeetCode Link: https://leetcode.com/problems/department-top-three-salaries/
 * 
 * Time Complexity:  O(N log N) where N = number of employee records
 * Space Complexity: O(N) auxiliary memory for departmental salary grouping
 */

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <cassert>

using namespace std;

struct Employee {
    int id;
    string name;
    int salary;
    int departmentId;
};

struct Department {
    int id;
    string name;
};

struct HighEarnerRecord {
    string department;
    string employee;
    int salary;

    bool operator==(const HighEarnerRecord& other) const {
        return department == other.department && employee == other.employee && salary == other.salary;
    }
};

class Solution {
public:
    vector<HighEarnerRecord> findHighEarners(const vector<Employee>& employees,
                                            const vector<Department>& departments) {
        unordered_map<int, string> deptNameMap;
        for (const auto& d : departments) {
            deptNameMap[d.id] = d.name;
        }

        // Group employee records by department ID
        unordered_map<int, vector<Employee>> deptEmployees;
        for (const auto& emp : employees) {
            deptEmployees[emp.departmentId].push_back(emp);
        }

        vector<HighEarnerRecord> result;

        for (const auto& [deptId, empList] : deptEmployees) {
            auto it = deptNameMap.find(deptId);
            if (it == deptNameMap.end()) continue;
            const string& deptName = it->second;

            // Extract unique salaries in descending order
            unordered_set<int> uniqueSalarySet;
            for (const auto& emp : empList) {
                uniqueSalarySet.insert(emp.salary);
            }
            vector<int> uniqueSalaries(uniqueSalarySet.begin(), uniqueSalarySet.end());
            sort(uniqueSalaries.rbegin(), uniqueSalaries.rend());

            // Retain top 3 unique salaries
            unordered_set<int> top3Salaries;
            for (size_t i = 0; i < min(size_t(3), uniqueSalaries.size()); ++i) {
                top3Salaries.insert(uniqueSalaries[i]);
            }

            for (const auto& emp : empList) {
                if (top3Salaries.count(emp.salary)) {
                    result.push_back({deptName, emp.name, emp.salary});
                }
            }
        }

        return result;
    }
};

// ==========================================
// Local Test Runner (Guarded for LeetCode Submission)
// ==========================================
#ifdef LOCAL_TEST
int main() {
    Solution solver;

    vector<Employee> employees = {
        {1, "Joe", 85000, 1},
        {2, "Henry", 80000, 2},
        {3, "Sam", 60000, 2},
        {4, "Max", 90000, 1},
        {5, "Janet", 69000, 1},
        {6, "Randy", 85000, 1},
        {7, "Will", 70000, 1}
    };

    vector<Department> departments = {
        {1, "IT"},
        {2, "Sales"}
    };

    auto results = solver.findHighEarners(employees, departments);
    assert(results.size() == 6);
    cout << "Test 1 Passed: 6 high earners correctly extracted!" << endl;

    cout << "All test cases passed successfully!" << endl;
    return 0;
}
#endif
