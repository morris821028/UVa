class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int n = (int) gas.size();
        
        int sum = 0, mn = 0, st = 0;
        for (int i = 0; i < n; i++) {
            sum += gas[i] - cost[i];
            if (sum < mn) {
                mn = sum;
                st = i+1;
            }
        }
        if (sum < 0)
            return -1;
        else
            return st;
    }
};