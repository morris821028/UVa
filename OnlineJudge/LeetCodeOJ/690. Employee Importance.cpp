/*
// Employee info
class Employee {
public:
    // It's the unique ID of each node.
    // unique id of this employee
    int id;
    // the importance value of this employee
    int importance;
    // the id of direct subordinates
    vector<int> subordinates;
};
*/
class Solution {
public:
    int getImportance(vector<Employee*> employees, int id) {
        unordered_map<int, Employee*> R;
        for (auto e : employees)
            R[e->id] = e;
        return importance(R, id);
    }
    int importance(unordered_map<int, Employee*> &R, int id) {
        if (R.count(id) == 0)
            return 0;
        Employee *ee = R[id];
        int ret = ee->importance;
        for (auto e : ee->subordinates)
            ret += importance(R, e);
        return ret;
    }
};
