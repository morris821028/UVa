class Solution {
public:
    vector<string> findRestaurant(vector<string>& list1, vector<string>& list2) {
        unordered_map<string, int> R;
        for (int i = list1.size()-1; i >= 0; i--)
            R[list1[i]] = i;
        
        vector<string> ret;
        int sum = list1.size() + list2.size();
        for (int i = list2.size()-1; i >= 0; i--) {
            unordered_map<string, int>::iterator it = R.find(list2[i]);
            if (it != R.end()) {
                int s = i + it->second;
                if (s < sum)    sum = s, ret.clear();
                if (s == sum)
                    ret.push_back(it->first);
            }
        }
        return ret;
    }
};
