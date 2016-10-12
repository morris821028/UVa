class RandomizedSet {
private:
    unordered_map<int, int> R;
    vector<int> V;
public:
    /** Initialize your data structure here. */
    RandomizedSet() {
        
    }
    
    /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
    bool insert(int val) {
        if (R.count(val))
            return false;
        V.push_back(val);
        R[val] = V.size()-1;
        return true;
    }
    
    /** Removes a value from the set. Returns true if the set contained the specified element. */
    bool remove(int val) {
        if (R.count(val) == 0)
            return false;
        int pos = R[val];
        V[pos] = V.back();
        R[V.back()] = pos;
        V.pop_back();
        R.erase(val);
        return true;
    }
    
    /** Get a random element from the set. */
    int getRandom() {
        return V[rand()%V.size()];
    }
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet obj = new RandomizedSet();
 * bool param_1 = obj.insert(val);
 * bool param_2 = obj.remove(val);
 * int param_3 = obj.getRandom();
 */
