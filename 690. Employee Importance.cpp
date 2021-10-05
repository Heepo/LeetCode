#include <vector>
#include <unordered_map>
using namespace std;

// Definition for Employee.
class Employee {
public:
    int id;
    int importance;
    vector<int> subordinates;
};

// T: O(n)
// S: O(n)
class Solution {
public:
    int getImportance(vector<Employee*> employees, int id) {
        if (employees.empty()) return 0;
        
        unordered_map<int, Employee*> employee_id_m;
        for (auto employee: employees) employee_id_m[employee->id] = employee;
        
        return dfs_(employee_id_m, id);
    }
    
private:
    int dfs_(unordered_map<int, Employee*>& employee_id_m, int id) {
        int sum = employee_id_m[id]->importance;
        
        for (auto subordinate: employee_id_m[id]->subordinates)
            sum += dfs_(employee_id_m, subordinate);
        
        return sum;
    }
};