#include <stdio.h>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<string> anagrams(vector<string>& strs) {
        unordered_map<string, int> R;
        for (int i = 0; i < strs.size(); i++) {
            string s = strs[i];
            sort(s.begin(), s.end());
            R[s]++;
        }
        
        vector<string> ret;
        for (int i = 0; i < strs.size(); i++) {
            string s = strs[i];
            sort(s.begin(), s.end());
            if (R[s] > 1)
                ret.push_back(strs[i]);
        }
        return ret;
    }
};

int main() {
    Solution s;
    string A[] = {"tea","and","ate","eat","den"};
    vector<string> v(A, A+5);
    vector<string> ret = s.anagrams(v);
    for (int i = 0; i < ret.size(); i++) {
        cout << ret[i] << endl;
    }
    return 0;
}